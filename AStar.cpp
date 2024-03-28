#include "Astar.h"

#include <iostream>

#include "utils.h"

// CostTracker implementation
void CostTracker::insert(Point a, float cost) {
  // if not evaluated
  if (cost_hashmap.find(a) == cost_hashmap.end()) {
    cost_hashmap.insert({a, cost});  // O(1)
    cost_heap.push({cost, a});       // O(logn)
  }
}

Point CostTracker::pop_point_with_least_cost() {
  if (cost_heap.empty()) return NULL_POINT;

  Point p = cost_heap.top().second;  // O(1)

  cost_heap.pop();  // O(logn)
  return p;
}

// AStar implementation
AstarGrid::AstarGrid(char **board, int _m, int _n) {
  this->board = board;
  this->m = _m;
  this->n = _n;
}

vector<Point> AstarGrid::trace_path(const Point &target) {
  vector<Point> result = {};

  // NULL_POINT means no path found, return empty vector
  if (target == NULL_POINT) result;

  // first target is ending point
  Point curr = target;
  result.push_back(curr);

  // keep tracing back until hit NULL
  while (curr.parent != NULL) {
    curr = *curr.parent;
    result.push_back(curr);
  }

  return result;
}

bool AstarGrid::is_out_of_bound(Point p) {
  if (p.pos.first >= 0 && p.pos.first < m && p.pos.second >= 0 &&
      p.pos.second < n)
    return false;
  return true;
};

vector<Point> AstarGrid::find_path(const Point &start, const Point &end) {
  // STEP 1: Find the path
  cost_tracker = CostTracker();
  Point target = start;

  // Calculate cost for neighbors, starting from start point
  while (target != end && target != NULL_POINT) {
    // calculate cost of neighbors
    Point dirs[4] = {Point{VECI{0, 1}}, Point{VECI{0, -1}}, Point{VECI{1, 0}},
                     Point{VECI{-1, 0}}};
    for (Point dir : dirs) {
      Point neighbor = target + dir;
      // skip obstacles or out of bound target
      if (is_out_of_bound(neighbor)) {
        continue;
      }
      char n_char = board[neighbor.pos.first][neighbor.pos.second];
      if (n_char == '\0' || (n_char != ' ' && neighbor != end)) continue;

      // set parent for path tracing
      Point *parent = new Point(target);
      neighbor.parent = parent;

      // evaluate cost
      float cost = cal_cost(neighbor, start, end);

      // only track target that turn once or twice
      if (cost <= 3000) cost_tracker.insert(neighbor, cost);
    }

    // pick next lowest cost target
    target = cost_tracker.pop_point_with_least_cost();
    // continue until target reach destination
  }

  // STEP 2: Trace back the path
  // if target is NULL_POINT, no path found, can't trace path
  return trace_path(target);
};

float AstarGrid::cal_cost(const Point &curr, const Point &start,
                          const Point &end) {
  // manhattan distance
  // int g = sqrt(pow(curr.x - start.x,2) + pow(curr.y - start.y,2));
  float h = sqrt(powf(curr.pos.first - end.pos.first, 2) +
                 powf(curr.pos.first - end.pos.first, 2));

  float f = h;

  // turning cost
  // need at lest 3 points to determine a turn, otherwise 0 turning cost
  if (curr.parent == NULL || curr.parent->parent == NULL) {
    return f;
  }

  Point *furthest = curr.parent->parent;
  Point *middle = curr.parent;

  // check if the 3 points are in the same line
  bool on_same_x_axis = furthest->pos.first == middle->pos.first &&
                        middle->pos.first == curr.pos.first;
  bool on_same_y_axis = furthest->pos.second == middle->pos.second &&
                        middle->pos.second == curr.pos.second;
  if (on_same_x_axis || on_same_y_axis) {
    return f;
  } else {
    // a turn is made, add 1000 as cost
    return f + 1000;
  }
  return f;
};

void AstarGrid::display_board() {
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      cout << this->board[i][j] << " ";
    }
    cout << endl;
  }
};
