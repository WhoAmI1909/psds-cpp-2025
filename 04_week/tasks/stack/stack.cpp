#include <vector>


class Stack {
    std::vector<int> storage;

public:
    Stack() = default;
    ~Stack() = default;
    void Push(int);
    bool Pop();
    int& Top();
    const int& Top() const;
    bool Empty() const;
    size_t Size() const;
    void Clear();
    void Swap(Stack&);
    friend bool operator==(const Stack& lhs, const Stack& rhs);
    friend bool operator!=(const Stack&, const Stack&);
};

void Stack::Push(int a) {
    storage.push_back(a);
}

bool Stack::Pop() {
    if(storage.empty()) {
        return false;
    }
    storage.pop_back();
    return true;
}

int& Stack::Top() {
    return storage.back();
}

const int& Stack::Top() const {
    return storage.back();
}

bool Stack::Empty() const {
    return storage.empty();
}

size_t Stack::Size() const {
    return storage.size();
}

void Stack::Clear() {
    storage.clear();
}

void Stack::Swap(Stack& other) {
    storage.swap(other.storage);
}

bool operator==(const Stack& lhs, const Stack& rhs) {
    return lhs.storage == rhs.storage;
}

bool operator!=(const Stack& lhs, const Stack& rhs) {
    return lhs.storage != rhs.storage;
}
