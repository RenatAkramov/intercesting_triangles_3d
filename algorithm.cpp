#include "include/main.hpp"

const double EPS = 1e-10;

static bool tolerant_compare(double a, double b) 
{
    double diff = std::fabs(a - b);
    if (diff <= EPS) return true;
    else return false;
}

static bool check_interval_overlap(double a_min, double a_max, double b_min, double b_max) 
{
    if (a_min > a_max) std::swap(a_min, a_max);
    if (b_min > b_max) std::swap(b_min, b_max);
    
    return !(a_max < b_min - EPS || b_max < a_min - EPS);
}

static bool compareMinX(const Triangle& a, const Triangle& b)
{
    return std::min({a.getP1().getX(), a.getP2().getX(), a.getP3().getX()}) < std::min({b.getP1().getX(), b.getP2().getX(), b.getP3().getX()});
}

AABB computeAABB(const Triangle& t) 
{
    AABB box;
    Point3D p1 = t.getP1();
    Point3D p2 = t.getP2();
    Point3D p3 = t.getP3();

    box.min[0] = std::min({p1.getX(), p2.getX(), p3.getX()});
    box.max[0] = std::max({p1.getX(), p2.getX(), p3.getX()});
    box.min[1] = std::min({p1.getY(), p2.getY(), p3.getY()});
    box.max[1] = std::max({p1.getY(), p2.getY(), p3.getY()});
    box.min[2] = std::min({p1.getZ(), p2.getZ(), p3.getZ()});
    box.max[2] = std::max({p1.getZ(), p2.getZ(), p3.getZ()});

    return box;
}

static bool checkAABBIntersectionYZ(const AABB& a, const AABB& b) 
{
    return check_interval_overlap(a.min[1], a.max[1], b.min[1], b.max[1]) &&
           check_interval_overlap(a.min[2], a.max[2], b.min[2], b.max[2]);
}

static Point3D crossProduct(const Point3D& a, const Point3D& b) 
{
    return Point3D(
        a.getY() * b.getZ() - a.getZ() * b.getY(),
        a.getZ() * b.getX() - a.getX() * b.getZ(),
        a.getX() * b.getY() - a.getY() * b.getX());
}

static double dotProduct(const Point3D& a, const Point3D& b) 
{
    return a.getX() * b.getX() + a.getY() * b.getY() + a.getZ() * b.getZ();
}

static double sign(double x1, double y1, double x2, double y2, double x3, double y3) 
{
    return (x1 - x3) * (y2 - y3) - (x2 - x3) * (y1 - y3);
}

static bool pointInTriangle2D(double x, double y,
                             double x1, double y1, double x2, double y2, double x3, double y3) 
{
    double d1 = sign(x, y, x1, y1, x2, y2);
    double d2 = sign(x, y, x2, y2, x3, y3);
    double d3 = sign(x, y, x3, y3, x1, y1);
    
    bool has_neg = (d1 < -EPS) || (d2 < -EPS) || (d3 < -EPS);
    bool has_pos = (d1 > EPS) || (d2 > EPS) || (d3 > EPS);
    
    return !(has_neg && has_pos);
}

static bool segmentsIntersect2D(double x1, double y1, double x2, double y2,
                               double x3, double y3, double x4, double y4) 
{
    double denom = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    if (std::fabs(denom) < EPS) return false;
    
    double t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / denom;
    double u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / denom;
    
    return (t >= -EPS && t <= 1.0 + EPS && u >= -EPS && u <= 1.0 + EPS);
}

static bool coplanarSegmentTriangleIntersection(const Point3D& p1, const Point3D& p2,
                                              const Point3D& a, const Point3D& b, const Point3D& c) 
{
    Point3D normal = crossProduct(b - a, c - a);
    
    int maxIndex = 0;
    double maxVal = std::fabs(normal.getX());
    if (std::fabs(normal.getY()) > maxVal) 
    {
        maxIndex = 1;
        maxVal = std::fabs(normal.getY());
    }
    if (std::fabs(normal.getZ()) > maxVal) 
    {
        maxIndex = 2;
    }
    
    auto project = [maxIndex](const Point3D& p) -> std::pair<double, double> 
    {
        if (maxIndex == 0) return {p.getY(), p.getZ()};
        if (maxIndex == 1) return {p.getX(), p.getZ()};
        return {p.getX(), p.getY()};
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

static bool pointInTriangle(const Point3D& p, const Point3D& a, const Point3D& b, const Point3D& c) 
{
    Point3D v0 = b - a;
    Point3D v1 = c - a;
    Point3D v2 = p - a;
    
    double d00 = dotProduct(v0, v0);
    double d01 = dotProduct(v0, v1);
    double d11 = dotProduct(v1, v1);
    double d20 = dotProduct(v2, v0);
    double d21 = dotProduct(v2, v1);
    
    double denom = d00 * d11 - d01 * d01;
    if (std::fabs(denom) < EPS) return false;
    
    double v = (d11 * d20 - d01 * d21) / denom;
    double w = (d00 * d21 - d01 * d20) / denom;
    double u = 1.0 - v - w;
    
    return (u >= -EPS) && (v >= -EPS) && (w >= -EPS);
}

static bool pointOnTriangleEdge(const Point3D& p, const Point3D& a, const Point3D& b, const Point3D& c) 
{
    auto pointOnSegment = [](const Point3D& p, const Point3D& a, const Point3D& b) -> bool 
    {
        Point3D ab = b - a;
        Point3D ap = p - a;
        
        if (dotProduct(crossProduct(ab, ap), crossProduct(ab, ap)) > EPS)
            return false;
        
        double t = dotProduct(ap, ab) / dotProduct(ab, ab);
        return t >= -EPS && t <= 1.0 + EPS;
    };
    
    return pointOnSegment(p, a, b) || pointOnSegment(p, b, c) || pointOnSegment(p, c, a);
}

static bool segmentsIntersect(const Point3D& p1, const Point3D& p2,
                             const Point3D& q1, const Point3D& q2) 
{
    Point3D d1 = p2 - p1;
    Point3D d2 = q2 - q1;
    Point3D r = p1 - q1;
    
    Point3D cross_d1_d2 = crossProduct(d1, d2);
    double denom = dotProduct(cross_d1_d2, cross_d1_d2);
    
    if (std::fabs(denom) < EPS) 
    {
        return false;
    }
    
    double t = dotProduct(crossProduct(r, d2), cross_d1_d2) / denom;
    double u = dotProduct(crossProduct(r, d1), cross_d1_d2) / denom;
    
    return (t >= -EPS && t <= 1.0 + EPS && u >= -EPS && u <= 1.0 + EPS);
}

static bool segmentTriangleIntersection(const Point3D& p1, const Point3D& p2,
                                       const Point3D& a, const Point3D& b, const Point3D& c) 
{
    Point3D ab = b - a;
    Point3D ac = c - a;
    Point3D qp = p1 - p2;
    
    Point3D n = crossProduct(ab, ac);
    double denom = dotProduct(qp, n);
    
    if (std::fabs(denom) < EPS) 
    {
        if (std::fabs(dotProduct(p1 - a, n)) < EPS) 
        {
            return coplanarSegmentTriangleIntersection(p1, p2, a, b, c);
        }
        return false;
    }
    
    double inv_denom = 1.0 / denom;
    Point3D ap = p1 - a;
    double t = dotProduct(ap, n) * inv_denom;
    
    if (t < -EPS || t > 1.0 + EPS) 
    {
        return false;
    }
    
    Point3D e = crossProduct(qp, ap);
    double v = dotProduct(ac, e) * inv_denom;
    double w = -dotProduct(ab, e) * inv_denom;
    double u = 1.0 - v - w;
    
    return (u >= -EPS) && (v >= -EPS) && (w >= -EPS) &&
           (u <= 1.0 + EPS) && (v <= 1.0 + EPS) && (w <= 1.0 + EPS);
}

static bool isTriangleDegenerate(const Point3D& a, const Point3D& b, const Point3D& c) 
{
    if (tolerant_compare(a.getX(), b.getX()) && tolerant_compare(a.getY(), b.getY()) && tolerant_compare(a.getZ(), b.getZ())) return true;
    if (tolerant_compare(a.getX(), c.getX()) && tolerant_compare(a.getY(), c.getY()) && tolerant_compare(a.getZ(), c.getZ())) return true;
    if (tolerant_compare(b.getX(), c.getX()) && tolerant_compare(b.getY(), c.getY()) && tolerant_compare(b.getZ(), c.getZ())) return true;
    
    Point3D ab = b - a;
    Point3D ac = c - a;
    Point3D cross = crossProduct(ab, ac);
    
    return dotProduct(cross, cross) < EPS * EPS;
}

static bool checkPlaneSeparation(const Point3D& a1, const Point3D& b1, const Point3D& c1,
                                const Point3D& n1, const Point3D& a2, const Point3D& b2, const Point3D& c2) 
{
    double d1 = dotProduct(n1, a1);
    double d_a2 = dotProduct(n1, a2) - d1;
    double d_b2 = dotProduct(n1, b2) - d1;
    double d_c2 = dotProduct(n1, c2) - d1;
    
    if (d_a2 > EPS && d_b2 > EPS && d_c2 > EPS) return false;
    if (d_a2 < -EPS && d_b2 < -EPS && d_c2 < -EPS) return false;
    
    return true;
}

static bool checkAxisSeparation(const Point3D& a1, const Point3D& b1, const Point3D& c1,
                               const Point3D& a2, const Point3D& b2, const Point3D& c2,
                               const Point3D& axis) 
{
    if (dotProduct(axis, axis) < EPS * EPS) return true;
    
    double proj1a = dotProduct(a1, axis);
    double proj1b = dotProduct(b1, axis);
    double proj1c = dotProduct(c1, axis);
    double min1 = std::min({proj1a, proj1b, proj1c});
    double max1 = std::max({proj1a, proj1b, proj1c});
    
    double proj2a = dotProduct(a2, axis);
    double proj2b = dotProduct(b2, axis);
    double proj2c = dotProduct(c2, axis);
    double min2 = std::min({proj2a, proj2b, proj2c});
    double max2 = std::max({proj2a, proj2b, proj2c});
    
    return !(max1 < min2 - EPS || max2 < min1 - EPS);
}

static bool checkEdgeAxisSeparation(const Point3D& a1, const Point3D& b1, const Point3D& c1,
                                    const Point3D& a2, const Point3D& b2, const Point3D& c2) 
{
    Point3D edges1[3] = {b1 - a1, c1 - b1, a1 - c1};
    Point3D edges2[3] = {b2 - a2, c2 - b2, a2 - c2};
    
    for (int i = 0; i < 3; i++) 
    {
        for (int j = 0; j < 3; j++) 
        {
            Point3D axis = crossProduct(edges1[i], edges2[j]);
            
            if (dotProduct(axis, axis) < EPS * EPS) continue;
            
            if (!checkAxisSeparation(a1, b1, c1, a2, b2, c2, axis)) 
            {
                return false;
            }
        }
    }
    
    return true;
}

static bool coplanarTrianglesIntersect(const Point3D& a1, const Point3D& b1, const Point3D& c1,
                                      const Point3D& a2, const Point3D& b2, const Point3D& c2) 
{
    Point3D edges1[3][2] = {{a1, b1}, {b1, c1}, {c1, a1}};
    Point3D edges2[3][2] = {{a2, b2}, {b2, c2}, {c2, a2}};
    
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

static bool triangleIntersection(const Triangle& t1, const Triangle& t2) 
{
    const Point3D& a1 = t1.getP1();
    const Point3D& b1 = t1.getP2();
    const Point3D& c1 = t1.getP3();
    
    const Point3D& a2 = t2.getP1();
    const Point3D& b2 = t2.getP2();
    const Point3D& c2 = t2.getP3();
    
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
    
    Point3D edges1[3][2] = {{a1, b1}, {b1, c1}, {c1, a1}};
    Point3D edges2[3][2] = {{a2, b2}, {b2, c2}, {c2, a2}};
    
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
    
    double dist_a1 = dotProduct(n2, a1 - a2);
    double dist_b1 = dotProduct(n2, b1 - a2);
    double dist_c1 = dotProduct(n2, c1 - a2);
    
    if (std::fabs(dist_a1) < EPS && std::fabs(dist_b1) < EPS && std::fabs(dist_c1) < EPS) 
    {
        return coplanarTrianglesIntersect(a1, b1, c1, a2, b2, c2);
    }
    
    return false;
}

std::vector<int> findIntersectingTriangles(const std::vector<Triangle>& triangles) 
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
            result.push_back(triangles[i].getNumber());
        }
    }

    std::sort(result.begin(), result.end());
    return result;
}