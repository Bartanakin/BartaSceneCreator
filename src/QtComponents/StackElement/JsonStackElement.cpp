#include <QtComponents/StackElement/JsonStackElement.h>

namespace Barta::QtComponents::StackElement {
JsonStackElement::JsonStackElement(
    std::string iconName,
    std::string text
) noexcept:
    iconName(iconName),
    text(text),
    list(false) {}

JsonStackElement::JsonStackElement(
    std::string iconName,
    std::string text,
    std::vector<std::string> listTags
) noexcept:
    iconName(iconName),
    text(text),
    list(true),
    listTags(std::move(listTags)) {}

QToolButton* JsonStackElement::getButton() const noexcept {
    auto button = new QToolButton();
    button->setFixedSize(100, 100);
    button->setIcon(QIcon((std::filesystem::path(":") / "Icons" / this->iconName).c_str()));
    button->setIconSize({48, 48});
    button->setText(this->text.c_str());
    button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    return button;
}

bool JsonStackElement::isList() const noexcept {
    return this->list;
}

std::vector<std::unique_ptr<JsonStackElement>>& JsonStackElement::getChildren() noexcept {
    return this->children;
}

std::vector<std::string>& JsonStackElement::getListTags() noexcept {
    return this->listTags;
}

void JsonStackElement::addChild(
    std::unique_ptr<JsonStackElement> child
) noexcept {
    this->children.push_back(std::move(child));
}
}
