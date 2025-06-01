#include <CustomWidgets/TextInputWidget.h>

namespace Barta::CustomWidgets {
TextInputWidget::TextInputWidget(
    std::string label,
    std::string& target,
    QWidget* parent
):
    QWidget(parent),
    target(target) {
    auto* layout = new QVBoxLayout(this);

    QLabel* titleLabel = new QLabel(label.c_str(), this);
    layout->addWidget(titleLabel);

    auto input = new QLineEdit(this);
    input->setText(this->target.c_str());
    layout->addWidget(input);

    QObject::connect(input, &QLineEdit::textChanged, this, &TextInputWidget::onTextChanged);
}

void TextInputWidget::onTextChanged(
    const QString& text
) {
    this->target = text.toStdString();
}
}
