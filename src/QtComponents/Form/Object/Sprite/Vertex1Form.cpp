#include <QtComponents/Form/Object/Sprite/Vertex1Form.h>

#include "QtComponents/DialogRepository.h"

namespace Barta::QtComponents::Form::Object::Sprite {
void Vertex1Form::bind(
    QVBoxLayout* layout,
    Scene::Model::Scene& model,
    std::vector<std::string>& hashStack
) {
    auto& sprite = model.objects.findOrCreateByHash(hashStack[0]).sprites.findOrCreateByHash(hashStack[1]);
    for (auto input: DialogRepository().getVectorInputs(sprite.vertex1)) {
        layout->addWidget(input);
    }
}
}
