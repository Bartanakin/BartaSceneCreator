#pragma once
#include "Camera.h"
#include "Object.h"
#include <pch.h>

#include "HashVector.h"

namespace Barta::Scene::Model {
struct Scene {
    Camera camera;
    HashVector<Object> objects;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
    Scene,
    camera,
    objects
)
}
