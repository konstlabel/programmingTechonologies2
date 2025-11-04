namespace Pairs {

    template<typename K, typename V>
    Pair<K, V>::Pair(const K& key, const V& value)
        : first(key), second(value) {}

    template<typename K, typename V>
    Pair<K, V>::Pair(const Pair<K, V>& other)
        : first(other.first), second(other.second) {}

    template<typename K, typename V>
    Pair<K, V>& Pair<K, V>::operator =(const Pair<K, V>& other) {

        if (this != &other) {
            first = other.first;
            second = other.second;
        }
        return *this;
    }

    template<typename K, typename V>
    bool Pair<K, V>::operator ==(const Pair<K, V>& other) const {

        return first == other.first && second == other.second;
    }

    template<typename K, typename V>
    bool Pair<K, V>::operator !=(const Pair<K, V>& other) const {

        return !(*this == other);
    }

    template<typename K, typename V>
    std::ostream& operator <<(std::ostream& os, const Pair<K, V>& pair) {

        os << "(" << pair.first << ", " << pair.second << ")";
        return os;
    }
}