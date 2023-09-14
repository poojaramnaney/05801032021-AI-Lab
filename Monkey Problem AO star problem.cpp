#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

// Define a structure to represent a state (position of monkey and box)
struct State {
    int monkey_x, monkey_y, box_x, box_y;
    
    State(int mx, int my, int bx, int by)
        : monkey_x(mx), monkey_y(my), box_x(bx), box_y(by) {}
};

// Define a function to calculate the Euclidean distance heuristic
int heuristic(int x1, int y1, int x2, int y2) {
    return static_cast<int>(sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
}

// Define a function to check if a state is valid
bool is_valid(const State& state, int rows, int cols) {
    return state.monkey_x >= 0 && state.monkey_x < rows &&
           state.monkey_y >= 0 && state.monkey_y < cols &&
           state.box_x >= 0 && state.box_x < rows &&
           state.box_y >= 0 && state.box_y < cols;
}

int ao_star(const State& start, const State& goal, int rows, int cols) {
    // Priority queue to store states
    priority_queue<pair<int, State>> open_set;
    
    // Map to store the cost to reach each state
    map<State, int> g_values;
    
    // Initialize the open set with the start state
    open_set.push({0 + heuristic(start.monkey_x, start.monkey_y, goal.monkey_x, goal.monkey_y), start});
    g_values[start] = 0;
    
    while (!open_set.empty()) {
        // Get the state with the lowest estimated cost
        State current = open_set.top().second;
        open_set.pop();
        
        // If we reach the goal state, return the cost
        if (current.monkey_x == goal.monkey_x && current.monkey_y == goal.monkey_y) {
            return g_values[current];
        }
        
        // Define possible moves (up, down, left, right)
        int dx[] = {1, -1, 0, 0};
        int dy[] = {0, 0, 1, -1};
        
        // Try each possible move
        for (int i = 0; i < 4; ++i) {
            int new_mx = current.monkey_x + dx[i];
            int new_my = current.monkey_y + dy[i];
            int new_bx = current.box_x;
            int new_by = current.box_y;
            
            // Check if the new state is valid
            State new_state(new_mx, new_my, new_bx, new_by);
            if (!is_valid(new_state, rows, cols)) {
                continue;
            }
            
            // Calculate the cost to reach the new state
            int new_g = g_values[current] + 1;
            
            // Update the cost if it's lower than the current cost
            if (new_g < g_values[new_state]) {
                g_values[new_state] = new_g;
                int f_value = new_g + heuristic(new_mx, new_my, goal.monkey_x, goal.monkey_y);
                open_set.push({f_value, new_state});
            }
        }
    }
    
    // If no path is found, return -1
    return -1;
}

int main() {
    int rows, cols;
    cout << "Enter the number of rows and columns in the grid: ";
    cin >> rows >> cols;
    
    int monkey_x, monkey_y, banana_x, banana_y, box_x, box_y;
    cout << "Enter the monkey's coordinates (x y): ";
    cin >> monkey_x >> monkey_y;
    
    cout << "Enter the banana's coordinates (x y): ";
    cin >> banana_x >> banana_y;
    
    cout << "Enter the box's coordinates (x y): ";
    cin >> box_x >> box_y;
    
    State start(monkey_x, monkey_y, box_x, box_y);
    State goal(banana_x, banana_y, box_x, box_y);
    
    int result = ao_star(start, goal, rows, cols);
    
    if (result != -1) {
        cout << "The monkey can reach the banana in " << result << " moves." << endl;
    } else {
        cout << "The monkey cannot reach the banana." << endl;
    }
    
    return 0;
}

//EXPLANATION

// The heuristic function calculates the Euclidean distance between two points, which we use as the heuristic for estimating the cost to reach the goal.
