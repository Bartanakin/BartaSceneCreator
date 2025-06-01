#include "./ui_bartascenecreator.h"
#include "Bartascenecreator.h"
#include "QtComponents/DialogRepository.h"
#include "QtComponents/Form/Camera/CenterForm.h"
#include "QtComponents/Form/Camera/UpForm.h"
#include "QtComponents/Form/NullForm.h"
#include "QtComponents/Form/Object/Hitbox/CenterForm.h"
#include "QtComponents/Form/Object/HitboxForm.h"
#include "QtComponents/Form/Object/MassCenterForm.h"
#include "QtComponents/Form/Object/RotationForm.h"
#include "QtComponents/Form/Object/VelocityForm.h"
#include "QtComponents/Form/ObjectForm.h"
#include "QtComponents/PageEnum.h"
#include "QtComponents/Form/Object/SpriteForm.h"
#include "QtComponents/Form/Object/TransformationForm.h"
#include "QtComponents/Form/Object/Sprite/CenterForm.h"
#include "QtComponents/Form/Object/Sprite/ColorForm.h"
#include "QtComponents/Form/Object/Sprite/OriginForm.h"
#include "QtComponents/Form/Object/Sprite/SizeForm.h"
#include "QtComponents/Form/Object/Sprite/Vertex1Form.h"
#include "QtComponents/Form/Object/Sprite/Vertex2Form.h"
#include "QtComponents/Form/Object/Sprite/Vertex3Form.h"
#include "include/CustomWidgets/JsonStackElement.h"
#include "include/QtComponents/Form/Camera/EyeForm.h"

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

    this->sceneElement = std::make_unique<JsonStackElement>(std::make_unique<NullForm>(0), "scene.png", "Scene");

    auto objectsElement = std::make_unique<JsonStackElement>(std::make_unique<ObjectForm>(), "objects.png", "Objects", true);

    {
        auto massCenterElement = std::make_unique<JsonStackElement>(std::make_unique<Object::MassCenterForm>(), "mass-center.png", "Mass center");
        objectsElement->addChild(std::move(massCenterElement));
        auto velocityElement = std::make_unique<JsonStackElement>(std::make_unique<Object::VelocityForm>(), "speed.png", "Velocity");
        objectsElement->addChild(std::move(velocityElement));
        auto rotationElement = std::make_unique<JsonStackElement>(std::make_unique<Object::RotationForm>(), "rotation.png", "Rotation");
        objectsElement->addChild(std::move(rotationElement));
        auto transformationElement = std::make_unique<JsonStackElement>(std::make_unique<Object::TransformationForm>(), "transformation.png", "Transformation");
        objectsElement->addChild(std::move(transformationElement));

        {
            {
                auto centerElement = std::make_unique<JsonStackElement>(std::make_unique<Object::Sprite::CenterForm>(), "center.png", "Center");
                auto originElement = std::make_unique<JsonStackElement>(std::make_unique<Object::Sprite::OriginForm>(), "center.png", "Origin");
                auto sizeElement = std::make_unique<JsonStackElement>(std::make_unique<Object::Sprite::SizeForm>(), "size.png", "Size");
                auto vertex1Element = std::make_unique<JsonStackElement>(std::make_unique<Object::Sprite::Vertex1Form>(), "vertex.png", "Vertex1");
                auto vertex2Element = std::make_unique<JsonStackElement>(std::make_unique<Object::Sprite::Vertex2Form>(), "vertex.png", "Vertex2");
                auto vertex3Element = std::make_unique<JsonStackElement>(std::make_unique<Object::Sprite::Vertex3Form>(), "vertex.png", "Vertex3");
                auto colorElement = std::make_unique<JsonStackElement>(std::make_unique<Object::Sprite::ColorForm>(), "color.png", "Color");

                auto spritesElement = std::make_unique<JsonStackElement>(std::make_unique<Object::SpriteForm>(
                    std::vector{centerElement.get()},
                    std::vector{originElement.get(), sizeElement.get()},
                    std::vector{vertex1Element.get(), vertex2Element.get(), vertex3Element.get()}
                ), "sprite.png", "Sprites", true);

                spritesElement->addChild(std::move(centerElement));
                spritesElement->addChild(std::move(originElement));
                spritesElement->addChild(std::move(sizeElement));
                spritesElement->addChild(std::move(vertex1Element));
                spritesElement->addChild(std::move(vertex2Element));
                spritesElement->addChild(std::move(vertex3Element));
                spritesElement->addChild(std::move(colorElement));

                objectsElement->addChild(std::move(spritesElement));
            }

            auto hitboxCenterElement = std::make_unique<JsonStackElement>(std::make_unique<Object::Hitbox::CenterForm>(), "center.png", "Center");

            auto hitboxElement =
                std::make_unique<JsonStackElement>(std::make_unique<Object::HitboxForm>(std::vector{hitboxCenterElement.get()}), "hitbox.png", "Hitbox");
            hitboxElement->addChild(std::move(hitboxCenterElement));

            objectsElement->addChild(std::move(hitboxElement));
        }
    }

    this->sceneElement->addChild(std::move(objectsElement));

    auto cameraElement = std::make_unique<JsonStackElement>(std::make_unique<NullForm>(0), "camera-movie.png", "Camera");
    {
        auto eyeElement = std::make_unique<JsonStackElement>(std::make_unique<Camera::EyeForm>(), "eye.png", "Eye");
        cameraElement->addChild(std::move(eyeElement));

        auto centerElement = std::make_unique<JsonStackElement>(std::make_unique<Camera::CenterForm>(), "center.png", "Center");
        cameraElement->addChild(std::move(centerElement));

        auto upElement = std::make_unique<JsonStackElement>(std::make_unique<Camera::UpForm>(), "up.png", "Up");
        cameraElement->addChild(std::move(upElement));
    }

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
            widget->setParent(nullptr);
        }

        delete item;
    }

    for (const auto& element: middleElements) {
        element->setState(JsonStackElement::State::MIDDLE);
        connect(element.get(), &QToolButton::clicked, this, [&]() {
            if (element->getState() != JsonStackElement::State::MIDDLE) {
                return;
            }

            if (element->isList()) {
                this->openObjectList(element.get());
            } else {
                this->addElementOnStack(element.get());
            }
        });

        middleLayout->addWidget(element.get(), 0, Qt::AlignHCenter | Qt::AlignTop);
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
    layout->insertWidget(0, element, 0, Qt::AlignHCenter | Qt::AlignBottom);
    element->setState(JsonStackElement::State::LEFT);
    connect(element, &QToolButton::clicked, this, [&, element, elementCount = this->elementStack.size()]() {
        if (element->getState() != JsonStackElement::State::LEFT) {
            return;
        }

        auto layout = ui->json_stack->widget()->layout();
        for (int i = 0; i < this->elementStack.size() - elementCount; i++) {
            QLayoutItem* item = layout->takeAt(0);
            if (item == nullptr) {
                break;
            }

            if (QWidget* widget = item->widget()) {
                layout->removeWidget(widget);
                widget->setParent(nullptr);
            }

            delete item;
        }

        for (int i = this->elementStack.size() - 1; i >= elementCount; i--) {
            if (this->elementStack[i]->isList()) {
                qDebug() << "popped";
                this->hashStack.pop_back();
            }
        }

        auto originalBack = this->elementStack.back();
        this->elementStack.erase(this->elementStack.begin() + elementCount, this->elementStack.end());

        if (element->isList() && element == originalBack) {
            if (!this->isListOpen) {
                this->openObjectList(element);
                qDebug() << "popped 2";
                this->elementStack.pop_back();
                this->hashStack.pop_back();

                QLayoutItem* item = layout->takeAt(0);
                if (item == nullptr) {
                    throw std::runtime_error("wanted to remove nonexisting element");
                }

                if (QWidget* widget = item->widget()) {
                    layout->removeWidget(widget);
                    widget->setParent(nullptr);
                }
            }
        } else {
            this->openForm(this->elementStack[this->elementStack.size() - 1]);
        }

        ui->json_stack->widget()->setMaximumHeight(this->elementStack.size() * (100 + 10));
        this->refreshMiddleColumn();
    });

    this->refreshMiddleColumn();
}

void BartaSceneCreator::openObjectList(
    Barta::QtComponents::StackElement::JsonStackElement* element
) {
    if (this->ui->selected_element_data->widget() != nullptr) {
        delete this->ui->selected_element_data->takeWidget();
    }

    this->isListOpen = true;
    QWidget* contentWidget = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(contentWidget);
    layout->setSpacing(5);
    layout->setContentsMargins(5, 5, 5, 5);
    layout->setAlignment(Qt::AlignTop);

    this->ui->selected_element_data->setWidget(contentWidget);
    this->ui->selected_element_data->setWidgetResizable(true);

    for (const auto& listTag: element->getForm()->getHashList(this->sceneDocument->getModel(), this->hashStack)) {
        auto choice = new QToolButton();
        choice->setText(listTag.c_str());
        choice->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        layout->addWidget(choice);

        connect(choice, &QToolButton::clicked, this, [=]() {
            this->hashStack.push_back(listTag);
            qDebug() << "pushed";

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
        auto now = std::chrono::system_clock::now();
        auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
        this->hashStack.push_back(std::to_string(millis));
        qDebug() << "pushed new";

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

    this->isListOpen = false;
    QWidget* contentWidget = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(contentWidget);
    layout->setSpacing(5);
    layout->setContentsMargins(5, 5, 5, 5);
    layout->setAlignment(Qt::AlignTop);

    this->ui->selected_element_data->setWidget(contentWidget);
    this->ui->selected_element_data->setWidgetResizable(true);

    if (element->getForm()->hashStackSizeRequirement() != this->hashStack.size()) {
        qDebug() << this->hashStack.size() << " " << element->getForm()->hashStackSizeRequirement();
        throw std::invalid_argument("Invalid hash stack size");
    }

    element->getForm()->bind(layout, this->sceneDocument->getModel(), this->hashStack);
}

void BartaSceneCreator::on_save_button_clicked()
{
    if (this->sceneDocument->saveToFile()) {
        QPalette palette = this->ui->save_status_label->palette();
        palette.setColor(QPalette::WindowText, Qt::green);
        this->ui->save_status_label->setPalette(palette);
        this->ui->save_status_label->setText(("Successfully saved to " + this->sceneDocument->getPath()).c_str());
        QTimer::singleShot(3000, this->ui->save_status_label, [this]() {
            this->ui->save_status_label->setText("");
        });
    } else {
        this->ui->save_status_label->setText("Saving unsuccessful.");
        QPalette palette = this->ui->save_status_label->palette();
        palette.setColor(QPalette::WindowText, Qt::red);
        this->ui->save_status_label->setPalette(palette);
        QTimer::singleShot(3000, this->ui->save_status_label, [this]() {
            this->ui->save_status_label->setText("");
        });
    }
}


void BartaSceneCreator::on_edit_scene_button_clicked()
{
    // TODO error message handling
    // clang-format off
    QString filePath = QFileDialog::getOpenFileName(
        this,
        tr("Select a json file"),
        ".."
    );
    // clang-format on

    this->sceneDocument = std::make_unique<Barta::Scene::SceneDocument>(std::filesystem::path(filePath.toStdString()));

    this->loadPage2();
}

