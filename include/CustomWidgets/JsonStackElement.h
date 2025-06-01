#pragma once
#include "QtComponents/Form/FormInterface.h"
#include <pch.h>

namespace Barta::QtComponents::StackElement {
class JsonStackElement: public QToolButton {
    Q_OBJECT

public:
    JsonStackElement(
        std::unique_ptr<Form::FormInterface> form,
        std::string iconName,
        std::string text,
        bool list = false,
        QWidget* parent = nullptr
    ) noexcept;

    bool isList() const noexcept;

    std::vector<std::unique_ptr<JsonStackElement>>& getChildren() noexcept;

    void addChild(std::unique_ptr<JsonStackElement> child) noexcept;

    Form::FormInterface* getForm() const noexcept;

public:
    enum class State {
        MIDDLE = 0,
        LEFT = 1
    };

    State getState() const { return this->state; }

    void setState(
        State state
    ) {
        this->state = state;
    }

private:
    State state;
    std::string iconName;
    std::string text;
    std::unique_ptr<Form::FormInterface> form;
    bool list;
    std::vector<std::unique_ptr<JsonStackElement>> children;
    std::vector<std::string> listTags;
};
}
