#pragma once
#include <pch.h>

namespace Barta::CustomWidgets {
class TextInputWidget: public QWidget {
    Q_OBJECT

public:
    TextInputWidget(std::string label, std::string& targetRef, QWidget* parent = nullptr);

private:
    std::string& target;

private slots:
    void onTextChanged(const QString& text);
};
}
