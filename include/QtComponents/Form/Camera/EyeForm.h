#pragma once
#include "../FormInterface.h"
#include <pch.h>

namespace Barta::QtComponents::Form::Camera {
class EyeForm: public virtual FormInterface {
public:

    int hashStackSizeRequirement() const noexcept override { return 0; }

    void bind(QVBoxLayout* layout, Scene::Model::Scene& model, std::vector<std::string>& hashStack) override;

    std::vector<std::string> getHashList(Scene::Model::Scene& model, std::vector<std::string>& hashStack) const override { return {}; }
};
}
