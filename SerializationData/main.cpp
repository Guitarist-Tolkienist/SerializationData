#include "CSerializedData.h"

// Following program declares 5 variables of different types:
// char array, int, short, std::string, wchar_t array.
// Then `Data` object of class SerializedData is created. 
// This is the main approach to serialize/deserialize data.
// Following fragment of code serialize and deserialize data of differrent types,
// it prints nothing to the console, but you can check if everything is okay using debuger
int main()
{
    // === SERIALIZATION ===
    char Str1[] = "hello";
    int Int1 = 26;
    short ShortInt1(10);
    std::string String1 = "STD::STRING1";
    wchar_t Wstr1[] = L"wchar";

    SerializedData Data;

    Data.Serialize(Str1, sizeof(Str1));
    Data.Serialize(Int1);
    Data.Serialize(ShortInt1);
    Data.Serialize(String1, String1.length());
    Data.Serialize(Wstr1, sizeof(Wstr1)); 


    // === DESERIALIZATION ====
    char* StrDest1(nullptr);
    int IntRes1(0);
    short ShortRes1(0);
    std::string StringDest1;
    wchar_t* WstrDest(nullptr);
    
    Data.Deserialize(WstrDest);
    Data.Deserialize(StringDest1);
    Data.Deserialize(ShortRes1);
    Data.Deserialize(IntRes1);
    Data.Deserialize(StrDest1);

    // You can uncomment following 5 lines of code
    // to check output of deserialized variables
    /*std::cout << StrDest1 << "\n";
    std::cout << IntRes1<< "\n";
    std::cout << ShortRes1<< "\n";
    std::cout << StringDest1 << "\n";
    std::wcout << WstrDest<< "\n";*/
    return 0;
}