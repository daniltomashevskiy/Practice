#pragma once

#include <cmath>
#include <string>
#include <fstream>
#include <numbers>
#include <iostream>
#include <vector>

// Функция для сравнения двух чисел с заданной точностью.
static bool equal(double a, double b, double precision);

// Структура Point для представления точек в двумерном пространстве.
struct Point
{
    double x;
    double y;
};

// Структура Vector для представления вектора в двумерном пространстве.
struct Vector
{
    double x;
    double y;
};

// Функция для вычисления расстояния между двумя точками.
double length(Point p1, Point p2);

// Функция для получения корректных координат точки.
Point get_valid_coordinates(const std::string& point_name);

class Triangle
{
public:

    // Перечисление Type для определения типов треугольников.
    enum Type
    {
        NotTriangle, // Не треугольник.
        Unknown, // Треугольник общего вида. 
        Rectangular, // Прямоугольный треугольник.
        Isosceles, // Равнобедренный треугольник.
        Equilateral, // Равносторонний треугольник.
        IsoscelesAndRectangular, // Равнобедренный и прямоугольный треугольник.
    };

    Triangle() = default;

    // Конструктор класса для инициализации треугольника по трем точкам.
    Triangle(Point p1, Point p2, Point p3);

    // Метод для вычисления длин сторон треугольника.
    void lengths_of_sides(double& side1, double& side2, double& side3) const;

    // Метод для вычисления периметра треугольника.
    double perimeter() const;

    // Метод для вычисления площади треугольника.
    double area() const;

    //
    //                       B
    //                      /\
    //                     /  \
    //                    /    \
    //                   /      \
    //                  /        \ 
    //                 /__________\  
    //               A              C
    //
    // Методы для вычисления углов треугольника (в радианах).
    double angleA() const;
    double angleB() const;
    double angleC() const;

    // Метод для проверки типа треугольника.
    Type check_type(double precision, double precision_angle) const;

    // Метод для перемещения треугольника на заданный вектор.
    Triangle move(const Vector& vector) const;

    //
    Point rotate_point(const Point& point, const Point& rotation_point, double cos_angle, double sin_angle) const;

    //
    Triangle rotated(double angle, const Point& rotation_point) const;

    //
    void rotate(double angle, const Point& rotation_point);

    //
    Point get_point1() const { return pnt1; }
    Point get_point2() const { return pnt2; }
    Point get_point3() const { return pnt3; }

    //
    void mirror(const Point& vector);

    //
    Triangle mirror(const Point& vector) const;

    //
    Point mirror_point(const Point& point, const double matrix[2][2]) const;

    //
    Triangle mirror_with_matrix(const double matrix[2][2]) const;

private:
    Point pnt1;
    Point pnt2;
    Point pnt3;
};