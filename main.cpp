#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/draw_polygon_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Polygon_2<Kernel> Polygon;
typedef CGAL::Point_2<Kernel> Point;
typedef std::istream_iterator<Point> iterator;
typedef CGAL::Segment_2<Kernel> Segment;


bool is_left_of(Point a, Point b) {
    return a.x() < b.x();
};

bool is_right_of(Point a, Point b) {
    return a.x() > b.x();
};

bool is_above(Point p, Segment s) {
    return CGAL::left_turn(s[0], s[1], p);
}

bool is_below(Point p, Segment s) {
    return CGAL::right_turn(s[0], s[1], p);
}

struct LeftComparator {
    bool operator() (const Point& a,const Point& b) const {
        return is_left_of(a, b);
    };
};

struct RightComparator {
    bool operator() (const Point& a,const Point& b) const {
        return is_right_of(a, b);
    };
};


Polygon create_non_intersecting_polygon(std::istream_iterator<Point> begin, std::istream_iterator<Point> end) {
    //initialize points, leftmost and rightmost
    std::unordered_set<Point> points{};
    Point leftmost = *begin;
    Point rightmost = leftmost;

    for (; begin != end; begin++) {
        Point const current_point = *begin;
        points.insert(current_point);
        if (is_left_of(current_point, leftmost)) {
            leftmost = current_point;
        }

        if (is_right_of(current_point, rightmost)) {
            rightmost = current_point;
        }
    }
    points.erase(rightmost);
    points.erase(leftmost);

    Segment middle_line(leftmost, rightmost);

    std::set<Point, LeftComparator> a;
    std::set<Point, RightComparator> b;
    for (Point const point: points) {
        if (is_above(point, middle_line)) {
            a.insert(point);
        } else {
            b.insert(point);
        }
    }

    Polygon polygon;
    polygon.push_back(leftmost);
    for (Point point : a) {
        polygon.push_back(point);
    }
    polygon.push_back(rightmost);
    for (Point point : b) {
        polygon.push_back(point);
    }
    return polygon;
};


int main() {
    iterator const input_begin(std::cin);
    iterator const input_end;

    //Polygon nonIntersectingPolygon = create_non_intersecting_polygon(input_begin, input_end);
    Polygon polygon(input_begin, input_end);
    //CGAL::draw(nonIntersectingPolygon);
    CGAL::draw(polygon);

    return 0;
}
