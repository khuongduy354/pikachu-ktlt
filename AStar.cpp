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
#define MAX_ARR_SIZE 100

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
  bool operator()(pair<int, Point> a, pair<int, Point> b) const
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

  public:
  AStarGrid(char **board)
  {
    this->board = board;
  }

  int cal_cost(const Point &prev, const Point &curr, const Point &start, const Point &end)
  {
    // manhattan distance
    int g = abs(curr.x - start.x) + abs(curr.y - start.y);
    int h = abs(curr.x - end.x) + abs(curr.y - end.y);

    int f = g + h;

    // turning cost

    return f;
  }

  void find_path(const Point &start,const Point &end)
  {
    // reset cost tracker
    cost_tracker = CostTracker(); 

    char start_letter = board[start.x][start.y]; 
    Point target = start;
    cout << "Start: " << target.x << " " << target.y << endl;
    while (target != end && target != NULL_POINT)
    {
      // calculate cost of neighbors
      Point dirs[4] = {Point{0, 1}, Point{0, -1}, Point{1, 0}, Point{-1, 0}};
      for (Point dir : dirs)
      {
        Point neighbor = target + dir;
        // skip obstacles
        char n_char = board[neighbor.x][neighbor.y];
        if (n_char == '\0' || (n_char != ' '  && n_char != start_letter))
          continue;

        // evaluate cost
        int cost = cal_cost(target ,neighbor, start, end);
        cost_tracker.insert(neighbor, cost);
      }

      // pick next lowest cost target
      target = cost_tracker.pop_point_with_least_cost();
      if(target != NULL_POINT) {
        cout << "Next target: " << target.x << " " << target.y << endl;
      }
      // continue until target reach destination
    } 
    if(target == NULL_POINT) {
      cout << "No path found" << endl;
    }else{ 
      cout << "Path found" << endl;
    }
  }
};
char** setup_board(char b[MAX_ARR_SIZE][MAX_ARR_SIZE], int size) {
  char **board = new char*[size];
  for(int i = 0; i < size; i++) {
    board[i] = new char[size];
    for(int j = 0; j < size; j++) {
      board[i][j] = b[i][j];
    }
  }
  return board;
}


int main() {
  //10
  char b1[MAX_ARR_SIZE][MAX_ARR_SIZE] = {{
      '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'},
      {'\0', 'A', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
      {'\0', 'F', '\0', 'A', ' ', ' ', ' ', ' ', ' ', '\0'},
      {'\0', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
      {'\0', ' ', ' ', ' ', 'B', ' ', ' ', ' ', ' ', '\0'},
      {'\0', ' ', ' ', 'C', ' ', ' ', ' ', ' ', ' ', '\0'},
      {'\0', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
      {'\0', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'},
      {'\0', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'A', '\0'},
      {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'}};
    
  char **board = setup_board(b1,10);
  AStarGrid astar = AStarGrid(board);
  astar.find_path(Point{1,1}, Point{8,8});
}
