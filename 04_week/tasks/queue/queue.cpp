#include <vector>
#include <stack>
#include <initializer_list>
#include <algorithm>
#include <stdexcept>

class Queue {
private:
    mutable std::vector<int> input_stack;
    mutable std::vector<int> output_stack;
    
    void MoveInputToOutput() const;

public:
    Queue();
    Queue(std::stack<int> stack);
    Queue(const std::vector<int>& vec);
    Queue(std::initializer_list<int> init_list);
    explicit Queue(size_t size);
    
    void Push(int value);
    bool Pop();
    int& Front();
    const int& Front() const;
    int& Back();
    const int& Back() const;
    bool Empty() const;
    size_t Size() const;
    void Clear();
    void Swap(Queue& other);
    
    bool operator==(const Queue& other) const;
    bool operator!=(const Queue& other) const;
};

void Queue::MoveInputToOutput() const {
        while (!input_stack.empty()) {
            output_stack.push_back(input_stack.back());
            input_stack.pop_back();
        }
    }

Queue::Queue() = default;

Queue::Queue(std::stack<int> stack) {
    while (!stack.empty()) {
        input_stack.push_back(stack.top());
        stack.pop();
    }
    std::reverse(input_stack.begin(), input_stack.end());
}

Queue::Queue(const std::vector<int>& vec) : input_stack(vec) {}

Queue::Queue(std::initializer_list<int> init_list) : input_stack(init_list) {}

Queue::Queue(size_t size) {
    input_stack.reserve(size);
    output_stack.reserve(size);
}

void Queue::Push(int value) {
    input_stack.push_back(value);
}

bool Queue::Pop() {
    if (Empty()) {
        return false;
    }
    
    if (output_stack.empty()) {
        MoveInputToOutput();
    }
    
    output_stack.pop_back();
    return true;
}

int& Queue::Front() {    
    if (output_stack.empty()) {
        MoveInputToOutput();
    }
    
    return output_stack.back();
}

const int& Queue::Front() const {    
    if (output_stack.empty()) {
        Queue* mutable_this = const_cast<Queue*>(this);
        mutable_this->MoveInputToOutput();
    }
    
    return output_stack.back();
}

int& Queue::Back() {
    if (!input_stack.empty()) {
        return input_stack.back();
    }
    
    return output_stack.front();
}

const int& Queue::Back() const {    
    if (!input_stack.empty()) {
        return input_stack.back();
    }
    
    return output_stack.front();
}

bool Queue::Empty() const {
    return input_stack.empty() && output_stack.empty();
}

size_t Queue::Size() const {
    return input_stack.size() + output_stack.size();
}

void Queue::Clear() {
    input_stack.clear();
    output_stack.clear();
}

void Queue::Swap(Queue& other) {
    input_stack.swap(other.input_stack);
    output_stack.swap(other.output_stack);
}

bool Queue::operator==(const Queue& other) const {
    if (Size() != other.Size()) {
        return false;
    }
    
    Queue q1 = *this;
    Queue q2 = other;
    
    while (!q1.Empty()) {
        if (q1.Front() != q2.Front()) {
            return false;
        }
        q1.Pop();
        q2.Pop();
    }
    
    return true;
}

bool Queue::operator!=(const Queue& other) const {
    return !(*this == other);
}