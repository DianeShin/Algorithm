#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>

#include <iostream>

using namespace std;

int main(int argc, char *argv[]){
    string buf = "";
    int result;
    std::vector<std::pair<int, int>> hole_vec;

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

        // fetch hole location
        while(getline(input_file, buf)){
            // process the holes
            int x = stoi(buf.substr(0, buf.find(' ')));
            int y = stoi(buf.substr(buf.find(' ') + 1));

            // save hole
            hole_vec.push_back(make_pair(x,y));
        }
        
        // close input file
        input_file.close();

        // 1. iterative backtracking
        if (stoi(argv[1]) == 1){
            // clock start
            auto start = chrono::high_resolution_clock::now();

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
        if (stoi(argv[1]) == 1){
            // clock start
            auto start = chrono::high_resolution_clock::now();

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