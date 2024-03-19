#include <unordered_map>
#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;

// Board representation: 2D array of char
// '\0' is obstacle 
// ' ' is empty
// 'A' is letter

#define INT_MAX 2147483647
#define NULL_POINT \
  Point { -1, -1 }

struct Point
{
  int x;
  int y;

  // Comparison operators
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

// Comparison function for the priority_queue
struct CompareCost
{
  bool operator()(const pair<int, vector<Point>> &a, const pair<int, vector<Point>> &b) const
  {
    return a.first < b.first;
  }
};

class CostTracker
{
  // In A* algorithm, we need to pick the point with the lowest cost frequently,
  // so a binary heap is a suitable data structure.

  // min heap, store cost-point pair, with cost as index.
  priority_queue<pair<int, Point>, vector<pair<int, Point>>, CompareCost> cost_heap;
  // track evaluated points to prevent duplicate.
  unordered_map<Point, int, Point::Hash> cost_hashmap;

public:
  void insert(Point a, int cost)
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
    cost_heap.pop();                  // O(logn)
    return p;
  }
};

class AStarGrid
{
  char **board;
  CostTracker cost_tracker;

  AStarGrid(char **board)
  {
    this->board = board;
  }

  int cal_cost(Point &target, Point &start, Point &end)
  {
  }

  void find_path(Point &start, Point &end)
  {
    // reset cost tracker
    cost_tracker = CostTracker(); 

    char letter = board[start.x][start.y]; 
    Point target = start;
    while (target != end && target != NULL_POINT)
    {
      // calculate cost of neighbors
      Point dirs[4] = {Point{0, 1}, Point{0, -1}, Point{1, 0}, Point{-1, 0}};
      for (Point dir : dirs)
      {
        Point neighbor = target + dir;
        // skip obstacles
        if (board[neighbor.x][neighbor.y] == '\0' || board[neighbor.x][neighbor.y] != letter)
          continue;

        // evaluate cost
        int cost = cal_cost(neighbor, start, end);
        cost_tracker.insert(neighbor, cost);
      }

      // pick next lowest cost target
      target = cost_tracker.pop_point_with_least_cost();

      // continue until target reach destination
    } 
    if(target == NULL_POINT) {
      cout << "No path found" << endl;
    }else{ 
      cout << "Path found" << endl;
    }
  }
};

int main() { char a = '\0'; }
