// incomplete!


#include <vector>
#include <utility>
#include <cmath>
#include <algorithm>

struct Point {
    int x, y; // position on the map, measured in meters
};
struct Line {
    Point a, b;
};

constexpr double BOUNDARY_TOLERANCE = 0.01; // 1 cm

static bool approx_equals(Point a, Point b, double tolerance = BOUNDARY_TOLERANCE) {
    return std::fabs(a.x - b.x) < tolerance
        && std::fabs(a.y - b.y) < tolerance;
}

static inline std::vector<Point> calculate_rays(std::vector<Point>& path) {
    std::vector<Point> ret;

    // Invalid input
//    if (path.size() < 2)
//        return ret;

    ret.reserve(path.size());

    ret.emplace_back(Point {
        .x = path[0].x - path.back().x,
        .y = path[0].y - path.back().y,
    });
    for (size_t i = 0; i < ret.size(); i++)
        ret.emplace_back(Point {
            .x = path[i].x - path[i - 1].x,
            .y = path[i].y - path[i - 1].x,
        });

    return ret;
}

/// Cross product
static inline double cross(const Point& a, const Point& b) {
    return a.x * b.y - a.y * b.x;
}

static bool is_clockwise(const std::vector<Point>& path) {

    // Invalid input
//    if (path.size() < 2)
//        return false;

    // duplicate vertices/rays case: this will give 0, thus continuing to next
    for (size_t i = 1; i < path.size(); i++)
        if (cross(path[i - 1], path[i]) > BOUNDARY_TOLERANCE)
            return false;
    return cross(path.back(), path[0]) > BOUNDARY_TOLERANCE;
}

static bool is_point_on_line(const Point& point, const Point& line_a, const Point& line_b) {
    // Check co-linearity
    if (std::fabs(cross(line_a, line_b)) - std::fabs(cross(line_a, point)) > BOUNDARY_TOLERANCE)
        return false;

    // Make sure it falls in range
    return ((point.x <= line_a.x && point.x >= line_b.x) || (point.x >= line_a.x && point.x <= line_b.x))
        && ((point.y <= line_a.y && point.y >= line_b.y) || (point.y >= line_a.y && point.y <= line_b.y));
}

struct Boundary {
    std::vector<Point> m_border; // always clockwise

    /**
     * Break off a piece of this boundary
     * @param list of points for the cut-out
     * @note snaps to existing border with tolerance of 0.01 meters
     * @return new boundary
     */
    Boundary subdivide(std::vector<Point>&& border) {
        if (border.size() < 3) {
            throw "border must form a polygon";
        }

        auto a_rays = calculate_rays(m_border);
        auto b_rays = calculate_rays(border);

        // Make sure clockwise order
        if (!is_clockwise(calculate_rays(border))) {
            std::reverse(border.begin(), border.end());
            b_rays = calculate_rays(border);
        }

        // TODO something similar to Greiner–Hormann clipping algorithm
        for (size_t i = 1; i < m_border.size(); i++) {
            for (size_t j = 0; j < border.size(); j++) {

            }
        }

    }
};

