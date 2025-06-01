#include <QtComponents/Form/Object/MassCenterForm.h>

#include "QtComponents/DialogRepository.h"

namespace Barta::QtComponents::Form::Object {
void MassCenterForm::bind(
    QVBoxLayout* layout,
    Scene::Model::Scene& model,
    std::vector<std::string>& hashStack
) {
    auto& object = model.objects.findOrCreateByHash(hashStack[0]);
    for (auto input : DialogRepository().getVectorInputs(object.dynamicsData.massCenter)) {
        layout->addWidget(input);
    }
}
}
