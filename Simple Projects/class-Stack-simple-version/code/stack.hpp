template <typename Type>
class stack {
private:
    Type value_;
    int size_ = 0;
    stack* prev_ = nullptr;
    stack* s = nullptr;
public:
    stack () = default; // default constructor
    stack (stack&& other) noexcept; // move constructor
    void push (Type x);
    void pop ();
    void clear ();
    [[nodiscard]] Type top () const;
    [[nodiscard]] int size () const;
    [[nodiscard]] bool empty () const;
};

#include "stack.cpp"