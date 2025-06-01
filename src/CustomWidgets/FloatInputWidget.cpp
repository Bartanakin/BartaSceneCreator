#include <CustomWidgets/FloatInputWidget.h>

namespace Barta::CustomWidgets {
FloatInputWidget::FloatInputWidget(
    const QString& labelText,
    float& targetRef,
    QWidget* parent
):
    QWidget(parent),
    target(targetRef) {
    this->label = new QLabel(labelText, this);
    this->input = new QLineEdit(this);

    this->input->setValidator(new QDoubleValidator(-1e10, 1e10, 3, this));
    this->input->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    this->input->setText(QString::number(this->target));

    auto* layout = new QHBoxLayout(this);
    layout->addWidget(this->label);
    layout->addWidget(this->input);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    QObject::connect(this->input, &QLineEdit::editingFinished, this, &FloatInputWidget::onEditingFinished);
}

void FloatInputWidget::onEditingFinished() {
    bool ok;
    float value = this->input->text().toFloat(&ok);
    if (ok) {
        this->target = value;
    } else {
        this->input->setText("");
    }
}
}
