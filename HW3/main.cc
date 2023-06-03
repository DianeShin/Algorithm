#include <string>
#include <vector>
#include <stack>
#include <fstream>
#include <sstream>
#include <chrono>

#include <iostream>

using namespace std;

void print_vect(vector<char>& vec){
    for (int i = 1; i < vec.size(); i++){
        cout << vec[i] << ' ';
    }
    cout << endl;
}
void print_board(vector<vector<char>> &vec){
    for (int i = 1; i < vec.size(); i++){
        print_vect(vec[i]);
    }
}

// Check queen placable
bool canPlace(vector<vector<char>>& board, int x, int y) {
    // Check if the position is a hole
    if (board[x][y] == 'X') return false;

    // Check if queen at left
    for (int col = y - 1; col >= 1; col--) {
        if (board[x][col] == 'X') break;
        else if (board[x][col] == 'Q') return false;
    }

    // Check if queen at right
    for (int col = y + 1; col < board.size(); col++) {
        if (board[x][col] == 'X') break;
        else if (board[x][col] == 'Q') return false;
    }

    // Check if queen at up
    for (int row = x - 1; row >= 1; row--) {
        if (board[row][y] == 'X') break;
        else if (board[row][y] == 'Q') return false;
    }

    // Check if queen at bottom
    for (int row = x + 1; row < board.size(); row++) {
        if (board[row][y] == 'X') break;
        else if (board[row][y] == 'Q') return false;
    }

    // Check if queen at left-top diagonal
    for (int row = x - 1, col = y - 1; row >= 1 && col >= 1; row--, col--) {
        if (board[row][col] == 'X') break;
        else if (board[row][col] == 'Q') return false;
    }

    // Check if queen at right-top diagonal
    for (int row = x - 1, col = y + 1; row >= 1 && col < board.size(); row--, col++) {
        if (board[row][col] == 'X') break;
        else if (board[row][col] == 'Q') return false;
    }

    // Check if queen at left-bottom diagonal
    for (int row = x + 1, col = y - 1; row < board.size() && col >= 1; row++, col--) {
        if (board[row][col] == 'X') break;
        else if (board[row][col] == 'Q') return false;
    }

    // Check if queen at right-bottom diagonal
    for (int row = x + 1, col = y + 1; row < board.size() && col < board.size(); row++, col++) {
        if (board[row][col] == 'X') break;
        else if (board[row][col] == 'Q') return false;
    }

    // can be placed.
    return true;
}

int iterativeSolve(vector<vector<char>>& board) {
    int height = board.size()-1;
    int count = 0;

    stack<pair<int, int>> positions;
    int row = 1;  // Start with the first row
    int column = 1;  // Start with the first column
    int queenCount = 0;  // Count of placed queens

    while (true) {
        if (row > height) {
            // All queens are placed
            if (queenCount == height) {
                count++;
            }

            // Backtrack to find more solutions
            if (positions.empty()) {
                // No more valid positions to backtrack, exit loop
                break;
            }

            // Backtrack to the previous position
            board[positions.top().first][positions.top().second] = '.';
            row = positions.top().first;
            column = positions.top().second + 1;
            positions.pop();
            queenCount--;
        } else if (column > height) {
            // Reached the end of the row, move to the next row
            row++;
            column = 1;
        } else {
            if (canPlace(board, row, column)) {
                // Place the queen at the current position
                board[row][column] = 'Q';
                positions.push({row, column});
                queenCount++;
            }
            
            // Move to the next column
            column++;
        }
    }

    return count;
}

int recursiveSolve(vector<vector<char>> &board, int row, int column, int queen_cnt) {
    // Base case: all queens are placed
    if (queen_cnt == board.size()-1) {
        return 1;
    }

    int count = 0;


    for (int i = row; i < board.size(); i++) {
        for (int j = (i == row) ? column : 1; j < board.size(); j++) {
            if (canPlace(board, i, j)) {
                // Place the queen at the current position
                board[i][j] = 'Q';

                // Recursive call to place the remaining queens and accumulate the count
                if (j == board.size()-1){
                    count += recursiveSolve(board, i+1, 1, queen_cnt+1);
                }
                else{
                    count += recursiveSolve(board, i, j+1, queen_cnt+1);
                }                

                // Backtrack: remove the queen from the current position
                board[i][j] = '.';
            }            
        }
    }

    return count;
}


int main(int argc, char *argv[]){
    string buf = "";
    int result;

    // check arg cnt
    if (argc == 4){
        // open input file
        fstream input_file;
        input_file.open(argv[2]);

        // read first line
        getline(input_file, buf);

        // fetch node_cnt
        int board_size = stoi(buf.substr(0, buf.find(' ')));
        int hole_cnt = stoi(buf.substr(buf.find(' ') + 1));

        // clear buffer string
        buf.clear();

        // declare board
        vector<vector<char>> board(board_size+1, vector<char>(board_size+1, '.'));

        // fetch hole location
        while(getline(input_file, buf)){
            // process the holes
            int x = stoi(buf.substr(0, buf.find(' ')));
            int y = stoi(buf.substr(buf.find(' ') + 1));

            // save hole
            board[x][y] = 'X';
        }
        
        // close input file
        input_file.close();

        // 1. iterative backtracking
        if (stoi(argv[1]) == 1){
            // clock start
            auto start = chrono::high_resolution_clock::now();

            // run algorithm
            result = iterativeSolve(board);

            // clock end
            auto stop = chrono::high_resolution_clock::now();

            // get duration
            auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

            // print clock
            cout << duration.count() << " microseconds" << endl;

            // open output file
            fstream output_file;
            output_file.open(argv[3], fstream::in | fstream::out | fstream::trunc);

            // write result
            output_file << result << endl;

            // close file
            output_file.close();

            // return
            return 0;
        }

        // 2. recursive backtracking
        if (stoi(argv[1]) == 2){
            // clock start
            auto start = chrono::high_resolution_clock::now();

            // run algorithm
            result = recursiveSolve(board, 1, 1, 0);

            // clock end
            auto stop = chrono::high_resolution_clock::now();

            // get duration
            auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

            // print clock
            cout << duration.count() << " microseconds" << endl;

            // open output file
            fstream output_file;
            output_file.open(argv[3], fstream::in | fstream::out | fstream::trunc);

            // write result
            output_file << result << endl;

            // close file
            output_file.close();

            // return
            return 0;
        }
    }
    // invalid argument number
    else{
        return 0;
    }
}