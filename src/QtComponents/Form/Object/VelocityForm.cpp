#include <QtComponents/Form/Object/VelocityForm.h>

#include "QtComponents/DialogRepository.h"

namespace Barta::QtComponents::Form::Object {
void VelocityForm::bind(
    QVBoxLayout* layout,
    Scene::Model::Scene& model,
    std::vector<std::string>& hashStack
) {
    auto& object = model.objects.findOrCreateByHash(hashStack[0]);
    for (auto input : DialogRepository().getVectorInputs(object.dynamicsData.velocity)) {
        layout->addWidget(input);
    }
}
}
