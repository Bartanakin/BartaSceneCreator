#pragma once
#include "FormInterface.h"
#include <pch.h>

namespace Barta::QtComponents::Form {
class EyeForm: public virtual FormInterface {
public:
    int tagStackSizeRequirement() const noexcept override { return 0; }

    void submit(QVBoxLayout* layout, Scene::Model::Scene& model, const std::vector<std::string>& tagStack) override;
};
}
