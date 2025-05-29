#pragma once
#include "Camera.h"
#include "Object.h"
#include <pch.h>

namespace Barta::Scene::Model {
struct Scene {
    Camera camera;
    std::vector<Object> objects;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
    Scene,
    camera,
    objects
)
}
