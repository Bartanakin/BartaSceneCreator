#pragma once
#include <pch.h>

#include "Vector3.h"

namespace Barta::Scene::Model {
struct Camera {
    Vector3 eye;
    Vector3 center;
    Vector3 up;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
    Camera,
    eye,
    center,
    up
);
}
