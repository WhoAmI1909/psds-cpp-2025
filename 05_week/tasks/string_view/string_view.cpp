#include <cstring>
#include <string>


class StringView {
    size_t size_;
    const char* data_;
public:
    static const size_t npos = static_cast<size_t>(-1);
    // Constructors
    StringView();   // Конструктор по умолчанию
    StringView(const std::string&, size_t = 0, size_t = npos);  // Конструктор от string, позиции начала подстроки (0), длины подстроки (npos)
    StringView(const char*);  // Конструктор от С-строки
    StringView(const char*, size_t);  // Конструктор от С-строки и длины
    // Methods
    const char* Data() const;
    const char& Front() const;
    const char& Back() const;
    size_t Size() const;
    size_t Length() const;
    bool Empty() const;
    void RemovePrefix(size_t) noexcept;
    void RemoveSuffix(size_t) noexcept;
    StringView Substr(size_t, size_t = npos) const;
    size_t Find(char, size_t = 0) const noexcept;
    size_t Find(const StringView&, size_t = 0) const noexcept;
    std::string ToString() const;
    // Operators
    const char& operator[](size_t) const noexcept;
};

const size_t StringView::npos;

StringView::StringView(): size_(0), data_(nullptr) {}

StringView::StringView(const std::string& str, size_t pos, size_t len) {
    if (pos > str.size()) {
        data_ = nullptr;
        size_ = 0;
        return;
    }

    size_ = std::min(len, str.size() - pos);
    data_ = str.data() + pos;
}

StringView::StringView(const char* cstr) {
    if (cstr == nullptr) {
        data_ = nullptr;
        size_ = 0;
    } else {
        data_ = cstr;
        size_ = std::strlen(cstr);
    }
}

StringView::StringView(const char* cstr, size_t len) {
    if (cstr == nullptr) {
        data_ = nullptr;
        size_ = 0;
    } else {
        size_ = std::min(len, std::strlen(cstr));
        data_ = cstr;
    }
}

// Methods
const char* StringView::Data() const {
    return data_;
}

const char& StringView::Front() const {
    return data_[0];
}

const char& StringView::Back() const {
    return data_[size_ - 1];
}

size_t StringView::Size() const {
    return size_;
}

size_t StringView::Length() const {
    return size_;
}

bool StringView::Empty() const {
    return size_ == 0;
}

void StringView::RemovePrefix(size_t n) noexcept {
    if (n >= size_) {
        data_ = nullptr;
        size_ = 0;
    } else {
        data_ += n;
        size_ -= n;
    }
}

void StringView::RemoveSuffix(size_t n) noexcept {
    if (n >= size_) {
        size_ = 0;
        data_ = nullptr;
    } else {
        size_ -= n;
    }
}


std::string StringView::ToString() const {
    return std::string(data_, size_);
}

StringView StringView::Substr(size_t pos, size_t len) const {
    if (pos > size_) {
        return StringView();
    }
    return StringView(data_ + pos, std::min(len, size_ - pos));
}

const char& StringView::operator[](size_t index) const noexcept {
    return data_[index];
}

size_t StringView::Find(char ch, size_t pos) const noexcept {
    if (pos >= size_) {
        return npos;
    }

    for (size_t i = pos; i < size_; ++i) {
        if (data_[i] == ch) {
            return i;
        }
    }
    return npos;
}

size_t StringView::Find(const StringView& sv, size_t pos) const noexcept {
    if (sv.size_ == 0) {
        return pos <= size_ ? pos : npos;
    }

    if (sv.size_ > size_ || pos >= size_) {
        return npos;
    }

    for (size_t i = pos; i + sv.size_ <= size_; ++i) {
        if (std::memcmp(data_ + i, sv.data_, sv.size_) == 0) {
            return i;
        }
    }

    return npos;
}