#pragma once
#include "Rotation.h"
#include "Vector3.h"
#include <pch.h>

namespace Barta::Scene::Model {
struct Hitbox {
    enum class Type {
        NULL_TYPE = 0,
        BALL,
        OBB
    };

    static constexpr std::string getTypeString(
        Type type
    ) {
        switch (type) {
        case Type::BALL: return "BALL";
        case Type::NULL_TYPE: return "NULL";
        // case Type::OBB: return "OBB";
        }

        return "";
    }

    std::string type = getTypeString(Type::NULL_TYPE);
    Vector3 center = {0.f, 0.f, 0.f};
    float radius = 1.f;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Hitbox, type, center, radius);
}
