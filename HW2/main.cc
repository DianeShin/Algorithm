#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>
#include <limits.h>
#include <queue>
#include <algorithm>

using namespace std;


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
    int getData() {
        return data;
    }
    Node* getNext() {
        return next;
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
    vector<int>& getArray(){
        return data;
    }
};

void print_vect(vector<int>& vec){
    for (int i = 1; i < vec.size(); i++){
        cout << vec[i] << ' ';
    }
    cout << endl;
}

void print_adj_list(vector<Node *> &vec){
    for (int i = 1; i < vec.size(); i++){
        Node * currNode = vec[i];
        while (currNode != nullptr){
            cout << currNode->getData() << ' ';
            currNode = currNode->getNext();
        }  
        cout << endl;    
    }
}

struct compare{
    vector<int> &time_vector;

    // Constructor
    compare(vector<int> &t_v) : time_vector(t_v){}

    // Operator definition
    bool operator()(int node1, int node2) {
        return time_vector[node1] < time_vector[node2];
    }
};

void reverse_sort_time_vector(vector<int> &time_vector, vector<int> &reverse_node_vector){
    compare comp(time_vector);

    // init max_heap
    priority_queue<int, vector<int>, compare> max_heap(comp);

    // init reverse_node_vector
    reverse_node_vector.push_back(0);

    // create max_heap
    for (int node = 1; node < time_vector.size(); node++){
        max_heap.push(node);
    }

    // fill reverse_node_vector
    while (!max_heap.empty()){
        int node = max_heap.top();
        max_heap.pop();
        reverse_node_vector.push_back(node);
    }
}

void DFS_matrix_a(vector<vector<bool>> &adjacency_matrix, vector<bool> &visited, vector<int> &time_vector, int time, int node){
    // d[v]
    ++time;

    // set visited node
    visited[node] = true;

    // visit adjacent vertices
    for (auto adj_node : adjacency_matrix.at(node + 1)){
        if (adjacency_matrix[node][adj_node] == false) continue;
        else{
            if (visited[adj_node] == false) DFS_matrix_a(adjacency_matrix, visited, time_vector, time, adj_node);
        }
    }
    
    // set time vector
    time_vector[node] = ++time;
}

void DFS_array_a(vector<Node_Array*> &adjacency_array, vector<bool> &visited, vector<int> &time_vector, int time, int node){
    // d[v]
    ++time;

    // set visited node
    visited[node] = true;

    // visit adjacent vertices
    for (auto adj_node : adjacency_array.at(node + 1)->getArray()){
        if (visited[adj_node] == false) DFS_array_a(adjacency_array, visited, time_vector, time, adj_node);
    }
    
    // set time vector
    time_vector[node] = ++time;
}

void DFS_list_a(vector<Node *> &adjacency_list, vector<bool> &visited, vector<int> &time_vector, int time, int node){
    // d[v]
    ++time;

    // set visited node
    visited[node] = true;

    // visit adjacent vertices
    Node * currNode = adjacency_list[node]->getNext();
    while (currNode != nullptr){
        if (visited[currNode->getData()] == false) DFS_list_a(adjacency_list, visited, time_vector, time, currNode->getData());
        currNode = currNode->getNext();
    }
    
    // set time vector
    time_vector[node] = ++time;
}

void DFS_matrix(vector<vector<bool>> &adjacency_matrix, vector<bool> &visited, vector<int> &time_vector){
    // initialize values
    int time = 0;

    // visit other nodes
    for (int index = 1; index < adjacency_matrix.size(); index++){
        if (visited[index] = false) DFS_matrix_a(adjacency_matrix, visited, time_vector, time, index);
    }
    
}

void DFS_array(vector<Node_Array *> &adjacency_array, vector<bool> &visited, vector<int> &time_vector){
    // initialize values
    int time = 0;

    // visit other nodes
    for (int index = 1; index < adjacency_array.size(); index++){
        if (visited[index] = false) DFS_array_a(adjacency_array, visited, time_vector, time, index);
    }
}

void DFS_list(vector<Node *> &adjacency_list, vector<bool> &visited, vector<int> &time_vector){
    // initialize values
    int time = 0;

    // visit other nodes
    for (int index = 1; index < adjacency_list.size(); index++){
        if (visited[index] == false) DFS_list_a(adjacency_list, visited, time_vector, time, index);
    }
}

void DFS_matrix_a_scc(vector<vector<bool>> &adjacency_matrix, vector<bool> &visited, int node, int &scc){
    // set visited node
    visited[node] = true;

    // perform xor with scc
    if (scc == -1) scc = node;
    else scc ^= node;

    // visit adjacent vertices
    for (auto adj_node : adjacency_matrix.at(node + 1)){
        if (adjacency_matrix[node][adj_node] == false) continue;
        else{
            if (visited[adj_node] == false){
                DFS_matrix_a_scc(adjacency_matrix, visited, adj_node, scc);
                break;
            } 
        }
    }
}

void DFS_list_a_scc(vector<Node *> &adjacency_list, vector<bool> &visited, int node, int &scc){
    // set visited node
    visited[node] = true;

    // perform xor with scc
    if (scc == -1) scc = node;
    else scc ^= node;

    // visit adjacent vertices
    Node * currNode = adjacency_list[node]->getNext();
    
    while (currNode != nullptr){
        if (visited[currNode->getData()] == false){
            DFS_list_a_scc(adjacency_list, visited,currNode->getData(), scc);
            break;
        } 
        currNode = currNode->getNext();
    }
}

void DFS_array_a_scc(vector<Node_Array*> &adjacency_array, vector<bool> &visited, int node, int &scc){
    // set visited node
    visited[node] = true;

    // perform xor with scc
    if (scc == -1) scc = node;
    else scc ^= node;

    // visit adjacent vertices
    for (auto adj_node : adjacency_array.at(node + 1)->getArray()){
        if (visited[adj_node] == false){
            DFS_array_a_scc(adjacency_array, visited, adj_node, scc);
            break;
        } 
    }
}

void strong_matrix(vector<vector<bool>> &adjacency_matrix, vector<vector<bool>> &adjacency_matrix_T, vector<int> &result){
    // initialize visited vector
    vector<bool> visited(adjacency_matrix.size(), false);
    vector<bool> visited_T(adjacency_matrix.size(), false);

    // initialize time_vector
    vector<int> time_vector(adjacency_matrix.size(), INT_MAX);
    vector<int> time_vector_T(adjacency_matrix.size(), INT_MAX);

    // initialize node_vector
    vector<int> reverse_node_vector;

    // run DFS
    DFS_matrix(adjacency_matrix, visited, time_vector);

    // fill reverse_node_vector
    reverse_sort_time_vector(time_vector, reverse_node_vector);

    // run DFS on G_T -> create SCC
    for (int index = 1; index < reverse_node_vector.size(); index++){
        // if not visited
        if (visited_T[index] == false){
            // initialize scc value(xor of scc nodes)
            int scc = -1;
            
            // perform DFS
            DFS_matrix_a_scc(adjacency_matrix_T,visited_T, index, scc);
            
            // push back result
            result.push_back(scc);
        }
    }

    // sort ascending order
    sort(result.begin(), result.end());
}

void strong_list(vector<Node *> &adjacency_list, vector<Node *> &adjacency_list_T, vector<int> &result){
    // initialize visited vector
    vector<bool> visited(adjacency_list.size(), false);
    vector<bool> visited_T(adjacency_list.size(), false);

    // initialize time_vector
    vector<int> time_vector(adjacency_list.size(), INT_MAX);

    // initialize node_vector
    vector<int> reverse_node_vector;
    
    // run DFS on G -> fill time_vector
    DFS_list(adjacency_list, visited, time_vector);

    // fill reverse_node_vector
    reverse_sort_time_vector(time_vector, reverse_node_vector);

    // run DFS on G_T -> create SCC
    for (int index = 1; index < reverse_node_vector.size(); index++){
        // if not visited
        if (visited_T[reverse_node_vector[index]] == false){
            // initialize scc value(xor of scc nodes)
            int scc = -1;
            
            // perform DFS
            DFS_list_a_scc(adjacency_list_T, visited_T, reverse_node_vector[index], scc);
            
            // push back result
            result.push_back(scc);
        }
    }

    // sort ascending order
    sort(result.begin(), result.end());
}

void strong_array(vector<Node_Array *> &adjacency_array, vector<Node_Array *> &adjacency_array_T, vector<int> &result){
    // initialize visited vector
    vector<bool> visited(adjacency_array.size(), false);
    vector<bool> visited_T(adjacency_array.size(), false);

    // initialize time_vector
    vector<int> time_vector(adjacency_array.size(), INT_MAX);
    vector<int> time_vector_T(adjacency_array.size(), INT_MAX);

    // initialize node_vector
    vector<int> reverse_node_vector;

    // run DFS
    DFS_array(adjacency_array, visited, time_vector);

    // fill reverse_node_vector
    reverse_sort_time_vector(time_vector, reverse_node_vector);

    // run DFS on G_T -> create SCC
    for (int index = 1; index < reverse_node_vector.size(); index++){
        // if not visited
        if (visited_T[index] == false){
            // initialize scc value(xor of scc nodes)
            int scc = -1;
            
            // perform DFS
            DFS_array_a_scc(adjacency_array_T, visited_T, index, scc);
            
            // push back result
            result.push_back(scc);
        }
    }

    // sort ascending order
    sort(result.begin(), result.end());
}

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


        // initialize result vector
        vector<int> result;

        // adjacency-matrix
        if (stoi(argv[1]) == 1){
            // clock start
            auto start = chrono::high_resolution_clock::now();

            // declare adjacency-matrix and transpose
            vector<vector<bool>> adjacency_matrix(node_cnt + 1, vector<bool>(node_cnt + 1, false));
            vector<vector<bool>> adjacency_matrix_T(node_cnt + 1, vector<bool>(node_cnt + 1, false));

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
            strong_matrix(adjacency_matrix, adjacency_matrix_T, result);

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
            output_file << result.size() << endl;
            for (int iter : result){
                output_file << iter << ' ';
            }

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
            vector<Node*> adjacency_list(node_cnt + 1, NULL);
            vector<Node*> adjacency_list_T(node_cnt + 1, NULL);

            // initialize adjacency-list/ adjacency_list_T
            for (int index = 1; index < node_cnt + 1; index++){
                adjacency_list[index] = new Node(index, NULL);
                adjacency_list_T[index] = new Node(index, NULL);
            }

            // fill adjacency-list and transpose
            while(getline(input_file, buf)){
                // process the edges
                int from_node = stoi(buf.substr(0, buf.find(' ')));
                int to_node = stoi(buf.substr(buf.find(' ') + 1));

                // fill list
                Node* newNode = new Node(to_node, adjacency_list[from_node]->getNext());
                adjacency_list[from_node]->setNext(newNode);
                
                // fill list transpose
                Node* newNode_T = new Node(from_node, adjacency_list_T[to_node]->getNext());
                adjacency_list_T[to_node]->setNext(newNode_T);
            }

            // run algorithm
            strong_list(adjacency_list, adjacency_list_T, result);

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
            output_file << result.size() << endl;
            for (int iter : result){
                output_file << iter << ' ';
            }

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
            vector<Node_Array*> adjacency_array(node_cnt + 1, NULL);
            vector<Node_Array*> adjacency_array_T(node_cnt + 1, NULL);

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
            strong_array(adjacency_array, adjacency_array_T, result);

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
            output_file << result.size() << endl;
            for (int iter : result){
                output_file << iter << ' ';
            }

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