#include "include/main.hpp"


const double EPS = 1e-12;


inline bool tolerant_compare(double a, double b, 
                            double abs_eps = 1e-12, 
                            double rel_eps = 1e-12) 
{
    double diff = std::fabs(a - b);
    if (diff <= abs_eps) return true;
    return diff <= std::max(std::fabs(a), std::fabs(b)) * rel_eps;
}

inline bool check_interval_overlap(double a_min, double a_max, double b_min, double b_max) 
{
    return (tolerant_compare(a_min, b_max) || a_min < b_max) &&
           (tolerant_compare(b_min, a_max) || b_min < a_max);
}

bool compareMinX(const Triangle& a, const Triangle& b)
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

static int orient3d(const Point3D& a, const Point3D& b, const Point3D& c, const Point3D& d) 
{
    double adx = a.getX() - d.getX();
    double bdx = b.getX() - d.getX();
    double cdx = c.getX() - d.getX();
    double ady = a.getY() - d.getY();
    double bdy = b.getY() - d.getY();
    double cdy = c.getY() - d.getY();
    double adz = a.getZ() - d.getZ();
    double bdz = b.getZ() - d.getZ();
    double cdz = c.getZ() - d.getZ();

    double det = adx * (bdy * cdz - bdz * cdy)
               + bdx * (cdy * adz - cdz * ady)
               + cdx * (ady * bdz - adz * bdy);

    double maxVal = std::max({std::abs(adx), std::abs(bdx), std::abs(cdx),
                             std::abs(ady), std::abs(bdy), std::abs(cdy),
                             std::abs(adz), std::abs(bdz), std::abs(cdz)});

    double scaledEps = EPS * maxVal * maxVal * maxVal;

    if (det > scaledEps) return 1;
    if (det < -scaledEps) return -1;
    return 0;
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

static bool pointInTriangle(const Point3D& p, const Point3D& a, const Point3D& b, const Point3D& c) 
{
    if (orient3d(a, b, c, p) != 0) return false;

    Point3D v0 = b - a;
    Point3D v1 = c - a;
    Point3D v2 = p - a;
    

    Point3D n = crossProduct(v0, v1);
    double denom = dotProduct(n, n);
    if (std::fabs(denom) < EPS) return false; 
    
    Point3D cross1 = crossProduct(v2, v1);
    double u = dotProduct(cross1, n) / denom;
    
    Point3D cross2 = crossProduct(v0, v2);
    double v = dotProduct(cross2, n) / denom;

    return (u >= -EPS) && (v >= -EPS) && (u + v <= 1.0 + EPS);
}

static bool triangleIntersection(const Triangle& t1, const Triangle& t2) 
{
    const Point3D& a1 = t1.getP1();
    const Point3D& b1 = t1.getP2();
    const Point3D& c1 = t1.getP3();
    
    const Point3D& a2 = t2.getP1();
    const Point3D& b2 = t2.getP2();
    const Point3D& c2 = t2.getP3();
    
    int o1 = orient3d(a1, b1, c1, a2);
    int o2 = orient3d(a1, b1, c1, b2);
    int o3 = orient3d(a1, b1, c1, c2);
    
    if (o1 == 0 && o2 == 0 && o3 == 0) {
        return pointInTriangle(a1, a2, b2, c2) ||
               pointInTriangle(b1, a2, b2, c2) ||
               pointInTriangle(c1, a2, b2, c2) ||
               pointInTriangle(a2, a1, b1, c1) ||
               pointInTriangle(b2, a1, b1, c1) ||
               pointInTriangle(c2, a1, b1, c1);
    }
    
    if (o1 * o2 > 0 && o1 * o3 > 0) return false;
    
    int o4 = orient3d(a2, b2, c2, a1);
    int o5 = orient3d(a2, b2, c2, b1);
    int o6 = orient3d(a2, b2, c2, c1);
    
    if (o4 * o5 > 0 && o4 * o6 > 0) return false;
    
    return true;
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

    return result;
}