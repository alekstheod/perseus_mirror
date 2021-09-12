
#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_NO_CPP17_UNCAUGHT_EXCEPTIONS
#include "catch.hpp"

#include <mirror.hpp>

namespace {

    struct TransformPosition {
        int operator()(const float& v) const {
            return v * 100;
        }

        float operator()(const int& v) const {
            return static_cast< float >(v) / 100;
        }
    };

    using PositionMirror = perseus::Mirror< float, int, TransformPosition >;

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

    SCENARIO("Set mirror to deprecated and new object position", "[mirror]") {
        GIVEN("An object with a deprecated an new position variables") {
            Object obj;
            WHEN("The deprecated variable is set") {
                obj.x = 33.F;
                THEN("The new variable is updated") {
                    int value = obj.position.x;
                    REQUIRE(value == 3300);
                }
            }
            WHEN("The new variable is set") {
                obj.x = 33.F;
                THEN("The deprecated variable is updated")

                {
                    float value = obj.x;
                    REQUIRE(value == 33.F);
                }
            }
        }
    }

} // namespace
