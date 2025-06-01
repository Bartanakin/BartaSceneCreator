#pragma once
#include "Scene/Model/Transformation.h"
#include <pch.h>

namespace Barta::CustomWidgets {
class MatrixWidget: public QWidget {
    Q_OBJECT

public:
    MatrixWidget(const std::string& label, Scene::Model::Transformation& targetRef, QWidget* parent = nullptr);

private:
    Scene::Model::Transformation& targetRef;
    QPlainTextEdit* input;
    QLabel* statusLabel;

    std::string matrixToString(const std::array<float, 16>& matrix) const;
    std::string matrixToGridString(const std::array<float, 16>& matrix) const;

private slots:
    void onEditingFinished();
};
}
