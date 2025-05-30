#pragma once
#include "Scene/Model/Scene.h"
#include <pch.h>

namespace Barta::QtComponents::Form {
class FormInterface {
public:
    virtual ~FormInterface() = default;

    virtual int tagStackSizeRequirement() const noexcept = 0;

    virtual void submit(QVBoxLayout* layout, Scene::Model::Scene& model, const std::vector<std::string>& tagStack) = 0;
};
}
