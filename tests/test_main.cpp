#include "../include/triangle_geometry.hpp"

using namespace TriangleGeometry;

// Тест 1: Два пересекающихся треугольника (double)
TEST(TriangleIntersectionTest, TwoIntersectingTrianglesDouble) 
{
    std::vector<Triangle<double>> triangles = {
        Triangle<double>(0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0),
        Triangle<double>(0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
    EXPECT_NE(std::find(result.begin(), result.end(), 0), result.end());
    EXPECT_NE(std::find(result.begin(), result.end(), 1), result.end());
}

// Тест 1: Два пересекающихся треугольника (float)
TEST(TriangleIntersectionTest, TwoIntersectingTrianglesFloat) 
{
    std::vector<Triangle<float>> triangles = {
        Triangle<float>(0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f),
        Triangle<float>(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
    EXPECT_NE(std::find(result.begin(), result.end(), 0), result.end());
    EXPECT_NE(std::find(result.begin(), result.end(), 1), result.end());
}

// Тест 2: Три треугольника, два пересекаются (double)
TEST(TriangleIntersectionTest, ThreeTrianglesTwoIntersectDouble) 
{
    std::vector<Triangle<double>> triangles = {
        Triangle<double>(0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0),
        Triangle<double>(0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0),
        Triangle<double>(2.0, 2.0, 2.0, 3.0, 2.0, 2.0, 2.0, 3.0, 2.0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
    EXPECT_NE(std::find(result.begin(), result.end(), 0), result.end());
    EXPECT_NE(std::find(result.begin(), result.end(), 1), result.end());
    EXPECT_EQ(std::find(result.begin(), result.end(), 2), result.end());
}

// Тест 3: Четыре треугольника, все пересекаются (double)
TEST(TriangleIntersectionTest, FourIntersectingTrianglesDouble) 
{
    std::vector<Triangle<double>> triangles = {
        Triangle<double>(0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0),
        Triangle<double>(0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0),
        Triangle<double>(0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 1.0),
        Triangle<double>(1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 1.0, 2.0, 1.0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 4);
}

// Тест 4: Касание по вершине (double)
TEST(TriangleIntersectionTest, VertexTouchDouble) 
{
    std::vector<Triangle<double>> triangles = {
        Triangle<double>(0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0),
        Triangle<double>(0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 5: Касание по ребру (double)
TEST(TriangleIntersectionTest, EdgeTouchDouble) 
{
    std::vector<Triangle<double>> triangles = {
        Triangle<double>(0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0),
        Triangle<double>(0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 6: Касание по плоскости (double)
TEST(TriangleIntersectionTest, PlaneTouchDouble) 
{
    std::vector<Triangle<double>> triangles = {
        Triangle<double>(0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0),
        Triangle<double>(0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 7: Копланарные пересекающиеся треугольники (double)
TEST(TriangleIntersectionTest, CoplanarIntersectingDouble) 
{
    std::vector<Triangle<double>> triangles = 
    {
        Triangle<double>(0.0, 0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 2.0, 0.0),
        Triangle<double>(1.0, 1.0, 0.0, 3.0, 1.0, 0.0, 1.0, 3.0, 0.0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 8: Копланарные непересекающиеся треугольники (double)
TEST(TriangleIntersectionTest, CoplanarNonIntersectingDouble) 
{
    std::vector<Triangle<double>> triangles = {
        Triangle<double>(0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0),
        Triangle<double>(2.0, 2.0, 0.0, 3.0, 2.0, 0.0, 2.0, 3.0, 0.0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 0);
}

// Тест 8: Копланарные непересекающиеся треугольники (float)
TEST(TriangleIntersectionTest, CoplanarNonIntersectingFloat) 
{
    std::vector<Triangle<float>> triangles = {
        Triangle<float>(0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f),
        Triangle<float>(2.0f, 2.0f, 0.0f, 3.0f, 2.0f, 0.0f, 2.0f, 3.0f, 0.0f)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 0);
}

// Тест 9: Копланарные треугольники с общим ребром (double)
TEST(TriangleIntersectionTest, CoplanarSharedEdgeDouble) 
{
    std::vector<Triangle<double>> triangles = {
        Triangle<double>(0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0),
        Triangle<double>(0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 10: Параллельные треугольники в разных плоскостях (double)
TEST(TriangleIntersectionTest, ParallelTrianglesDifferentPlanesDouble) 
{
    std::vector<Triangle<double>> triangles = {
        Triangle<double>(0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0),
        Triangle<double>(0.0, 0.0, 1.0, 1.0, 0.0, 1.0, 0.0, 1.0, 1.0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 0);
}

// Тест 11: Параллельные треугольники со смещением (double)
TEST(TriangleIntersectionTest, ParallelTrianglesOffsetDouble) 
{
    std::vector<Triangle<double>> triangles = {
        Triangle<double>(0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0),
        Triangle<double>(0.0, 0.0, 1.0, 1.0, 0.0, 1.0, 0.0, 1.0, 1.0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 0);
}

// Тест 12: Параллельные треугольники с пересекающимися AABB (double)
TEST(TriangleIntersectionTest, ParallelTrianglesIntersectingAABBDouble) 
{
    std::vector<Triangle<double>> triangles = {
        Triangle<double>(0.0, 0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 2.0, 0.0),
        Triangle<double>(1.0, 1.0, 1.0, 3.0, 1.0, 1.0, 1.0, 3.0, 1.0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 0);
}

// Тест 13: Вырожденный треугольник (линия) (double)
TEST(TriangleIntersectionTest, DegenerateLineTriangleDouble) 
{
    std::vector<Triangle<double>> triangles = {
        Triangle<double>(0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.5, 0.0, 0.0),
        Triangle<double>(0.0, 0.0, 1.0, 1.0, 0.0, 1.0, 0.0, 1.0, 1.0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 0);
}

// Тест 14: Вырожденный треугольник (точка) (double)
TEST(TriangleIntersectionTest, DegeneratePointTriangleDouble) 
{
    std::vector<Triangle<double>> triangles = {
        Triangle<double>(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0),
        Triangle<double>(0.0, 0.0, 1.0, 1.0, 0.0, 1.0, 0.0, 1.0, 1.0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 0);
}

// Тест 15: Два вырожденных треугольника (double)
TEST(TriangleIntersectionTest, TwoDegenerateTrianglesDouble) 
{
    std::vector<Triangle<double>> triangles = {
        Triangle<double>(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0),
        Triangle<double>(1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 0);
}

// Тест 16: Треугольники с большими координатами (double)
TEST(TriangleIntersectionTest, LargeCoordinatesDouble) 
{
    std::vector<Triangle<double>> triangles = {
        Triangle<double>(0.0, 0.0, 0.0, 1000000.0, 0.0, 0.0, 0.0, 1000000.0, 0.0),
        Triangle<double>(500000.0, 500000.0, 0.0, 1500000.0, 500000.0, 0.0, 500000.0, 1500000.0, 0.0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 17: Треугольники с очень большими координатами (double)
TEST(TriangleIntersectionTest, VeryLargeCoordinatesDouble) 
{
    std::vector<Triangle<double>> triangles = {
        Triangle<double>(0.0, 0.0, 0.0, 1.0e9, 0.0, 0.0, 0.0, 1.0e9, 0.0),
        Triangle<double>(5.0e8, 5.0e8, 0.0, 1.5e9, 5.0e8, 0.0, 5.0e8, 1.5e9, 0.0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 18: Треугольники почти касаются (double)
TEST(TriangleIntersectionTest, AlmostTouchingDouble) 
{
    std::vector<Triangle<double>> triangles = {
        Triangle<double>(0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0),
        Triangle<double>(1.0000001, 0.0, 0.0, 2.0000001, 0.0, 0.0, 1.0000001, 1.0, 0.0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 0);
}

// Тест 18: Треугольники почти касаются (float)
TEST(TriangleIntersectionTest, AlmostTouchingFloat) 
{
    std::vector<Triangle<float>> triangles = {
        Triangle<float>(0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f),
        Triangle<float>(1.000001f, 0.0f, 0.0f, 2.000001f, 0.0f, 0.0f, 1.000001f, 1.0f, 0.0f)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 0);
}

// Тест 19: Треугольники с граничным пересечением (double)
TEST(TriangleIntersectionTest, BoundaryIntersectionDouble) 
{
    std::vector<Triangle<double>> triangles = {
        Triangle<double>(0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0),
        Triangle<double>(1.0, 0.0, 0.0, 2.0, 0.0, 0.0, 1.0, 1.0, 0.0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 20: Много треугольников без пересечений (double)
TEST(TriangleIntersectionTest, ManyNonIntersectingTrianglesDouble) 
{
    std::vector<Triangle<double>> triangles;
    for (int i = 0; i < 100; i++) 
    {
        triangles.push_back(Triangle<double>(i*3.0, 0.0, 0.0, i*3.0+1.0, 0.0, 0.0, i*3.0, 1.0, 0.0));
    }
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 0);
}

// Тест 21: Много треугольников со всеми пересечениями (double)
TEST(TriangleIntersectionTest, ManyAllIntersectingTrianglesDouble) 
{
    std::vector<Triangle<double>> triangles;
    for (int i = 0; i < 1000; i++) 
    {
        triangles.push_back(Triangle<double>(0.0, 0.0, 0.0, 1.0, 0.0, i, 0.0, 1.0, i));
    }
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 1000);
}

// Тест 22: Треугольники в разных плоскостях с пересекающимися проекциями (double)
TEST(TriangleIntersectionTest, DifferentPlanesIntersectingProjectionsDouble) 
{
    std::vector<Triangle<double>> triangles = {
        Triangle<double>(0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0),
        Triangle<double>(0.0, 0.0, 1.0, 1.0, 0.0, 1.0, 0.0, 1.0, 1.0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 0);
}

// Тест 23: Треугольники с общим ребром (double)
TEST(TriangleIntersectionTest, SharedEdge3DDouble) 
{
    std::vector<Triangle<double>> triangles = {
        Triangle<double>(0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0),
        Triangle<double>(0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 24: Треугольники с общей вершиной (double)
TEST(TriangleIntersectionTest, SharedVertex3DDouble) 
{
    std::vector<Triangle<double>> triangles = {
        Triangle<double>(0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0),
        Triangle<double>(0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 25: Один треугольник (double)
TEST(TriangleIntersectionTest, SingleTriangleDouble) 
{
    std::vector<Triangle<double>> triangles = {
        Triangle<double>(0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 0);
}

// Тест 25: Один треугольник (float)
TEST(TriangleIntersectionTest, SingleTriangleFloat) 
{
    std::vector<Triangle<float>> triangles = {
        Triangle<float>(0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 0);
}

// Тест 26: Нулевое количество треугольников (double)
TEST(TriangleIntersectionTest, NoTrianglesDouble) 
{
    std::vector<Triangle<double>> triangles;
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 0);
}

// Тест 27: Точность вычислений с плавающей точкой (double)
TEST(TriangleIntersectionTest, FloatingPointPrecisionDouble) 
{
    std::vector<Triangle<double>> triangles = {
        Triangle<double>(0.0000001, 0.0000001, 0.0000001, 1.0000001, 0.0000001, 0.0000001, 0.0000001, 1.0000001, 0.0000001),
        Triangle<double>(0.0000001, 0.0000001, 0.0000001, 0.0000001, 1.0000001, 0.0000001, 0.0000001, 0.0000001, 1.0000001)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 28: Два одинаковых треугольника (double)
TEST(TriangleIntersectionTest, TwoIdenticalTrianglesDouble) 
{
    std::vector<Triangle<double>> triangles = {
        Triangle<double>(0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0),
        Triangle<double>(0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
    EXPECT_NE(std::find(result.begin(), result.end(), 0), result.end());
    EXPECT_NE(std::find(result.begin(), result.end(), 1), result.end());
}

// Тест 29: Два близких треугольника (double)
TEST(TriangleIntersectionTest, TwoCloseTrianglesDouble) 
{
    std::vector<Triangle<double>> triangles = {
        Triangle<double>(0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0),
        Triangle<double>(0.0, 0.0, 0.01, 5.0, 5.0, 0.01, 5.0, 5.0, 0.0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 0);
}

// Тест 30: Треугольники с пересечением через вершину (double)
TEST(TriangleIntersectionTest, VertexIntersectionDouble) 
{
    std::vector<Triangle<double>> triangles = {
        Triangle<double>(0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0),
        Triangle<double>(0.0, 0.0, 0.0, 0.0, -1.0, 0.0, -1.0, 0.0, 0.0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 31: Треугольники с пересечением по линии (double)
TEST(TriangleIntersectionTest, LineIntersectionDouble) 
{
    std::vector<Triangle<double>> triangles = {
        Triangle<double>(0.0, 0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 2.0, 0.0),
        Triangle<double>(1.0, 1.0, -1.0, 1.0, 1.0, 1.0, 2.0, 2.0, 0.0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 32: Треугольники с минимальным расстоянием (но не пересекающиеся) (double)
TEST(TriangleIntersectionTest, MinimalDistanceNoIntersectionDouble) 
{
    std::vector<Triangle<double>> triangles = {
        Triangle<double>(0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0),
        Triangle<double>(0.0, 0.0, 0.0001, 1.0, 0.0, 0.0001, 0.0, 1.0, 0.0001)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 0);
}

// Тест 32: Треугольники с минимальным расстоянием (но не пересекающиеся) (float)
TEST(TriangleIntersectionTest, MinimalDistanceNoIntersectionFloat) 
{
    std::vector<Triangle<float>> triangles = {
        Triangle<float>(0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f),
        Triangle<float>(0.0f, 0.0f, 0.0001f, 1.0f, 0.0f, 0.0001f, 0.0f, 1.0f, 0.0001f)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 0);
}

// Тест 33: Треугольники с большим количеством вершин на одной линии (double)
TEST(TriangleIntersectionTest, CollinearPointsDouble) 
{
    std::vector<Triangle<double>> triangles = {
        Triangle<double>(0.0, 0.0, 0.0, 2.0, 0.0, 0.0, 1.0, 0.0, 0.0),
        Triangle<double>(0.0, 1.0, 0.0, 2.0, 1.0, 0.0, 1.0, 1.0, 0.0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 0);
}

// Тест 34: Треугольники в разных октантах (double)
TEST(TriangleIntersectionTest, DifferentOctantsDouble) 
{
    std::vector<Triangle<double>> triangles = {
        Triangle<double>(-1.0, -1.0, -1.0, 0.0, 0.0, 0.0, -1.0, 0.0, 0.0),
        Triangle<double>(1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 35: Треугольники с очень малыми координатами (double)
TEST(TriangleIntersectionTest, VerySmallCoordinatesDouble) 
{
    std::vector<Triangle<double>> triangles = {
        Triangle<double>(0.0, 0.0, 0.0, 1e-12, 0.0, 0.0, 0.0, 1e-12, 0.0),
        Triangle<double>(0.0, 0.0, 1e-12, 1e-12, 0.0, 1e-12, 0.0, 1e-12, 1e-12)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 0);
}

// Тест 35: Треугольники с очень малыми координатами (float)
TEST(TriangleIntersectionTest, VerySmallCoordinatesFloat) 
{
    std::vector<Triangle<float>> triangles = {
        Triangle<float>(0.0f, 0.0f, 0.0f, 1e-6f, 0.0f, 0.0f, 0.0f, 1e-6f, 0.0f),
        Triangle<float>(0.0f, 0.0f, 1e-6f, 1e-6f, 0.0f, 1e-6f, 0.0f, 1e-6f, 1e-6f)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 0);
}

// Тест 36: Треугольники с чередующимися координатами (double)
TEST(TriangleIntersectionTest, AlternatingCoordinatesDouble) 
{
    std::vector<Triangle<double>> triangles = {
        Triangle<double>(0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0),
        Triangle<double>(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 37: Треугольники с отрицательными координатами (double)
TEST(TriangleIntersectionTest, NegativeCoordinatesDouble) 
{
    std::vector<Triangle<double>> triangles = {
        Triangle<double>(-1.0, -1.0, -1.0, 0.0, 0.0, 0.0, -1.0, 0.0, 0.0),
        Triangle<double>(-2.0, -2.0, -2.0, -1.0, -1.0, -1.0, -2.0, -1.0, -1.0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 38: Треугольники с смешанными знаками координат (double)
TEST(TriangleIntersectionTest, MixedSignCoordinatesDouble) 
{
    std::vector<Triangle<double>> triangles = {
        Triangle<double>(-1.0, 1.0, 0.0, 1.0, -1.0, 0.0, -1.0, -1.0, 0.0),
        Triangle<double>(0.0, 0.0, -1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 39: Два одинаковых треугольника (полное совпадение) (double)
TEST(TriangleIntersectionTest, IdenticalTrianglesDouble) 
{
    std::vector<Triangle<double>> triangles = {
        Triangle<double>(0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0),
        Triangle<double>(0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 40: Треугольники с частичным перекрытием (double)
TEST(TriangleIntersectionTest, PartialOverlapDouble) 
{
    std::vector<Triangle<double>> triangles = {
        Triangle<double>(0.0, 0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 2.0, 0.0),
        Triangle<double>(1.0, 1.0, 0.0, 3.0, 1.0, 0.0, 1.0, 3.0, 0.0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 41: Треугольники с пересечением в одной точке (вершина) (double)
TEST(TriangleIntersectionTest, SinglePointIntersectionDouble) 
{
    std::vector<Triangle<double>> triangles = {
        Triangle<double>(0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0),
        Triangle<double>(0.0, 0.0, 0.0, 0.0, -1.0, 0.0, -1.0, 0.0, 0.0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 42: Треугольники с пересечением по отрезку (double)
TEST(TriangleIntersectionTest, SegmentIntersectionDouble) 
{
    std::vector<Triangle<double>> triangles = {
        Triangle<double>(0.0, 0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 2.0, 0.0),
        Triangle<double>(1.0, 0.0, -1.0, 1.0, 2.0, -1.0, 1.0, 0.0, 1.0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 43: Треугольники с общим ребром и смещением по Z (double)
TEST(TriangleIntersectionTest, SharedEdgeZOffsetDouble) 
{
    std::vector<Triangle<double>> triangles = {
        Triangle<double>(0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0),
        Triangle<double>(0.0, 0.0, 0.001, 1.0, 0.0, 0.001, 0.0, 1.0, 0.001)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 0);
}

// Тест 44: Треугольники с почти касанием (double)
TEST(TriangleIntersectionTest, AlmostTouchinggDouble) 
{
    std::vector<Triangle<double>> triangles = {
        Triangle<double>(0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0),
        Triangle<double>(1.0000000001, 0.0, 0.0, 2.0, 0.0, 0.0, 1.0000000001, 1.0, 0.0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 0);
}

// Тест 45: Треугольники с пересечением через центр (double)
TEST(TriangleIntersectionTest, CenterIntersectionDouble) 
{
    std::vector<Triangle<double>> triangles = {
        Triangle<double>(0.0, 0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 2.0, 0.0),
        Triangle<double>(1.0, 1.0, -1.0, 1.0, 1.0, 1.0, 2.0, 2.0, 0.0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 46: Треугольники с зеркальным отражением (double)
TEST(TriangleIntersectionTest, MirrorTrianglesDouble) 
{
    std::vector<Triangle<double>> triangles = {
        Triangle<double>(0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0),
        Triangle<double>(0.0, 0.0, 0.0, -1.0, 0.0, 0.0, 0.0, -1.0, 0.0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 47: Треугольники с вращением (double)
TEST(TriangleIntersectionTest, RotatedTrianglesDouble) 
{
    std::vector<Triangle<double>> triangles = {
        Triangle<double>(0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0),
        Triangle<double>(0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 48: Треугольники с ступенчатым расположением (double)
TEST(TriangleIntersectionTest, SteppedArrangementDouble) 
{
    std::vector<Triangle<double>> triangles = {
        Triangle<double>(0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0),
        Triangle<double>(0.0, 0.0, 1.0, 1.0, 0.0, 1.0, 0.0, 1.0, 1.0),
        Triangle<double>(0.0, 0.0, 2.0, 1.0, 0.0, 2.0, 0.0, 1.0, 2.0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 0);
}

// Тест 49: Треугольники с вложенными AABB (double)
TEST(TriangleIntersectionTest, NestedAABBDouble) 
{
    std::vector<Triangle<double>> triangles = {
        Triangle<double>(0.0, 0.0, 0.0, 3.0, 0.0, 0.0, 0.0, 3.0, 0.0),
        Triangle<double>(1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 1.0, 2.0, -1.0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 50: Треугольники с касанием по ребру под углом (double)
TEST(TriangleIntersectionTest, EdgeTouchAngleDouble) 
{
    std::vector<Triangle<double>> triangles = {
        Triangle<double>(0.0, 0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 2.0, 0.0),
        Triangle<double>(1.0, 0.0, 0.0, 3.0, 0.0, 0.0, 1.0, 2.0, 0.0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 51: Треугольники с очень большими числами (double)
TEST(TriangleIntersectionTest, InfinityLikeCoordinatesDouble) 
{
    std::vector<Triangle<double>> triangles = {
        Triangle<double>(1.0e308, 1.0e308, 1.0e308, 1.0e308, 0.0, 1.0e308, 0.0, 1.0e308, 1.0e308),
        Triangle<double>(0.0, 0.0, 0.0, 1.0e308, 0.0, 0.0, 0.0, 1.0e308, 0.0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_TRUE(result.size() >= 0);
}

// Тест 52: Треугольники с бесконечно малыми разностями (double)
TEST(TriangleIntersectionTest, InfinitesimalDifferencesDouble) 
{
    std::vector<Triangle<double>> triangles = {
        Triangle<double>(0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0),
        Triangle<double>(0.0, 0.0, 1e-10, 1.0, 0.0, 1e-10, 0.0, 1.0, 1e-10)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 0);
}

// Тест 53: Треугольники с чередующимися пересечениями (double)
TEST(TriangleIntersectionTest, AlternatingIntersectionsDouble) 
{
    std::vector<Triangle<double>> triangles = {
        Triangle<double>(0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0),
        Triangle<double>(0.5, 0.5, 0.0, 1.5, 0.5, 0.0, 0.5, 1.5, 0.0),
        Triangle<double>(2.0, 2.0, 0.0, 3.0, 2.0, 0.0, 2.0, 3.0, 0.0),
        Triangle<double>(2.5, 2.5, 0.0, 3.5, 2.5, 0.0, 2.5, 3.5, 0.0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 4);
}

// Тест 54: Треугольники с веерным расположением (double)
TEST(TriangleIntersectionTest, FanArrangementDouble) 
{
    std::vector<Triangle<double>> triangles;
    for (int i = 0; i < 10; i++) {
        double angle = i * M_PI / 5;
        triangles.push_back(Triangle<double>(
            0.0, 0.0, 0.0,
            cos(angle), sin(angle), 0.0,
            cos(angle + M_PI/10), sin(angle + M_PI/10), 0.0
        ));
    }
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 10);
}

// Тест 55: Треугольники со спиральным расположением (double)
TEST(TriangleIntersectionTest, SpiralArrangementDouble) 
{
    std::vector<Triangle<double>> triangles;
    for (int i = 0; i < 5; i++) {
        double angle = i * 2 * M_PI / 5;
        triangles.push_back(Triangle<double>(
            cos(angle), sin(angle), i * 0.1,
            cos(angle + 2*M_PI/5), sin(angle + 2*M_PI/5), i * 0.1,
            0.0, 0.0, i * 0.1 + 0.05
        ));
    }
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 0);
}

// Тест 56: Производительность с большим количеством треугольников (double)
TEST(TriangleIntersectionTest, PerformanceTestDouble) 
{
    std::vector<Triangle<double>> triangles;
    int n = 100;
    
    for (int i = 0; i < n; i++) {
        double x = i * 3.0;
        triangles.push_back(Triangle<double>(
            x, 0.0, 0.0,
            x + 1.0, 0.0, 0.0,
            x, 1.0, 0.0
        ));
    }
    
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> result = findIntersectingTriangles(triangles);
    auto end = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    EXPECT_TRUE(duration.count() < 5000);
    EXPECT_EQ(result.size(), 0);
}

// Тест 57: Треугольники с граничными значениями double
TEST(TriangleIntersectionTest, DoubleBoundaryValues) 
{
    std::vector<Triangle<double>> triangles = {
        Triangle<double>(DBL_MIN, DBL_MIN, DBL_MIN, DBL_MIN, 0.0, DBL_MIN, 0.0, DBL_MIN, DBL_MIN),
        Triangle<double>(0.0, 0.0, 0.0, DBL_MIN, 0.0, 0.0, 0.0, DBL_MIN, 0.0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_TRUE(result.size() >= 0);
}

// Тест 57: Треугольники с граничными значениями float
TEST(TriangleIntersectionTest, FloatBoundaryValues) 
{
    std::vector<Triangle<float>> triangles = {
        Triangle<float>(FLT_MIN, FLT_MIN, FLT_MIN, FLT_MIN, 0.0f, FLT_MIN, 0.0f, FLT_MIN, FLT_MIN),
        Triangle<float>(0.0f, 0.0f, 0.0f, FLT_MIN, 0.0f, 0.0f, 0.0f, FLT_MIN, 0.0f)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_TRUE(result.size() >= 0);
}

// Тест 58: 1000 треугольников без пересечений (double)
TEST(PerformanceTest, Grid1000TrianglesNoIntersectionsDouble) 
{
    std::vector<Triangle<double>> triangles;
    int size = 10;
    
    for (int x = 0; x < size; x++) 
    {
        for (int y = 0; y < size; y++) 
        {
            for (int z = 0; z < size; z++) 
            {
                double base_x = x * 5.0;
                double base_y = y * 5.0;
                double base_z = z * 5.0;
                
                triangles.push_back(Triangle<double>(
                    base_x, base_y, base_z,
                    base_x + 1.0, base_y, base_z,
                    base_x, base_y + 1.0, base_z
                ));
            }
        }
    }
    
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> result = findIntersectingTriangles(triangles);
    auto end = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    EXPECT_EQ(result.size(), 0);
    EXPECT_TRUE(duration.count() < 10000);
}

// Тест 59: 2000 треугольников в случайных положениях (double)
TEST(PerformanceTest, Random2000TrianglesDouble) 
{
    std::vector<Triangle<double>> triangles;
    std::srand(42); 
    
    for (int i = 0; i < 2000; i++) 
    {
        double center_x = (std::rand() % 1000) / 10.0;
        double center_y = (std::rand() % 1000) / 10.0;
        double center_z = (std::rand() % 1000) / 10.0;
        
        double size = 1.0 + (std::rand() % 100) / 100.0; 
        
        triangles.push_back(Triangle<double>(
            center_x, center_y, center_z,
            center_x + size, center_y, center_z,
            center_x, center_y + size, center_z
        ));
    }
    
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> result = findIntersectingTriangles(triangles);
    auto end = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    EXPECT_TRUE(duration.count() < 20000);
    EXPECT_TRUE(result.size() >= 0 && result.size() <= 2000);
}

// Тест 60: 1000 треугольников, все пересекаются в одной точке (double)
TEST(PerformanceTest, AllTrianglesIntersectAtCenterDouble) 
{
    std::vector<Triangle<double>> triangles;
    
    for (int i = 0; i < 1000; i++) 
    {
        double angle = i * 2 * M_PI / 1000;
        double next_angle = (i + 1) * 2 * M_PI / 1000;
        
        triangles.push_back(Triangle<double>(
            0.0, 0.0, 0.0, 
            cos(angle), sin(angle), 0.0,
            cos(next_angle), sin(next_angle), 0.0
        ));
    }
    
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> result = findIntersectingTriangles(triangles);
    auto end = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    EXPECT_EQ(result.size(), 1000); 
    EXPECT_TRUE(duration.count() < 50000);
}

// Тест 61: Вырожденные треугольники среди нормальных (double)
TEST(PerformanceTest, MixedDegenerateAndNormalTrianglesDouble) 
{
    std::vector<Triangle<double>> triangles;
    
    // Нормальные треугольники
    for (int i = 0; i < 200; i++) 
    {
        triangles.push_back(Triangle<double>(
            i * 3.0, 0.0, 0.0,
            i * 3.0 + 1.0, 0.0, 0.0,
            i * 3.0, 1.0, 0.0
        ));
    }
    
    // Вырожденные треугольники (точки)
    for (int i = 0; i < 100; i++) 
    {
        triangles.push_back(Triangle<double>(
            i * 3.0, 100.0, 100.0,
            i * 3.0, 100.0, 100.0,
            i * 3.0, 100.0, 100.0
        ));
    }
    
    // Вырожденные треугольники (линии)
    for (int i = 0; i < 1000; i++) 
    {
        triangles.push_back(Triangle<double>(
            i * 3.0, 200.0, 200.0,
            i * 3.0 + 1.0, 200.0, 200.0, 
            i * 3.0 + 0.5, 200.0, 200.0
        ));
    }
    
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> result = findIntersectingTriangles(triangles);
    auto end = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    EXPECT_EQ(result.size(), 0); 
    EXPECT_TRUE(duration.count() < 10000);
}

// Тест 62: Случайные треугольники с различными ориентациями (double)
TEST(PerformanceTest, RandomOrientationsDouble) 
{
    std::vector<Triangle<double>> triangles;
    std::srand(12345);
    
    for (int i = 0; i < 800; i++) 
    {
        double cx = (std::rand() % 200) / 10.0;
        double cy = (std::rand() % 200) / 10.0;
        double cz = (std::rand() % 200) / 10.0;
        
        double dx1 = (std::rand() % 100 - 50) / 50.0;
        double dy1 = (std::rand() % 100 - 50) / 50.0;
        double dz1 = (std::rand() % 100 - 50) / 50.0;
        
        double dx2 = (std::rand() % 100 - 50) / 50.0;
        double dy2 = (std::rand() % 100 - 50) / 50.0;
        double dz2 = (std::rand() % 100 - 50) / 50.0;
        
        double dx3 = (std::rand() % 100 - 50) / 50.0;
        double dy3 = (std::rand() % 100 - 50) / 50.0;
        double dz3 = (std::rand() % 100 - 50) / 50.0;
        
        triangles.push_back(Triangle<double>(
            cx + dx1, cy + dy1, cz + dz1,
            cx + dx2, cy + dy2, cz + dz2,
            cx + dx3, cy + dy3, cz + dz3
        ));
    }
    
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> result = findIntersectingTriangles(triangles);
    auto end = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    EXPECT_TRUE(result.size() >= 0 && result.size() <= 800);
    EXPECT_TRUE(duration.count() < 20000);
}

// Тест 63: Extreme performance test - максимальная нагрузка (double)
TEST(PerformanceTest, ExtremeLoadTestDouble) 
{
    std::vector<Triangle<double>> triangles;
    
    for (int x = 0; x < 15; x++)
    {
        for (int y = 0; y < 10; y++) 
        {
            for (int z = 0; z < 10; z++) 
            {
                double base_x = x * 0.1;
                double base_y = y * 0.1;
                double base_z = z * 0.1;
                
                triangles.push_back(Triangle<double>(
                    base_x, base_y, base_z,
                    base_x + 1.0, base_y, base_z,
                    base_x, base_y + 1.0, base_z
                ));
            }
        }
    }
    
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> result = findIntersectingTriangles(triangles);
    auto end = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    EXPECT_GT(result.size(), 1200);
    EXPECT_TRUE(duration.count() < 30000);
}

int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}