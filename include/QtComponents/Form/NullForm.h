#pragma once
#include "FormInterface.h"
#include <pch.h>

namespace Barta::QtComponents::Form {
class NullForm: public virtual FormInterface {
public:
    NullForm(
        int hashStackSize
    ) noexcept:
        hashStackSize(hashStackSize) {}

    int hashStackSizeRequirement() const noexcept override { return this->hashStackSize; }

    void bind(
        QVBoxLayout* layout,
        Scene::Model::Scene& model,
        std::vector<std::string>& hashStack
    ) override {}

    std::vector<std::string> getHashList(Scene::Model::Scene& model, std::vector<std::string>& hashStack) const override { return {}; }

private:
    int hashStackSize;
};
}
