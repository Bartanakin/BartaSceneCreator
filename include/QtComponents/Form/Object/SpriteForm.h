#pragma once
#include "CustomWidgets/JsonStackElement.h"
#include "QtComponents/Form/FormInterface.h"
#include <pch.h>

namespace Barta::QtComponents::Form::Object {
class SpriteForm: public virtual FormInterface {
public:
    SpriteForm(
        std::vector<StackElement::JsonStackElement*> ballElements,
        std::vector<StackElement::JsonStackElement*> rectangleElements,
        std::vector<StackElement::JsonStackElement*> triangleElements
    ) noexcept;

    int hashStackSizeRequirement() const noexcept override { return 2; }

    void bind(QVBoxLayout* layout, Scene::Model::Scene& model, std::vector<std::string>& hashStack) override;

    std::vector<std::string> getHashList(Scene::Model::Scene& model, std::vector<std::string>& hashStack) const override;
private:

    std::vector<StackElement::JsonStackElement*> ballElements;
    std::vector<StackElement::JsonStackElement*> rectangleElements;
    std::vector<StackElement::JsonStackElement*> triangleElements;
};
}
