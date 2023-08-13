#include "pch.h"
#include "CppUnitTest.h"
#include "Triangle.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public: 
		TEST_METHOD(TestEquilateralTriangle)
		{
			double precision = 1e-5;
			double precision_angle = 1e-2;
			double a = 0.67979863453453879808;
			const double c = 1e10;
			const double k = sqrt(2.);
			Point P1{ k * c, k * c };
			Point P2{ k * (c + a / 2.), k * (c + a / 2. / tan(std::numbers::pi / 6.)) };
			Point P3{ k * (c + a), k * c };
			Triangle triangle = Triangle(P1, P2, P3);

			Triangle::Type result = triangle.check_type(precision, precision_angle);

			Assert::AreEqual(static_cast<int>(Triangle::Type::Equilateral), static_cast<int>(result));
		}
		TEST_METHOD(TestIsoscelesAndRectangularTriangle)
		{
			double precision = 1e-10;
			double precision_angle = 1e-2;
			double side_length = 0.00320302032030203203020302323211223;
			const double c = 1e10;
			const double k = sqrt(2.);
			Point P1{ k * c, k * c };
			Point P2{ k * (c +side_length), k * c };
			Point P3{ k * c, k * (c + side_length) };
			Triangle triangle = Triangle(P1, P2, P3);

			Triangle::Type result = triangle.check_type(precision, precision_angle);

			Assert::AreEqual(static_cast<int>(Triangle::Type::IsoscelesAndRectangular), static_cast<int>(result));
		}
		TEST_METHOD(TestIsoscelesTriangle)
		{
			double precision = 1e-5;
			double precision_angle = 1e-2;
			double side_length = 5.0;
			Point P1{ 0, 0 };
			Point P2{ side_length, 0 };
			Point P3{ side_length / 2, side_length };
			Triangle triangle = Triangle(P1, P2, P3);

			Triangle::Type result = triangle.check_type(precision, precision_angle);

			Assert::AreEqual(static_cast<int>(Triangle::Type::Isosceles), static_cast<int>(result));
		}
		TEST_METHOD(TestRectangularTriangle)
		{
			double precision = 1e-5;
			double precision_angle = 1e-2;
			double side_length = 5.0;
			double a = 3.0;
			Point P1{ 0, 0 };
			Point P2{ side_length + a, 0 };
			Point P3{ 0, side_length };
			Triangle triangle = Triangle(P1, P2, P3);

			Triangle::Type result = triangle.check_type(precision, precision_angle);

			Assert::AreEqual(static_cast<int>(Triangle::Type::Rectangular), static_cast<int>(result));
		}
		TEST_METHOD(TestNotTriangle)
		{
			double precision = 1e-50;
			double precision_angle = 1e-2;
			double a = 1e30;
			double b = 1e-30;
			double c = sqrt(1.);
			double min = 0.32032302393939393939393933922222;
			Point P1{ c * min, c * min };
			Point P2{ a * min, c * min };
			Point P3{ b * min, c * min };
			Triangle triangle = Triangle(P1, P2, P3);

			Triangle::Type result = triangle.check_type(precision, precision_angle);

			Assert::AreEqual(static_cast<int>(Triangle::Type::NotTriangle), static_cast<int>(result));
		}
	};
}
