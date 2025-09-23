#include "include/main.hpp"

int main()
{
    std::vector<Triangle> triangles = create_triangles();
    std::vector<int> intersecting = findIntersectingTriangles(triangles);


    for (int num : intersecting) 
    {
        std::cout << num << std::endl;
    }
    #ifdef DEBUG 
        std::cout << "Больше пересекающихся треугольников нет" << std::endl;
    #endif    
    return 0;
}

std::vector<Triangle> create_triangles()
{
    int numbers_triangles = -1;
    #ifdef DEBUG 
    std::cout << "Введите количество треугольников: ";
    #endif
    std::cin >> numbers_triangles;
    #ifdef DEBUG
    std::cout << "Вы ввели: " << numbers_triangles << " - количество треуголников" << std::endl;
    #endif
    std::vector<Triangle> triangles;

    for (int i = 0; i < numbers_triangles; i ++)
    {
        double x1, y1, z1, x2, y2, z2, x3, y3, z3;
        #ifdef DEBUG
        std::cout << "Введите 9 координат для треугольника " << (i + 1) << " (x1 y1 z1 x2 y2 z2 x3 y3 z3): ";
        #endif
        std::cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> x3 >> y3 >> z3;

        triangles.emplace_back(x1, y1, z1, x2, y2, z2, x3, y3, z3, i + 1);
    }
  
    return triangles;
}
