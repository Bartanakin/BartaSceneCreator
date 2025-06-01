#include <CustomWidgets/HashInputWidget.h>

namespace Barta::CustomWidgets {
HashInputWidget::HashInputWidget(
    std::vector<std::string> hashes,
    std::string& target,
    std::vector<std::string>& hashStack,
    QWidget* parent
):
    QWidget(parent),
    target(target),
    hashStack(hashStack),
    existingHashes(std::move(hashes)) {
    auto* layout = new QVBoxLayout(this);

    QLabel* titleLabel = new QLabel("Hash (alphanumeric characters)", this); // TODO what is more intuitive?
    layout->addWidget(titleLabel);

    statusLabel = new QLabel("", this);

    QPalette palette = statusLabel->palette();
    palette.setColor(QPalette::WindowText, Qt::red);
    statusLabel->setPalette(palette);

    layout->addWidget(statusLabel);

    input = new QLineEdit(this);
    this->input->setText(this->target.c_str());
    QRegularExpression rx("^[a-zA-Z0-9]*$"); // alphanumeric characters only
    input->setValidator(new QRegularExpressionValidator(rx, this));

    layout->addWidget(input);

    QObject::connect(input, &QLineEdit::textChanged, this, &HashInputWidget::onTextChanged);
}

void HashInputWidget::onTextChanged(
    const QString& text
) {
    std::string inputText = text.toStdString();

    if (inputText.empty()) {
        statusLabel->setText("Input cannot be empty.");

        return;
    }

    auto it = std::find(existingHashes.begin(), existingHashes.end(), inputText);
    if (it != existingHashes.end()) {
        statusLabel->setText("Input must be unique. This one already exists.");

        return;
    }

    statusLabel->setText("");
    this->target = inputText;
    this->hashStack.back() = target;
}
} // namespace Barta::CustomWidgets
