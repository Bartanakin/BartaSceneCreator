#pragma once
#include <pch.h>

#include "DynamicsData.h"
#include "HashVector.h"
#include "Hitbox.h"
#include "Sprite.h"
#include "Transformation.h"

namespace Barta::Scene::Model {
struct Object {
    enum class Type {
        BARTA_RIGID_OBJECT,
        BARTA_SOFT_OBJECT,
    };

    static constexpr std::string getTypeName(
        Type type
    ) {
        switch (type) {
        case Type::BARTA_RIGID_OBJECT: return "BARTA_RIGID_OBJECT";
        case Type::BARTA_SOFT_OBJECT: return "BARTA_SOFT_OBJECT";
        }

        return "";
    }

    enum class MeshType {
        MSH,
    };

    static constexpr std::string getMeshTypeName(
        MeshType meshType
    ) {
        switch (meshType) {
        case MeshType::MSH: return "msh";
        }

        return "";
    }

    std::string hash;
    std::string type = getTypeName(Type::BARTA_RIGID_OBJECT);
    std::string meshType = getMeshTypeName(MeshType::MSH);
    std::string sourceFileName = "";
    int z_index = 0;
    DynamicsData dynamicsData;
    Hitbox hitbox;
    HashVector<Sprite> sprites;
    Transformation transformation;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Object, hash, type, meshType, sourceFileName, z_index, hitbox, sprites, transformation);
}
