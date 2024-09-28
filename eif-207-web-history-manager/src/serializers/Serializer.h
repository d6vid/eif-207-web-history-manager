#pragma once

#include <fstream>

template <typename T>
class Serializer {
public:
    virtual ~Serializer() = default;
    virtual void save(const T& object, std::ofstream& out) const = 0;
    virtual void load(T& object, std::ifstream& in) const = 0;
};