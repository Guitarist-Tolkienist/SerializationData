#pragma once

#include <iostream>
#include <fstream>

// This class implements the way to serialize different types
// by storing bytes in a char array
// Then these by can be poped up from the array
// Keep in mind that you should store and take 
// these bytes of data in a specific order
class SerializedData
{
    char* Data; // array to store serialized bytes
    size_t DataLength; // length of Data array

public:
    SerializedData() : Data(nullptr), DataLength(0)
    {
    }

    ~SerializedData()
    {
        if (Data) free(Data);
    }

    template <typename T>
    void Serialize(T DataToSerialize, size_t SizeOfDataToSerialize = 0);

    template <>
    void Serialize(int DataToSerialize, size_t SizeOfDataToSerialize);

    template <>
    void Serialize(short DataToSerialize, size_t SizeOfDataToSerialize);

    template <>
    void Serialize(float DataToSerialize, size_t SizeOfDataToSerialize);

    template <>
    void Serialize(char DataToSerialize, size_t SizeOfDataToSerialize);

    template <>
    void Serialize(char* DataToSerialize, size_t SizeOfDataToSerialize);

    template <>
    void Serialize(wchar_t* DataToSerialize, size_t SizeOfDataToSerialize);

    template <>
    void Serialize(std::string DataToSerialize, size_t SizeOfDataToSerialize);


    template <typename T>
    void Deserialize(T& DataToDeserialize);

    template <>
    void Deserialize(int& DataToDeserialize);

    template <>
    void Deserialize(short& DataToDeserialize);

    template <>
    void Deserialize(float& DataToDeserialize);

    template <>
    void Deserialize(char& DataToDeserialize);

    // If `DataToDeserialize` points to some memory address of char
    // it will be deleted. Then new memory will be dynamically allocated
    // for `DataToDeserialize` so it needs to be deleted manually afterwards
    template <>
    void Deserialize(char*& DataToDeserialize);

    // If `DataToDeserialize` points to some memory address of wchar_t
    // it will be deleted. Then new memory will be dynamically allocated
    // for `DataToDeserialize` so it needs to be deleted manually afterwards
    template <>
    void Deserialize(wchar_t*& DataToDeserialize);

    template <>
    void Deserialize(std::string& DataToDeserialize);

    void Push(const void* Src, size_t NumBytesToTakeFromSrc = 0);

    void RemoveBytes(size_t NumBytesToDeserialize);
};