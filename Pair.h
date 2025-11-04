#pragma once
#include <iostream>

namespace Pairs {

    template<typename K, typename V>
    class Pair {
    public:
        K first;
        V second;

        Pair() = default;

        Pair(const K& key, const V& value);

        Pair(const Pair<K, V>& other);

        Pair<K, V>& operator=(const Pair<K, V>& other);

        bool operator==(const Pair<K, V>& other) const;

        bool operator!=(const Pair<K, V>& other) const;

        friend std::ostream& operator<<(std::ostream& os, const Pair<K, V>& pair);
    };
}

#include "Pair.inl"