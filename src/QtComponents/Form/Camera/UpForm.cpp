#include <QtComponents/Form/Camera/UpForm.h>

#include "QtComponents/DialogRepository.h"

namespace Barta::QtComponents::Form::Camera {
void UpForm::bind(
    QVBoxLayout* layout,
    Scene::Model::Scene& model,
    std::vector<std::string>& hashStack
) {
    for (auto input : DialogRepository().getVectorInputs(model.camera.up)) {
        layout->addWidget(input);
    }
}
}
