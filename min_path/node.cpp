#include <vector>

using namespace std;

class Node{
    
    public:
        int index;
        bool visited;
        vector<Node> Successors;
        Node(int index, int pred);
        

};