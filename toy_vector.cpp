#include <iostream>
#include <stdexcept>
#include <initializer_list>

// Toy Vector Class - Move Semantics

template <typename T>
class Vector
{
private:
    int capacity_;
    int size_;
    T *ptr_;

public:

    // Constructors

    Vector() : capacity_{0}, size_{0}, ptr_{nullptr} { std::cout << "\tctor: Vector() {}\n";}
    Vector(int size) : capacity_{size}, size_{size}, ptr_{new T[size]} { std::cout << "\tctor: Vector(int size) {} | Mem Alloc: ptr_ { new T[size] }\n";}
    Vector(int size, T data) : Vector(size) // ctor constructs vector of size_{size} & initializes all elements as data
    {
        std::cout << "\tctor: Vector(int size, T data) {}\n";

        for (int i{ 0 }; i < size; ++i)
        {
            ptr_[i] = data;
        }
    }

    Vector(std::initializer_list<T> list) : capacity_{static_cast<int>(list.size())}, size_{0}, ptr_{new T[list.size()]} // ctor using initializer_list
    {
        std::cout << "\tctor: Vector(std::initializer_list<T> list) {}\n";
        std::cout << "\t  Mem Alloc: ptr_ = new T[capacity_]\n";
        
        for (const T &elem : list)
        {
            push_back(elem);
        }
    }

    ~Vector()
    {
        std::cout << "\ndestructor: ~Vector() {}\n";

        clear();
    }

    // Copy constructor

    Vector(const Vector& v)
    {
        std::cout << "\tcopy ctor: Vector(const Vector& v) {}\n";

        if (this == &v)
        {
            return;
        }

        capacity_ = v.capacity_;
        size_ = v.size_;
        std::cout << "\t  Mem Alloc: ptr_ = new T[v.size_]\n";
        ptr_ = new T[v.size_];

        for (int i{ 0 }; i < v.size_; i++)
        {
            ptr_[i] = v.ptr_[i];
        }
    }

    // Copy assignment operator

    Vector<T>& operator=(const Vector<T>& v)
    {
        std::cout << "\tcopy-assignment= ctor: Vector<T>& operator=(const Vector<T>& v) {}\n";

        if (this != &v) // Check memory address (if they are the same or not)
        {
            delete[] ptr_;
            ptr_ = nullptr;

            capacity_ = v.capacity_;
            size_ = v.size_;

            std::cout << "\t  Mem Alloc: ptr_ = new T[v.size_]\n";
            ptr_ = new T[v.size_];

            for (int i{ 0 }; i < v.size_; i++)
            {
                ptr_[i] = v.ptr_[i];
            }
        }

        return *this;
    }

    // Methods

    T& operator[](int i)
    {
        std::cout << "\tT& operator[](int j) {}\n";

        if (i >= 0 && i < size_)
            return ptr_[i];
        else
            throw std::out_of_range("Index out of bounds");
    }

    T& operator[](int i) const
    {
    
        std::cout << "\tT& operator[](int j) const {}\n";

        if (i >= 0 && i < size_)
            return ptr_[i];
        else
            throw std::out_of_range("Index out of bounds");
    }

    void reserve(int size)
    {
        std::cout << "  reserve(int size) {}\n";
        if (size_ < capacity_) return;

        if (ptr_ == nullptr)
        {
            size_ = 0;
            capacity_ = 0;
        }

        std::cout << "\t  Mem Alloc: T* bufferNew = new T[size]\n";
        T* bufferNew = new T[size];
        unsigned int l_size = std::min(capacity_, size);
        for (unsigned int i{ 0 }; i < l_size; i++)
        {
            bufferNew[i] = ptr_[i];
        }

        if (ptr_ != nullptr)
            delete[] ptr_;
        
        ptr_ = bufferNew;
        capacity_ = size;
    }

    void clear()
    {
        if (ptr_ != nullptr)
        {
            delete[] ptr_;
        }

        ptr_ = nullptr;
        size_ = 0;
        capacity_ = 0;
    }

    int size() const
    {
        return size_;
    }

    void push_back(const T &elem)
    {
        if (size_ >= capacity_)
        {
            reserve(capacity_ + 5);
        }

        ptr_[size_++] = elem;
    }

    void pop_back()
    {
        --size_;
    }

    T front()
    {
        if (size_ > 0)
            return ptr_[0];
        else
            throw std::out_of_range("Index out of bounds");
    }

    T back()
    {
        if (size > 0)
            return ptr_[size_ - 1];
        else
            throw std::out_of_range("Index out of bounds");
    }

};


template <typename T>
Vector<T> operator+(const Vector<T> &v1, const Vector<T> &v2)
{
    if (v1.size() != v2.size())
        throw std::logic_error("Vector Lengths must be equal.");

    Vector<T> result;
    for (int i{0}; i < v1.size(); i++)
    {
        result.push_back(v1[i] + v2[i]);
    }

    return result;
}

Vector<Vector<double>> createAndInsert()
{
    std::cout << "Vector<Vector<double>> createAndInsert() {}";
    std::cout << "\nVector<Vector<double>> pts\n";
    Vector<Vector<double>> pts;
    std::cout << "\npts.reserve(3)\n";
    // Within pts.reserve(3) call - ctor: Vector() {} called thrice because Vector<Vector<double>>
    pts.reserve(3);
    std::cout << "\nVector<double> x{ 1.0, 2.0 }\n";
    Vector<double> x{ 1.0, 2.0 };
    std::cout << "\npts.push_back(x)\n";
    pts.push_back(x);
    std::cout << "\npts.push_back(x + x)\n";
    pts.push_back(x + x);
    std::cout << "\npts.push_back(x)\n";
    pts.push_back(x);
    
    return pts;

}


int main()
{
    Vector<Vector<double>> result = createAndInsert();
    return 0;
}
