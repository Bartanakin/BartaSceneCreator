#pragma once
#include <pch.h>

#include "Color.h"
#include "DynamicsData.h"
#include "Hitbox.h"

namespace Barta::Scene::Model {
struct Sprite {
    enum class Type {
        RECTANGLE,
        BALL,
        TRIANGLE,
        CIRCLE
    };

    static constexpr std::string getTypeName(
        Type type
    ) {
        switch (type) {
        case Type::RECTANGLE: return "RECTANGLE";
        case Type::BALL: return "BALL";
        case Type::TRIANGLE: return "TRIANGLE";
        case Type::CIRCLE: return "CIRCLE";
        }

        return "";
    }

    std::string hash;
    std::string type = getTypeName(Type::BALL);

    // BALL, CIRCLE
    Vector3 center;
    float radius;

    // RECTANGLE
    Vector3 origin;
    Vector3 size;

    // TRIANGLE
    Vector3 vertex1;
    Vector3 vertex2;
    Vector3 vertex3;

    Color color;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Sprite, hash, type, center, radius, origin, size, vertex1, vertex2, vertex3, color);
}
