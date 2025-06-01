#pragma once
#include "HashFieldConcept.h"
#include <pch.h>

namespace Barta {
template<HasHashFieldConcept T>
class HashVector: public std::vector<T> {
public:
    T& findOrCreateByHash(
        const std::string& searchHash
    ) {
        for (auto& item: *this) {
            if (item.hash == searchHash) {
                return item;
            }
        }

        this->emplace_back(searchHash);

        return this->back();
    }

    std::vector<std::string> getAllHashes() const {
        std::vector<std::string> hashes;
        hashes.reserve(this->size());
        for (const auto& item: *this) {
            hashes.push_back(item.hash);
        }

        return hashes;
    }
};
}
