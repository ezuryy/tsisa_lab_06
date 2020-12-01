#include <iostream>
#include <map>
#include <limits>
#include <vector>
#include <algorithm>

using std::map;
using std::vector;
using std::cout;

struct Node {
    size_t num;
    map<Node, size_t> input;
    map<Node, size_t> output;

    explicit Node(const size_t &n) : num(n) {}

    bool FindOutputNode(const Node &n) {
        for (const auto &node: output) {
            if (node.first.num == n.num) return true;
        }
        return false;
    }

    size_t GetWeightToOutputNode(const Node &n) {
        for (const auto &node : output) {
            if (node.first.num == n.num) return node.second;
        }
        return 0;
    }

    friend bool operator<(const Node &left, const Node &right) {
        return left.num < right.num;
    }

};

void Pair(Node &left, Node &right, const size_t &weight) {
    left.output.insert(std::make_pair(right, weight));
    right.input.insert(std::make_pair(left, weight));
}

void PrintMatrix(const vector<vector<size_t>> &matrix) {
    for (const auto &str:matrix) {
        for (const auto &el:str) {
            cout << el << "\t\t";
        }
        cout << '\n';
    }
    cout << '\n';
}

size_t FloydAlgorithm(std::vector<Node> &graph) {
    size_t infinity = 999;//std::numeric_limits<size_t>::max();
    vector<vector<size_t>> matrix(graph.size());
    for (auto &str:matrix) {
        str.resize(graph.size());
    }
    for (size_t i = 0; i < graph.size(); ++i) {
        for (size_t j = 0; j < graph.size(); ++j) {
            if (i == j) {
                matrix[i][j] = 0;
            } else if (graph[i].FindOutputNode(graph[j])) {
                matrix[i][j] = graph[i].GetWeightToOutputNode(graph[j]);
            } else {
                matrix[i][j] = infinity;
            }
        }
    }
    cout << "Matrix for iteration 0 :\n";
    PrintMatrix(matrix);

    for (size_t k = 0; k < graph.size(); ++k) {
        for (size_t i = 0; i < graph.size(); ++i) {
            for (size_t j = 0; j < graph.size(); ++j) {
                if (matrix[i][k] != infinity && matrix[k][j] != infinity) {
                    matrix[i][j] = //std::min(matrix[i][j], matrix[i][k] + matrix[k][j]);
                            (matrix[i][j] == infinity ? matrix[i][k] + matrix[k][j] :
                             std::max(matrix[i][j], matrix[i][k] + matrix[k][j]));
                }
            }
        }
        cout << "Matrix for iteration " << k + 1 << " :\n";
        PrintMatrix(matrix);
    }
    return matrix[0][graph.size() - 1];
}


int main() {
    size_t a = 3, b = 5, c = 2, d = 4, e = 3,
            f = 1, g = 4, h = 3, i = 3, j = 2, k = 5;
    Node n1(1);
    Node n2(2);
    Node n3(3);
    Node n4(4);
    Node n5(5);
    Node n6(6);
    Node n7(7);
    Pair(n1, n2, 0);
    Pair(n2, n3, a);
    Pair(n1, n3, b);
    Pair(n3, n4, c);
    Pair(n4, n5, e);
    Pair(n3, n5, f);
    Pair(n1, n5, d);
    Pair(n4, n6, g);
    Pair(n3, n6, h);
    Pair(n6, n7, i);
    Pair(n5, n7, j);
    Pair(n4, n7, k);
    std::vector<Node> graph = {n1, n2, n3, n4, n5, n6, n7};

    size_t len = FloydAlgorithm(graph);
    std::cout << "Critical path length = " << len << std::endl;

    return 0;
}
