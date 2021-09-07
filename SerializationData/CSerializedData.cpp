#include "CSerializedData.h"

// SERIALIZATION METHODS IMPLEMENTATION
template <typename T>
void SerializedData::Serialize(T DataToSerialize, size_t SizeOfDataToSerialize)
{
    // Unhandled type 
}

template <>
void SerializedData::Serialize<int>(int DataToSerialize, size_t SizeOfDataToSerialize)
{
    Push(&DataToSerialize, sizeof(DataToSerialize));
}

template <>
void SerializedData::Serialize<short>(short DataToSerialize, size_t SizeOfDataToSerialize)
{
    Push(&DataToSerialize, sizeof(DataToSerialize));
}

template <>
void SerializedData::Serialize<float>(float DataToSerialize, size_t SizeOfDataToSerialize)
{
    Push(&DataToSerialize, sizeof(DataToSerialize));
}

template <>
void SerializedData::Serialize<char>(char DataToSerialize, size_t SizeOfDataToSerialize)
{
    Push(&DataToSerialize, sizeof(DataToSerialize));
}

template <>
void SerializedData::Serialize<char*>(char* DataToSerialize, size_t SizeOfDataToSerialize)
{
    int StrLength = SizeOfDataToSerialize;
    Push(DataToSerialize, SizeOfDataToSerialize);
    Serialize(StrLength);
}

template <>
void SerializedData::Serialize<wchar_t*>(wchar_t* DataToSerialize, size_t SizeOfDataToSerialize)
{
    int StrLength = SizeOfDataToSerialize;
    Push(DataToSerialize, SizeOfDataToSerialize);
    Serialize(StrLength);
}

template <>
void SerializedData::Serialize<std::string>(std::string DataToSerialize, size_t SizeOfDataToSerialize)
{
    int StrLength = SizeOfDataToSerialize;
    Push(DataToSerialize.c_str(), SizeOfDataToSerialize);
    Serialize(StrLength);
}

// DESERIALIZATION METHODS IMPLEMENTATION
template <typename T>
void SerializedData::Deserialize(T& DataToSerialize)
{
    // Unhandled type 
}

template <>
void SerializedData::Deserialize(int& DataToDeserialize)
{
    size_t offset = DataLength - sizeof(DataToDeserialize); // offset of Data
    size_t NumBytesToDeserialize = sizeof(DataToDeserialize);

    // Copy `num` bytes of Data to `Des_Int` starting from `offset`
    memcpy(&DataToDeserialize, Data + offset, NumBytesToDeserialize);

    RemoveBytes(NumBytesToDeserialize);
}

template <>
void SerializedData::Deserialize(short& DataToDeserialize)
{
    size_t offset = DataLength - sizeof(DataToDeserialize); // offset of Data
    size_t NumBytesToDeserialize = sizeof(DataToDeserialize);

    // Copy `num` bytes of Data to `Des_Int` starting from `offset`
    memcpy(&DataToDeserialize, Data + offset, NumBytesToDeserialize);

    RemoveBytes(NumBytesToDeserialize);
}

template <>
void SerializedData::Deserialize(float& DataToDeserialize)
{
    size_t offset = DataLength - sizeof(DataToDeserialize); // offset of Data
    size_t NumBytesToDeserialize = sizeof(DataToDeserialize);

    // Copy `num` bytes of Data to `Des_Int` starting from `offset`
    memcpy(&DataToDeserialize, Data + offset, NumBytesToDeserialize);

    RemoveBytes(NumBytesToDeserialize);
}

template <>
void SerializedData::Deserialize(char& DataToDeserialize)
{
    size_t offset = DataLength - sizeof(DataToDeserialize); // offset of Data
    size_t NumBytesToDeserialize = sizeof(DataToDeserialize);

    // Copy `num` bytes of Data to `Des_Int` starting from `offset`
    memcpy(&DataToDeserialize, Data + offset, NumBytesToDeserialize);

    RemoveBytes(NumBytesToDeserialize);
}

// If `DataToDeserialize` points to some memory address of char
// it will be deleted. Then new memory will be dynamically allocated
// for `DataToDeserialize` so it needs to be deleted manually afterwards
template <>
void SerializedData::Deserialize(char*& DataToDeserialize)
{
    int NumBytesToDeserialize(0);
    Deserialize(NumBytesToDeserialize);
    size_t offset = DataLength - NumBytesToDeserialize; // offset of Data

    if (DataToDeserialize) {
        delete[] DataToDeserialize;
    }
    DataToDeserialize = new char[NumBytesToDeserialize];
    // Copy `NumBytesToDeserialize` bytes of Data starting from `offset` to `Des_String`
    memcpy(DataToDeserialize, Data + offset, NumBytesToDeserialize);
    DataToDeserialize[NumBytesToDeserialize] = '\0';

    RemoveBytes(NumBytesToDeserialize);
}

// If `DataToDeserialize` points to some memory address of wchar_t
// it will be deleted. Then new memory will be dynamically allocated
// for `DataToDeserialize` so it needs to be deleted manually afterwards
template <>
void SerializedData::Deserialize(wchar_t*& DataToDeserialize)
{
    int NumBytesToDeserialize(0);
    Deserialize(NumBytesToDeserialize);
    size_t offset = DataLength - NumBytesToDeserialize; // offset of Data

    if (DataToDeserialize) {
        delete[] DataToDeserialize;
    }
    DataToDeserialize = new wchar_t[NumBytesToDeserialize];

    // Copy `num` bytes of Data  starting from `offset` to `Des_WcharString`
    memcpy(DataToDeserialize, Data + offset, NumBytesToDeserialize);

    RemoveBytes(NumBytesToDeserialize);
}

template <>
void SerializedData::Deserialize(std::string& DataToDeserialize)
{
    int NumBytesToDeserialize(0);
    Deserialize(NumBytesToDeserialize);
    size_t offset = DataLength - NumBytesToDeserialize; // offset of Data

    // Copy `num` bytes of Data starting from `offset` to `Des_String`
    char* char_array = new char[NumBytesToDeserialize];
    memcpy(char_array, Data + offset, NumBytesToDeserialize);
    DataToDeserialize.assign(char_array, NumBytesToDeserialize);

    delete[] char_array;
    RemoveBytes(NumBytesToDeserialize);
}



void SerializedData::Push(const void* Src, size_t NumBytesToTakeFromSrc)
{
    // In case if memory for Data buffer hasn't been allocated we need to do it manually
    if (!Data)
    {
        Data = static_cast<char*>(malloc(NumBytesToTakeFromSrc));
    }
    else
    {
        // In order to stack `Src` to `Data` buffer we need to reallocate memory for `Buff` pointer
        Data = static_cast<char*>(realloc(Data, DataLength + NumBytesToTakeFromSrc));
    }

    // Copy `NumBytesToTakeFromSrc` bytes of data from `Src` to the end of `Buff`
    memcpy(Data + DataLength, Src, NumBytesToTakeFromSrc);
    DataLength += NumBytesToTakeFromSrc;
}


void SerializedData::RemoveBytes(size_t NumBytesToDeserialize) {
    // Remove deserialized bytes from `Data`
    Data = static_cast<char*>(realloc(Data, DataLength - NumBytesToDeserialize));
    DataLength -= NumBytesToDeserialize;
}
