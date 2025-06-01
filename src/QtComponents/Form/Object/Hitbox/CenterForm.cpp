#include <QtComponents/Form/Object/Hitbox/CenterForm.h>

#include "QtComponents/DialogRepository.h"

namespace Barta::QtComponents::Form::Object::Hitbox {
void CenterForm::bind(
    QVBoxLayout* layout,
    Scene::Model::Scene& model,
    std::vector<std::string>& hashStack
) {
    auto& hitbox = model.objects.findOrCreateByHash(hashStack[0]).hitbox;
    for (auto input : DialogRepository().getVectorInputs(hitbox.center)) {
        layout->addWidget(input);
    }
}
}
