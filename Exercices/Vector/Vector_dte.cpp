#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <utility>

template <typename T>
class vector
{
public:
    auto push_back(const T& elem) -> void
    {
        if (m_capacity == 0)
        {
            m_array = new T[1];
            ++m_capacity;
        }

        else if (m_size == m_capacity)
        {
            auto* next = new T[2 * m_size];
            std::memcpy(next, m_array, sizeof(T) * m_size);
            delete[] m_array;

            m_array = next;
            m_capacity = 2 * m_capacity;
        }

        m_array[m_size] = elem;
        ++m_size;
    }

    auto size() const -> size_t { return m_size; };
    auto capacity() const -> size_t { return m_capacity; };

    auto operator[](size_t index) -> T& { return m_array[index]; };
    auto operator[](size_t index) const -> const T& { return m_array[index]; };

    ~vector() { delete[] m_array; };

private:
    size_t m_size = 0;
    size_t m_capacity = 0;
    T* m_array;
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
    // basics
    {
        auto v = vector<int>{};

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
        auto v = vector<int>{};
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
        auto v = vector<int>{};

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

        v.push_back(5);
        v.push_back(6);
        v.push_back(7);

        check_equal(v.size(), 8);
        check_equal(v.capacity(), 8);

        v.push_back(8);

        check_equal(v.size(), 9);
        check_equal(v.capacity(), 16);
    }

    std::cout << "✨ 👻 💖" << std::endl;
}