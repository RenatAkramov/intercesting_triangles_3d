#include "../include/main.hpp"

// Тест 1: Два пересекающихся треугольника
TEST(TriangleIntersectionTest, TwoIntersectingTriangles) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 1, 0, 0, 0, 1, 0, 1),
        Triangle(0, 0, 0, 0, 1, 0, 0, 0, 1, 2)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
    EXPECT_NE(std::find(result.begin(), result.end(), 1), result.end());
    EXPECT_NE(std::find(result.begin(), result.end(), 2), result.end());
}

// Тест 2: Три треугольника, два пересекаются
TEST(TriangleIntersectionTest, ThreeTrianglesTwoIntersect) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 1, 0, 0, 0, 1, 0, 1),
        Triangle(0, 0, 0, 0, 1, 0, 0, 0, 1, 2),
        Triangle(2, 2, 2, 3, 2, 2, 2, 3, 2, 3)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
    EXPECT_NE(std::find(result.begin(), result.end(), 1), result.end());
    EXPECT_NE(std::find(result.begin(), result.end(), 2), result.end());
    EXPECT_EQ(std::find(result.begin(), result.end(), 3), result.end());
}

// Тест 3: Четыре треугольника, все пересекаются
TEST(TriangleIntersectionTest, FourIntersectingTriangles) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 1, 0, 0, 0, 1, 0, 1),
        Triangle(0, 0, 0, 0, 1, 0, 0, 0, 1, 2),
        Triangle(0, 0, 0, 1, 1, 1, 1, 0, 1, 3),
        Triangle(1, 1, 1, 2, 1, 1, 1, 2, 1, 4)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 4);
}

// Тест 4: Касание по вершине
TEST(TriangleIntersectionTest, VertexTouch) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 1, 0, 0, 0, 1, 0, 1),
        Triangle(0, 0, 0, 0, 0, 1, 0, 1, 0, 2)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 5: Касание по ребру
TEST(TriangleIntersectionTest, EdgeTouch) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 1, 0, 0, 0, 1, 0, 1),
        Triangle(0, 0, 0, 1, 0, 0, 0, 0, 1, 2)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 6: Касание по плоскости
TEST(TriangleIntersectionTest, PlaneTouch) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 1, 0, 0, 0, 1, 0, 1),
        Triangle(0, 0, 0, 0, 1, 0, 1, 0, 0, 2)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 7: Копланарные пересекающиеся треугольники
TEST(TriangleIntersectionTest, CoplanarIntersecting) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 2, 0, 0, 0, 2, 0, 1),
        Triangle(1, 1, 0, 3, 1, 0, 1, 3, 0, 2)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 8: Копланарные непересекающиеся треугольники
TEST(TriangleIntersectionTest, CoplanarNonIntersecting) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 1, 0, 0, 0, 1, 0, 1),
        Triangle(2, 2, 0, 3, 2, 0, 2, 3, 0, 2)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 0);
}

// Тест 9: Копланарные треугольники с общим ребром
TEST(TriangleIntersectionTest, CoplanarSharedEdge) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 1, 0, 0, 0, 1, 0, 1),
        Triangle(0, 0, 0, 0, 1, 0, 1, 0, 0, 2)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 10: Параллельные треугольники в разных плоскостях
TEST(TriangleIntersectionTest, ParallelTrianglesDifferentPlanes) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 1, 0, 0, 0, 1, 0, 1),
        Triangle(0, 0, 1, 1, 0, 1, 0, 1, 1, 2)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 0);
}

// Тест 11: Параллельные треугольники со смещением
TEST(TriangleIntersectionTest, ParallelTrianglesOffset) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 1, 0, 0, 0, 1, 0, 1),
        Triangle(0, 0, 1, 1, 0, 1, 0, 1, 1, 2)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 0);
}

// Тест 12: Параллельные треугольники с пересекающимися AABB
TEST(TriangleIntersectionTest, ParallelTrianglesIntersectingAABB) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 2, 0, 0, 0, 2, 0, 1),
        Triangle(1, 1, 1, 3, 1, 1, 1, 3, 1, 2)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 0);
}

// Тест 13: Вырожденный треугольник (линия)
TEST(TriangleIntersectionTest, DegenerateLineTriangle) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 1, 0, 0, 0.5, 0, 0, 1),
        Triangle(0, 0, 1, 1, 0, 1, 0, 1, 1, 2)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 0);
}

// Тест 14: Вырожденный треугольник (точка)
TEST(TriangleIntersectionTest, DegeneratePointTriangle) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 0, 0, 0, 0, 0, 0, 1),
        Triangle(0, 0, 1, 1, 0, 1, 0, 1, 1, 2)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 0);
}

// Тест 15: Два вырожденных треугольника
TEST(TriangleIntersectionTest, TwoDegenerateTriangles) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 0, 0, 0, 0, 0, 0, 1),
        Triangle(1, 1, 1, 1, 1, 1, 1, 1, 1, 2)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 0);
}

// Тест 16: Треугольники с большими координатами
TEST(TriangleIntersectionTest, LargeCoordinates) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 1000000, 0, 0, 0, 1000000, 0, 1),
        Triangle(500000, 500000, 0, 1500000, 500000, 0, 500000, 1500000, 0, 2)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 17: Треугольники с очень большими координатами
TEST(TriangleIntersectionTest, VeryLargeCoordinates) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 1e9, 0, 0, 0, 1e9, 0, 1),
        Triangle(5e8, 5e8, 0, 1.5e9, 5e8, 0, 5e8, 1.5e9, 0, 2)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 18: Треугольники почти касаются
TEST(TriangleIntersectionTest, AlmostTouching) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 1, 0, 0, 0, 1, 0, 1),
        Triangle(1.0000001, 0, 0, 2.0000001, 0, 0, 1.0000001, 1, 0, 2)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 0);
}

// Тест 19: Треугольники с граничным пересечением
TEST(TriangleIntersectionTest, BoundaryIntersection) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 1, 0, 0, 0, 1, 0, 1),
        Triangle(1, 0, 0, 2, 0, 0, 1, 1, 0, 2)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 20: Много треугольников без пересечений
TEST(TriangleIntersectionTest, ManyNonIntersectingTriangles) 
{
    std::vector<Triangle> triangles;
    for (int i = 0; i < 100; i++) 
    {
        triangles.push_back(Triangle(i*3, 0, 0, i*3+1, 0, 0, i*3, 1, 0, i+1));
    }
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 0);
}

// Тест 21: Много треугольников со всеми пересечениями
TEST(TriangleIntersectionTest, ManyAllIntersectingTriangles) 
{
    std::vector<Triangle> triangles;
    for (int i = 0; i < 1000; i++) 
    {
        triangles.push_back(Triangle(0, 0, 0, 1, 0, i, 0, 1, i, i+1));
    }
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 1000);
}

// Тест 22: Треугольники в разных плоскостях с пересекающимися проекциями
TEST(TriangleIntersectionTest, DifferentPlanesIntersectingProjections) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 1, 0, 0, 0, 1, 0, 1),
        Triangle(0, 0, 1, 1, 0, 1, 0, 1, 1, 2)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 0);
}

// Тест 23: Треугольники с общим ребром в 3D
TEST(TriangleIntersectionTest, SharedEdge3D) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 1, 0, 0, 0, 0, 1, 1),
        Triangle(0, 0, 0, 1, 0, 0, 0, 1, 0, 2)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 24: Треугольники с общей вершиной в 3D
TEST(TriangleIntersectionTest, SharedVertex3D) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 1, 0, 0, 0, 0, 1, 1),
        Triangle(0, 0, 0, 0, 1, 0, 0, 0, 1, 2)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 25: Один треугольник
TEST(TriangleIntersectionTest, SingleTriangle) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 1, 0, 0, 0, 1, 0, 1)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 0);
}

// Тест 26: Нулевое количество треугольников
TEST(TriangleIntersectionTest, NoTriangles) 
{
    std::vector<Triangle> triangles;
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 0);
}

// Тест 27: Точность вычислений с плавающей точкой
TEST(TriangleIntersectionTest, FloatingPointPrecision) 
{
    std::vector<Triangle> triangles = {
        Triangle(0.0000001, 0.0000001, 0.0000001, 1.0000001, 0.0000001, 0.0000001, 0.0000001, 1.0000001, 0.0000001, 1),
        Triangle(0.0000001, 0.0000001, 0.0000001, 0.0000001, 1.0000001, 0.0000001, 0.0000001, 0.0000001, 1.0000001, 2)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 28: Два одинаковых треугольника
TEST(TriangleIntersectionTest, TwoidenticalTriangles) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 1, 0, 0, 0, 0, 1, 0, 0, 1),
        Triangle(0, 0, 0, 0, 1, 0, 0, 0, 1, 2)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
    EXPECT_NE(std::find(result.begin(), result.end(), 1), result.end());
    EXPECT_NE(std::find(result.begin(), result.end(), 2), result.end());
}

int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}