#include <CustomWidgets/SelectWidget.h>

#include "../../Bartascenecreator.h"

namespace Barta::CustomWidgets {
SelectWidget::SelectWidget(
    const std::string& labelText,
    const std::vector<DropdownOption>& options,
    std::string& targetRef,
    bool refreshOnChange,
    QWidget* parent
):
    QWidget(parent),
    options(options),
    targetRef(targetRef),
    refreshOnChange(refreshOnChange) {
    if (options.empty()) {
        throw std::invalid_argument("SelectWidget needs at least one option");
    }

    this->label = new QLabel(labelText.c_str(), this);
    this->comboBox = new QComboBox(this);

    for (const auto& opt: options) {
        this->comboBox->addItem(QIcon(std::filesystem::path(":/Icons/" + opt.iconName).c_str()), opt.label.c_str());
    }

    this->comboBox->setCurrentIndex(0);
    for (int i = 0; i < options.size(); i++) {
        if (options[i].label == this->targetRef) {
            this->comboBox->setCurrentIndex(i);
        }
    }

    auto* layout = new QHBoxLayout(this);
    layout->addWidget(this->label);
    layout->addWidget(this->comboBox);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    connect(this->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &SelectWidget::onSelectionChanged);
}

void SelectWidget::onSelectionChanged(
    int index
) {
    this->targetRef = this->options.at(index).label;

    emit this->onChange();
}
}
