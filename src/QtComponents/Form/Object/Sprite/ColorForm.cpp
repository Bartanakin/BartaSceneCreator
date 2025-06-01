#include <QtComponents/Form/Object/Sprite/ColorForm.h>

#include "CustomWidgets/ColorInputWidget.h"

namespace Barta::QtComponents::Form::Object::Sprite {
void ColorForm::bind(
    QVBoxLayout* layout,
    Scene::Model::Scene& model,
    std::vector<std::string>& hashStack
) {
    auto& sprite = model.objects.findOrCreateByHash(hashStack[0]).sprites.findOrCreateByHash(hashStack[1]);
    layout->addWidget(new CustomWidgets::ColorInputWidget(sprite.color));
}
}
