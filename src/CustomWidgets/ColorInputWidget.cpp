#include <CustomWidgets/ColorInputWidget.h>

namespace Barta::CustomWidgets {
ColorInputWidget::ColorInputWidget(
    Scene::Model::Color& ref,
    QWidget* parent
):
    QWidget(parent),
    ref(ref) {
    // Create widgets
    this->redLabel = new QLabel("Red", this);
    this->greenLabel = new QLabel("Green", this);
    this->blueLabel = new QLabel("Blue", this);

    this->redInput = new QLineEdit(QString::number(this->ref.r), this);
    this->greenInput = new QLineEdit(QString::number(this->ref.g), this);
    this->blueInput = new QLineEdit(QString::number(this->ref.b), this);

    this->redInput->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    this->greenInput->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    this->blueInput->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    this->redInput->setText(QString::number(this->ref.r));
    this->greenInput->setText(QString::number(this->ref.g));
    this->blueInput->setText(QString::number(this->ref.b));

    // Status label
    this->statusLabel = new QLabel("", this);
    QPalette palette = statusLabel->palette();
    palette.setColor(QPalette::WindowText, Qt::red);
    statusLabel->setPalette(palette);

    // Layout setup
    auto* layout = new QVBoxLayout(this);
    auto* inputLayout = new QHBoxLayout();
    inputLayout->addWidget(this->redLabel);
    inputLayout->addWidget(this->redInput);
    inputLayout->addWidget(this->greenLabel);
    inputLayout->addWidget(this->greenInput);
    inputLayout->addWidget(this->blueLabel);
    inputLayout->addWidget(this->blueInput);

    layout->addLayout(inputLayout);
    layout->addWidget(statusLabel);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    // Connections
    connect(this->redInput, &QLineEdit::editingFinished, this, &ColorInputWidget::onEditingFinished);
    connect(this->greenInput, &QLineEdit::editingFinished, this, &ColorInputWidget::onEditingFinished);
    connect(this->blueInput, &QLineEdit::editingFinished, this, &ColorInputWidget::onEditingFinished);
}

bool ColorInputWidget::updateColor(
    QLineEdit* input,
    unsigned int& ref
) {
    bool ok;
    int v = input->text().toInt(&ok);
    if (v > 255 || v < 0 || !ok) {
        this->statusLabel->setText("All fields must be integers between 0 and 255.");
        input->setText("");

        return false;
    }


    input->setText(QString::number(v));
    ref = v;

    return true;
}

void ColorInputWidget::onEditingFinished() {
    if (this->updateColor(this->redInput, this->ref.r) && this->updateColor(this->greenInput, this->ref.g)
        && this->updateColor(this->blueInput, this->ref.b)) {
        this->statusLabel->setText("");
    }
}
} // namespace Barta::CustomWidgets
