#pragma once
#include <pch.h>

namespace Barta::CustomWidgets {
class HashInputWidget: public QWidget {
    Q_OBJECT

public:
    HashInputWidget(std::vector<std::string> hashes, std::string& target, std::vector<std::string>& hashStack, QWidget* parent = nullptr);

private slots:

    void onTextChanged(const QString& text);

private:
    QLineEdit* input;
    QLabel* statusLabel;
    std::string& target;
    std::vector<std::string>& hashStack;
    std::vector<std::string> existingHashes;
};
}
