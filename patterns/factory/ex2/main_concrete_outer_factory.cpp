
#include <iostream>
#include <math.h>

using namespace std;


enum class PointType {cartesian, polar};

class Point {
private:

    float m_x;
    float m_y;
    PointType m_type;

    // private constructor, so that object could not be created directly
    Point(const float x, const float y, PointType t) : m_x{x}, m_y{y}, m_type{t} {}

public:

    friend ostream &operator<<(ostream &os, const Point &obj) {
        return os << "x: " << obj.m_x << " y: " << obj.m_y;
    }
    static Point NewCartesian(float x, float y) {
        return {x, y, PointType::cartesian};
    }
    static Point NewPolar(float r ,float theta) {
        return {r * cos(theta), r * sin(theta), PointType::polar};
    }

    struct Factory {
        static Point NewCartesian(float x, float y) {
            return Point::NewCartesian(x, y);
        }
        static Point NewPolar(float r, float theta) {
            return Point::NewPolar(r, theta);
        }
    };
};

// CONCRETE FACTORY


int main() {
    auto p = Point::Factory::NewCartesian();
    return EXIT_SUCCESS;
}