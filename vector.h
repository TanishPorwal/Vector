#pragma once

#include <iostream>

template<typename T>
class vector
{
    using this_type = vector<T>;
public:
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using const_pointer = const T*;
    using const_reference = const T&;
    using iterator = T*;
    using const_iterator = const T*;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    using size_type = size_t;
    using difference_type = ptrdiff_t;

public:
    vector();
    vector(size_type size);
    vector(this_type& x);
    vector(this_type&& x) noexcept;
    vector(std::initializer_list<value_type> iList);

    template<typename InputIterator>
    vector(InputIterator first, InputIterator last);

    ~vector();

    this_type& operator=(const this_type& x);
    this_type& operator=(const this_type&& x) noexcept;
    this_type& operator=(std::initializer_list<value_type> iList);

    void swap(this_type& x);

    void assign(size_type n, const value_type& value);

    template<typename InputIterator>
    void assign(InputIterator first, InputIterator last, const value_type& value);
    void assign(std::initializer_list<value_type> iList);

    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;

    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;

    reverse_iterator rbegin() noexcept;
    const_reverse_iterator rbegin() const noexcept;
    const_reverse_iterator crbegin() const noexcept;

    reverse_iterator rend() noexcept;
    const_reverse_iterator rend() const noexcept;
    const_reverse_iterator crend() const noexcept;

    bool empty() const noexcept;
    size_type size() const noexcept;
    size_type capacity() const noexcept;

    void resize(size_type n, const value_type& value);
    void resize(size_type n);
    void reserve(size_type n);
    void shrink_to_fit();

    pointer data() noexcept;
    const_pointer data() const noexcept;

    reference operator[](size_type n);
    const_reference operator[](size_type n) const;

    reference at(size_type n);
    const_reference at(size_type n) const;

    reference front();
    const_reference front() const;

    reference back();
    const_reference back() const;

    void clear() noexcept;

    void push_back(const value_type& value);
    void push_back(value_type&& value);
    void pop_back();

    template<class... Args>
    reference emplace_back(Args&&... args);

private:
    T* m_Data = nullptr;
    size_type m_Size = 0, m_Capacity = 0;

    enum class method  { copy, move };

protected:
    void DoRealloc(const size_type& newCapacity);

    template<typename InputIterator>
    void DoInit(InputIterator first, InputIterator last);

    template<typename InputIterator>
    void DoInitFromIterator(InputIterator first, InputIterator last);

    void DoAssign(size_type n, const value_type& value);
    void DoAssign(size_type n, value_type&& value);

    template<typename InputIterator>
    void DoAssignFromIterator(InputIterator first, InputIterator last, method m);
};

template<typename T>
vector<T>::vector()
{ }

template<typename T>
vector<T>::vector(size_type size)
{
    DoRealloc(size);
}

template<typename T>
vector<T>::vector(this_type& x)
{
    DoRealloc(x.size());
    m_Size = x.size();
    DoAssignFromIterator(x.begin(), x.end(), method::copy);
}

template<typename T>
vector<T>::vector(this_type&& x) noexcept
{
    DoRealloc(x.size());
    m_Size = x.size();
    DoAssignFromIterator(x.begin(), x.end(), method::move);
    x.m_Size = 0;
    x.m_Capacity = 0;
    x.DoRealloc(0);
}

template<typename T>
vector<T>::vector(std::initializer_list<value_type> iList)
{
    DoRealloc(iList.size());
    DoInit(iList.begin(), iList.end());
}

template<typename T>
template<typename InputIterator>
vector<T>::vector(InputIterator first, InputIterator last)
{
    DoInit(first, last);
}

template<typename T>
vector<T>::~vector()
{
    delete[] m_Data;
}
template<typename T>
typename vector<T>::this_type& vector<T>::operator=(const this_type& x)
{
    DoRealloc(x.size());
    DoInit(x.begin(), x.end());
    return *this;
}

template<typename T>
typename vector<T>::this_type& vector<T>::operator=(const this_type&& x) noexcept
{
    DoRealloc(x.size());
    DoInit(x.begin(), x.end());
    return *this;
}

template<typename T>
typename vector<T>::this_type& vector<T>::operator=(std::initializer_list<value_type> iList)
{
    DoRealloc(iList.size());
    DoInit(iList.begin(), iList.end());
    return *this;
}

template<typename T>
void vector<T>::swap(this_type& x)
{
    if(x.m_Size > m_Size) DoRealloc(x.m_Size);
    else if(x.m_Size < m_Size) x.DoRealloc(m_Size);
    std::swap(m_Data, x.m_Data);
}

template<typename T>
typename vector<T>::size_type vector<T>::size() const noexcept
{
    return m_Size;
}

template<typename T>
typename vector<T>::size_type vector<T>::capacity() const noexcept
{
    return m_Capacity;
}

template<typename T>
typename vector<T>::reference vector<T>::operator[](size_type n)
{
    if(n > m_Size - 1) throw std::out_of_range("out of range");
    return m_Data[n];
}

template<typename T>
typename vector<T>::const_reference vector<T>::operator[](size_type n) const
{
    if(n > m_Size - 1) throw std::out_of_range("out of range");
    return m_Data[n];
}

template<typename T>
typename vector<T>::reference vector<T>::at(size_type n)
{
    if(n > m_Size - 1) throw std::out_of_range("out of range");
    return m_Data[n];
}

template<typename T>
typename vector<T>::const_reference vector<T>::at(size_type n) const
{
    if(n > m_Size - 1) throw std::out_of_range("out of range");
    return m_Data[n];
}

template<typename T>
typename vector<T>::reference vector<T>::front()
{
    return m_Data[0];
}

template<typename T>
typename vector<T>::const_reference vector<T>::front() const
{
    return m_Data[0];
}

template<typename T>
typename vector<T>::reference vector<T>::back()
{
    return m_Data[m_Size - 1];
}

template<typename T>
typename vector<T>::const_reference vector<T>::back() const
{
    return m_Data[m_Size - 1];
}

template<typename T>
void vector<T>::clear() noexcept
{
    for(size_type i = 0; i < m_Size; i++)
        m_Data[i].~T();
    m_Size = 0;
}

template<typename T>
void vector<T>::shrink_to_fit()
{
    DoRealloc(m_Size);
}


template<typename T>
typename vector<T>::pointer vector<T>::data() noexcept
{
    return m_Data;
}

template<typename T>
typename vector<T>::const_pointer vector<T>::data() const noexcept
{
    return m_Data;
}


template<typename T>
void vector<T>::assign(size_type n, const value_type& value)
{
    DoAssign(n, value);
}

template<typename T>
void vector<T>::assign(std::initializer_list<value_type> iList)
{
    DoInit(iList.begin(), iList.end());
}

template<typename T>
template<typename InputIterator>
void vector<T>::assign(InputIterator first, InputIterator last, const value_type& value)
{
    for(int i = 0; first != last; ++first, i++)
        m_Data[i] = value;
}

template<typename T>
bool vector<T>::empty() const noexcept
{
    return m_Data == nullptr;
}

template<typename T>
void vector<T>::push_back(const value_type& value)
{
    if(m_Size >= m_Capacity) DoRealloc(2 * m_Capacity);
    m_Data[m_Size++] = value;
}

template<typename T>
void vector<T>::push_back(value_type&& value)
{
    if(m_Size >= m_Capacity) DoRealloc(2 * m_Capacity);
    m_Data[m_Size++] = std::move(value);
}

template<typename T>
void vector<T>::pop_back()
{
    if(m_Size > 0)
    {
        m_Size--;
        m_Data[m_Size].~T();
    }
}

template<typename T>
template<class ... Args>
typename vector<T>::reference vector<T>::emplace_back(Args&&... args)
{
    if(m_Size > m_Capacity) DoRealloc(2 * m_Capacity);
    new(&m_Data[m_Size]) T(std::forward<Args>(args)...);
    return m_Data[m_Size++];
}

template<typename T>
void vector<T>::resize(size_type n)
{
    if(n < m_Size)
        for(size_type i = n - 1; i < m_Size; i++)
        {
            m_Data[i].~T();
            m_Size--;
        }
    else
    {
        DoRealloc(n);
        for(size_type i = m_Size; i < n; i++)
        {
            m_Data[i] = 0;
            m_Size++;
        }
    }
}

template<typename T>
void vector<T>::reserve(size_type n)
{
    if(n > m_Capacity)
        DoRealloc(n);
}

template<typename T>
void vector<T>::resize(size_type n, const value_type& value)
{
    if(n < m_Size)
        for(size_type i = n - 1; i < m_Size; i++)
        {
            m_Data[i].~T();
            m_Size--;
        }
    else
    {
        DoRealloc(n);
        for(size_type i = m_Size; i < n; i++)
        {
            m_Data[i] = value;
            m_Size++;
        }
    }
}

template<typename T>
typename vector<T>::iterator vector<T>::begin() noexcept
{
    return &m_Data[0];
}

template<typename T>
typename vector<T>::const_iterator vector<T>::begin() const noexcept
{
    return &m_Data[0];
}

template<typename T>
typename vector<T>::const_iterator vector<T>::cbegin() const noexcept
{
    return &m_Data[0];
}

template<typename T>
typename vector<T>::iterator vector<T>::end() noexcept
{
    return &m_Data[m_Size];
}

template<typename T>
typename vector<T>::const_iterator vector<T>::end() const noexcept
{
    return &m_Data[m_Size];
}

template<typename T>
typename vector<T>::const_iterator vector<T>::cend() const noexcept
{
    return &m_Data[m_Size];
}

template<typename T>
typename vector<T>::reverse_iterator vector<T>::rbegin() noexcept
{
    return reverse_iterator(&m_Data[m_Size]);
}

template<typename T>
typename vector<T>::const_reverse_iterator vector<T>::rbegin() const noexcept
{
    return const_reverse_iterator(&m_Data[m_Size]);
}

template<typename T>
typename vector<T>::const_reverse_iterator vector<T>::crbegin() const noexcept
{
    return const_reverse_iterator(&m_Data[m_Size]);
}

template<typename T>
typename vector<T>::reverse_iterator vector<T>::rend() noexcept
{
    return reverse_iterator(&m_Data[0]);
}

template<typename T>
typename vector<T>::const_reverse_iterator vector<T>::rend() const noexcept
{
    return const_reverse_iterator(&m_Data[0]);
}

template<typename T>
typename vector<T>::const_reverse_iterator vector<T>::crend() const noexcept
{
    return const_reverse_iterator(&m_Data[0]);
}

template<typename T>
void vector<T>::DoRealloc(const size_type& newCapacity)
{
    T* newBlock = new T[newCapacity];
    if(newCapacity < m_Size) m_Size = newCapacity;

    for(size_type i = 0; i < m_Size; i++) newBlock[i] = std::move(m_Data[i]);

    delete m_Data;
    m_Data = newBlock;
    m_Capacity = newCapacity;
}

template<typename T>
template<typename InputIterator>
void vector<T>::DoInit(InputIterator first, InputIterator last)
{
    DoInitFromIterator(first, last);
}

template<typename T>
template<typename InputIterator>
void vector<T>::DoInitFromIterator(InputIterator first, InputIterator last)
{
    for(; first != last; ++first) push_back(*first);
}

template<typename T>
void vector<T>::DoAssign(size_type n, const value_type& value)
{
    if(n > m_Size)
        DoRealloc(n);
    for(int i = 0; i < n; i++) m_Data[i] = value;
}

template<typename T>
void vector<T>::DoAssign(size_type n, value_type&& value)
{
    if(n > m_Size)
        DoRealloc(n);
    for(int i = 0; i < n; i++) m_Data[i] = std::move(value);
}

template<typename T>
template<typename InputIterator>
void vector<T>::DoAssignFromIterator(InputIterator first, InputIterator last, method m)
{
    for(int i = 0; first != last; ++first, i++)
        if(m == method::copy)
            m_Data[i] = *first;
        else
            m_Data[i] = std::move(*first);
}