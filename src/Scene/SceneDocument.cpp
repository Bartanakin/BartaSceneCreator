#include <Scene/SceneDocument.h>

namespace Barta::Scene {

SceneDocument::SceneDocument(
    const std::filesystem::path& existingScenePath
):
    scenePath(existingScenePath) {
    if (!std::filesystem::is_regular_file(existingScenePath)) {
        throw std::invalid_argument("existingScenePath path should be a file");
    }

    std::ifstream file(existingScenePath);

    json parsedJson;
    file >> parsedJson;
    this->sceneModel = parsedJson.get<Model::Scene>();
}

SceneDocument::SceneDocument(
    const std::filesystem::path& newScenePath,
    const std::string& fileName
):
    scenePath(newScenePath) {
    if (!std::filesystem::is_directory(newScenePath)) {
        throw std::invalid_argument("scene path should be a directory");
    }

    if (fileName.empty()) {
        throw std::invalid_argument("file name should be nonempty");
    }

    this->sceneModel = SceneDocument::generateDefaultModel();
    this->scenePath /= fileName;
}

Model::Scene SceneDocument::generateDefaultModel() {
    Model::Scene sceneModel;
    sceneModel.camera.center = {0.f, 0.f, -0.f};
    sceneModel.camera.eye = {0.f, 0.f, -1.f};
    sceneModel.camera.up = {0.f, 1.f, 0.f};

    sceneModel.objects = {};

    return sceneModel;
}

bool SceneDocument::saveToFile() {
    try {
        std::ofstream file(this->scenePath);
        json j = this->sceneModel;

        file << std::setw(4) << j << std::endl;
    } catch (std::exception& e) {
        return false;
    }

    return true;
}

std::string SceneDocument::getPath() const {
    return this->scenePath.string();
}
}
