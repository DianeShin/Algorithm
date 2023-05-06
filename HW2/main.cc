#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>

using namespace std;

void strong_matrix(){;}
void strong_list(){;}
void strong_array(){;}

class Node {
private:
    int data;
    Node* next;
public:
    Node(int newData, Node* newNext) {
        data = newData;
        next = newNext;
    }
    void setData(int newData) {
        data = newData;
    }
    void setNext(Node* newNext) {
        next = newNext;
    }
};

class Node_Array {
private:
    int cnt = 0;
    vector<int> data;
public:
    void insertNode(int node){
        data.push_back(node);
        cnt++;
    }
};

int main(int argc, char *argv[]){
    string buf = "";
    int result;
    vector<int> input_array;
    if (argc == 4){
        // open input file
        fstream input_file;
        input_file.open(argv[2]);

        // read first line
        getline(input_file, buf);

        // fetch node_cnt
        int node_cnt = stoi(buf);

        // clear buffer string
        buf.clear();

        // read second line
        getline(input_file, buf);

        // fetch node_cnt
        int edge_cnt = stoi(buf);

        // clear buffer string
        buf.clear();    

        // adjacency-matrix
        if (stoi(argv[1]) == 1){
            // clock start
            auto start = chrono::high_resolution_clock::now();

            // declare adjacency-matrix and transpose
            vector<vector<bool>> adjacency_matrix(node_cnt, vector<bool>(node_cnt, false));
            vector<vector<bool>> adjacency_matrix_T(node_cnt, vector<bool>(node_cnt, false));

            // fill adjacency-matrix and transpose
            while(getline(input_file, buf)){
                // process the edges
                int from_node = stoi(buf.substr(0, buf.find(' ')));
                int to_node = stoi(buf.substr(buf.find(' ') + 1));
                // fill matrix
                adjacency_matrix[from_node][to_node] = true;
                adjacency_matrix[to_node][from_node] = true;
            }
            
            // run algorithm
            strong_matrix();

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
            output_file << result;

            // close file
            output_file.close();

            // return
            return 0;
        }

        // adjacency-list
        else if (stoi(argv[1]) == 2){
            // clock start
            auto start = chrono::high_resolution_clock::now();

            // declare adjacency-list and transpose
            vector<Node*> adjacency_list(node_cnt, NULL);
            vector<Node*> adjacency_list_T(node_cnt, NULL);

            // fill adjacency-list and transpose
            while(getline(input_file, buf)){
                // process the edges
                int from_node = stoi(buf.substr(0, buf.find(' ')));
                int to_node = stoi(buf.substr(buf.find(' ') + 1));

                // fill list
                Node* newNode = new Node(to_node, adjacency_list[from_node]);
                adjacency_list[from_node] = newNode;

                // fill list transpose
                Node* newNode = new Node(from_node, adjacency_list_T[to_node]);
                adjacency_list[to_node] = newNode;
            }

            // run algorithm
            strong_list();

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
            output_file << result;

            // close file
            output_file.close();

            // return
            return 0;           
        }
        // adjacency-array
        else if (stoi(argv[1]) == 3){
            // clock start
            auto start = chrono::high_resolution_clock::now();

            // declare adjacency-array and transpose
            vector<Node_Array*> adjacency_array(node_cnt, NULL);
            vector<Node_Array*> adjacency_array_T(node_cnt, NULL);

            // fill adjacency-list and trnaspose
            while(getline(input_file, buf)){
                // process the edges
                int from_node = stoi(buf.substr(0, buf.find(' ')));
                int to_node = stoi(buf.substr(buf.find(' ') + 1));

                // fill array
                adjacency_array[from_node]->insertNode(to_node);
                adjacency_array_T[to_node]->insertNode(from_node);
            }

            // run algorithm
            strong_array();

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
            output_file << result;

            // close file
            output_file.close();

            // return
            return 0;           
        }
        // invalid argument
        else{
            return 0;
        }

        // close input file
        input_file.close();
    }
    // invalid argument number
    else{
        return 0;
    }
}