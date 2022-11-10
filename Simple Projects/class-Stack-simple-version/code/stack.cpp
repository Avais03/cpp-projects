// realization
template <typename Type>
stack<Type>::stack (stack&& other) noexcept : value_(other.value_), size_(other.size_), prev_(other.prev_), s(other.s) {}

template <typename Type>
void stack<Type>::push(Type x) {
    auto *n = new stack();
    n->value_ = x;
    n->prev_ = s;
    if (s == nullptr)
        n->size_ = 1;
    else
        n->size_ = s->size_ + 1;
    s = n;
}

template <typename Type>
void stack<Type>::pop() {
    stack *n = s->prev_;
    delete s;
    s = n;
}

template <typename Type>
[[nodiscard]] Type stack<Type>::top() const {
    return s->value_;
}

template <typename Type>
[[nodiscard]] bool stack<Type>::empty() const {
    if (s == nullptr)
        return true;
    else
        return false;
}

template <typename Type>
[[nodiscard]] int stack<Type>::size() const {
    if (s == nullptr)
        return 0;
    else
        return s->size_;
}

/// TODO !!! MEMORY LEAK !!!
template <typename Type>
void stack<Type>::clear() {
    s->size_ = 0;
    s->prev_ = nullptr;
    s = nullptr;
}