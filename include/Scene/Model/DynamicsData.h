#pragma once
#include <pch.h>

#include "Rotation.h"
#include "Vector3.h"

namespace Barta::Scene::Model {
struct DynamicsData {
    Vector3 massCenter = {0.f, 0.f, 0.f};
    Vector3 velocity = {0.f, 0.f, 0.f};
    Rotation rotation = {0.f, 0.f, 1.f, 0.f};
    bool hasInfiniteMass = false;
    float inverseMass = 1.f;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(DynamicsData, massCenter, velocity, rotation, hasInfiniteMass, inverseMass);
}
