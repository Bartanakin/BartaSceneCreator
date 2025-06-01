#include <QtComponents/Form/Object/RotationForm.h>

#include "CustomWidgets/FloatInputWidget.h"

namespace Barta::QtComponents::Form::Object {
void RotationForm::bind(
    QVBoxLayout* layout,
    Scene::Model::Scene& model,
    std::vector<std::string>& hashStack
) {
    auto& rotation = model.objects.findOrCreateByHash(hashStack[0]).dynamicsData.rotation;
    layout->addWidget(new CustomWidgets::FloatInputWidget("x", rotation.x));
    layout->addWidget(new CustomWidgets::FloatInputWidget("y", rotation.y));
    layout->addWidget(new CustomWidgets::FloatInputWidget("z", rotation.z));
    layout->addWidget(new CustomWidgets::FloatInputWidget("angle", rotation.angle));
}
}
