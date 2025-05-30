#include "./ui_bartascenecreator.h"
#include "Bartascenecreator.h"
#include "QtComponents/DialogRepository.h"
#include "QtComponents/Form/EyeForm.h"
#include "QtComponents/Form/NullForm.h"
#include "QtComponents/PageEnum.h"
#include "QtComponents/StackElement/JsonStackElement.h"

using JsonStackElement = Barta::QtComponents::StackElement::JsonStackElement;
using namespace Barta::QtComponents::Form;

BartaSceneCreator::BartaSceneCreator(
    QWidget* parent
):
    QMainWindow(parent),
    ui(new Ui::BartaSceneCreator) {
    ui->setupUi(this);
}

BartaSceneCreator::~BartaSceneCreator() {
    delete ui;
}

void BartaSceneCreator::on_add_scene_button_clicked() {
    // TODO error message handling
    // clang-format off
    QString dir = QFileDialog::getExistingDirectory(
        this,
        tr("Select a directory"),
        "",
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
    );
    // clang-format on

    if (dir.isEmpty()) {
        return;
    }

    auto dialogRepository = Barta::QtComponents::DialogRepository(this);
    QString fileName = dialogRepository.askForSceneNameDialog();

    if (fileName.isEmpty()) {
        return;
    }

    this->sceneDocument = std::make_unique<Barta::Scene::SceneDocument>(std::filesystem::path(dir.toStdString()), fileName.toStdString());

    this->loadPage2();
}

void BartaSceneCreator::loadPage2() {
    ui->stackedWidget->setCurrentIndex(static_cast<int>(Barta::QtComponents::PageEnum::SCENE_COMPONENTS));
    ui->centralwidget->setMaximumSize(1200, 900);

    // auto emptyTags = std::vector<std::string>();

    this->sceneElement = std::make_unique<JsonStackElement>(std::make_unique<NullForm>(0), "scene.png", "Scene");

    auto cameraElement = std::make_unique<JsonStackElement>(std::make_unique<NullForm>(0), "camera-movie.png", "Camera");

    auto objectsElement = std::make_unique<JsonStackElement>(std::make_unique<NullForm>(0), "objects.png", "Objects", std::vector<std::string>());
    this->sceneElement->addChild(std::move(objectsElement));

    auto eyeElement = std::make_unique<JsonStackElement>(std::make_unique<EyeForm>(), "eye.png", "Eye");
    cameraElement->addChild(std::move(eyeElement));

    auto centerElement = std::make_unique<JsonStackElement>(std::make_unique<NullForm>(0), "center.png", "Center");
    cameraElement->addChild(std::move(centerElement));

    auto upElement = std::make_unique<JsonStackElement>(std::make_unique<NullForm>(0), "up.png", "Up");
    cameraElement->addChild(std::move(upElement));

    this->sceneElement->addChild(std::move(cameraElement));

    // left column
    QWidget* leftColumns = ui->json_stack->widget();
    QVBoxLayout* layout = new QVBoxLayout(leftColumns);
    layout->setSpacing(10);
    layout->setContentsMargins(0, 0, 0, 5);
    leftColumns->setLayout(layout);

    // middle column
    QWidget* middleColumns = ui->selected_element_children->widget();
    QVBoxLayout* middleLayout = new QVBoxLayout(middleColumns);
    middleLayout->setSpacing(10);
    middleLayout->setContentsMargins(0, 5, 0, 0);
    middleColumns->setLayout(middleLayout);

    this->addElementOnStack(this->sceneElement.get());
}

void BartaSceneCreator::refreshMiddleColumn() {
    // middle column
    auto& middleElements = this->elementStack[this->elementStack.size() - 1]->getChildren();
    auto middleLayout = dynamic_cast<QVBoxLayout*>(ui->selected_element_children->widget()->layout());
    ui->selected_element_children->widget()->setMaximumHeight(middleElements.size() * (100 + 10));
    QLayoutItem* item;
    while ((item = middleLayout->takeAt(0)) != nullptr) {
        if (QWidget* widget = item->widget()) {
            middleLayout->removeWidget(widget);
            widget->deleteLater();
        }

        delete item;
    }

    for (const auto& element: middleElements) {
        auto button = element->getButton();
        connect(button, &QToolButton::clicked, this, [&]() {
            if (element->isList()) {
                this->openObjectList(element.get());
            } else {
                this->addElementOnStack(element.get());
            }
        });

        middleLayout->addWidget(button, 0, Qt::AlignHCenter | Qt::AlignTop);
    }
}

void BartaSceneCreator::addElementOnStack(
    JsonStackElement* element
) {
    this->elementStack.push_back(element);
    this->openForm(element);

    // left column
    auto layout = dynamic_cast<QVBoxLayout*>(ui->json_stack->widget()->layout());
    ui->json_stack->widget()->setMaximumHeight(this->elementStack.size() * (100 + 10));
    auto button = element->getButton();
    layout->insertWidget(0, button, 0, Qt::AlignHCenter | Qt::AlignBottom);
    connect(button, &QToolButton::clicked, this, [&, elementCount = this->elementStack.size()]() {
        auto layout = ui->json_stack->widget()->layout();
        for (int i = 0; i < this->elementStack.size() - elementCount; i++) {
            QLayoutItem* item = layout->takeAt(0);
            if (item == nullptr) {
                break;
            }

            if (QWidget* widget = item->widget()) {
                layout->removeWidget(widget);
                widget->deleteLater();
            }

            delete item;
        }

        for (int i = this->elementStack.size() - 1; i >= elementCount; i--) {
            if (this->elementStack[i]->isList()) {
                this->tagStack.pop_back();
            }
        }

        this->elementStack.erase(this->elementStack.begin() + elementCount, this->elementStack.end());
        ui->json_stack->widget()->setMaximumHeight(this->elementStack.size() * (100 + 10));

        this->refreshMiddleColumn();
        this->openForm(this->elementStack[this->elementStack.size() - 1]);
    });

    this->refreshMiddleColumn();
}

void BartaSceneCreator::openObjectList(
    Barta::QtComponents::StackElement::JsonStackElement* element
) {
    if (this->ui->selected_element_data->widget() != nullptr) {
        delete this->ui->selected_element_data->takeWidget();
    }

    QWidget* contentWidget = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(contentWidget);
    layout->setSpacing(5);
    layout->setContentsMargins(5, 5, 5, 5);
    layout->setAlignment(Qt::AlignTop);

    this->ui->selected_element_data->setWidget(contentWidget);
    this->ui->selected_element_data->setWidgetResizable(true);

    for (const auto& listTag: element->getListTags()) {
        auto choice = new QToolButton();
        choice->setText(listTag.c_str());
        choice->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        layout->addWidget(choice);

        connect(choice, &QToolButton::clicked, this, [=]() {
            this->tagStack.push_back(listTag);

            this->addElementOnStack(element);
            this->refreshMiddleColumn();
        });
    }

    auto choice = new QToolButton();
    choice->setText("Add new object");
    choice->setIcon(QIcon(std::filesystem::path(":/Icons/plus.png").c_str()));
    choice->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    choice->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    layout->addWidget(choice);
    connect(choice, &QToolButton::clicked, this, [=]() {
        this->tagStack.push_back("New object");
        element->addListTag("New object");

        this->addElementOnStack(element);
        this->refreshMiddleColumn();
    });
}

void BartaSceneCreator::openForm(
    Barta::QtComponents::StackElement::JsonStackElement* element
) {
    if (this->ui->selected_element_data->widget() != nullptr) {
        delete this->ui->selected_element_data->takeWidget();
    }

    QWidget* contentWidget = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(contentWidget);
    layout->setSpacing(5);
    layout->setContentsMargins(5, 5, 5, 5);
    layout->setAlignment(Qt::AlignTop);

    this->ui->selected_element_data->setWidget(contentWidget);
    this->ui->selected_element_data->setWidgetResizable(true);

    element->getForm()->submit(layout, this->sceneDocument->getModel(), this->tagStack);
}
