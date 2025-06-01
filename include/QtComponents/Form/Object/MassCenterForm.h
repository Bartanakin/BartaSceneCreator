#pragma once
#include "QtComponents/Form/FormInterface.h"
#include <pch.h>

namespace Barta::QtComponents::Form::Object {
class MassCenterForm: public virtual FormInterface {
public:
    int hashStackSizeRequirement() const noexcept override { return 1; }

    void bind(QVBoxLayout* layout, Scene::Model::Scene& model, std::vector<std::string>& hashStack) override;

    std::vector<std::string> getHashList(
        Scene::Model::Scene& model,
        std::vector<std::string>& hashStack
    ) const override {
        return {};
    }
};
}
