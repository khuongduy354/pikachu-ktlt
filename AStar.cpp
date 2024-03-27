#include "Astar.h"
using namespace std;

class CostTracker
{
  priority_queue<pair<float, Point>, vector<pair<float, Point>>, CompareCost> cost_heap;
  unordered_map<Point, float, Point::Hash> cost_hashmap;

public:
  void insert(Point a, float cost)
  {
    if (cost_hashmap.find(a) == cost_hashmap.end())
    {
      cost_hashmap.insert({a, cost}); // O(1)
      cost_heap.push({cost, a});      // O(logn)
    }
  };

  Point pop_point_with_least_cost()
  {
    if (cost_heap.empty())
      return NULL_POINT;
    Point p = cost_heap.top().second; // O(1)

    cost_heap.pop(); // O(logn)
    return p;
  }
};

class AStarGrid
{
public:
  AStarGrid(char **board)
  {
    this->board = board;
  }

private:
  char **board;
  CostTracker cost_tracker;
  float cal_cost(const Point &curr, const Point &start, const Point &end)
  {
    // manhattan distance
    // int g = sqrt(pow(curr.x - start.x,2) + pow(curr.y - start.y,2));
    float h = sqrt(powf(curr.x - end.x, 2) + powf(curr.y - end.y, 2));

    float f = h;

    // turning cost
    // need at lest 3 points to determine a turn, otherwise 0 turning cost
    if (curr.parent == NULL || curr.parent->parent == NULL)
    {
      return f;
    }

    Point *furthest = curr.parent->parent;
    Point *middle = curr.parent;

    // check if the 3 points are in the same line
    bool on_same_x_axis = furthest->x == middle->x && middle->x == curr.x;
    bool on_same_y_axis = furthest->y == middle->y && middle->y == curr.y;
    if (on_same_x_axis || on_same_y_axis)
    {
      return f;
    }
    else
    {
      // a turn is made, add 1000 as cost
      return f + 1000;
    }
    return f;
  }

  vector<Point> *trace_path(const Point &target)
  {
    if (target == NULL_POINT)
    {
      return NULL;
    }

    vector<Point> *result = new vector<Point>();
    Point curr = target;
    result->push_back(curr);

    while (curr.parent != NULL)
    {
      curr = *curr.parent;
      result->push_back(curr);
    }

    return result;
  };

public:
  // A* search algorithm, return true if path found, false otherwise
  vector<Point> *find_path(const Point &start, const Point &end)
  {

    // STEP 1: Find the path
    cost_tracker = CostTracker();
    char start_letter = board[start.x][start.y];
    Point target = start;

    // Calculate cost for neighbors, starting from start point
    while (target != end && target != NULL_POINT)
    {
      // calculate cost of neighbors
      Point dirs[4] = {Point{0, 1}, Point{0, -1}, Point{1, 0}, Point{-1, 0}};
      for (Point dir : dirs)
      {
        Point neighbor = target + dir;
        // skip obstacles
        char n_char = board[neighbor.x][neighbor.y];
        if (n_char == '\0' || (n_char != ' ' && neighbor != end))
          continue;

        // set parent for path tracing
        Point *parent = new Point(target);
        neighbor.parent = parent;

        // evaluate cost
        float cost = cal_cost(neighbor, start, end);
        cost_tracker.insert(neighbor, cost);
      }

      // pick next lowest cost target
      target = cost_tracker.pop_point_with_least_cost();
      // continue until target reach destination
    }

    // STEP 2: Trace back the path

    // if target is NULL_POINT, no path found, can't trace path
    if (target == NULL_POINT)
    {
      return NULL;
    }

    return trace_path(target);
  }
};
