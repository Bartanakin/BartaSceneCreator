#pragma once
#include <pch.h>

#include "QtComponents/Form/FormInterface.h"

namespace Barta::QtComponents::Form::Camera {
class UpForm : public virtual FormInterface {
public:

    int hashStackSizeRequirement() const noexcept override { return 0; }

    void bind(QVBoxLayout* layout, Scene::Model::Scene& model, std::vector<std::string>& hashStack) override;

    std::vector<std::string> getHashList(Scene::Model::Scene& model, std::vector<std::string>& hashStack) const override { return {}; }
};
}
