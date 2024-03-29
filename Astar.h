#pragma once
#include <math.h>

#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

#include "utils.h"

// avoid global std namespace due to packages conflict
using std::cout;
using std::endl;
using std::pair;
using std::priority_queue;
using std::unordered_map;
using std::vector;

// null point for function returning point, indicating not found, not valid
#define NULL_POINT  \
  Point {           \
    VECI { -1, -1 } \
  }

// Wrapper type arround VECI coordinate, have reference to previous Point
// Use especially for Astar
struct Point {
  VECI pos;

  // use for backtracking & turning point cost calculation
  Point *parent = NULL;

  // Overload operators for easier calculation
  // Allow Point + Point, Point == Point,...
  bool operator==(const Point &other) const {
    return pos.first == other.pos.first && pos.second == other.pos.second;
  }

  bool operator!=(const Point &other) const { return !(*this == other); }

  Point operator+(const Point &other) const {
    int x = pos.first + other.pos.first;
    int y = pos.second + other.pos.second;
    return Point{VECI{x, y}};
  }

  // Hash function for unordered_map
  struct Hash {
    size_t operator()(const Point &p) const {
      return std::hash<int>()(p.pos.first) ^ std::hash<int>()(p.pos.first);
    }
  };
};
// Comparison function for the priority_queue (min heap)
struct CompareCost {
  bool operator()(pair<float, Point> a, pair<float, Point> b) const {
    return a.first > b.first;
  }
};
class CostTracker {  // In A* algorithm, we need to pick the point with the
  // lowest cost frequently,
  // so a binary heap is a suitable data structure.

  // min heap, store cost-point pair, with cost as index.
  priority_queue<pair<float, Point>, vector<pair<float, Point>>, CompareCost>
      cost_heap;
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

class AstarGrid {
 public:
  AstarGrid(char **board, int _m, int _n);

  // A* search algorithm, return full path of Points
  vector<Point> find_path(const Point &start, const Point &end);
  int m;
  int n;
  void display_board(); 

  // suggest 2 point that can be matched, if none is found -> return pair of NULL_POINT
  pair<Point,Point> suggest_path(); 

 private:
  char **board;
  CostTracker cost_tracker;
  float cal_cost(const Point &curr, const Point &start, const Point &end);
  vector<Point> trace_path(const Point &target);
  bool is_out_of_bound(Point p);
};
