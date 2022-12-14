#pragma once

#include "point.hpp"
#include <vector>

struct AABB
{

public:
    Point lower;
    Point upper;
    AABB();
    AABB(float min_x, float max_x, float min_y, float max_y, float min_z, float max_z);
    AABB(std::vector<Point *> points);
    AABB(Point lower, Point upper);
    AABB(AABB parent, Point *split, int alignment, bool upper);

    bool includes(Point *p) const;
    float distance_outside(Point *p) const;
    float distance_inside(Point *p) const;
};

std::ostream &operator<<(std::ostream &os, const AABB &aabb);
