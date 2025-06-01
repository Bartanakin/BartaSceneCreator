#include <QtComponents/Form/Object/Sprite/SizeForm.h>
#include "QtComponents/DialogRepository.h"

namespace Barta::QtComponents::Form::Object::Sprite {
void SizeForm::bind(
    QVBoxLayout* layout,
    Scene::Model::Scene& model,
    std::vector<std::string>& hashStack
) {
    auto& sprite = model.objects.findOrCreateByHash(hashStack[0]).sprites.findOrCreateByHash(hashStack[1]);
    for (auto input: DialogRepository().getVectorInputs(sprite.size)) {
        layout->addWidget(input);
    }
}
}
