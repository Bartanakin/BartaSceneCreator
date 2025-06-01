#pragma once
#include <pch.h>

namespace Barta::Scene::Model {
struct Rotation {
    float x;
    float y;
    float z;
    float angle;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Rotation, x, y, z, angle);
}
