#include <../../../../include/QtComponents/Form/Camera/EyeForm.h>
#include "QtComponents/DialogRepository.h"

namespace Barta::QtComponents::Form::Camera {
void EyeForm::bind(
    QVBoxLayout* layout,
    Scene::Model::Scene& model,
    std::vector<std::string>& hashStack
) {
    for (auto input : DialogRepository().getVectorInputs(model.camera.eye)) {
        layout->addWidget(input);
    }
}
}
