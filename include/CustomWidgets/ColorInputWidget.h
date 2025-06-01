#pragma once
#include "Scene/Model/Color.h"
#include <pch.h>

namespace Barta::CustomWidgets {
class ColorInputWidget: public QWidget {
    Q_OBJECT

public:
    explicit ColorInputWidget(Scene::Model::Color& ref, QWidget* parent = nullptr);
    void updateColor(bool okRed);

private slots:
    void onEditingFinished();

private:
    bool updateColor(QLineEdit* input, unsigned int& ref);

    Scene::Model::Color& ref;

    QLabel* redLabel;
    QLabel* greenLabel;
    QLabel* blueLabel;

    QLineEdit* redInput;
    QLineEdit* greenInput;
    QLineEdit* blueInput;
    QLabel* statusLabel;
};
}
