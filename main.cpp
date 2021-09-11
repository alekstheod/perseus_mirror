#include <vector>
#include <algorithm>
#include <iostream>

template< typename From, typename To >
struct Transform;

template< typename T >
struct Transform< T, T > {
    const T& operator()(const T& v) const {
        return v;
    }
};

template< typename T, typename M, typename TFunc = Transform< T, M > >
struct Mirror {
    Mirror(T& v, M& m) : value{v}, mirror{m} {
    }

    Mirror(const Mirror& other) : value{other.value}, mirror{other.mirror} {
    }

    operator T&() {
        return value;
    }

    explicit operator M&() {
        return mirror;
    }

    Mirror& operator=(const Mirror& other) {
        value = other.value;
        mirror = other.value;
        return *this;
    }

    Mirror& operator=(const T& v) {
        value = v;
        mirror = TFunc{}(v);
        return *this;
    }

    Mirror& operator=(const M& v) {
        value = TFunc{}(v);
        mirror = v;
        return *this;
    }

  private:
    T& value;
    M& mirror;
};

struct TransformPosition {
    int operator()(const float& v) const {
        return v * 100;
    }

    float operator()(const int& v) const {
        return static_cast< float >(v) / 100;
    }
};

using PositionMirror = Mirror< float, int, TransformPosition >;

struct Position {
    PositionMirror x;
    PositionMirror y;
};

struct Object {
    float real_x;
    float real_y;
    int new_x;
    int new_y;
    Position position{{real_x, new_x}, {real_y, new_y}};
    PositionMirror x{position.x};
    PositionMirror y{position.y};
};

int main(int argc, char* argv[]) {
    Object obj;
    obj.position.x = 33.f;
    std::cout << obj.real_x << std::endl;
    std::cout << int(obj.position.x) << std::endl;
    std::cout << obj.x << std::endl;

    obj.x = 34.f;
    std::cout << obj.real_x << std::endl;
    std::cout << int(obj.position.x) << std::endl;
    std::cout << obj.x << std::endl;
    return 0;
}
