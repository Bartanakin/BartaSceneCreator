#pragma once
#include <pch.h>

namespace Barta::Scene::Model {
struct Vector3 {
    float x;
    float y;
    float z;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Vector3, x, y, z);
}
