#include <unordered_map>
#include <iostream>
#include <math.h>
#include <vector>
#include <queue>
#include <set>
using namespace std;

// Board representation: 2D array of char
// '\0' is obstacle
// ' ' is empty
// 'A' is letter

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
{
  // In A* algorithm, we need to pick the point with the lowest cost frequently,
  // so a binary heap is a suitable data structure.

  // min heap, store cost-point pair, with cost as index.
  priority_queue<pair<float, Point>, vector<pair<float, Point>>, CompareCost> cost_heap;
  // track evaluated points to prevent duplicate.
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

char **setup_board(char b[MAX_ARR_SIZE][MAX_ARR_SIZE], int size)
{
  char **board = new char *[size];
  for (int i = 0; i < size; i++)
  {
    board[i] = new char[size];
    for (int j = 0; j < size; j++)
    {
      board[i][j] = b[i][j];
    }
  }
  return board;
}

// int main()
// {
//   // 10
//   char b1[MAX_ARR_SIZE][MAX_ARR_SIZE] = {{'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'},
//                                          {'\0', 'A', ' ', ' ', 'X', ' ', ' ', ' ', ' ', '\0'},
//                                          {'\0', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
//                                          {'\0', 'B', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
//                                          {'\0', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
//                                          {'\0', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
//                                          {'\0', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
//                                          {'\0', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
//                                          {'\0', ' ', ' ', ' ', 'A', ' ', ' ', ' ', 'A', '\0'},
//                                          {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'}};

//   char **board = setup_board(b1, 10);
//   AStarGrid astar = AStarGrid(board);
//   cout << "Scan order: " << endl;
//   vector<Point>* path = astar.find_path(Point{1, 1}, Point{8,8});
//   if(path == NULL) {
//     cout << "No path found" << endl;
//   } else {
//     cout << endl;
//     cout << "Found Path size: " << path->size() << endl;
//     cout << "Path from destination to start: " << endl;
//     for(Point p : *path) {
//       cout << "(" << p.x << ", " << p.y << ")" << endl;
//     }
//   }
// }
