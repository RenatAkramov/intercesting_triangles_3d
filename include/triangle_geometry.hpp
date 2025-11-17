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
    const long double EPS = 1e-10;

    template <typename type = double>
    class Point3D
    {
    public:
        type x, y, z;

        Point3D() : x(0), y(0), z(0) {}
        Point3D(type x, type y, type z) : x(x), y(y), z(z) {}
        
        Point3D operator-(const Point3D& other) const 
        {
            return Point3D(x - other.x, y - other.y, z - other.z);
        }
    };

    template <typename type = double>
    class Triangle
    {
    public:
        Point3D<type> p1, p2, p3;
        Triangle() = default;
        Triangle(type x1, type y1, type z1, 
                type x2, type y2, type z2,
                type x3, type y3, type z3) 
                : p1(x1, y1, z1), p2(x2, y2, z2), p3(x3, y3, z3) {}   

        Point3D<type> getP1() const { return p1; }
        Point3D<type> getP2() const { return p2; }
        Point3D<type> getP3() const { return p3; }       
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
    


    template <typename type>
    bool check_interval_overlap(type a_min, type a_max, type b_min, type b_max) 
    {
        if (a_min > a_max) std::swap(a_min, a_max);
        if (b_min > b_max) std::swap(b_min, b_max);
        
        return !(a_max < b_min - EPS || b_max < a_min - EPS);
    }


    template <typename type>
    bool compareMinX(const Triangle<type>& a, const Triangle<type>& b)
    {
        return std::min({a.getP1().x, a.getP2().x, a.getP3().x}) < std::min({b.getP1().x, b.getP2().x, b.getP3().x});
    }

    template <typename type>
    type sign(type x1, type y1, type x2, type y2, type x3, type y3) 
    {
        return (x1 - x3) * (y2 - y3) - (x2 - x3) * (y1 - y3);
    }

    template <typename type>
    bool pointOnTriangleEdge(const Point3D<type>& p, const Point3D<type>& a, const Point3D<type>& b, const Point3D<type>& c) 
    {
        auto pointOnSegment = [](const Point3D<type>& p, const Point3D<type>& a, const Point3D<type>& b) -> bool 
        {
            Point3D<type> ab = b - a;
            Point3D<type> ap = p - a;
            
            if (dotProduct(crossProduct(ab, ap), crossProduct(ab, ap)) > EPS) return false;
            
            double t = dotProduct(ap, ab) / dotProduct(ab, ab);
            return t >= -EPS && t <= 1.0 + EPS;
        };
        
        return pointOnSegment(p, a, b) || pointOnSegment(p, b, c) || pointOnSegment(p, c, a);
    }

    template <typename type>
    bool segmentsIntersect(const Point3D<type>& p1, const Point3D<type>& p2,
                          const Point3D<type>& q1, const Point3D<type>& q2) 
    {
        Point3D<type> d1 = p2 - p1;
        Point3D<type> d2 = q2 - q1;
        Point3D<type> r = p1 - q1;
        
        Point3D<type> cross_d1_d2 = crossProduct(d1, d2);
        double denom = dotProduct(cross_d1_d2, cross_d1_d2);
        
        if (std::fabs(denom) < EPS) 
        {
            return false;
        }
        
        double t = dotProduct(crossProduct(r, d2), cross_d1_d2) / denom;
        double u = dotProduct(crossProduct(r, d1), cross_d1_d2) / denom;
        
        return (t >= -EPS && t <= 1.0 + EPS && u >= -EPS && u <= 1.0 + EPS);
    }


    template <typename type>
    bool pointInTriangle2D(type x, type y,
                          type x1, type y1, type x2, type y2, type x3, type y3) 
    {
        type d1 = sign(x, y, x1, y1, x2, y2);
        type d2 = sign(x, y, x2, y2, x3, y3);
        type d3 = sign(x, y, x3, y3, x1, y1);
        
        bool has_neg = (d1 < -EPS) || (d2 < -EPS) || (d3 < -EPS);
        bool has_pos = (d1 > EPS) || (d2 > EPS) || (d3 > EPS);
        
        return !(has_neg && has_pos);
    }

    template <typename type>
    bool pointInTriangle(const Point3D<type>& p, const Point3D<type>& a, const Point3D<type>& b, const Point3D<type>& c) 
    {
        Point3D<type> v0 = b - a;
        Point3D<type> v1 = c - a;
        Point3D<type> v2 = p - a;
        
        type d00 = dotProduct(v0, v0);
        type d01 = dotProduct(v0, v1);
        type d11 = dotProduct(v1, v1);
        type d20 = dotProduct(v2, v0);
        type d21 = dotProduct(v2, v1);
        
        type denom = d00 * d11 - d01 * d01;
        if (std::fabs(denom) < EPS) return false;
        
        type v = (d11 * d20 - d01 * d21) / denom;
        type w = (d00 * d21 - d01 * d20) / denom;
        type u = 1.0 - v - w;
        
        return (u >= -EPS) && (v >= -EPS) && (w >= -EPS);
    }

    template <typename type>
    bool segmentsIntersect2D(type x1, type y1, type x2, type y2,
                            type x3, type y3, type x4, type y4) 
    {
        type denom = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
        if (std::fabs(denom) < EPS) return false;
        
        type t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / denom;
        type u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / denom;
        
        return (t >= -EPS && t <= 1.0 + EPS && u >= -EPS && u <= 1.0 + EPS);
    }

    template <typename type>
    bool coplanarSegmentTriangleIntersection(const Point3D<type>& p1, const Point3D<type>& p2,
                                            const Point3D<type>& a, const Point3D<type>& b, const Point3D<type>& c) 
    {
        Point3D<type> normal = crossProduct(b - a, c - a);
        
        int maxIndex = 0;
        type maxVal = std::fabs(normal.x);
        if (std::fabs(normal.y) > maxVal) 
        {
            maxIndex = 1;
            maxVal = std::fabs(normal.y);
        }
        if (std::fabs(normal.z) > maxVal) 
        {
            maxIndex = 2;
        }
        
        auto project = [maxIndex](const Point3D<type>& p) -> std::pair<type, type> 
        {
            if (maxIndex == 0) return {p.y, p.z};
            if (maxIndex == 1) return {p.x, p.z};
            return {p.x, p.y};
        };
        
        auto [p1x, p1y] = project(p1);
        auto [p2x, p2y] = project(p2);
        auto [ax, ay] = project(a);
        auto [bx, by] = project(b);
        auto [cx, cy] = project(c);
        
        return segmentsIntersect2D(p1x, p1y, p2x, p2y, ax, ay, bx, by) ||
               segmentsIntersect2D(p1x, p1y, p2x, p2y, bx, by, cx, cy) ||
               segmentsIntersect2D(p1x, p1y, p2x, p2y, cx, cy, ax, ay) ||
               (pointInTriangle2D(p1x, p1y, ax, ay, bx, by, cx, cy) &&
                pointInTriangle2D(p2x, p2y, ax, ay, bx, by, cx, cy));
    }

    template <typename type>
    bool coplanarTrianglesIntersect(const Point3D<type>& a1, const Point3D<type>& b1, const Point3D<type>& c1,
                                  const Point3D<type>& a2, const Point3D<type>& b2, const Point3D<type>& c2) 
    {
        Point3D<type> edges1[3][2] = {{a1, b1}, {b1, c1}, {c1, a1}};
        Point3D<type> edges2[3][2] = {{a2, b2}, {b2, c2}, {c2, a2}};
        
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (segmentsIntersect(edges1[i][0], edges1[i][1], edges2[j][0], edges2[j][1])) 
                {
                    return true;
                }
            }
        }
        
        if (pointInTriangle(a1, a2, b2, c2) || pointInTriangle(b1, a2, b2, c2) || 
            pointInTriangle(c1, a2, b2, c2) || pointInTriangle(a2, a1, b1, c1) || 
            pointInTriangle(b2, a1, b1, c1) || pointInTriangle(c2, a1, b1, c1)) {
            return true;
        }
        
        return false;
    }

    template <typename type>
    bool segmentTriangleIntersection(const Point3D<type>& p1, const Point3D<type>& p2,
                                   const Point3D<type>& a, const Point3D<type>& b, const Point3D<type>& c) 
    {
        Point3D<type> ab = b - a;
        Point3D<type> ac = c - a;
        Point3D<type> qp = p1 - p2;
        
        Point3D<type> n = crossProduct(ab, ac);
        type denom = dotProduct(qp, n);
        
        if (std::fabs(denom) < EPS) 
        {
            if (std::fabs(dotProduct(p1 - a, n)) < EPS) 
            {
                return coplanarSegmentTriangleIntersection(p1, p2, a, b, c);
            }
            return false;
        }
        
        type inv_denom = 1.0 / denom;
        Point3D<type> ap = p1 - a;
        type t = dotProduct(ap, n) * inv_denom;
        
        if (t < -EPS || t > 1.0 + EPS) 
        {
            return false;
        }
        
        Point3D<type> e = crossProduct(qp, ap);
        type v = dotProduct(ac, e) * inv_denom;
        type w = -dotProduct(ab, e) * inv_denom;
        type u = 1.0 - v - w;
        
        return (u >= -EPS) && (v >= -EPS) && (w >= -EPS) &&
               (u <= 1.0 + EPS) && (v <= 1.0 + EPS) && (w <= 1.0 + EPS);
    }

    template <typename type>
    bool checkEdgeAxisSeparation(const Point3D<type>& a1, const Point3D<type>& b1, const Point3D<type>& c1,
                                const Point3D<type>& a2, const Point3D<type>& b2, const Point3D<type>& c2) 
    {
        Point3D<type> edges1[3] = {b1 - a1, c1 - b1, a1 - c1};
        Point3D<type> edges2[3] = {b2 - a2, c2 - b2, a2 - c2};
        
        for (int i = 0; i < 3; i++) 
        {
            for (int j = 0; j < 3; j++) 
            {
                Point3D<type> axis = crossProduct(edges1[i], edges2[j]);
                
                if (dotProduct(axis, axis) < EPS * EPS) continue;
                
                if (!checkAxisSeparation(a1, b1, c1, a2, b2, c2, axis)) 
                {
                    return false;
                }
            }
        }
        
        return true;
    }

    template <typename type>
    type dotProduct(const Point3D<type>& a, const Point3D<type>& b) 
    {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    template <typename type>
    bool checkAxisSeparation(const Point3D<type>& a1, const Point3D<type>& b1, const Point3D<type>& c1,
                           const Point3D<type>& a2, const Point3D<type>& b2, const Point3D<type>& c2,
                           const Point3D<type>& axis) 
    {
        if (dotProduct(axis, axis) < EPS * EPS) return true;
        
        type proj1a = dotProduct(a1, axis);
        type proj1b = dotProduct(b1, axis);
        type proj1c = dotProduct(c1, axis);
        type min1 = std::min({proj1a, proj1b, proj1c});
        type max1 = std::max({proj1a, proj1b, proj1c});
        
        type proj2a = dotProduct(a2, axis);
        type proj2b = dotProduct(b2, axis);
        type proj2c = dotProduct(c2, axis);
        type min2 = std::min({proj2a, proj2b, proj2c});
        type max2 = std::max({proj2a, proj2b, proj2c});
        
        return !(max1 < min2 - EPS || max2 < min1 - EPS);
    }

    template <typename type>
    bool checkPlaneSeparation(const Point3D<type>& a1, const Point3D<type>& b1, const Point3D<type>& c1,
                            const Point3D<type>& n1, const Point3D<type>& a2, const Point3D<type>& b2, const Point3D<type>& c2) 
    {
        type d1 = dotProduct(n1, a1);
        type d_a2 = dotProduct(n1, a2) - d1;
        type d_b2 = dotProduct(n1, b2) - d1;
        type d_c2 = dotProduct(n1, c2) - d1;
        
        if (d_a2 > EPS && d_b2 > EPS && d_c2 > EPS) return false;
        if (d_a2 < -EPS && d_b2 < -EPS && d_c2 < -EPS) return false;
        
        return true;
    }

    template<typename type>
    Point3D<type> crossProduct(const Point3D<type>& a, const Point3D<type>& b) 
    {
        return Point3D<type>(a.y * b.z - a.z * b.y,
                             a.z * b.x - a.x * b.z,
                             a.x * b.y - a.y * b.x);
    }

    template<typename type>
    bool tolerant_compare(type a, type b) 
    {
        type diff = std::fabs(a - b);
        if (diff <= EPS) return true;
        else return false;
    }

    template <typename type>
    bool isTriangleDegenerate(const Point3D<type>& a, const Point3D<type>& b, const Point3D<type>& c) 
    {
        if (tolerant_compare(a.x, b.x) && tolerant_compare(a.y, b.y) && tolerant_compare(a.z, b.z)) return true;
        if (tolerant_compare(a.x, c.x) && tolerant_compare(a.y, c.y) && tolerant_compare(a.z, c.z)) return true;
        if (tolerant_compare(b.x, c.x) && tolerant_compare(b.y, c.y) && tolerant_compare(b.z, c.z)) return true;
        
        Point3D<type> ab = b - a;
        Point3D<type> ac = c - a;
        Point3D<type> cross = crossProduct(ab, ac);
        
        return dotProduct(cross, cross) < EPS * EPS;
    }

    template <typename type>
    bool triangleIntersection(const Triangle<type>& t1, const Triangle<type>& t2) 
    {
        const Point3D<type>& a1 = t1.getP1();
        const Point3D<type>& b1 = t1.getP2();
        const Point3D<type>& c1 = t1.getP3();
        
        const Point3D<type>& a2 = t2.getP1();
        const Point3D<type>& b2 = t2.getP2();
        const Point3D<type>& c2 = t2.getP3();
        
        if (isTriangleDegenerate(a1, b1, c1) || isTriangleDegenerate(a2, b2, c2)) 
        {
            return false;
        }
        
        Point3D n1 = crossProduct(b1 - a1, c1 - a1);
        Point3D n2 = crossProduct(b2 - a2, c2 - a2);
        
        if (!checkPlaneSeparation(a1, b1, c1, n1, a2, b2, c2) ||
            !checkPlaneSeparation(a2, b2, c2, n2, a1, b1, c1)) 
        {
            return false;
        }
        
        if (!checkAxisSeparation(a1, b1, c1, a2, b2, c2, n1) ||
            !checkAxisSeparation(a1, b1, c1, a2, b2, c2, n2) ||
            !checkEdgeAxisSeparation(a1, b1, c1, a2, b2, c2)) 
        {
            return false;
        }
        
        Point3D<type> edges1[3][2] = {{a1, b1}, {b1, c1}, {c1, a1}};
        Point3D<type> edges2[3][2] = {{a2, b2}, {b2, c2}, {c2, a2}};
        
        for (int i = 0; i < 3; i++) 
        {
            for (int j = 0; j < 3; j++) 
            {
                if (segmentTriangleIntersection(edges1[i][0], edges1[i][1], a2, b2, c2) ||
                    segmentTriangleIntersection(edges2[j][0], edges2[j][1], a1, b1, c1)) {
                    return true;
                }
            }
        }
        
        type dist_a1 = dotProduct(n2, a1 - a2);
        type dist_b1 = dotProduct(n2, b1 - a2);
        type dist_c1 = dotProduct(n2, c1 - a2);
        
        if (std::fabs(dist_a1) < EPS && std::fabs(dist_b1) < EPS && std::fabs(dist_c1) < EPS) 
        {
            return coplanarTrianglesIntersect(a1, b1, c1, a2, b2, c2);
        }
        
        return false;
    }

    template <typename type>
    bool is_valid_number(type value) 
    {
        return !std::isnan(value) && !std::isinf(value) && value != std::numeric_limits<type>::max();
    }


    bool checkAABBIntersectionYZ(const AABB& a, const AABB& b) 
    {
        return check_interval_overlap(a.min[1], a.max[1], b.min[1], b.max[1]) &&
               check_interval_overlap(a.min[2], a.max[2], b.min[2], b.max[2]);
    }

    template <typename type>
    std::vector<Triangle<type>> create_triangles()
    {
        int numbers_triangles = -1;

        if (!(std::cin >> numbers_triangles)) 
        {
            std::cerr << "Ошибка: ожидается целое число для количества треугольников" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return {};
        }
        
        if (numbers_triangles < 0) 
        {
            std::cerr << "Ошибка: количество треугольников не может быть отрицательным" << std::endl;
            return {};
        }
        
        if (numbers_triangles > 1000000) 
        {
            std::cerr << "Ошибка: слишком большое количество треугольников (максимум 1000000)" << std::endl;
            return {};
        }

        
        std::vector<Triangle<type>> triangles;
        triangles.reserve(numbers_triangles);

        for (int i = 0; i < numbers_triangles; i++)
        {
            type x1, y1, z1, x2, y2, z2, x3, y3, z3;
            
            if (!(std::cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> x3 >> y3 >> z3)) 
            {
                std::cerr << "Ошибка: ожидается 9 вещественных чисел для координат треугольника " << (i + 1) << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return {};
            }

            if (!is_valid_number(x1) || !is_valid_number(y1) || !is_valid_number(z1) ||
                !is_valid_number(x2) || !is_valid_number(y2) || !is_valid_number(z2) ||
                !is_valid_number(x3) || !is_valid_number(y3) || !is_valid_number(z3)) 
            {
                std::cerr << "Ошибка: координаты треугольника " << (i + 1) << " содержат недопустимые значения" << std::endl;
                return {};
            }

            triangles.emplace_back(x1, y1, z1, x2, y2, z2, x3, y3, z3);
        }
    
        return triangles;
    }


    template <typename type>
    std::vector<int> findIntersectingTriangles(const std::vector<Triangle<type>>& triangles)
    {
        int n = triangles.size();
        if (n == 0) return {};

        std::vector<AABB> aabbs(n);
        for (int i = 0; i < n; i++) 
        {
            aabbs[i] = computeAABB(triangles[i]);
        }

        std::vector<Event> events;
        for (int i = 0; i < n; i++) 
        {
            events.push_back(Event(aabbs[i].min[0], i, true));
            events.push_back(Event(aabbs[i].max[0], i, false));
        }
        std::sort(events.begin(), events.end());

        std::set<int> activeSet;
        std::vector<std::pair<int, int>> candidatePairs;

        for (const Event& event : events) 
        {
            if (event.isStart) 
            {
                for (int j : activeSet) 
                {
                    if (checkAABBIntersectionYZ(aabbs[event.index], aabbs[j])) 
                    {
                        int i1 = event.index;
                        int i2 = j;
                        if (i1 > i2) std::swap(i1, i2);
                        candidatePairs.emplace_back(i1, i2);
                    }
                }
                activeSet.insert(event.index);
            } 
            else 
            {
                activeSet.erase(event.index);
            }
        }

        std::sort(candidatePairs.begin(), candidatePairs.end());
        candidatePairs.erase(std::unique(candidatePairs.begin(), candidatePairs.end()), candidatePairs.end());

        std::vector<bool> hasIntersection(n, false);
        for (auto& p : candidatePairs) 
        {
            if (triangleIntersection(triangles[p.first], triangles[p.second])) 
            {
                hasIntersection[p.first] = true;
                hasIntersection[p.second] = true;
            }
        }

        std::vector<int> result;
        for (int i = 0; i < n; i++) 
        {
            if (hasIntersection[i]) 
            {
                result.push_back(i);
            }
        }

        std::sort(result.begin(), result.end());
        return result;
    }

    template <typename type>
    AABB computeAABB(const Triangle<type>& t)
    {
        AABB box;
        Point3D p1 = t.getP1();
        Point3D p2 = t.getP2();
        Point3D p3 = t.getP3();

        box.min[0] = std::min({p1.x, p2.x, p3.x});
        box.max[0] = std::max({p1.x, p2.x, p3.x});
        box.min[1] = std::min({p1.y, p2.y, p3.y});
        box.max[1] = std::max({p1.y, p2.y, p3.y});
        box.min[2] = std::min({p1.z, p2.z, p3.z});
        box.max[2] = std::max({p1.z, p2.z, p3.z});

        return box;
    }


    

} 

#endif 