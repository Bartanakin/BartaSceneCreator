#pragma once
#include <pch.h>

#include "QtComponents/Form/FormInterface.h"

namespace Barta::QtComponents::Form::Object::Sprite {
class SizeForm: public virtual FormInterface {
public:
    int hashStackSizeRequirement() const noexcept override { return 2; }

    void bind(QVBoxLayout* layout, Scene::Model::Scene& model, std::vector<std::string>& hashStack) override;

    std::vector<std::string> getHashList(
        Scene::Model::Scene& model,
        std::vector<std::string>& hashStack
    ) const override {
        return {};
    }
};
}
