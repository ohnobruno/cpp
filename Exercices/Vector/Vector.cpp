// Make the tests pass
// run tests with: clang++ --std=c++1z vector.cpp && ./a.out

#include <iostream>

template <typename T>
class vector {
  public:
    auto push_back(const T& elem) -> void;

    auto size() -> size_t;
    auto capacity() -> size_t;

    auto operator[](size_t index) -> T&;
    auto operator[](size_t index) const -> const T&;

    ~vector();
};

auto check_equal = [](auto left, auto right) {
    if (left != right) {
        std::cout << "💥 💅\n";
        std::cout << left << " != " << right << '\n';
        std::exit(1);
    }
};

int main() {

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
        for (auto i = 0; i < iterations; ++i) {
            v.push_back(i);
        }

        for (auto i = 0; i < iterations; ++i) {
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
    }

    std::cout << "✨ 👻 💖" << std::endl;
}

