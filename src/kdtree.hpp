#include "point.hpp"
#include "aabb.hpp"

class KDTree
{
public:
    Point *point;
    int alignment = 0;
    KDTree *upper_child;
    KDTree *lower_child;    
    AABB aabb;

    KDTree();
    KDTree(int alignment);
    KDTree(AABB aabb);
    KDTree(Point *p, int alignment, AABB aabb);
    void insert(Point *p);
    Point *find_point(Point *p) const;
};

std::ostream &operator<<(std::ostream &os, const KDTree &tree);
