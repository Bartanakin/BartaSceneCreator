#pragma once
#include "Model/Scene.h"
#include <pch.h>

namespace Barta::Scene {
class SceneDocument {
public:
    explicit SceneDocument(const std::filesystem::path& existingScenePath);
    explicit SceneDocument(const std::filesystem::path& newScenePath, const std::string& fileName);

    static Model::Scene generateDefaultModel();

private:
    Model::Scene sceneModel;
    std::filesystem::path scenePath;
};
}
