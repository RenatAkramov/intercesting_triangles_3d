#ifndef TRIANGLE_GEOMETRY_HPP
#define TRIANGLE_GEOMETRY_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>
#include <chrono>
#include <gtest/gtest.h>

namespace TriangleGeometry 
{

class Point3D
{
public:
    double x, y, z;

    Point3D() : x(0), y(0), z(0) {}
    Point3D(double x, double y, double z) : x(x), y(y), z(z) {}
    
    Point3D operator-(const Point3D& other) const 
    {
        return Point3D(x - other.x, y - other.y, z - other.z);
    }
};

class Triangle
{
private:
    Point3D p1, p2, p3;

public:
    Triangle() = default;
    Triangle(double x1, double y1, double z1, 
            double x2, double y2, double z2,
            double x3, double y3, double z3) 
            : p1(x1, y1, z1), p2(x2, y2, z2), p3(x3, y3, z3) {}   

    Point3D getP1() const { return p1; }
    Point3D getP2() const { return p2; }
    Point3D getP3() const { return p3; }       
};

class Event
{
public:
    double x;
    int index;
    bool isStart;

    Event() : x(0), index(0), isStart(false) {}
    Event(double x, int index, bool isStart) : x(x), index(index), isStart(isStart) {}

    bool operator<(const Event& other) const 
    {
        if (x != other.x) return x < other.x;
        if (isStart != other.isStart) return isStart;
        return index < other.index;
    }
};

struct AABB
{
    double min[3];
    double max[3];
};

std::vector<Triangle> create_triangles();
std::vector<int> findIntersectingTriangles(const std::vector<Triangle>& triangles);
AABB computeAABB(const Triangle& t);

} 

#endif 