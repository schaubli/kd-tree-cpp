#include <iostream>
#include "src/kdtree.hpp"

void test_kdtree(std::vector<std::vector<Point *>> insert_points, int insert_point_limit, std::vector<Point *> search_points);

int main()
{
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

    std::cout << "Found point :" << (tree->find_point(new Point(5, 5, 5)) != nullptr) << std::endl;
    std::cout << "Found point :" << (tree->find_point(new Point(-1, 5, 5)) != NULL) << std::endl;
    std::cout << "Found point :" << (tree->find_point(new Point(1, 10, 5)) != NULL) << std::endl;
    std::cout << "Found point :" << (tree->find_point(new Point(1, 10, 5.001)) != NULL) << std::endl;

    std::vector<Point *> nearest_search_point;
    nearest_search_point.push_back(new Point(0, 0, 2.1));
    nearest_search_point.push_back(new Point(0.1, 0.1, 2.1));
    nearest_search_point.push_back(new Point(5, 5, 5));
    nearest_search_point.push_back(new Point(10, 11, 10));
    nearest_search_point.push_back(new Point(0, 0, -1));
    nearest_search_point.push_back(new Point(4, 4, 4));
    nearest_search_point.push_back(new Point(-1, 5, 5));
    nearest_search_point.push_back(new Point(1, 10, 5.001));
    for (int i = 0; i < nearest_search_point.size(); i++)
    {
        std::cout << "Searching for point closest to " << *nearest_search_point[i] << ": ";
        Point *closest = tree->find_nearest(nearest_search_point[i]);
        std::cout << *closest << " with distance: " << (*nearest_search_point[i] - *closest).length() << std::endl;
    }

    // Create insert points
    int insert_tests = 10;
    int insert_count = 10000000;
    std::vector<std::vector<Point *>> insert_points = std::vector<std::vector<Point *>>();
    std::cout << "Creating " << insert_count << " points..." << std::endl;
    for (int j = 0; j < insert_tests; j++)
    {
        std::vector<Point *> new_points;
        for (int i = 0; i < insert_count; i++)
        {
            float rand_x = ((float)std::rand()) / (float)RAND_MAX * 100.0f;
            float rand_y = ((float)std::rand()) / (float)RAND_MAX * 100.0f;
            float rand_z = ((float)std::rand()) / (float)RAND_MAX * 100.0f;
            new_points.push_back(new Point(rand_x, rand_y, rand_z));
        }
        insert_points.push_back(new_points);
    }

    // Create search points
    int search_count = 10;
    std::vector<Point *> search_points;
    std::cout << "Creating " << search_count << " search points..." << std::endl;
    for (int i = 0; i < search_count; i++)
    {
        float rand_x = ((float)std::rand()) / (float)RAND_MAX * 100.0f;
        float rand_y = ((float)std::rand()) / (float)RAND_MAX * 100.0f;
        float rand_z = ((float)std::rand()) / (float)RAND_MAX * 100.0f;
        search_points.push_back(new Point(rand_x, rand_y, rand_z));
    }

    for (int i = 0; i <= 4000000; i += 50000)
    {
        test_kdtree(insert_points, i, search_points);
    }

    printf("Finished testing kdtree!\n");
}

void test_kdtree(std::vector<std::vector<Point *>> insert_points, int insert_point_limit, std::vector<Point *> search_points)
{
    clock_t start, end;
    std::cout << insert_point_limit << ", ";
    int build_duration_sum = 0;
    int search_duration_sum = 0;
    for (int j = 0; j < insert_points.size(); j++)
    {
        KDTree *test_tree = new KDTree(AABB(Point(0, 0, 0), Point(100, 100, 100)));

        start = clock();
        for (int i = 0; i < insert_point_limit; i++)
        {
            test_tree->insert(insert_points[j][i]);
        }
        end = clock();
        build_duration_sum += (int)((float)(end - start) * 1000.0f / CLOCKS_PER_SEC);
        // std::cout << build_duration << ", ";

        start = clock();
        for (int i = 0; i < search_points.size(); i++)
        {
            test_tree->find_nearest(search_points[i]);
        }
        end = clock();
        search_duration_sum += (int)((float)(end - start) * 1000.0f / CLOCKS_PER_SEC / search_points.size());
        delete test_tree;
        // std::cout << search_duration << ", ";
    }
    // int build_duration = build_duration_sum / insert_points.size();
    // int search_duration = search_duration_sum / insert_points.size();
    std::cout << (build_duration_sum * 1.0f / insert_points.size()) << ", ";
    std::cout << (search_duration_sum * 1.0f / insert_points.size()) << ", ";
    std::cout << std::endl;
}
