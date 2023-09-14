#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

// Define the dimensions of the grid
const int ROWS = 5;
const int COLS = 5;

// Define possible directions (up, down, left, right)
const int dx[] = {0, 0, -1, 1};
const int dy[] = {-1, 1, 0, 0};

// Define a structure to represent a cell in the grid
struct Cell {
    int x, y; // Coordinates of the cell
    int cost; // Cost to reach this cell
    int heuristic; // Heuristic value
    int totalCost; // Total cost (cost + heuristic)
};

// Custom comparator for the priority queue
struct CompareCell {
    bool operator()(const Cell& a, const Cell& b) const {
        return a.totalCost > b.totalCost;
    }
};

// Function to calculate the heuristic value (Euclidean distance)
int calculateHeuristic(int x1, int y1, int x2, int y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

// Function to check if a cell is valid (within grid bounds)
bool isValid(int x, int y) {
    return x >= 0 && x < ROWS && y >= 0 && y < COLS;
}

// AO* algorithm
void aoStar(int startX, int startY, int goalX, int goalY) {
    // Create a 2D array to store the cost of reaching each cell
    vector<vector<int>> costGrid(ROWS, vector<int>(COLS, INT_MAX));
    
    // Create a priority queue for open cells
    priority_queue<Cell, vector<Cell>, CompareCell> open;
    
    // Initialize the start cell
    Cell startCell = {startX, startY, 0, calculateHeuristic(startX, startY, goalX, goalY)};
    startCell.totalCost = startCell.cost + startCell.heuristic;
    open.push(startCell);
    
    while (!open.empty()) {
        // Get the cell with the lowest total cost from the priority queue
        Cell current = open.top();
        open.pop();
        
        int x = current.x;
        int y = current.y;
        int cost = current.cost;
        
        // If we reached the goal cell, we're done
        if (x == goalX && y == goalY) {
            cout << "Monkey reached the banana with a cost of " << cost << endl;
            return;
        }
        
        // Skip this cell if we have already found a cheaper path
        if (cost >= costGrid[x][y])
            continue;
        
        // Update the cost of reaching this cell
        costGrid[x][y] = cost;
        
        // Expand to neighboring cells
        for (int i = 0; i < 4; ++i) {
            int newX = x + dx[i];
            int newY = y + dy[i];
            
            // Check if the neighbor is valid and not an obstacle
            if (isValid(newX, newY)) {
                int newCost = cost + 1; // Assuming uniform cost for simplicity
                
                // Calculate the heuristic for the neighbor
                int newHeuristic = calculateHeuristic(newX, newY, goalX, goalY);
                
                // Create the neighbor cell
                Cell neighbor = {newX, newY, newCost, newHeuristic};
                neighbor.totalCost = newCost + newHeuristic;
                
                // Add the neighbor to the open list
                open.push(neighbor);
            }
        }
    }
    
    // If we reach here, there is no path to the goal
    cout << "No path found to the banana." << endl;
}

int main() {
    int startX, startY, goalX, goalY;
    
    // Input the monkey's starting position and banana's position
    cout << "Enter monkey's starting position (x y): ";
    cin >> startX >> startY;
    cout << "Enter banana's position (x y): ";
    cin >> goalX >> goalY;
    
    // Check if the positions are valid
    if (!isValid(startX, startY) || !isValid(goalX, goalY)) {
        cout << "Invalid positions. Please ensure they are within the grid." << endl;
        return 1;
    }
    
    // Call the AO* algorithm to find the shortest path
    aoStar(startX, startY, goalX, goalY);
    
    return 0;
}
