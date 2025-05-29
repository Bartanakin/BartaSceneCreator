#pragma once
#include <pch.h>

namespace Barta::QtComponents {
class DialogRepository {
public:
    DialogRepository(QWidget* parent = nullptr) noexcept;

    QString askForSceneNameDialog();

private:
    QWidget* parent;
};

}
