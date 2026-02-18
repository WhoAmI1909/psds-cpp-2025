#include <cstring>
#include <string>


class StringView {
    int size;
    char* symbol;
public:
    // Constructors
    StringView() {}
    StringView(std::string) {}
    StringView(int size, char* sympos) {}
    StringView(char* sympos) {}
    // Methods
    char* Front() {}
    char* Back() {}
    int Size() {}
    int Length() {}
    bool Empty() {}
    void RemovePrefix(int) {}
    void RemoveSuffix(int) {}
    StringView Substr(char*, int) {}
    char* Find(char, char*) {}
    std::string ToString() {}
    // Operators
    char* operator[](const StringView& obj) {}
};

StringView::StringView(): size(0), symbol(nullptr) {}