// Make the tests pass
// run tests with: clang++ --std=c++1z vector.cpp && ./a.out

#include <iostream>
using namespace std;

template <typename T>
class myVector
{
public:
    myVector()
    : m_size(0)
    , m_capacity(0)
    , m_container(nullptr)
    {
    }

    ~myVector()
    {
        delete[] m_container;
        cout << " /// Vector destructed \\\\\\\n";
    }

    void print()
    {
        cout << "\n===Vector=== ";
        cout << "\nSize: " << m_size;
        cout << " | Capacity: " << m_capacity;
        cout << "\nValues: \n";
        for (int i = 0; i < m_size; i++)
        {
            cout << i << ": " << m_container[i] << "\n";
        }
    }

    const size_t size() { return m_size; }

    const size_t capacity() { return m_capacity; }

    void push_back(const T& n)
    {
        if (m_capacity == 0)
        {
            ++m_capacity;
            m_container = new T[m_capacity];
        }
        else if (m_size >= m_capacity)
        {
            m_capacity *= 2;
            resize_container();
        }
        m_container[m_size] = n;
        ++m_size;
    }

    T& operator[](size_t index) { return m_container[index]; }

    const T& operator[](size_t index) const { return m_container[index]; }

private:
    size_t m_size;
    size_t m_capacity;
    T* m_container;

    void resize_container()
    {
        T* new_container = new T[m_capacity];
        memcpy(new_container, m_container, m_size * sizeof(T));
        delete[] m_container;
        m_container = new_container;
    }
};

auto check_equal = [](auto left, auto right) {
    if (left != right)
    {
        std::cout << "💥 💅\n";
        std::cout << left << " != " << right << '\n';
        std::exit(1);
    }
};

int main()
{
    {
        auto v = myVector<int>{};
        v.print();

        check_equal(v.size(), 0);
        check_equal(v.capacity(), 0);

        int nb_push = 9;
        for (int i = 1; i <= nb_push; i++)
        {
            v.push_back(i);
            v.print();
        }
    }
    // STRING
    {
        string s = "hiiieeeeee";
        auto v = myVector<string>{};
        v.print();
        check_equal(v.size(), 0);
        check_equal(v.capacity(), 0);
        v.push_back(s);
        v.print();
    }

    // basics
    {
        cout << "\n======TEST======\n";
        auto v = myVector<int>{};

        check_equal(v.size(), 0);
        check_equal(v.capacity(), 0);

        v.push_back(1);

        check_equal(v[0], 1);
        check_equal(v.size(), 1);
        check_equal(v.capacity(), 1);
    }

    // add many elements
    {
        constexpr auto iterations = 10'000;
        auto v = myVector<int>{};
        for (auto i = 0; i < iterations; ++i)
        {
            v.push_back(i);
        }

        for (auto i = 0; i < iterations; ++i)
        {
            check_equal(v[i], i);
        }
    }

    // capacity increases exponentially
    {
        auto v = myVector<int>{};

        check_equal(v.size(), 0);
        check_equal(v.capacity(), 0);

        v.push_back(0);

        check_equal(v.size(), 1);
        check_equal(v.capacity(), 1);

        v.push_back(1);

        check_equal(v.size(), 2);
        check_equal(v.capacity(), 2);

        v.push_back(2);

        check_equal(v.size(), 3);
        check_equal(v.capacity(), 4);

        v.push_back(3);

        check_equal(v.size(), 4);
        check_equal(v.capacity(), 4);

        v.push_back(4);

        check_equal(v.size(), 5);
        check_equal(v.capacity(), 8);
    }

    std::cout << "✨ 👻 💖" << std::endl;
}