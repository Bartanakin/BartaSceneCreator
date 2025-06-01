#include <QtComponents/Form/Camera/CenterForm.h>

#include "QtComponents/DialogRepository.h"

namespace Barta::QtComponents::Form::Camera {
void CenterForm::bind(
    QVBoxLayout* layout,
    Scene::Model::Scene& model,
    std::vector<std::string>& hashStack
) {
    for (auto input : DialogRepository().getVectorInputs(model.camera.center)) {
        layout->addWidget(input);
    }
}
}
