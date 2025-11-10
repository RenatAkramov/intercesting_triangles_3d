#include "../include/triangle_geometry.hpp"

using namespace TriangleGeometry;

// Тест 1: Два пересекающихся треугольника
TEST(TriangleIntersectionTest, TwoIntersectingTriangles) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 1, 0, 0, 0, 1, 0),
        Triangle(0, 0, 0, 0, 1, 0, 0, 0, 1)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
    EXPECT_NE(std::find(result.begin(), result.end(), 0), result.end());
    EXPECT_NE(std::find(result.begin(), result.end(), 1), result.end());
}

// Тест 2: Три треугольника, два пересекаются
TEST(TriangleIntersectionTest, ThreeTrianglesTwoIntersect) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 1, 0, 0, 0, 1, 0),
        Triangle(0, 0, 0, 0, 1, 0, 0, 0, 1),
        Triangle(2, 2, 2, 3, 2, 2, 2, 3, 2)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
    EXPECT_NE(std::find(result.begin(), result.end(), 0), result.end());
    EXPECT_NE(std::find(result.begin(), result.end(), 1), result.end());
    EXPECT_EQ(std::find(result.begin(), result.end(), 2), result.end());
}

// Тест 3: Четыре треугольника, все пересекаются
TEST(TriangleIntersectionTest, FourIntersectingTriangles) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 1, 0, 0, 0, 1, 0),
        Triangle(0, 0, 0, 0, 1, 0, 0, 0, 1),
        Triangle(0, 0, 0, 1, 1, 1, 1, 0, 1),
        Triangle(1, 1, 1, 2, 1, 1, 1, 2, 1)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 4);
}

// Тест 4: Касание по вершине
TEST(TriangleIntersectionTest, VertexTouch) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 1, 0, 0, 0, 1, 0),
        Triangle(0, 0, 0, 0, 0, 1, 0, 1, 0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 5: Касание по ребру
TEST(TriangleIntersectionTest, EdgeTouch) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 1, 0, 0, 0, 1, 0),
        Triangle(0, 0, 0, 1, 0, 0, 0, 0, 1)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 6: Касание по плоскости
TEST(TriangleIntersectionTest, PlaneTouch) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 1, 0, 0, 0, 1, 0),
        Triangle(0, 0, 0, 0, 1, 0, 1, 0, 0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 7: Копланарные пересекающиеся треугольники
TEST(TriangleIntersectionTest, CoplanarIntersecting) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 2, 0, 0, 0, 2, 0),
        Triangle(1, 1, 0, 3, 1, 0, 1, 3, 0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 8: Копланарные непересекающиеся треугольники
TEST(TriangleIntersectionTest, CoplanarNonIntersecting) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 1, 0, 0, 0, 1, 0),
        Triangle(2, 2, 0, 3, 2, 0, 2, 3, 0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 0);
}

// Тест 9: Копланарные треугольники с общим ребром
TEST(TriangleIntersectionTest, CoplanarSharedEdge) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 1, 0, 0, 0, 1, 0),
        Triangle(0, 0, 0, 0, 1, 0, 1, 0, 0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 10: Параллельные треугольники в разных плоскостях
TEST(TriangleIntersectionTest, ParallelTrianglesDifferentPlanes) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 1, 0, 0, 0, 1, 0),
        Triangle(0, 0, 1, 1, 0, 1, 0, 1, 1)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 0);
}

// Тест 11: Параллельные треугольники со смещением
TEST(TriangleIntersectionTest, ParallelTrianglesOffset) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 1, 0, 0, 0, 1, 0),
        Triangle(0, 0, 1, 1, 0, 1, 0, 1, 1)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 0);
}

// Тест 12: Параллельные треугольники с пересекающимися AABB
TEST(TriangleIntersectionTest, ParallelTrianglesIntersectingAABB) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 2, 0, 0, 0, 2, 0),
        Triangle(1, 1, 1, 3, 1, 1, 1, 3, 1)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 0);
}

// Тест 13: Вырожденный треугольник (линия)
TEST(TriangleIntersectionTest, DegenerateLineTriangle) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 1, 0, 0, 0.5, 0, 0),
        Triangle(0, 0, 1, 1, 0, 1, 0, 1, 1)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 0);
}

// Тест 14: Вырожденный треугольник (точка)
TEST(TriangleIntersectionTest, DegeneratePointTriangle) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 0, 0, 0, 0, 0, 0),
        Triangle(0, 0, 1, 1, 0, 1, 0, 1, 1)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 0);
}

// Тест 15: Два вырожденных треугольника
TEST(TriangleIntersectionTest, TwoDegenerateTriangles) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 0, 0, 0, 0, 0, 0),
        Triangle(1, 1, 1, 1, 1, 1, 1, 1, 1)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 0);
}

// Тест 16: Треугольники с большими координатами
TEST(TriangleIntersectionTest, LargeCoordinates) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 1000000, 0, 0, 0, 1000000, 0),
        Triangle(500000, 500000, 0, 1500000, 500000, 0, 500000, 1500000, 0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 17: Треугольники с очень большими координатами
TEST(TriangleIntersectionTest, VeryLargeCoordinates) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 1e9, 0, 0, 0, 1e9, 0),
        Triangle(5e8, 5e8, 0, 1.5e9, 5e8, 0, 5e8, 1.5e9, 0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 18: Треугольники почти касаются
TEST(TriangleIntersectionTest, AlmostTouching) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 1, 0, 0, 0, 1, 0),
        Triangle(1.0000001, 0, 0, 2.0000001, 0, 0, 1.0000001, 1, 0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 0);
}

// Тест 19: Треугольники с граничным пересечением
TEST(TriangleIntersectionTest, BoundaryIntersection) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 1, 0, 0, 0, 1, 0),
        Triangle(1, 0, 0, 2, 0, 0, 1, 1, 0)
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
        triangles.push_back(Triangle(i*3, 0, 0, i*3+1, 0, 0, i*3, 1, 0));
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
        triangles.push_back(Triangle(0, 0, 0, 1, 0, i, 0, 1, i));
    }
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 1000);
}

// Тест 22: Треугольники в разных плоскостях с пересекающимися проекциями
TEST(TriangleIntersectionTest, DifferentPlanesIntersectingProjections) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 1, 0, 0, 0, 1, 0),
        Triangle(0, 0, 1, 1, 0, 1, 0, 1, 1)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 0);
}

// Тест 23: Треугольники с общим ребром
TEST(TriangleIntersectionTest, SharedEdge3D) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 1, 0, 0, 0, 0, 1),
        Triangle(0, 0, 0, 1, 0, 0, 0, 1, 0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 24: Треугольники с общей вершиной
TEST(TriangleIntersectionTest, SharedVertex3D) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 1, 0, 0, 0, 0, 1),
        Triangle(0, 0, 0, 0, 1, 0, 0, 0, 1)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 25: Один треугольник
TEST(TriangleIntersectionTest, SingleTriangle) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 1, 0, 0, 0, 1, 0)
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
        Triangle(0.0000001, 0.0000001, 0.0000001, 1.0000001, 0.0000001, 0.0000001, 0.0000001, 1.0000001, 0.0000001),
        Triangle(0.0000001, 0.0000001, 0.0000001, 0.0000001, 1.0000001, 0.0000001, 0.0000001, 0.0000001, 1.0000001)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 28: Два одинаковых треугольника
TEST(TriangleIntersectionTest, TwoIdenticalTriangles) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 1, 0, 0, 0, 0, 1, 0, 0),
        Triangle(0, 0, 0, 0, 1, 0, 0, 0, 1)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
    EXPECT_NE(std::find(result.begin(), result.end(), 0), result.end());
    EXPECT_NE(std::find(result.begin(), result.end(), 1), result.end());
}

// Тест 29: Два близких треугольника
TEST(TriangleIntersectionTest, TwoCloseTriangles) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 1, 0, 0, 0, 1, 0),
        Triangle(0, 0, 0.01, 5, 5, 0.01, 5, 5, 0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 0);
}

// Тест 30: Треугольники с пересечением через вершину
TEST(TriangleIntersectionTest, VertexIntersection) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 1, 0, 0, 0, 1, 0),
        Triangle(0, 0, 0, 0, -1, 0, -1, 0, 0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 31: Треугольники с пересечением по линии
TEST(TriangleIntersectionTest, LineIntersection) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 2, 0, 0, 0, 2, 0),
        Triangle(1, 1, -1, 1, 1, 1, 2, 2, 0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 32: Треугольники с минимальным расстоянием (но не пересекающиеся)
TEST(TriangleIntersectionTest, MinimalDistanceNoIntersection) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 1, 0, 0, 0, 1, 0),
        Triangle(0, 0, 0.0001, 1, 0, 0.0001, 0, 1, 0.0001)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 0);
}

// Тест 33: Треугольники с большим количеством вершин на одной линии
TEST(TriangleIntersectionTest, CollinearPoints) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 2, 0, 0, 1, 0, 0),
        Triangle(0, 1, 0, 2, 1, 0, 1, 1, 0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 0);
}

// Тест 34: Треугольники в разных октантах
TEST(TriangleIntersectionTest, DifferentOctants) 
{
    std::vector<Triangle> triangles = {
        Triangle(-1, -1, -1, 0, 0, 0, -1, 0, 0),
        Triangle(1, 1, 1, 0, 0, 0, 1, 0, 0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 35: Треугольники с очень малыми координатами
TEST(TriangleIntersectionTest, VerySmallCoordinates) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 1e-12, 0, 0, 0, 1e-12, 0),
        Triangle(0, 0, 1e-12, 1e-12, 0, 1e-12, 0, 1e-12, 1e-12)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 0);
}

// Тест 36: Треугольники с чередующимися координатами
TEST(TriangleIntersectionTest, AlternatingCoordinates) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 1, 0, 1, 0, 0, 0, 0, 1),
        Triangle(1, 0, 0, 0, 1, 0, 0, 0, 1)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 37: Треугольники с отрицательными координатами
TEST(TriangleIntersectionTest, NegativeCoordinates) 
{
    std::vector<Triangle> triangles = {
        Triangle(-1, -1, -1, 0, 0, 0, -1, 0, 0),
        Triangle(-2, -2, -2, -1, -1, -1, -2, -1, -1)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 38: Треугольники с смешанными знаками координат
TEST(TriangleIntersectionTest, MixedSignCoordinates) 
{
    std::vector<Triangle> triangles = {
        Triangle(-1, 1, 0, 1, -1, 0, -1, -1, 0),
        Triangle(0, 0, -1, 0, 0, 1, 1, 0, 0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 39: Два одинаковых треугольника (полное совпадение)
TEST(TriangleIntersectionTest, IdenticalTriangles) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 1, 0, 0, 0, 1, 0),
        Triangle(0, 0, 0, 1, 0, 0, 0, 1, 0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 40: Треугольники с частичным перекрытием
TEST(TriangleIntersectionTest, PartialOverlap) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 2, 0, 0, 0, 2, 0),
        Triangle(1, 1, 0, 3, 1, 0, 1, 3, 0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 41: Треугольники с пересечением в одной точке (вершина)
TEST(TriangleIntersectionTest, SinglePointIntersection) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 1, 0, 0, 0, 1, 0),
        Triangle(0, 0, 0, 0, -1, 0, -1, 0, 0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 42: Треугольники с пересечением по отрезку
TEST(TriangleIntersectionTest, SegmentIntersection) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 2, 0, 0, 0, 2, 0),
        Triangle(1, 0, -1, 1, 2, -1, 1, 0, 1)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 43: Треугольники с общим ребром и смещением по Z
TEST(TriangleIntersectionTest, SharedEdgeZOffset) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 1, 0, 0, 0, 1, 0),
        Triangle(0, 0, 0.001, 1, 0, 0.001, 0, 1, 0.001)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 0);
}

// Тест 44: Треугольники с почти касанием
TEST(TriangleIntersectionTest, AlmostTouchingg) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 1, 0, 0, 0, 1, 0),
        Triangle(1.0000000001, 0, 0, 2, 0, 0, 1.0000000001, 1, 0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 0);
}

// Тест 45: Треугольники с пересечением через центр
TEST(TriangleIntersectionTest, CenterIntersection) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 2, 0, 0, 0, 2, 0),
        Triangle(1, 1, -1, 1, 1, 1, 2, 2, 0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 46: Треугольники с зеркальным отражением
TEST(TriangleIntersectionTest, MirrorTriangles) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 1, 0, 0, 0, 1, 0),
        Triangle(0, 0, 0, -1, 0, 0, 0, -1, 0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 47: Треугольники с вращением
TEST(TriangleIntersectionTest, RotatedTriangles) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 1, 0, 0, 0, 1, 0),
        Triangle(0, 0, 0, 0, 1, 0, 0, 0, 1)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 48: Треугольники с ступенчатым расположением
TEST(TriangleIntersectionTest, SteppedArrangement) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 1, 0, 0, 0, 1, 0),
        Triangle(0, 0, 1, 1, 0, 1, 0, 1, 1),
        Triangle(0, 0, 2, 1, 0, 2, 0, 1, 2)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 0);
}

// Тест 49: Треугольники с вложенными AABB
TEST(TriangleIntersectionTest, NestedAABB) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 3, 0, 0, 0, 3, 0),
        Triangle(1, 1, 1, 2, 1, 1, 1, 2, -1)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 50: Треугольники с касанием по ребру под углом
TEST(TriangleIntersectionTest, EdgeTouchAngle) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 2, 0, 0, 0, 2, 0),
        Triangle(1, 0, 0, 3, 0, 0, 1, 2, 0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 2);
}

// Тест 51: Треугольники с очень большими числами
TEST(TriangleIntersectionTest, InfinityLikeCoordinates) 
{
    std::vector<Triangle> triangles = {
        Triangle(1e308, 1e308, 1e308, 1e308, 0, 1e308, 0, 1e308, 1e308),
        Triangle(0, 0, 0, 1e308, 0, 0, 0, 1e308, 0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_TRUE(result.size() >= 0);
}

// Тест 52: Треугольники с бесконечно малыми разностями
TEST(TriangleIntersectionTest, InfinitesimalDifferences) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 1, 0, 0, 0, 1, 0),
        Triangle(0, 0, 1e-10, 1, 0, 1e-10, 0, 1, 1e-10)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 0);
}

// Тест 53: Треугольники с чередующимися пересечениями
TEST(TriangleIntersectionTest, AlternatingIntersections) 
{
    std::vector<Triangle> triangles = {
        Triangle(0, 0, 0, 1, 0, 0, 0, 1, 0),
        Triangle(0.5, 0.5, 0, 1.5, 0.5, 0, 0.5, 1.5, 0),
        Triangle(2, 2, 0, 3, 2, 0, 2, 3, 0),
        Triangle(2.5, 2.5, 0, 3.5, 2.5, 0, 2.5, 3.5, 0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 4);
}

// Тест 54: Треугольники с веерным расположением
TEST(TriangleIntersectionTest, FanArrangement) 
{
    std::vector<Triangle> triangles;
    for (int i = 0; i < 10; i++) {
        double angle = i * M_PI / 5;
        triangles.push_back(Triangle(
            0, 0, 0,
            cos(angle), sin(angle), 0,
            cos(angle + M_PI/10), sin(angle + M_PI/10), 0
        ));
    }
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 10);
}

// Тест 55: Треугольники со спиральным расположением
TEST(TriangleIntersectionTest, SpiralArrangement) 
{
    std::vector<Triangle> triangles;
    for (int i = 0; i < 5; i++) {
        double angle = i * 2 * M_PI / 5;
        triangles.push_back(Triangle(
            cos(angle), sin(angle), i * 0.1,
            cos(angle + 2*M_PI/5), sin(angle + 2*M_PI/5), i * 0.1,
            0, 0, i * 0.1 + 0.05
        ));
    }
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_EQ(result.size(), 0);
}

// Тест 56: Производительность с большим количеством треугольников
TEST(TriangleIntersectionTest, PerformanceTest) 
{
    std::vector<Triangle> triangles;
    int n = 100;
    
    for (int i = 0; i < n; i++) {
        double x = i * 3.0;
        triangles.push_back(Triangle(
            x, 0, 0,
            x + 1, 0, 0,
            x, 1, 0
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
    std::vector<Triangle> triangles = {
        Triangle(DBL_MIN, DBL_MIN, DBL_MIN, DBL_MIN, 0, DBL_MIN, 0, DBL_MIN, DBL_MIN),
        Triangle(0, 0, 0, DBL_MIN, 0, 0, 0, DBL_MIN, 0)
    };
    std::vector<int> result = findIntersectingTriangles(triangles);
    EXPECT_TRUE(result.size() >= 0);
}

// Тест 58: 1000 треугольников без пересечений
TEST(PerformanceTest, Grid1000TrianglesNoIntersections) 
{
    std::vector<Triangle> triangles;
    int size = 10;
    int counter = 1;
    
    for (int x = 0; x < size; x++) 
    {
        for (int y = 0; y < size; y++) 
        {
            for (int z = 0; z < size; z++) 
            {
                double base_x = x * 5.0;
                double base_y = y * 5.0;
                double base_z = z * 5.0;
                
                triangles.push_back(Triangle(
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

// Тест 59: 20000 треугольников в случайных положениях
TEST(PerformanceTest, Random2000Triangles) 
{
    std::vector<Triangle> triangles;
    std::srand(42); 
    
    for (int i = 0; i < 2000; i++) 
    {
        double center_x = (std::rand() % 1000) / 10.0;
        double center_y = (std::rand() % 1000) / 10.0;
        double center_z = (std::rand() % 1000) / 10.0;
        
        double size = 1.0 + (std::rand() % 100) / 100.0; 
        
        triangles.push_back(Triangle(
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

// Тест 60: 1000 треугольников, все пересекаются в одной точке
TEST(PerformanceTest, AllTrianglesIntersectAtCenter) 
{
    std::vector<Triangle> triangles;
    
    for (int i = 0; i < 1000; i++) 
    {
        double angle = i * 2 * M_PI / 1000;
        double next_angle = (i + 1) * 2 * M_PI / 1000;
        
        triangles.push_back(Triangle(
            0, 0, 0, 
            cos(angle), sin(angle), 0,
            cos(next_angle), sin(next_angle), 0
        ));
    }
    
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> result = findIntersectingTriangles(triangles);
    auto end = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    EXPECT_EQ(result.size(), 1000); 
    EXPECT_TRUE(duration.count() < 50000);
}

// Тест 61: Вырожденные треугольники среди нормальных
TEST(PerformanceTest, MixedDegenerateAndNormalTriangles) 
{
    std::vector<Triangle> triangles;
    
    // Нормальные треугольники
    for (int i = 0; i < 200; i++) 
    {
        triangles.push_back(Triangle(
            i * 3.0, 0, 0,
            i * 3.0 + 1.0, 0, 0,
            i * 3.0, 1.0, 0
        ));
    }
    
    // Вырожденные треугольники (точки)
    for (int i = 0; i < 100; i++) 
    {
        triangles.push_back(Triangle(
            i * 3.0, 100, 100,
            i * 3.0, 100, 100,
            i * 3.0, 100, 100
        ));
    }
    
    // Вырожденные треугольники (линии)
    for (int i = 0; i < 1000; i++) 
    {
        triangles.push_back(Triangle(
            i * 3.0, 200, 200,
            i * 3.0 + 1.0, 200, 200, 
            i * 3.0 + 0.5, 200, 200
        ));
    }
    
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> result = findIntersectingTriangles(triangles);
    auto end = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    EXPECT_EQ(result.size(), 0); 
    EXPECT_TRUE(duration.count() < 10000);
}

// Тест 62: Случайные треугольники с различными ориентациями
TEST(PerformanceTest, RandomOrientations) 
{
    std::vector<Triangle> triangles;
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
        
        triangles.push_back(Triangle(
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

// Тест 63: Extreme performance test - максимальная нагрузка
TEST(PerformanceTest, ExtremeLoadTest) 
{
    std::vector<Triangle> triangles;
    
    for (int x = 0; x < 15; x++)
    {
        for (int y = 0; y < 10; y++) 
        {
            for (int z = 0; z < 10; z++) 
            {
                double base_x = x * 0.1;
                double base_y = y * 0.1;
                double base_z = z * 0.1;
                
                triangles.push_back(Triangle(
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