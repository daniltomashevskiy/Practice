// Создать класс треугольник, который будет инициализироваться по 3 точкам в 2д. У этого класса методы возвращают длинны сторон, 
// величини углов, P, S, проверяют являеться ли треугольник равнобедренным, равносторонним, прямоугольным.

// Добавить различные команды:
// - решить треугольник,
// - вывести координаты точек,
// - переместить треугольник на заданный вектор,
// - повернуть тругольник на заданный угол относительно заданной точки,
// - отзеркалить треугольник относительно заданной оси (вектора).

#include "Triangle.h"
#include "Configuration.h"

int main()
{

    Configuration Configuration("config.json");

    if (!Configuration.read_config())
    {
        return 1;
    }

    double precision = Configuration.get_precision();
    double precision_angle = Configuration.get_precision_angle();

    char user_choice = 'y';
    do 
    {
        double mirror_matrix[2][2] = {
        {-1, 0},
        {0, 1}
        };

        Point P1 = get_valid_coordinates("Point A");
        Point P2 = get_valid_coordinates("Point B");
        Point P3 = get_valid_coordinates("Point C");
    
        const Triangle triangle = Triangle(P1, P2, P3);
        Triangle mmirrored_triangle = triangle.mirror_with_matrix(mirror_matrix);

        Vector vector_to_move;
        std::cout << "Enter the x and y coordinates of the vector: ";
        std::cin >> vector_to_move.x >> vector_to_move.y;

        const Triangle moved_triangle = triangle.move(vector_to_move);

        double angle_degrees;
        std::cout << "Enter the angle (in degrees) to rotate the triangle: ";
        std::cin >> angle_degrees;

        double angle_radians = angle_degrees * std::numbers::pi / 180.0;

        Point rotation_point = get_valid_coordinates("Rotation Point");
        Point mirror_vector;
        std::cout << "Enter the x and y coordinates of the mirror vector: ";
        std::cin >> mirror_vector.x >> mirror_vector.y;

        Triangle rotated_triangle = triangle.rotated(angle_radians, rotation_point);

        Triangle mirrored_triangle = triangle.mirror(mirror_vector);

        double side1 = 0;
        double side2 = 0;
        double side3 = 0;
        triangle.lengths_of_sides(side1, side2, side3);
        double A = triangle.angleA();
        double B = triangle.angleB();
        double C = triangle.angleC();
        double p = triangle.perimeter();
        double s = triangle.area();

        Triangle::Type type = triangle.check_type(precision, precision_angle);

        std::cout << "Side lengths: \n\tAB = " << side1 << "\n\tBC = " << side2 << "\n\tAC = " << side3 << std::endl;
        std::cout << "Angles:\n\tABC = " << A << ", " << A * 180 / std::numbers::pi << "\n\tBAC = " << B << ", " << (B * 180 / std::numbers::pi) << "\n\tACB = " << C << ", " << (C * 180 / std::numbers::pi) << std::endl;
        std::cout << "Perimeter: " << p << std::endl;
        std::cout << "Area: " << s << std::endl;

        std::cout << "Coordinates of the moved triangle:" << std::endl;
        Point moved_p1 = moved_triangle.get_point1();
        Point moved_p2 = moved_triangle.get_point2();
        Point moved_p3 = moved_triangle.get_point3();
        std::cout << "Point A: (" << moved_p1.x << ", " << moved_p1.y << ")" << std::endl;
        std::cout << "Point B: (" << moved_p2.x << ", " << moved_p2.y << ")" << std::endl;
        std::cout << "Point C: (" << moved_p3.x << ", " << moved_p3.y << ")" << std::endl;

        std::cout << "Coordinates of the rotated triangle:" << std::endl;
        Point rotated_p1 = rotated_triangle.get_point1();
        Point rotated_p2 = rotated_triangle.get_point2();
        Point rotated_p3 = rotated_triangle.get_point3();
        std::cout << "Point A: (" << rotated_p1.x << ", " << rotated_p1.y << ")" << std::endl;
        std::cout << "Point B: (" << rotated_p2.x << ", " << rotated_p2.y << ")" << std::endl;
        std::cout << "Point C: (" << rotated_p3.x << ", " << rotated_p3.y << ")" << std::endl;

        std::cout << "Coordinates of the mirrored triangle:" << std::endl;
        Point mirrored_p1 = mirrored_triangle.get_point1();
        Point mirrored_p2 = mirrored_triangle.get_point2();
        Point mirrored_p3 = mirrored_triangle.get_point3();
        std::cout << "Point A (Mirrored): (" << mirrored_p1.x << ", " << mirrored_p1.y << ")" << std::endl;
        std::cout << "Point B (Mirrored): (" << mirrored_p2.x << ", " << mirrored_p2.y << ")" << std::endl;
        std::cout << "Point C (Mirrored): (" << mirrored_p3.x << ", " << mirrored_p3.y << ")" << std::endl;

        std::cout << "Coordinates of the mirrored triangle:" << std::endl;
        Point mmirrored_p1 = mmirrored_triangle.get_point1();
        Point mmirrored_p2 = mmirrored_triangle.get_point2();
        Point mmirrored_p3 = mmirrored_triangle.get_point3();
        std::cout << "Point A (Mirrored): (" << mmirrored_p1.x << ", " << mmirrored_p1.y << ")" << std::endl;
        std::cout << "Point B (Mirrored): (" << mmirrored_p2.x << ", " << mmirrored_p2.y << ")" << std::endl;
        std::cout << "Point C (Mirrored): (" << mmirrored_p3.x << ", " << mmirrored_p3.y << ")" << std::endl;

        switch (type)
        {
        case Triangle::NotTriangle:
            std::cout << "This is not triangle." << std::endl;
            break;
        case Triangle::Equilateral:
            std::cout << "Triangle is Equilateral." << std::endl;
            break;
        case Triangle::Isosceles:
            std::cout << "Triangle is Isosceles." << std::endl;
            break;
        case Triangle::Rectangular:
            std::cout << "Triangle is Rectangular." << std::endl;
            break;
        case Triangle::IsoscelesAndRectangular:
            std::cout << "Triangle is Isosceles and Rectangular." << std::endl;
            break;
        case Triangle::Unknown:
            std::cout << "Triangle is of unknown type." << std::endl;
            break;
        }
        std::cout << "Do you want to continue? (Enter 'Y' to continue or 'N' to quit): ";
        std::cin >> user_choice;
        user_choice = std::tolower(user_choice);

        while (user_choice != 'y' && user_choice != 'n') {
            std::cout << "Invalid input. Please enter 'Y' to continue or 'N' to quit: ";
            std::cin >> user_choice;
            user_choice = std::tolower(user_choice);
        }
    } while (user_choice == 'y');

    std::cout << "Exiting the program." << std::endl;
    return 0;
}