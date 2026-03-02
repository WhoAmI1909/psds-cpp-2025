#include <string>
#include <utility>

class WeakPtr;

class SharedPtr {
private:
    struct ControlBlock {
        std::string* ptr;
        size_t shared_count;
        size_t weak_count;

        ControlBlock(std::string* p);
    };

    ControlBlock* control_;

    void Release();

public:
    SharedPtr();
    explicit SharedPtr(std::string* ptr);

    SharedPtr(const SharedPtr& other);
    SharedPtr(SharedPtr&& other) noexcept;

    SharedPtr& operator=(const SharedPtr& other);
    SharedPtr& operator=(SharedPtr&& other) noexcept;

    ~SharedPtr();

    std::string* Get() const;
    void Reset(std::string* ptr = nullptr);
    void Swap(SharedPtr& other) noexcept;
    size_t UseCount() const;

    std::string& operator*() const;
    std::string* operator->() const;
    explicit operator bool() const;

    friend class WeakPtr;
};

class WeakPtr {
private:
    SharedPtr::ControlBlock* control_;

    void Release();

public:
    WeakPtr();
    WeakPtr(const SharedPtr& shared);

    WeakPtr(const WeakPtr& other);
    WeakPtr(WeakPtr&& other) noexcept;

    WeakPtr& operator=(const WeakPtr& other);
    WeakPtr& operator=(WeakPtr&& other) noexcept;

    ~WeakPtr();

    void Reset();
    void Swap(WeakPtr& other) noexcept;

    size_t UseCount() const;
    bool Expired() const;
    SharedPtr Lock() const;
};

// ControlBlock

SharedPtr::ControlBlock::ControlBlock(std::string* p)
    : ptr(p), shared_count(1), weak_count(0) {}

// SharedPtr

SharedPtr::SharedPtr() : control_(nullptr) {}

SharedPtr::SharedPtr(std::string* ptr) {
    if (ptr)
        control_ = new ControlBlock(ptr);
    else
        control_ = nullptr;
}

SharedPtr::SharedPtr(const SharedPtr& other)
    : control_(other.control_) {
    if (control_)
        ++control_->shared_count;
}

SharedPtr::SharedPtr(SharedPtr&& other) noexcept
    : control_(other.control_) {
    other.control_ = nullptr;
}

SharedPtr& SharedPtr::operator=(const SharedPtr& other) {
    if (this != &other) {
        Release();
        control_ = other.control_;
        if (control_)
            ++control_->shared_count;
    }
    return *this;
}

SharedPtr& SharedPtr::operator=(SharedPtr&& other) noexcept {
    if (this != &other) {
        Release();
        control_ = other.control_;
        other.control_ = nullptr;
    }
    return *this;
}

void SharedPtr::Release() {
    if (!control_)
        return;

    --control_->shared_count;

    if (control_->shared_count == 0) {
        delete control_->ptr;
        control_->ptr = nullptr;

        if (control_->weak_count == 0) {
            delete control_;
        }
    }

    control_ = nullptr;
}

SharedPtr::~SharedPtr() {
    Release();
}

std::string* SharedPtr::Get() const {
    return control_ ? control_->ptr : nullptr;
}

void SharedPtr::Reset(std::string* ptr) {
    Release();
    if (ptr)
        control_ = new ControlBlock(ptr);
}

void SharedPtr::Swap(SharedPtr& other) noexcept {
    std::swap(control_, other.control_);
}

size_t SharedPtr::UseCount() const {
    return control_ ? control_->shared_count : 0;
}

std::string& SharedPtr::operator*() const {
    return *control_->ptr;
}

std::string* SharedPtr::operator->() const {
    return control_->ptr;
}

SharedPtr::operator bool() const {
    return Get() != nullptr;
}

// WeakPtr

WeakPtr::WeakPtr() : control_(nullptr) {}

WeakPtr::WeakPtr(const SharedPtr& shared)
    : control_(shared.control_) {
    if (control_)
        ++control_->weak_count;
}

WeakPtr::WeakPtr(const WeakPtr& other)
    : control_(other.control_) {
    if (control_)
        ++control_->weak_count;
}

WeakPtr::WeakPtr(WeakPtr&& other) noexcept
    : control_(other.control_) {
    other.control_ = nullptr;
}

WeakPtr& WeakPtr::operator=(const WeakPtr& other) {
    if (this != &other) {
        Release();
        control_ = other.control_;
        if (control_)
            ++control_->weak_count;
    }
    return *this;
}

WeakPtr& WeakPtr::operator=(WeakPtr&& other) noexcept {
    if (this != &other) {
        Release();
        control_ = other.control_;
        other.control_ = nullptr;
    }
    return *this;
}

void WeakPtr::Release() {
    if (!control_)
        return;

    --control_->weak_count;

    if (control_->shared_count == 0 &&
        control_->weak_count == 0) {
        delete control_;
    }

    control_ = nullptr;
}

WeakPtr::~WeakPtr() {
    Release();
}

void WeakPtr::Reset() {
    Release();
}

void WeakPtr::Swap(WeakPtr& other) noexcept {
    std::swap(control_, other.control_);
}

size_t WeakPtr::UseCount() const {
    return control_ ? control_->shared_count : 0;
}

bool WeakPtr::Expired() const {
    return !control_ || control_->shared_count == 0;
}

SharedPtr WeakPtr::Lock() const {
    if (Expired())
        return SharedPtr();

    SharedPtr result;
    result.control_ = control_;
    ++control_->shared_count;
    return result;
}

// MakeShared функции

SharedPtr MakeShared(const std::string& str) {
    return SharedPtr(new std::string(str));
}

SharedPtr MakeShared(std::string&& str) {
    return SharedPtr(new std::string(std::move(str)));
}

// Swap функции
void Swap(SharedPtr& lhs, SharedPtr& rhs) noexcept {
    lhs.Swap(rhs);
}

void Swap(WeakPtr& lhs, WeakPtr& rhs) noexcept {
    lhs.Swap(rhs);
}