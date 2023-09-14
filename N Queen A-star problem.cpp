#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

// Define a structure to represent a state in the search space
struct State {
    vector<int> board; // Stores the positions of queens on the board
    int cost; // Represents the heuristic cost of the state
};

// Define a comparison function for the priority queue
struct CompareStates {
    bool operator()(const State& s1, const State& s2) const {
        return s1.cost > s2.cost; // Use cost as the priority criterion
    }
};

// Function to check if a queen can be placed at a given position (row, col)
bool isSafe(const vector<int>& board, int row, int col) {
    for (int i = 0; i < row; ++i) {
        if (board[i] == col || abs(board[i] - col) == abs(i - row)) {
            return false; // There is a conflict with another queen
        }
    }
    return true; // It is safe to place a queen here
}

// Function to compute the heuristic cost of a state (number of conflicts)
int computeHeuristic(const vector<int>& board) {
    int n = board.size();
    int conflicts = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (board[i] == board[j] || abs(board[i] - board[j]) == abs(i - j)) {
                conflicts++;
            }
        }
    }

    return conflicts;
}

// Function to solve the N-Queens problem using A*
vector<int> solveNQueens(int n) {
    // Create an initial state with an empty board
    State initial;
    initial.board.resize(n);
    initial.cost = 0;

    // Create a priority queue for the open set of states
    priority_queue<State, vector<State>, CompareStates> openSet;
    openSet.push(initial);

    while (!openSet.empty()) {
        // Get the state with the lowest cost from the priority queue
        State current = openSet.top();
        openSet.pop();

        // If the board is complete, return the solution
        if (current.board.size() == n) {
            return current.board;
        }

        // Try placing a queen in each column of the current row
        int row = current.board.size();
        for (int col = 0; col < n; ++col) {
            if (isSafe(current.board, row, col)) {
                // Create a new state with the queen placed in the current column
                State child = current;
                child.board[row] = col;
                child.cost = computeHeuristic(child.board);

                // Add the new state to the open set
                openSet.push(child);
            }
        }
    }

    // No solution found
    return vector<int>();
}

int main() {
    int n;
    cout << "Enter the value of N: ";
    cin >> n;

    vector<int> solution = solveNQueens(n);

    if (solution.empty()) {
        cout << "No solution found for N = " << n << endl;
    } else {
        cout << "Solution for N = " << n << ":" << endl;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (solution[i] == j) {
                    cout << "Q ";
                } else {
                    cout << ". ";
                }
            }
            cout << endl;
        }
    }

    return 0;
}
