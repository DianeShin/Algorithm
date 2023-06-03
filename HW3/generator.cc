#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <set>
#include <vector>

using namespace std;

int main() {
    // Open the output file
    ofstream output_file("2.in");

    // Set random seed
    random_device rd;
    mt19937 gen(rd());

    // Define board size and number of holes
    int board_size, num_holes;
    cout << "Enter the board size: ";
    cin >> board_size;
    cout << "Enter the number of holes: ";
    cin >> num_holes;

    // Generate random holes
    set<pair<int, int>> holes;
    uniform_int_distribution<int> distribution(1, board_size);
    while (holes.size() < num_holes) {
        int row = distribution(gen);
        int column = distribution(gen);
        holes.insert({row, column});
    }

    // Write board size and number of holes to the file
    output_file << board_size << " " << num_holes << endl;

    // Write hole coordinates to the file
    for (const auto& hole : holes) {
        output_file << hole.first << " " << hole.second << endl;
    }

    // Close the output file
    output_file.close();

    cout << "Random board with holes has been generated and saved to '1.in'." << endl;

    return 0;
}
