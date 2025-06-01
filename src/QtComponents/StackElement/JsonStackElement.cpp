#include <CustomWidgets/JsonStackElement.h>

namespace Barta::QtComponents::StackElement {
JsonStackElement::JsonStackElement(
    std::unique_ptr<Form::FormInterface> form,
    std::string iconName,
    std::string text,
    bool list,
    QWidget* parent
) noexcept:
    QToolButton(parent),
    state(State::MIDDLE),
    form(std::move(form)),
    iconName(iconName),
    text(text),
    list(list) {
    this->setFixedSize(100, 100);
    this->setIcon(QIcon(std::filesystem::path(":/Icons/" + this->iconName).c_str()));
    this->setIconSize({48, 48});
    this->setText(this->text.c_str());
    this->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

bool JsonStackElement::isList() const noexcept {
    return this->list;
}

std::vector<std::unique_ptr<JsonStackElement>>& JsonStackElement::getChildren() noexcept {
    return this->children;
}

void JsonStackElement::addChild(
    std::unique_ptr<JsonStackElement> child
) noexcept {
    this->children.push_back(std::move(child));
}

Form::FormInterface* JsonStackElement::getForm() const noexcept {
    return this->form.get();
}
}
