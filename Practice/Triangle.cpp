#include "Triangle.h"

bool equal(double a, double b, double precision)
{
    return abs(a - b) < precision;
}

double length(Point p1, Point p2)
{
    double l = sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
    return l;
}

Point get_valid_coordinates(const std::string& point_name)
{
    Point P;

    while (true)
    {
        std::cout << "Enter coordinates for " << point_name << " (x y): ";

        if (std::cin >> P.x >> P.y)
        {
            break;
        }
        else
        {
            std::cout << "Invalid input. Please enter numeric values." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return P;
}

Triangle::Triangle(Point p1, Point p2, Point p3)
{
    pnt1 = p1;
    pnt2 = p2;
    pnt3 = p3;
}

void Triangle::lengths_of_sides(double& side1, double& side2, double& side3) const
{
    side1 = length(pnt1, pnt2);
    side2 = length(pnt2, pnt3);
    side3 = length(pnt1, pnt3);
}

double Triangle::perimeter() const
{
    double side1 = 0;
    double side2 = 0;
    double side3 = 0;
    lengths_of_sides(side1, side2, side3);
    double p = side1 + side2 + side3;
    return p;
}

double Triangle::area() const
{
    double side1 = 0;
    double side2 = 0;
    double side3 = 0;
    lengths_of_sides(side1, side2, side3);
    double halfp = perimeter() / 2;
    double s = sqrt(halfp * (halfp - side1) * (halfp - side2) * (halfp - side3));
    return s;
}

double Triangle::angleA() const
{
    double side1 = 0;
    double side2 = 0;
    double side3 = 0;
    lengths_of_sides(side1, side2, side3);
    double C = acos((pow(side1, 2) + pow(side2, 2) - pow(side3, 2)) / (2 * side1 * side2));
    return C;
}

double Triangle::angleB() const
{
    double side1 = 0;
    double side2 = 0;
    double side3 = 0;
    lengths_of_sides(side1, side2, side3);
    double B = acos((pow(side1, 2) + pow(side3, 2) - pow(side2, 2)) / (2 * side1 * side3));
    return B;
}

double Triangle::angleC() const
{
    double side1 = 0;
    double side2 = 0;
    double side3 = 0;
    lengths_of_sides(side1, side2, side3);
    double A = acos((pow(side2, 2) + pow(side3, 2) - pow(side1, 2)) / (2 * side2 * side3));
    return A;
}

Triangle::Type Triangle::check_type(double precision, double precision_angle) const
{
    double side1 = 0;
    double side2 = 0;
    double side3 = 0;
    lengths_of_sides(side1, side2, side3);
    double A = angleA();
    double B = angleB();
    double C = angleC();
    double s = area();
    constexpr auto right_angle = std::numbers::pi / 2.;

    if (side1 + side2 <= side3 || side1 + side3 <= side2 || side2 + side3 <= side1)
    {
        return Type::NotTriangle;
    }
    else if (equal(side1, side2, precision) || equal(side2, side3, precision) || equal(side1, side3, precision))
    {
        if (equal(A, right_angle, precision_angle) || equal(B, right_angle, precision_angle) || equal(C, right_angle, precision_angle))
        {
            return Type::IsoscelesAndRectangular;
        }
        else if (equal(side1, side2, precision) && equal(side2, side3, precision))
        {
            return Type::Equilateral;
        }
        return Type::Isosceles;
    }
    else if (equal(A, right_angle, precision_angle) || equal(B, right_angle, precision_angle) || equal(C, right_angle, precision_angle))
    {
        return Type::Rectangular;
    }
    else
    {
        return Type::Unknown;
    }
}

Triangle Triangle::move(const Vector& vector) const
{
    Point new_pnt1 = { pnt1.x + vector.x, pnt1.y + vector.y };
    Point new_pnt2 = { pnt2.x + vector.x, pnt2.y + vector.y };
    Point new_pnt3 = { pnt3.x + vector.x, pnt3.y + vector.y };

    return Triangle(new_pnt1, new_pnt2, new_pnt3);
}

Point Triangle::rotate_point(const Point& point, const Point& rotation_point, double cos_angle, double sin_angle) const
{
    double new_x = cos_angle * (point.x - rotation_point.x) - sin_angle * (point.y - rotation_point.y) + rotation_point.x;
    double new_y = sin_angle * (point.x - rotation_point.x) + cos_angle * (point.y - rotation_point.y) + rotation_point.y;

    return Point(new_x, new_y);
}


Triangle Triangle::rotated(double angle, const Point& rotation_point) const
{
    Triangle rotated_triangle(*this);
    rotated_triangle.rotate(angle, rotation_point);
    return rotated_triangle;
}


void Triangle::rotate(double angle, const Point& rotation_point)
{
    double cos_angle = std::cos(angle);
    double sin_angle = std::sin(angle);

    pnt1 = rotate_point(pnt1, rotation_point, cos_angle, sin_angle);
    pnt2 = rotate_point(pnt2, rotation_point, cos_angle, sin_angle);
    pnt3 = rotate_point(pnt3, rotation_point, cos_angle, sin_angle);
}

void Triangle::mirror(const Point& vector)
{
    double v_x = vector.x;
    double v_y = vector.y;

    double matrix[2][2] = {
        {1 - 2 * v_x * v_x, -2 * v_x * v_y},
        {-2 * v_x * v_y, 1 - 2 * v_y * v_y}
    };

    pnt1 = mirror_point(pnt1, matrix);
    pnt2 = mirror_point(pnt2, matrix);
    pnt3 = mirror_point(pnt3, matrix);
}

Triangle Triangle::mirror(const Point& vector) const
{
    Triangle mirrored_triangle = *this;
    mirrored_triangle.mirror(vector);
    return mirrored_triangle;
}

Point Triangle::mirror_point(const Point& point, const double matrix[2][2]) const
{
    double new_x = matrix[0][0] * point.x + matrix[0][1] * point.y;
    double new_y = matrix[1][0] * point.x + matrix[1][1] * point.y;

    return Point(new_x, new_y);
}

Triangle Triangle::mirror_with_matrix(const double matrix[2][2]) const
{
    Point new_pnt1 = mirror_point(pnt1, matrix);
    Point new_pnt2 = mirror_point(pnt2, matrix);
    Point new_pnt3 = mirror_point(pnt3, matrix);

    return Triangle(new_pnt1, new_pnt2, new_pnt3);
}

