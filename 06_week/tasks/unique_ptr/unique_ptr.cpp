#include <string>


class UniquePtr {
private:
    std::string* ptr_;

public:
    // Конструкторы
    UniquePtr();                          
    explicit UniquePtr(std::string* ptr);

    UniquePtr(UniquePtr&& other) noexcept;
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(UniquePtr&& other) noexcept;
    UniquePtr& operator=(const UniquePtr&) = delete;

    ~UniquePtr();

    // Методы
    std::string* Get() const;
    std::string* Release();
    void Reset(std::string* ptr = nullptr);
    void Swap(UniquePtr& other) noexcept;

    // Операторы
    std::string& operator*() const;
    std::string* operator->() const;
    explicit operator bool() const;
};

UniquePtr::UniquePtr() : ptr_(nullptr) {}

UniquePtr::UniquePtr(std::string* ptr) : ptr_(ptr) {}

UniquePtr::UniquePtr(UniquePtr&& other) noexcept : ptr_(other.ptr_) {
    other.ptr_ = nullptr;
}

UniquePtr& UniquePtr::operator=(UniquePtr&& other) noexcept {
    if (this != &other) {
        delete ptr_;
        ptr_ = other.ptr_;
        other.ptr_ = nullptr;
    }
    return *this;
}

UniquePtr::~UniquePtr() {
    delete ptr_;
}

// Методы
std::string* UniquePtr::Get() const {
    return ptr_;
}

std::string* UniquePtr::Release() {
    std::string* tmp = ptr_;
    ptr_ = nullptr;
    return tmp;
}

void UniquePtr::Reset(std::string* ptr) {
    delete ptr_;
    ptr_ = ptr;
}

void UniquePtr::Swap(UniquePtr& other) noexcept {
    std::swap(ptr_, other.ptr_);
}

// Операторы
std::string& UniquePtr::operator*() const {
    return *ptr_;
}

std::string* UniquePtr::operator->() const {
    return ptr_;
}

UniquePtr::operator bool() const {
    return ptr_ != nullptr;
}

// MakeUnique функции
UniquePtr MakeUnique(const std::string& str) {
    return UniquePtr(new std::string(str));
}

UniquePtr MakeUnique(std::string&& str) {
    return UniquePtr(new std::string(std::move(str)));
}

// Глобальная Swap
void Swap(UniquePtr& lhs, UniquePtr& rhs) noexcept {
    lhs.Swap(rhs);
}