#include <QtComponents/Form/Object/TransformationForm.h>

#include "CustomWidgets/MatrixWidget.h"

namespace Barta::QtComponents::Form::Object {
void TransformationForm::bind(
    QVBoxLayout* layout,
    Scene::Model::Scene& model,
    std::vector<std::string>& hashStack
) {
    auto& object = model.objects.findOrCreateByHash(hashStack[0]);
    layout->addWidget(new CustomWidgets::MatrixWidget("Transformation", object.transformation));
}
}
