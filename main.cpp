#include <iostream>
#include "src/kdtree.hpp"

int main () {
    KDTree *tree = new KDTree(AABB(Point(0, 0, 0), Point(10, 10, 10)));
    std::cout << *tree << std::endl;
    tree->insert(new Point(5, 5, 5));
    std::cout << *tree << std::endl;
    tree->insert(new Point(2, 5, 5));
    std::cout << *tree << std::endl;
    tree->insert(new Point(8, 5, 5));
    tree->insert(new Point(1, 0, 5));
    tree->insert(new Point(1, 10, 5));
    std::cout << *tree << std::endl;
    std::cout << *tree->upper_child << std::endl;
    std::cout << *tree->lower_child << std::endl;
    std::cout << *tree->lower_child->lower_child << std::endl;
    std::cout << *tree->lower_child->upper_child << std::endl;
    std::cout << *tree->lower_child->upper_child << std::endl;

    std::cout << "Found point :" << (tree->find_point(new Point(5, 5, 5))!=nullptr) << std::endl;
    std::cout << "Found point :" << (tree->find_point(new Point(-1, 5, 5))!=NULL) << std::endl;
    std::cout << "Found point :" << (tree->find_point(new Point(1, 10, 5))!=NULL) << std::endl;
    std::cout << "Found point :" << (tree->find_point(new Point(1, 10, 5.001))!=NULL) << std::endl;

}
