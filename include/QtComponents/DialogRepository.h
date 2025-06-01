#pragma once
#include <pch.h>

#include "Scene/Model/Vector3.h"

namespace Barta::QtComponents {
class DialogRepository {
public:
    DialogRepository(QWidget* parent = nullptr) noexcept;

    QString askForSceneNameDialog();

    std::array<QWidget*, 3> getVectorInputs(Scene::Model::Vector3& target);

private:
    QWidget* parent;
};

}
