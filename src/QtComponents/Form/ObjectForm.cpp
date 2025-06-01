#include <QtComponents/Form/ObjectForm.h>

#include "CustomWidgets/FloatInputWidget.h"
#include "CustomWidgets/HashInputWidget.h"
#include "CustomWidgets/IntegerInputWidget.h"
#include "CustomWidgets/SelectWidget.h"
#include "CustomWidgets/TextInputWidget.h"

namespace Barta::QtComponents::Form {
void ObjectForm::bind(
    QVBoxLayout* layout,
    Scene::Model::Scene& model,
    std::vector<std::string>& hashStack
) {
    auto& object = model.objects.findOrCreateByHash(hashStack[0]);
    layout->addWidget(new CustomWidgets::HashInputWidget(model.objects.getAllHashes(), object.hash, hashStack));
    layout->addWidget(new CustomWidgets::IntegerInputWidget("Z index", object.z_index));
    auto selectType = new CustomWidgets::SelectWidget(
        "Object type",
        {
            {Scene::Model::Object::getTypeName(Scene::Model::Object::Type::BARTA_RIGID_OBJECT), "polygon"       },
            {Scene::Model::Object::getTypeName(Scene::Model::Object::Type::BARTA_SOFT_OBJECT),  "meshed-polygon"},
    },
        object.type
    );

    layout->addWidget(selectType);
    QObject::connect(selectType, &CustomWidgets::SelectWidget::onChange, [layout, &model, &hashStack, this]() {
        while (QLayoutItem* item = layout->takeAt(0)) {
            if (QWidget* widget = item->widget()) {
                widget->hide();
                widget->deleteLater();
            }

            delete item;
        }

        this->bind(layout, model, hashStack);
    });

    if (object.type == Scene::Model::Object::getTypeName(Scene::Model::Object::Type::BARTA_SOFT_OBJECT)) {
        layout->addWidget(new CustomWidgets::SelectWidget(
            "Mesh type",
            {
                {Scene::Model::Object::getMeshTypeName(Scene::Model::Object::MeshType::MSH), "meshed-polygon"},
        },
            object.meshType
        ));
        layout->addWidget(new CustomWidgets::TextInputWidget("Source file name", object.sourceFileName));
    }

    layout->addWidget(new CustomWidgets::FloatInputWidget("Inverse of mass", object.dynamicsData.inverseMass));
}

std::vector<std::string> ObjectForm::getHashList(
    Scene::Model::Scene& model,
    std::vector<std::string>& hashStack
) const {
    return model.objects.getAllHashes();
}
}
