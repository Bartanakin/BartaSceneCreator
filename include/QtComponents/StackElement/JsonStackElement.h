#pragma once
#include "QtComponents/Form/FormInterface.h"
#include <pch.h>

namespace Barta::QtComponents::StackElement {
class JsonStackElement {
public:
    JsonStackElement(std::unique_ptr<Form::FormInterface> form, std::string iconName, std::string text) noexcept;
    JsonStackElement(std::unique_ptr<Form::FormInterface> form, std::string iconName, std::string text, std::vector<std::string> listTags) noexcept;

    QToolButton* getButton() const noexcept;

    bool isList() const noexcept;

    std::vector<std::unique_ptr<JsonStackElement>>& getChildren() noexcept;

    std::vector<std::string>& getListTags() noexcept;

    void addChild(std::unique_ptr<JsonStackElement> child) noexcept;

    void addListTag(const std::string& listTag);

    Form::FormInterface* getForm() const noexcept;

private:
    std::string iconName;
    std::string text;
    std::unique_ptr<Form::FormInterface> form;
    bool list;
    std::vector<std::unique_ptr<JsonStackElement>> children;
    std::vector<std::string> listTags;
};
}
