#pragma once
#include <pch.h>

namespace Barta::QtComponents {
class DialogRepository {
public:
    DialogRepository(QWidget* parent = nullptr) noexcept;

    QString askForSceneNameDialog();

    QWidget* getFloatingPointInput(const std::string& label, float& target);
private:
    QWidget* parent;
};

}
