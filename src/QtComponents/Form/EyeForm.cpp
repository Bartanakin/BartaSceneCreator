#include <QtComponents/Form/EyeForm.h>

#include "QtComponents/DialogRepository.h"

namespace Barta::QtComponents::Form {
void EyeForm::submit(
    QVBoxLayout* layout,
    Scene::Model::Scene& model,
    const std::vector<std::string>& tagStack
) {
    auto rep = DialogRepository();
    layout->addWidget(
        DialogRepository().getFloatingPointInput("x", model.camera.eye.x)
        );
    layout->addWidget(
        DialogRepository().getFloatingPointInput("y", model.camera.eye.y)
        );
    layout->addWidget(
        DialogRepository().getFloatingPointInput("z", model.camera.eye.z)
    );
}
}
