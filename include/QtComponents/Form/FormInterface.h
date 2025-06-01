#pragma once
#include "Scene/Model/Scene.h"
#include <pch.h>

namespace Barta::QtComponents::Form {
class FormInterface {
public:
    virtual ~FormInterface() = default;

    virtual int hashStackSizeRequirement() const noexcept = 0;

    virtual void bind(QVBoxLayout* layout, Scene::Model::Scene& model, std::vector<std::string>& hashStack) = 0;

    virtual std::vector<std::string> getHashList(Scene::Model::Scene& model, std::vector<std::string>& hashStack) const = 0;
};
}
