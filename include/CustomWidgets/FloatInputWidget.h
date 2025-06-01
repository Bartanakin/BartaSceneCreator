#pragma once
#include <pch.h>

namespace Barta::CustomWidgets {
class FloatInputWidget: public QWidget {
    Q_OBJECT

public:
    explicit FloatInputWidget(const QString& labelText, float& targetRef, QWidget* parent = nullptr);

private slots:
    void onEditingFinished();

private:
    QLineEdit* input;
    QLabel* label;
    float& target;
};
}
