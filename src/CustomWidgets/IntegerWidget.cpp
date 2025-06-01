#include <CustomWidgets/IntegerInputWidget.h>

namespace Barta::CustomWidgets {
IntegerInputWidget::IntegerInputWidget(
    const std::string& label,
    int& targetRef,
    QWidget* parent
):
    QWidget(parent),
    targetRef(targetRef) {
    auto* layout = new QHBoxLayout(this);

    auto* labelWidget = new QLabel(QString::fromStdString(label), this);
    this->inputField = new QLineEdit(this);
    this->inputField->setValidator(new QIntValidator(this));

    layout->addWidget(labelWidget);
    layout->addWidget(this->inputField);
    setLayout(layout);

    connect(this->inputField, &QLineEdit::textChanged, this, &IntegerInputWidget::onTextChanged);
}

void IntegerInputWidget::onTextChanged(
    const QString& text
) {
    bool ok;
    int value = text.toInt(&ok);
    if (ok) {
        this->targetRef = value;
    }
}
}
