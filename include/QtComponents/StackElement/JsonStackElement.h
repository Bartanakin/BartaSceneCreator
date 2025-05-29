#pragma once
#include <pch.h>

namespace Barta::QtComponents::StackElement {
class JsonStackElement {
public:
    JsonStackElement(std::string iconName, std::string text) noexcept;
    JsonStackElement(std::string iconName, std::string text, std::vector<std::string> listTags) noexcept;

    QToolButton* getButton() const noexcept;

    bool isList() const noexcept;

    std::vector<std::unique_ptr<JsonStackElement>>& getChildren() noexcept;

    std::vector<std::string>& getListTags() noexcept;

    void addChild(std::unique_ptr<JsonStackElement> child) noexcept;

private:
    std::string iconName;
    std::string text;
    bool list;
    std::vector<std::unique_ptr<JsonStackElement>> children;
    std::vector<std::string> listTags;
};
}
