#pragma once

#include <stdexcept>

template <class T> class DynamicArray
{
private:
    int size = 0;
    T* array = nullptr;

public:
    DynamicArray()
    {
        this->size = 0;
        this->array = new T[this->size];
    }
    DynamicArray(const T* items, int size)
    {
        if (size < 0) throw std::out_of_range("Invalid size\n");
        array = new T[size];
        for (int i = 0; i < size; i++) {
            array[i] = items[i];
        }
        this->size = size;
    }
    DynamicArray(int size)
    {
        if (size < 0) throw std::out_of_range("Invalid size\n");
        this->array = new T[size];
        this->size = size;
    }
    DynamicArray(const DynamicArray<T>& other)
    {
        this->size = other.size;
        this->array = new T[size];
        for (int i = 0; i < size; i++)
        {
            this->array[i] = other.array[i];
        }
    }
    ~DynamicArray()
    {
        delete[] this->array;
    }
    T& operator[](int index)
    {
        if (index < 0 || index >= this->size) throw std::out_of_range("Index is invalid");
        return array[index];
    }
    T& get(int index) const
    {
        if (index < 0 || index >= this->size) throw std::out_of_range("Index out of range\n");
        return (this->array)[index];
    }
    size_t getSize() const
    {
        if (size < 0) throw std::out_of_range("Invalid size\n");
        return this->size;
    }
    void set(int index, const T& value)
    {
        if (index < 0 || index > this->size) throw std::out_of_range("Index out of range\n");
        this->array[index] = value;
    }
    void resize(int newSize)
    {
        if (newSize < 0) throw std::out_of_range("Invalid size");
        int size1 = 0;
        if (newSize > size)
        {
            size1 = this->size;
        }
        else
        {
            size1 = newSize;
        }
        T* newArray = new T[newSize];
        for (int i = 0; i < size1; i++)
        {
            newArray[i] = this->array[i];
        }

        delete[] this->array;
        this->array = newArray;
        this->size = newSize;
    }
    void append(const T& value)
    {
        this->resize(this->getSize() + 1);
        array[size - 1] = value;
    }
    bool contains(const T& value)
    {
        int flag = -1;
        for (int i = 0; i < this->getSize(); i++)
        {
            if (this->get(i) == value)
            {
                flag = 1;
            }
        }
        if (flag == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};