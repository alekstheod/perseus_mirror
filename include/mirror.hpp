#pragma once

namespace perseus {
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

        operator M&() {
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
} // namespace perseus
