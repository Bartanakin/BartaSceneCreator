#pragma once
#include <pch.h>

namespace Barta::Scene::Model {
struct Transformation {
    // clang-format off
    std::array<float, 16> array = {
        1.f, 0.f, 0.f, 0.f,
        0.f, 1.f, 0.f, 0.f,
        0.f, 0.f, 1.f, 0.f,
        0.f, 0.f, 0.f, 1.f,
    };
};

inline void to_json(json& j, const Transformation& p) {
    j = json{
        {"a00", p.array[0]},
        {"a01", p.array[1]},
        {"a02", p.array[2]},
        {"a03", p.array[3]},

        {"a10", p.array[4]},
        {"a11", p.array[5]},
        {"a12", p.array[6]},
        {"a13", p.array[7]},


        {"a20", p.array[8]},
        {"a21", p.array[9]},
        {"a22", p.array[10]},
        {"a23", p.array[11]},

        {"a30", p.array[12]},
        {"a31", p.array[13]},
        {"a32", p.array[14]},
        {"a33", p.array[15]},
    };
}

inline void from_json(const json& j, Transformation& p) {
    j.at("a00").get_to(p.array[0]);
    j.at("a01").get_to(p.array[1]);
    j.at("a02").get_to(p.array[2]);
    j.at("a03").get_to(p.array[3]);

    j.at("a10").get_to(p.array[4]);
    j.at("a11").get_to(p.array[5]);
    j.at("a12").get_to(p.array[6]);
    j.at("a13").get_to(p.array[7]);

    j.at("a20").get_to(p.array[8]);
    j.at("a21").get_to(p.array[9]);
    j.at("a22").get_to(p.array[10]);
    j.at("a23").get_to(p.array[11]);

    j.at("a30").get_to(p.array[12]);
    j.at("a31").get_to(p.array[13]);
    j.at("a32").get_to(p.array[14]);
    j.at("a33").get_to(p.array[15]);
}
    // clang-format on
}
