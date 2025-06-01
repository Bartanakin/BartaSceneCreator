#pragma once
#include <pch.h>

namespace Barta::Scene::Model {
struct Color {
    unsigned int r;
    unsigned int g;
    unsigned int b;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Color, r, g, b);
}
