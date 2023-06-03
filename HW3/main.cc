#include <string>
#include <vector>
#include <stack>
#include <fstream>
#include <sstream>
#include <chrono>

#include <iostream>

using namespace std;
/*
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
*/

// Check queen placable
bool canPlace(char board[14][14], int x, int y, int N) {
    // Check if the position is a hole
    if (board[x][y] == 'X') return false;

    // Check if queen at left
    for (int col = y - 1; col >= 1; col--) {
        if (board[x][col] == 'X') break;
        else if (board[x][col] == 'Q') return false;
    }

    // Check if queen at up
    for (int row = x - 1; row >= 1; row--) {
        if (board[row][y] == 'X') break;
        else if (board[row][y] == 'Q') return false;
    }

    // Check if queen at left-top diagonal
    for (int row = x - 1, col = y - 1; row >= 1 && col >= 1; row--, col--) {
        if (board[row][col] == 'X') break;
        else if (board[row][col] == 'Q') return false;
    }

    // Check if queen at right-top diagonal
    for (int row = x - 1, col = y + 1; row >= 1 && col < N+1; row--, col++) {
        if (board[row][col] == 'X') break;
        else if (board[row][col] == 'Q') return false;
    }

    // can be placed.
    return true;
}

int iterativeSolve(char board[14][14], int N) {
    int count = 0;

    stack<pair<int, int>> positions;
    int row = 1;  // Start with the first row
    int column = 1;  // Start with the first column
    int queenCount = 0;  // Count of placed queens

    while (true) {
        if (row > N) {
            // All queens are placed
            if (queenCount == N) {
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
        } else if (column > N) {
            // Reached the end of the row, move to the next row
            row++;
            column = 1;
        } else {
            if (canPlace(board, row, column, N)) {
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

int recursiveSolve(char board[14][14], int row, int column, int queen_cnt, int N) {
    // Base case: all queens are placed
    if (queen_cnt == N) {
        return 1;
    }

    int count = 0;


    for (int i = row; i < N+1; i++) {
        for (int j = (i == row) ? column : 1; j < N+1; j++) {
            if (canPlace(board, i, j, N)) {
                // Place the queen at the current position
                board[i][j] = 'Q';

                // Recursive call to place the remaining queens and accumulate the count
                if (j == N){
                    count += recursiveSolve(board, i+1, 1, queen_cnt+1, N);
                }
                else{
                    count += recursiveSolve(board, i, j+1, queen_cnt+1, N);
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
        char board[14][14] = {'.'};

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
            /*
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
            */

            // print result
            result = iterativeSolve(board, board_size);

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
            /*
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
            */

            // print result
            result = recursiveSolve(board, 1, 1, 0, board_size);

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