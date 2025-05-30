#pragma once
#include "FormInterface.h"
#include <pch.h>

namespace Barta::QtComponents::Form {
class NullForm: public virtual FormInterface {
public:
    NullForm(
        int tagSize
    ) noexcept:
        tagSize(tagSize) {}

    int tagStackSizeRequirement() const noexcept override { return this->tagSize; }

    void submit(
        QVBoxLayout* layout,
        Scene::Model::Scene& model,
        const std::vector<std::string>& tagStack
    ) override {}

private:
    int tagSize;
};
}
