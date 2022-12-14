#include "kdtree.hpp"

KDTree::KDTree() : alignment(0), point(nullptr), upper_child(nullptr), lower_child(nullptr) {}
KDTree::KDTree(int alignment) : alignment(alignment), point(nullptr), upper_child(nullptr), lower_child(nullptr) {}
KDTree::KDTree(AABB aabb) : alignment(0), aabb(aabb), point(nullptr), upper_child(nullptr), lower_child(nullptr) {}
KDTree::KDTree(Point *p, int alignment, AABB aabb) : alignment(alignment), point(p), aabb(aabb), upper_child(nullptr), lower_child(nullptr) {}

void KDTree::insert(Point *p)
{
    if (point == nullptr)
    {
        point = p;
        return;
    }

    bool is_upper = alignment == 0 ? (p->x > point->x) : (alignment == 1 ? (p->y > point->y) : (p->z > point->z));
    KDTree *correct_child = is_upper ? (upper_child) : (lower_child);
    if (correct_child == nullptr)
    {
        int child_alignment = (alignment + 1) % 3;
        correct_child = new KDTree(p, child_alignment, AABB(aabb, point, child_alignment, is_upper));
        if (is_upper)
        {
            upper_child = correct_child;
        }
        else
        {
            lower_child = correct_child;
        }
    }
    else
    {
        correct_child->insert(p);
    }
}

Point *KDTree::find_point(Point *p) const
{
    if (*p == *point)
    {
        return point;
    }
    bool is_upper = alignment == 0 ? (p->x > point->x) : (alignment == 1 ? (p->y > point->y) : (p->z > point->z));
    KDTree *correct_child = is_upper ? (upper_child) : (lower_child);
    bool child_exists = correct_child != nullptr;
    return child_exists ? correct_child->find_point(p) : nullptr;
}

Point *KDTree::find_nearest(Point *p) const
{
    // Set own point as closest
    Point *closest_p = point;

    // Check the children that include the point
    if (lower_child != nullptr && lower_child->aabb.includes(p))
    {
        Point *new_closest = lower_child->find_nearest(p);
        if (new_closest != nullptr && (*p - *new_closest).length() < (*p - *closest_p).length())
        {
            closest_p = new_closest;
        }
    } else if (upper_child != nullptr && upper_child->aabb.includes(p))
    {
        Point *new_closest = upper_child->find_nearest(p);
        if (new_closest != nullptr && (*p - *new_closest).length() < (*p - *closest_p).length())
        {
            closest_p = new_closest;
        }
    }

    // Check the children that do not include the point
    if (lower_child != nullptr && lower_child->aabb.distance_outside(p) < (*closest_p - *p).length())
    {
        Point *new_closest = lower_child->find_nearest(p);
        if (new_closest != nullptr && (*p - *new_closest).length() < (*p - *closest_p).length())
        {
            closest_p = new_closest;
        }
    }
    else if (upper_child != nullptr && upper_child->aabb.distance_outside(p) < (*closest_p - *p).length())
    {
        Point *new_closest = upper_child->find_nearest(p);
        if (new_closest != nullptr && (*p - *new_closest).length() < (*p - *closest_p).length())
        {
            closest_p = new_closest;
        }
    }
    return closest_p;
}

KDTree::~ KDTree()
{
    delete lower_child;
    delete upper_child;
}


std::ostream &operator<<(std::ostream &os, const KDTree &tree)
{

    os << "KDTree: (" << tree.aabb << ") with alignment " << tree.alignment;
    if (tree.point == nullptr)
    {
        os << " without point";
    }
    else
    {
        os << " and point " << *tree.point;
    }
    return os;
}
