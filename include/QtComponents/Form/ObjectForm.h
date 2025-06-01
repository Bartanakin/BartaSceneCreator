#pragma once
#include <pch.h>

#include "FormInterface.h"

namespace Barta::QtComponents::Form {
class ObjectForm : public virtual FormInterface {
public:
    int hashStackSizeRequirement() const noexcept override { return 1; }

    void bind(QVBoxLayout* layout, Scene::Model::Scene& model, std::vector<std::string>& hashStack) override;

    std::vector<std::string> getHashList(Scene::Model::Scene& model, std::vector<std::string>& hashStack) const override;
};
}
