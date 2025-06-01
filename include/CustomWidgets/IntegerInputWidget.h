#pragma once
#include <pch.h>

namespace Barta::CustomWidgets {
class IntegerInputWidget: public QWidget {
    Q_OBJECT

public:
    IntegerInputWidget(const std::string& label, int& targetRef, QWidget* parent = nullptr);

private:
    int& targetRef;
    QLineEdit* inputField;

private slots:
    void onTextChanged(const QString& text);
};
}
