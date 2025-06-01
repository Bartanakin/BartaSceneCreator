#include <CustomWidgets/MatrixWidget.h>

namespace Barta::CustomWidgets {

MatrixWidget::MatrixWidget(
    const std::string& label,
    Scene::Model::Transformation& targetRef,
    QWidget* parent
):
    QWidget(parent),
    targetRef(targetRef) {
    auto* layout = new QVBoxLayout(this);

    QLabel* titleLabel = new QLabel(label.c_str(), this);
    layout->addWidget(titleLabel);

    this->input = new QPlainTextEdit(this);
    this->input->setPlainText(this->matrixToGridString(this->targetRef.array).c_str());
    QFont font = input->font();
    font.setFamily("Courier");
    input->setFont(font);

    QFontMetrics metrics(font);
    int charWidth = metrics.horizontalAdvance(QLatin1Char('0'));
    int charHeight = metrics.height();
    input->setMinimumSize(charWidth * 12, charHeight * 5);

    layout->addWidget(input);
    this->input->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    this->statusLabel = new QLabel("", this);
    QPalette palette = statusLabel->palette();
    palette.setColor(QPalette::WindowText, Qt::red);
    this->statusLabel->setPalette(palette);
    layout->addWidget(statusLabel);

    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    connect(input, &QPlainTextEdit::textChanged, this, &MatrixWidget::onEditingFinished);
}

void MatrixWidget::onEditingFinished() {
    statusLabel->setText("");
    QString text = input->toPlainText();
    QString flatText = text;
    flatText.replace(QRegularExpression("[\n\r]+"), " ");
    QStringList parts = flatText.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);

    std::string message = "";
    if (parts.size() != 16) {
        message += "You must enter exactly 16 float values. ";
    }

    std::array<float, 16> parsedMatrix;
    bool ok = true;

    for (int i = 0; i < parts.size(); ++i) {
        bool localOk;
        float value = parts[i].toFloat(&localOk);
        if (!localOk) {
            ok = false;
            break;
        }

        if (parts.size() != 16) {
            continue;
        }

        parsedMatrix[i] = value;
    }

    if (!ok) {
        message += "All inputs must be valid float values. ";
    }

    if (!message.empty()) {
        this->statusLabel->setText(message.c_str());

        return;
    }

    this->targetRef.array = parsedMatrix;
}

std::string MatrixWidget::matrixToString(
    const std::array<float, 16>& matrix
) const {
    QStringList parts;
    for (float val: matrix) {
        parts << QString::number(val);
    }
    return parts.join(" ").toStdString();
}

std::string MatrixWidget::matrixToGridString(
    const std::array<float, 16>& matrix
) const {
    QStringList lines;
    for (int row = 0; row < 4; ++row) {
        QStringList rowParts;
        for (int col = 0; col < 4; ++col) {
            rowParts << QString::number(matrix[row * 4 + col]);
        }
        lines << rowParts.join(" ");
    }
    return lines.join("\n").toStdString();
}

} // namespace Barta::CustomWidgets
