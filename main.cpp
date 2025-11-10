#include "include/triangle_geometry.hpp"
#include <limits>
#include <sstream>

using namespace TriangleGeometry;


static bool is_valid_number(double value) 
{
    return !std::isnan(value) && !std::isinf(value) && value != std::numeric_limits<double>::max();
}


int main()
{
    std::vector<Triangle> triangles = create_triangles();
    
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

std::vector<Triangle> TriangleGeometry::create_triangles()
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

    
    std::vector<Triangle> triangles;
    triangles.reserve(numbers_triangles);

    for (int i = 0; i < numbers_triangles; i++)
    {
        double x1, y1, z1, x2, y2, z2, x3, y3, z3;
        
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