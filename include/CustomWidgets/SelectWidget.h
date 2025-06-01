#pragma once
#include <pch.h>

namespace Barta::CustomWidgets {
struct DropdownOption {
    std::string label;
    std::string iconName;
};

class SelectWidget: public QWidget {
    Q_OBJECT

public:
    explicit SelectWidget(
        const std::string& labelText,
        const std::vector<DropdownOption>& options,
        std::string& targetRef,
        bool refreshOnChange = false,
        QWidget* parent = nullptr
    );

private slots:
    void onSelectionChanged(int index);

signals:
    void onChange();

private:
    QLabel* label;
    QComboBox* comboBox;
    std::vector<DropdownOption> options;
    std::string& targetRef;
    bool refreshOnChange;
};
}
