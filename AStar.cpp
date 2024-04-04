#include "Astar.h"

#include <iostream>

#include "utils.h"

void CostTracker::insert(Point a, float cost) {
  // only track point-cost, if it's not calculated before
  if (cost_hashmap.find(a) == cost_hashmap.end()) {
    // save to heap, it will reorder so that the point with lowest cost is
    // accessed most efficiently
    cost_heap.push({cost, a});

    // insert to hashmap means calculated, do not calculate this point again.
    cost_hashmap.insert({a, cost});
  }
}

Point CostTracker::pop_point_with_least_cost() {
  if (cost_heap.empty()) return NULL_POINT;

  // get lowest cost point with O(1)
  Point p = cost_heap.top().second;

  // remove from heap
  cost_heap.pop();
  return p;
}

AstarGrid::AstarGrid(char **board, int _m, int _n) {
  this->board = board;
  this->m = _m;
  this->n = _n;
}

vector<Point> AstarGrid::trace_path(const Point &target) {
  // Trace path, return vector of points from destination to starting.
  vector<Point> result = {};

  // NULL_POINT means no path found, return empty vector
  if (target == NULL_POINT) return result;

  // first target is ending point
  Point curr = target;
  result.push_back(curr);

  // check if nearest point to destination is a turn.
  int turn_count = 0;
  auto pair = cost_tracker.cost_hashmap.find(curr);
  if (pair != cost_tracker.cost_hashmap.end()) {
    int cost = pair->second;
    if (cost >= 1000) {
      turn_count++;
    }
  }

  // keep tracing back until hit NULL
  while (curr.parent != NULL) {
    curr = *curr.parent;

    // check turns
    auto pair = cost_tracker.cost_hashmap.find(curr);
    if (pair != cost_tracker.cost_hashmap.end()) {
      int cost = pair->second;
      if (cost >= 1000) {
        turn_count++;

        // consider path invalid if turning times is > 2
        if (turn_count > 2) return vector<Point>{};
      }
    }

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
  // Searching algorithm

  // Check if starting letter match ending letter
  if (board[start.pos.first][start.pos.second] !=
      board[end.pos.first][end.pos.second]) {
    return {};
  }

  // STEP 1: Find the target
  cost_tracker = CostTracker();
  Point target = start;

  // Calculate cost for neighbors, starting from start point
  while (target != end && target != NULL_POINT) {
    // 4 directions: up down left right
    Point dirs[4] = {Point{VECI{0, 1}}, Point{VECI{0, -1}}, Point{VECI{1, 0}},
                     Point{VECI{-1, 0}}};

    // calculate each direction (each neighbor)
    for (Point dir : dirs) {
      Point neighbor = target + dir;

      // skip out of bound (outside board) points
      if (is_out_of_bound(neighbor)) {
        continue;
      }

      // skip obstacles
      char n_char = board[neighbor.pos.first][neighbor.pos.second];
      if (n_char == '\0') continue;

      // skip lettered cell that is not the target letter
      if (n_char != ' ' && neighbor != end) continue;

      // set parent for later path tracing
      Point *parent = new Point(target);
      neighbor.parent = parent;

      // evaluate cost
      float cost = cal_cost(neighbor, start, end);
      cost_tracker.insert(neighbor, cost);
    }

    // pick next lowest cost target
    target = cost_tracker.pop_point_with_least_cost();

    // continue until end point is reached or no more points on board to
    // calculate
  }

  // STEP 2: Trace back the path
  return trace_path(target);
};

float AstarGrid::cal_cost(const Point &curr, const Point &start,
                          const Point &end) {
  // calculate distance heuristic,
  // since distance doesn't matter, ignore distance to starting
  // only calculate distance to destination
  float h = sqrt(powf(curr.pos.first - end.pos.first, 2) +
                 powf(curr.pos.second - end.pos.second, 2));

  float f = h;

  // calculate turning cost
  // need at lest 3 points to determine a turn, otherwise 0 turning cost
  if (curr.parent == NULL || curr.parent->parent == NULL) {
    return f;
  }

  Point *furthest = curr.parent->parent;
  Point *middle = curr.parent;

  // check if the 3 points are in the same line
  // if 3 x are equal, it means on same x axis
  // if 3 y are equal, it means on same y axis
  bool on_same_x_axis = furthest->pos.first == middle->pos.first &&
                        middle->pos.first == curr.pos.first;
  bool on_same_y_axis = furthest->pos.second == middle->pos.second &&
                        middle->pos.second == curr.pos.second;

  // if either on x or on y axis, these 3 points are considered on the same line
  // if 3 points aren't on the same line, then a turn is made, add 1000 to cost;
  if (!(on_same_x_axis || on_same_y_axis)) {
    f += 1000;
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

pair<Point, Point> AstarGrid::suggest_path() {
  // from board, group into array of letters, so that
  // each letter contains a vector of points
  vector<Point> letter_points[26];

  // initialize default empty array
  for (int i = 0; i < 26; i++) {
    letter_points[i] = {};
  }

  // start scanning and grouping
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      char c = board[i][j];
      if (c >= 'A' && c <= 'Z') {
        // c-'A' outputs the integer from 0-25, representing 26 letters in
        // alphabet
        letter_points[c - 'A'].push_back(Point{VECI{i, j}});
      }
    }
  }

  // for each letter, find_path for every combination of 2 points
  for (int i = 0; i < 26; i++) {
    if (letter_points[i].size() < 2) continue;

    // brute force all combination of 2 points, and find_path
    for (int j = 0; j < letter_points[i].size(); j++) {
      for (int k = j + 1; k < letter_points[i].size(); k++) {
        vector<Point> path =
            find_path(letter_points[i][j], letter_points[i][k]);
        if (path.size() > 0) {
          // first path found, return it
          return {letter_points[i][j], letter_points[i][k]};
        }
      }
    }
  }

  // after all iteration, none found -> return NULL_POINT
  return pair<Point, Point>{NULL_POINT, NULL_POINT};
};