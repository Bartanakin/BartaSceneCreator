#pragma once
#include <pch.h>

namespace Barta {
template<typename T>
concept HasHashFieldConcept = requires(T t) {
    { t.hash } -> std::convertible_to<std::string>;
};
}