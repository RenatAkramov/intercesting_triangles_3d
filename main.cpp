#include "include/triangle_geometry.hpp"
#include <limits>
#include <sstream>

using namespace TriangleGeometry;




int main()
{
    auto triangles = create_triangles<double>();
    
    if (triangles.empty() && std::cin.fail()) 
    {
        std::cerr << "Программа завершена из-за ошибок ввода." << std::endl;
        return 1;
    }
    
    std::vector<int> intersecting = findIntersectingTriangles(triangles);

    for (int index : intersecting) 
    {
        std::cout << index << std::endl;
    }
      
    return 0;
}

