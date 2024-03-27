#include <unordered_map>
#include <iostream>
#include <math.h>
#include <vector>
#include <queue>
#include <set>

#ifndef INT_MAX
#define INT_MAX 2147483647
#endif

#define NULL_POINT \
    Point { -1, -1 }
#define MAX_ARR_SIZE 100

struct Point
{
    int x;
    int y;

    // use for backtracking & turning point cost calculation
    Point *parent = NULL;

    // Overload operators for easier calculation
    // Allow Point + Point, Point == Point,...
    bool operator==(const Point &other) const
    {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Point &other) const
    {
        return !(*this == other);
    }

    Point operator+(const Point &other) const
    {
        return Point{x + other.x, y + other.y};
    }

    // Hash function for unordered_map
    struct Hash
    {
        size_t operator()(const Point &p) const
        {
            return std::hash<int>()(p.x) ^ std::hash<int>()(p.y);
        }
    };
};
// Comparison function for the priority_queue (min heap)
struct CompareCost
{
    bool operator()(pair<float, Point> a, pair<float, Point> b) const
    {
        return a.first > b.first;
    }
};
class CostTracker
{ // In A* algorithm, we need to pick the point with the lowest cost frequently,
    // so a binary heap is a suitable data structure.

    // min heap, store cost-point pair, with cost as index.
    priority_queue<pair<float, Point>, vector<pair<float, Point>>, CompareCost> cost_heap;
    // track evaluated points to prevent duplicate.
    unordered_map<Point, float, Point::Hash> cost_hashmap;

public:
    void insert(Point a, float cost);
    Point pop_point_with_least_cost();
};

// Board representation: 2D array of char
// '\0' is obstacle
// ' ' is empty
// 'A' is letter

class AstarGrid
{
public:
    AStarGrid(char **board);

    // A* search algorithm, return full path of Points
    vector<Point> *find_path(const Point &start, const Point &end);

private:
    char **board;
    CostTracker cost_tracker;
    float cal_cost(const Point &curr, const Point &start, const Point &end);
    vector<Point> *trace_path(const Point &target);
};