#include <vector>

template<typename Type>
class Deque {
public:
  Deque();
  Deque(size_t size);
  Deque(size_t size, const Type& value);
  Deque(const Deque& another);
  Deque& operator =(const Deque& another);
  [[nodiscard]] size_t size() const;
  Type& operator [](size_t pos);
  const Type& operator [](size_t pos) const;
  //
  Type& at(size_t pos);
  const Type& at(size_t pos) const;
  //
  void pop_back();
  void pop_front();
  //
  void push_back(const Type& value);
  void push_front(const Type& value);
  // iterators

  template<bool IsConst>
  struct common_iterator {
  public:
    // constructors
    common_iterator(size_t buffer_index,
                    size_t portion_index,
                    std::conditional_t<IsConst, const Type*, Type*> ptr,
                    const std::vector<Type*>* vector_of_pointers);
    common_iterator(size_t index, std::conditional_t<IsConst, const Deque&, Deque&> deque_);
    //
    common_iterator& operator ++();
    common_iterator& operator --();
    //
    common_iterator operator ++(int);
    common_iterator operator --(int);
    //
    common_iterator& operator +=(int x);
    common_iterator& operator -=(int x);
    //
    common_iterator operator +(int x);
    common_iterator operator -(int x);
    //
    int64_t operator -(const common_iterator& another) const;
    //
    bool operator ==(const common_iterator& another) const;
    bool operator !=(const common_iterator& another) const;
    bool operator <(const common_iterator& another) const;
    bool operator >(const common_iterator& another) const;
    bool operator <=(const common_iterator& another) const;
    bool operator >=(const common_iterator& another) const;
    //
    std::conditional_t<IsConst, const Type&, Type&> operator *() const;
    std::conditional_t<IsConst, const Type*, Type*> operator ->() const;
    //
    operator common_iterator<true>();

  private:
    friend class Deque;
    //
    const std::vector<Type*>* vector_of_pointers;
    size_t buffer_index;
    size_t portion_index;
    std::conditional_t<IsConst, const Type*, Type*> ptr;

  };
  // using
  using iterator = common_iterator<false>;
  using const_iterator = common_iterator<true>;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;
  //
  iterator begin();
  const_iterator begin() const;
  //
  iterator end();
  const_iterator end() const;
  //
  const_iterator cbegin() const;
  const_iterator cend() const;
  //
  reverse_iterator rbegin();
  reverse_iterator rend();
  //
  const_reverse_iterator crbegin() const;
  const_reverse_iterator crend() const;
  //
  void erase(iterator it);
  void insert(iterator it, const Type& value);
private:
  std::vector<Type*> buff;
  //
  static const size_t portion_size = 8;
  //
  size_t sz = 0;
  size_t sizeof_buffer = 0;
  size_t main_portion_ind = 0;
  size_t main_buf_ind = 0;
  //
  void resize(size_t new_sizeof_buffer);
  void swap(Deque& another);
  void push_back_helper(const Type& value);
  void push_front_helper(const Type& value);
};

// definitions of constructors and copy operator

template<typename Type>
Deque<Type>::Deque() {
  resize(1);
}

template<typename Type>
Deque<Type>::Deque(size_t size) {
  resize(size / portion_size + 1);
  for (size_t i = 0; i < size; ++i) {
    push_back(Type());
  }
}

template<typename Type>
Deque<Type>::Deque(const Deque& another) try : Deque() {
  for (size_t i = 0; i < another.sz; ++i) {
    push_back(another[i]);
  }
} catch (...) {
  throw;
}

template<typename Type>
Deque<Type>::Deque(size_t size, const Type& value) : Deque() {
  for (size_t i = 0; i < size; ++i) {
    push_back(value);
  }
}

template<typename Type>
Deque<Type>& Deque<Type>::operator =(const Deque<Type>& another) { //copy-and-swap idiom
  Deque deque_copy = another;
  swap(deque_copy);
  return *this;
}

// functions and operators definitions
template<typename Type>
size_t Deque<Type>::size() const {
  return sz;
}

template<typename Type>
Type& Deque<Type>::operator [](size_t pos) {
  return buff[main_buf_ind + (main_portion_ind + pos) / portion_size][(main_portion_ind + pos) % portion_size];
}

template<typename Type>
const Type& Deque<Type>::operator [](size_t pos) const {
  return buff[main_buf_ind + (main_portion_ind + pos) / portion_size][(main_portion_ind + pos) % portion_size];
}

template<typename Type>
Type& Deque<Type>::at(size_t pos) {
  if (pos < sz) {
    return buff[main_buf_ind + (main_portion_ind + pos) / portion_size][(main_portion_ind + pos) % portion_size];
  }
  throw std::out_of_range("...");
}

template<typename Type>
const Type& Deque<Type>::at(size_t pos) const {
  if (pos < sz)
    return buff[main_buf_ind + (main_portion_ind + pos) / portion_size][(main_portion_ind + pos) % portion_size];
  throw std::out_of_range(" caught ");
}

template<typename Type>
void Deque<Type>::push_front(const Type& value) {
  if (!(main_portion_ind || main_buf_ind)) {
    resize(sizeof_buffer * 3);
  }
  push_front_helper(value);
}

template<typename Type>
void Deque<Type>::push_front_helper(const Type& value) try {
  new(buff[main_buf_ind - (main_portion_ind == 0)] + (main_portion_ind - 1 + portion_size) % portion_size) Type(value);
  ++sz;
  main_buf_ind -= (main_portion_ind == 0);
  main_portion_ind = (main_portion_ind - 1 + portion_size) % portion_size;
} catch (...) {
  throw;
}

template<typename Type>
void Deque<Type>::push_back(const Type& value) {
  if (main_buf_ind + (main_portion_ind + sz) / portion_size == sizeof_buffer)
    resize(sizeof_buffer * 3);
  push_back_helper(value);
}

template<typename Type>
void Deque<Type>::push_back_helper(const Type& value) try {
  long long tmp_index1 = main_buf_ind + (main_portion_ind + sz) / portion_size;
  long long tmp_index2 = (main_portion_ind + sz) % portion_size;
  new(buff[tmp_index1] + tmp_index2) Type(value);
  ++sz;
} catch (...) {
  throw;
}

template<typename Type>
void Deque<Type>::insert(Deque::iterator it, const Type& value) {
  push_back(value);
  iterator it_ = end() - 1;
  iterator prev_it = it_ - 1;
  while (it_ > it) {
    std::swap(*it_, *(prev_it));
    --it_;
    --prev_it;
  }
}

template<typename Type>
void Deque<Type>::erase(Deque::iterator it) {
  iterator next_it = it;
  iterator it_ = next_it++;
  while (it_ < end()) {
    std::swap(*it_, *(next_it));
    ++it_;
    ++next_it;
  }
  pop_back();
}

template<typename Type>
void Deque<Type>::pop_back() {
  size_t tail_portion_ind = (main_portion_ind + sz) % portion_size;
  size_t tail_buf_ind = main_buf_ind + (main_portion_ind + sz) / portion_size;
  sz--;
  (buff[tail_buf_ind] + tail_portion_ind)->~Type();
}

template<typename Type>
void Deque<Type>::pop_front() {
  (buff[main_buf_ind] + main_portion_ind)->~Type();
  main_portion_ind = (main_portion_ind + 1) % portion_size;
  sz--;
  main_buf_ind += (main_portion_ind + 1) / portion_size;
}

// they give us security

// Private functions
template<typename Type>
void Deque<Type>::resize(size_t new_sizeof_buffer) {
  if (new_sizeof_buffer >= sizeof_buffer) {
    std::vector<Type*> tmp_buff;

    size_t new_main_buf_ind = (new_sizeof_buffer - sizeof_buffer) / 2;
    size_t tmp_buf_ind = new_main_buf_ind + sizeof_buffer;
    for (size_t i = 0; i < new_main_buf_ind; ++i) {
      tmp_buff.push_back(reinterpret_cast<Type*>(new int8_t[portion_size * sizeof(Type)]));
    }
    for (size_t i = 0; i < sizeof_buffer; ++i) {
      tmp_buff.push_back(buff[i]);
    }
    for (size_t i = tmp_buf_ind; i < new_sizeof_buffer; ++i) {
      tmp_buff.push_back(reinterpret_cast<Type*>(new int8_t[portion_size * sizeof(Type)]));
    }
    main_portion_ind = (main_portion_ind + new_main_buf_ind * portion_size) % portion_size;
    std::swap(buff, tmp_buff);
    sizeof_buffer = new_sizeof_buffer;
    main_buf_ind = new_main_buf_ind;
  }

}

template<typename Type>
void Deque<Type>::swap(Deque<Type>& another) {
  std::swap(another.main_portion_ind, main_portion_ind);
  std::swap(another.buff, buff);
  std::swap(another.sizeof_buffer, sizeof_buffer);
  std::swap(another.sz, sz);
  std::swap(another.main_buf_ind, main_buf_ind);
}

// definitions of iterator constructors and copy constructor

template<typename Type>
template<bool IsConst>
Deque<Type>::common_iterator<IsConst>::common_iterator(
  size_t buffer_index,
  size_t portion_index,
  std::conditional_t<IsConst, const Type*, Type*> ptr,
  const std::vector<Type*>* vector_of_pointers) : buffer_index(buffer_index),
                                                  portion_index(portion_index),
                                                  ptr(ptr),
                                                  vector_of_pointers(vector_of_pointers) {}

template<typename Type>
template<bool IsConst>
Deque<Type>::common_iterator<IsConst>::common_iterator(
  size_t index, std::conditional_t<IsConst, const Deque<Type>&, Deque<Type>&> deque_) {
  buffer_index = deque_.main_buf_ind + (deque_.main_portion_ind + index) / portion_size;
  portion_index = (deque_.main_portion_ind + index) % portion_size;
  ptr = deque_.buff[buffer_index] + portion_index;
  vector_of_pointers = &deque_.buff;
}

template<typename Type>
template<bool IsConst>
typename Deque<Type>::template common_iterator<IsConst>& Deque<Type>::common_iterator<IsConst>::operator ++() {
  ++portion_index;
  if (portion_index == portion_size) {
    ++buffer_index;
    ptr = (*vector_of_pointers)[buffer_index];
    portion_index = 0;
  } else {
    ++ptr;
  }
  return *this;
}

template<typename Type>
template<bool IsConst>
typename Deque<Type>::template common_iterator<IsConst> Deque<Type>::common_iterator<IsConst>::operator ++(int) {
  common_iterator copy = *this;
  ++*this;
  return copy;
}

template<typename Type>
template<bool IsConst>
typename Deque<Type>::template common_iterator<IsConst>& Deque<Type>::common_iterator<IsConst>::operator --() {
  if (portion_index != 0u) {
    --portion_index;
    --ptr;

  } else {
    --buffer_index;
    ptr = (*vector_of_pointers)[buffer_index] + portion_size - 1;
    portion_index = portion_size - 1;
  }
  return *this;
}

template<typename Type>
template<bool IsConst>
typename Deque<Type>::template common_iterator<IsConst> Deque<Type>::common_iterator<IsConst>::operator --(int) {
  common_iterator copy = *this;
  --*this;
  return copy;
}

template<typename Type>
template<bool IsConst>
typename Deque<Type>::template common_iterator<IsConst>& Deque<Type>::common_iterator<IsConst>::operator +=(int x) {
  size_t index = buffer_index * portion_size + portion_index + x;
  buffer_index = (index) / portion_size;
  portion_index = (index) % portion_size;
  ptr = (*vector_of_pointers)[buffer_index] + portion_index;
  return *this;
}

template<typename Type>
template<bool IsConst>
typename Deque<Type>::template common_iterator<IsConst>& Deque<Type>::common_iterator<IsConst>::operator -=(int x) {
  size_t index = buffer_index * portion_size + portion_index - x;
  buffer_index = (index) / portion_size;
  portion_index = (index) % portion_size;
  ptr = (*vector_of_pointers)[buffer_index] + portion_index;
  return *this;
}

template<typename Type>
template<bool IsConst>
typename Deque<Type>::template common_iterator<IsConst> Deque<Type>::common_iterator<IsConst>::operator +(int x) {
  common_iterator copy = *this;
  copy += x;
  return copy;
}

template<typename Type>
template<bool IsConst>
typename Deque<Type>::template common_iterator<IsConst> Deque<Type>::common_iterator<IsConst>::operator -(int x) {
  common_iterator copy = *this;
  copy -= x;
  return copy;
}

template<typename Type>
template<bool IsConst>
int64_t Deque<Type>::common_iterator<IsConst>::operator -(const common_iterator<IsConst>& another) const {
  size_t another_index = another.buffer_index * portion_size + another.portion_index;
  size_t index = buffer_index * portion_size + portion_index;
  return index - another_index;
}

template<typename Type>
template<bool IsConst>
bool Deque<Type>::common_iterator<IsConst>::operator ==(const common_iterator<IsConst>& another) const {
  return ptr == another.ptr;
}

template<typename Type>
template<bool IsConst>
bool Deque<Type>::common_iterator<IsConst>::operator <(const common_iterator<IsConst>& another) const {
  return buffer_index < another.buffer_index
    || (buffer_index == another.buffer_index && portion_index < another.portion_index);
}

template<typename Type>
template<bool IsConst>
bool Deque<Type>::common_iterator<IsConst>::operator >(const common_iterator<IsConst>& another) const {
  return another < *this;
}

template<typename Type>
template<bool IsConst>
bool Deque<Type>::common_iterator<IsConst>::operator !=(const common_iterator<IsConst>& another) const {
  return !(another == *this);
}

template<typename Type>
template<bool IsConst>
bool Deque<Type>::common_iterator<IsConst>::operator <=(const common_iterator<IsConst>& another) const {
  return another == *this || another > *this;
}

template<typename Type>
template<bool IsConst>
bool Deque<Type>::common_iterator<IsConst>::operator >=(const common_iterator<IsConst>& another) const {
  return another <= *this;
}
template<typename Type>
template<bool IsConst>
std::conditional_t<IsConst, const Type&, Type&> Deque<Type>::common_iterator<IsConst>::operator *() const {
  return *ptr;
}

template<typename Type>
template<bool IsConst>
std::conditional_t<IsConst, const Type*, Type*> Deque<Type>::common_iterator<IsConst>::operator ->() const {
  return ptr;
}

template<typename Type>
typename Deque<Type>::iterator Deque<Type>::begin() {
  return iterator(0, *this);
}

template<typename Type>
typename Deque<Type>::const_iterator Deque<Type>::begin() const {
  return const_iterator(0, *this);
}
template<typename Type>
typename Deque<Type>::iterator Deque<Type>::end() {
  return iterator(sz, *this);
}
template<typename Type>
typename Deque<Type>::const_iterator Deque<Type>::end() const {
  return const_iterator(sz, *this);
}
template<typename Type>
typename Deque<Type>::const_iterator Deque<Type>::cbegin() const {
  return const_iterator(0, *this);
}
template<typename Type>
typename Deque<Type>::const_iterator Deque<Type>::cend() const {
  return const_iterator(sz, *this);
}
template<typename Type>
typename Deque<Type>::reverse_iterator Deque<Type>::rbegin() {
  return std::make_reverse_iterator(end());
}
template<typename Type>
typename Deque<Type>::reverse_iterator Deque<Type>::rend() {
  return std::make_reverse_iterator(begin());
}
template<typename Type>
typename Deque<Type>::const_reverse_iterator Deque<Type>::crbegin() const {
  return std::make_reverse_iterator(cend());
}
template<typename Type>
typename Deque<Type>::const_reverse_iterator Deque<Type>::crend() const {
  return std::make_reverse_iterator(cbegin());
}

template<typename Type>
template<bool IsConst>
Deque<Type>::common_iterator<IsConst>::operator common_iterator<true>() {
  return common_iterator<true>(buffer_index, portion_index, ptr, vector_of_pointers);
}