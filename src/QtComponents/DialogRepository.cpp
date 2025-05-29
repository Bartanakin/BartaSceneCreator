#include <QtComponents/DialogRepository.h>

namespace Barta::QtComponents {
DialogRepository::DialogRepository(
    QWidget* parent
) noexcept:
    parent(parent) {}

QString DialogRepository::askForSceneNameDialog() {
    QDialog dialog(this->parent);
    dialog.setWindowTitle("Enter scene name");
    dialog.resize(400, 150);

    QVBoxLayout* layout = new QVBoxLayout(&dialog);

    QLabel* label = new QLabel("Scene name:");
    QLineEdit* lineEdit = new QLineEdit;
    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    layout->addWidget(label);
    layout->addWidget(lineEdit);
    layout->addWidget(buttonBox);

    QObject::connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    QObject::connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    QString result;
    if (dialog.exec() == QDialog::Accepted && !lineEdit->text().isEmpty()) {
        result = lineEdit->text();
    }

    return result + ".json";
}
}
