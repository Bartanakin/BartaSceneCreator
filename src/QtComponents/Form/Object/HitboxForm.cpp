#include <QtComponents/Form/Object/HitboxForm.h>
#include "CustomWidgets/FloatInputWidget.h"
#include "CustomWidgets/SelectWidget.h"

namespace Barta::QtComponents::Form::Object {
HitboxForm::HitboxForm(
    std::vector<StackElement::JsonStackElement*> ballButtons
) noexcept:
    ballButtons(std::move(ballButtons)) {}

void HitboxForm::bind(
    QVBoxLayout* layout,
    Scene::Model::Scene& model,
    std::vector<std::string>& hashStack
) {
    for (auto ballButton : this->ballButtons) {
        ballButton->setDisabled(true);
    }

    auto& hitbox = model.objects.findOrCreateByHash(hashStack[0]).hitbox;
    auto selectType = new CustomWidgets::SelectWidget(
        "Object type",
        {
            {Scene::Model::Hitbox::getTypeString(Scene::Model::Hitbox::Type::NULL_TYPE), ""              },
            {Scene::Model::Hitbox::getTypeString(Scene::Model::Hitbox::Type::BALL),      "meshed-polygon"},
    },
        hitbox.type
    );

    layout->addWidget(selectType);
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

    if (hitbox.type == Scene::Model::Hitbox::getTypeString(Scene::Model::Hitbox::Type::BALL)) {
        layout->addWidget(new CustomWidgets::FloatInputWidget("Ball radius", hitbox.radius));
        for (auto ballButton : this->ballButtons) {
            ballButton->setDisabled(false);
        }
    }
}
}
