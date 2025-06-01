#include <QtComponents/Form/Object/SpriteForm.h>

#include "CustomWidgets/HashInputWidget.h"
#include "CustomWidgets/SelectWidget.h"

namespace Barta::QtComponents::Form::Object {
using Sprite = Barta::Scene::Model::Sprite;

SpriteForm::SpriteForm(
    std::vector<StackElement::JsonStackElement*> ballElements,
    std::vector<StackElement::JsonStackElement*> rectangleElements,
    std::vector<StackElement::JsonStackElement*> triangleElements
) noexcept:
    ballElements(std::move(ballElements)),
    rectangleElements(std::move(rectangleElements)),
    triangleElements(std::move(triangleElements)) {}

void SpriteForm::bind(
    QVBoxLayout* layout,
    Scene::Model::Scene& model,
    std::vector<std::string>& hashStack
) {
    for (auto element: std::views::join(
             std::array{std::views::all(this->ballElements), std::views::all(this->rectangleElements), std::views::all(this->triangleElements)}
         )) {
        element->setDisabled(true);
    }

    auto& ref = model.objects.findOrCreateByHash(hashStack[0]).sprites.findOrCreateByHash(hashStack[1]);

    layout->addWidget(new CustomWidgets::HashInputWidget(
        this->getHashList(model, hashStack),
        ref.hash,
        hashStack
    ));

    auto selectType = new CustomWidgets::SelectWidget(
        "Sprite type",
        {
            {Sprite::getTypeName(Sprite::Type::RECTANGLE), "RECTANGLE"},
            {Sprite::getTypeName(Sprite::Type::BALL),      "BALL"     },
            {Sprite::getTypeName(Sprite::Type::TRIANGLE),  "TRIANGLE" },
            {Sprite::getTypeName(Sprite::Type::CIRCLE),    "CIRCLE"   }
    },
        ref.type
    );

    QObject::connect(selectType, &CustomWidgets::SelectWidget::onChange, [layout, &model, &hashStack, this]() {
        while (QLayoutItem* item = layout->takeAt(0)) {
            if (QWidget* widget = item->widget()) {
                widget->hide();
                widget->deleteLater();
            }

            delete item;
        }

        this->bind(layout, model, hashStack);
    });
    layout->addWidget(selectType);

    if (ref.type == Sprite::getTypeName(Sprite::Type::CIRCLE) || ref.type == Sprite::getTypeName(Sprite::Type::BALL)) {
        for (auto element : this->ballElements) {
            element->setDisabled(false);
        }
    }

    if (ref.type == Sprite::getTypeName(Sprite::Type::RECTANGLE)) {
        for (auto element : this->rectangleElements) {
            element->setDisabled(false);
        }
    }

    if (ref.type == Sprite::getTypeName(Sprite::Type::TRIANGLE)) {
        for (auto element : this->triangleElements) {
            element->setDisabled(false);
        }
    }
}

std::vector<std::string> SpriteForm::getHashList(
    Scene::Model::Scene& model,
    std::vector<std::string>& hashStack
) const {
    return model.objects.findOrCreateByHash(hashStack[0]).sprites.getAllHashes();
}
}
