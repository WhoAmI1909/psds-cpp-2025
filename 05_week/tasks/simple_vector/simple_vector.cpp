#include <initializer_list>
#include <algorithm>
#include <cstddef>

class SimpleVector {
public:
    SimpleVector();
    explicit SimpleVector(size_t size);
    explicit SimpleVector(size_t size, int value);
    SimpleVector(std::initializer_list<int> init);
    SimpleVector(const SimpleVector& other);
    SimpleVector(SimpleVector&& other) noexcept;

    SimpleVector& operator=(const SimpleVector& other);
    SimpleVector& operator=(SimpleVector&& other) noexcept;

    ~SimpleVector();

    void Swap(SimpleVector& other) noexcept;

    int& operator[](size_t index);
    const int& operator[](size_t index) const;

    size_t Size() const;
    size_t Capacity() const;
    bool Empty() const;
    const int* Data() const;

    void PushBack(int value);
    void PopBack();

    int* Insert(const int* pos, int value);
    int* Erase(const int* pos);

    void Clear();
    void Resize(size_t new_size, int value = 0);
    void Reserve(size_t new_capacity);

    int* begin();
    int* end();
    const int* begin() const;
    const int* end() const;

private:
    int* data_;
    size_t size_;
    size_t capacity_;
};

SimpleVector::SimpleVector() 
    : data_(nullptr), size_(0), capacity_(0) {}

SimpleVector::SimpleVector(size_t size)
    : data_(new int[size]()), size_(size), capacity_(size) {}

SimpleVector::SimpleVector(size_t size, int value)
    : data_(new int[size]),
      size_(size),
      capacity_(size)
{
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = value;
    }
}

SimpleVector::SimpleVector(std::initializer_list<int> init)
    : data_(new int[init.size()]), size_(init.size()), capacity_(init.size()) {
    std::copy(init.begin(), init.end(), data_);
}

SimpleVector::SimpleVector(const SimpleVector& other)
    : data_(new int[other.capacity_]), 
      size_(other.size_), 
      capacity_(other.capacity_) {
    std::copy(other.data_, other.data_ + size_, data_);
}

SimpleVector::SimpleVector(SimpleVector&& other) noexcept
    : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

SimpleVector& SimpleVector::operator=(const SimpleVector& other) {
    if (this != &other) {
        SimpleVector tmp(other);
        Swap(tmp);
    }
    return *this;
}

SimpleVector& SimpleVector::operator=(SimpleVector&& other) noexcept {
    if (this != &other) {
        delete[] data_;
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    return *this;
}

SimpleVector::~SimpleVector() {
    delete[] data_;
}

void SimpleVector::Swap(SimpleVector& other) noexcept {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}

int& SimpleVector::operator[](size_t index) {
    return data_[index];
}

const int& SimpleVector::operator[](size_t index) const {
    return data_[index];
}

size_t SimpleVector::Size() const {
    return size_;
}

size_t SimpleVector::Capacity() const {
    return capacity_;
}

bool SimpleVector::Empty() const {
    return size_ == 0;
}

const int* SimpleVector::Data() const {
    return data_;
}

void SimpleVector::Reserve(size_t new_capacity) {
    if (new_capacity <= capacity_) return;

    int* new_data = new int[new_capacity];
    std::copy(data_, data_ + size_, new_data);

    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
}

void SimpleVector::PushBack(int value) {
    if (size_ == capacity_) {
        size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
        Reserve(new_capacity);
    }
    data_[size_++] = value;
}

void SimpleVector::PopBack() {
    if (size_ > 0) {
        --size_;
    }
}

int* SimpleVector::Insert(const int* pos, int value) {
    if (pos < data_ || pos > data_ + size_) {
        return data_ + size_;
    }

    size_t index = pos - data_;

    if (size_ == capacity_) {
        size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
        Reserve(new_capacity);
    }

    for (size_t i = size_; i > index; --i) {
        data_[i] = data_[i - 1];
    }

    data_[index] = value;
    ++size_;
    return data_ + index;
}

int* SimpleVector::Erase(const int* pos) {
    if (pos < data_ || pos >= data_ + size_)
        return data_ + size_;

    size_t index = pos - data_;

    for (size_t i = index; i + 1 < size_; ++i) {
        data_[i] = data_[i + 1];
    }

    --size_;

    return data_ + index;
}

void SimpleVector::Clear() {
    size_ = 0;
}

void SimpleVector::Resize(size_t new_size, int value) {
    if (new_size <= size_) {
        size_ = new_size;
        return;
    }

    if (new_size > capacity_) {
        Reserve(new_size);
    }

    for (size_t i = size_; i < new_size; ++i) {
        data_[i] = value;
    }

    size_ = new_size;
}

int* SimpleVector::begin() {
    return data_;
}

int* SimpleVector::end() {
    return data_ + size_;
}

const int* SimpleVector::begin() const {
    return data_;
}

const int* SimpleVector::end() const {
    return data_ + size_;
}

inline void swap(SimpleVector& lhs, SimpleVector& rhs) noexcept {
    lhs.Swap(rhs);
}

bool operator==(const SimpleVector& lhs, const SimpleVector& rhs) {
    if (lhs.Size() != rhs.Size())
        return false;
    
    for (size_t i = 0; i < lhs.Size(); ++i) {
        if (lhs[i] != rhs[i])
            return false;
    }
    
    return true;
}

bool operator!=(const SimpleVector& lhs, const SimpleVector& rhs) {
    return !(lhs == rhs);
}