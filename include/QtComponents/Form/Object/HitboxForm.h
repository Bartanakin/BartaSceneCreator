#pragma once
#include <pch.h>

#include "CustomWidgets/JsonStackElement.h"
#include "QtComponents/Form/FormInterface.h"

namespace Barta::QtComponents::Form::Object {
class HitboxForm : public virtual FormInterface {
public:
    HitboxForm(
        std::vector<StackElement::JsonStackElement*> ballButtons
    ) noexcept;

    int hashStackSizeRequirement() const noexcept override { return 1; }

    void bind(QVBoxLayout* layout, Scene::Model::Scene& model, std::vector<std::string>& hashStack) override;

    std::vector<std::string> getHashList(
        Scene::Model::Scene& model,
        std::vector<std::string>& hashStack
    ) const override {
        return {};
    }
private:
    std::vector<StackElement::JsonStackElement*> ballButtons;
};
}
