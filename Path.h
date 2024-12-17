#pragma once
#include "DynamicArray.h"
template <typename T>
class Path {
private:
    DynamicArray<T> path;
public:
    Path() {}
    void append(const T& vertex) {
        path.resize(path.getSize() + 1);
        if (path.getSize() == 1)
        {
            path.set(0, vertex);
        }
        else
        {
            for (int i = path.getSize() - 1; i >= 1; i--)
            {
                path.set(i, path.get(i - 1));
            }
            path.set(0, vertex);
        }
    }
    void appendWithoutInvert(const T& vertex)
    {
        path.append(vertex);
    }
    T& get(int index) const {
        return path.get(index);
    }
    size_t getSize() const {
        return path.getSize();;
    }
};