#pragma once
#include <pch.h>

namespace Barta::Scene::Model {
struct Object {
    std::string type;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Object, type);
}
