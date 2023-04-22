#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <cmath>

enum Action {
    ADVANCE = 1,
    U_TURN = 2,
    TURN_RIGHT = 3,
    TURN_LEFT = 4,
    HALT = 5
};

enum Direction {
    NORTH = 1,
    SOUTH = 2,
    WEST = 3,
    EAST = 4
};

// Construct class Node and its member functions
// You may add more member functions to meet your needs
class Node {
public:
    Node(int index = 0, Node* pred = nullptr) : index(index), visited(false), predecessor(pred) {}
    int getIndex() { return index; }
    std::vector<std::tuple<Node*, Direction, int>> getSuccessors() { return successors; }
    void addSuccessor(Node* successor, int direction, int length = 1) {
        successors.emplace_back(successor, static_cast<Direction>(direction), length);
        std::cout << "For Node " << this->index << ", a successor " << direction << " is set." << std::endl;
    }
    Direction getDirection(Node* nd) {
        // if nd is adjacent to the present node, return the direction of nd from the present node
        // For example, if the direction of nd from the present node is EAST, then return Direction::EAST = 4
        // However, if nd is not adjacent to the present node, print error message and return 0
        for (const auto& successor : successors) {
            if (std::get<Node*>(successor) == nd) {
                return std::get<Direction>(successor);
            }
        }
        std::cout << "Not Adjacent Node!!" << std::endl;
        return static_cast<Direction>(0);
    }
    bool isSuccessor(Node* nd) {
        for (const auto& successor : successors) {
            if (std::get<Node*>(successor) == nd) {
                return true;
            }
        }
        return false;
    }
    std::vector<std::tuple<Node*, Direction, int>> successors;
    bool visited;
    Node* predecessor;
private:
    int index;
};

class Maze {
public:
    Maze(const std::string& filepath) {
        // read file and implement a data structure you like
        // For example, when parsing raw_data, you may create several Node objects.  
        // Then you can store these objects into self.nodes.  
        // Finally, add to nd_dict by {key(index): value(corresponding node)}
        auto raw_data = pd.read_csv(filepath).values;
        nodes_.reserve(raw_data.size());
        for (const auto& data_row : raw_data) {
            auto cur_node = new Node(data_row[0]);
            nodes_.emplace_back(cur_node);
            node_dict_[cur_node->getIndex()] = cur_node;
        }
        for (auto& cur_node : nodes_) {
            for (auto i = 1; i <= 4; ++i) {
                if (!pd.isna(raw_data[cur_node->getIndex() - 1][i])) {
                    cur_node->addSuccessor(node_dict_[raw_data[cur_node->getIndex() - 1][i]], i, raw_data[cur_node->getIndex() - 1][i + 4]);
                }
            }
        }
    }
    Node* getStartPoint() {
        if (node_dict_.size() < 2) {
            std::cerr << "Error: the start point is not included." << std::endl;
            return nullptr;
        }
        return node_dict_[1];
    }
    std::unordered_map<int, Node*> getNodeDict() { return node_dict_; }
    std::vector<Node*> BFS(Node* nd) {
        std::vector<Node*> ret;
        // design your data structure here for your algorithm
        std::queue<Node*> q;
        q.push(nd);
        Node* last_node = nullptr;
        bool flag = false;
        while (!flag) { // flag == 1 means that all adjacent nodes are visited
            auto tmp_node = q.front();
            q.pop();
            tmp_node->visited = true;
            flag = true;
            for (const auto& successor : tmp_node->successors) {
                auto [node, direction, length] = successor;
                if (!node->visited) {
                    q.push(node);
                    flag = false;
                    node->predecessor = tmp_node;
                }
            }
            if (flag) {
                last_node = tmp_node;
            }
        }
        while (last_node != nd) {
            std::cout << last_node->getIndex() << " ";
            last_node = last_node->predecessor;
        }
        std::cout << nd->getIndex() << std::endl;
        // return a sequence of nodes from the node to the nearest unexplored deadend
        return ret;
    }
    std::vector<Node*> BFS_2(Node* nd_from, Node* nd_to) {
        std::vector<Node*> ret;
        // similar to BFS but with fixed start point and end point
        std::queue<Node*> q;
        q.push(nd_from);
        bool flag = false;
        while (!flag) {
            auto tmp_node = q.front();
            q.pop();
            tmp_node->visited = true;
            for (const auto& successor : tmp_node->successors) {
                auto [node, direction, length] = successor;
                if (!node->visited) {
                    q.push(node);
                    if (node == nd_to) {
                        flag = true;
                    }
                    node->predecessor = tmp_node;
                }
            }
        }
        auto cur_node = nd_to;
        while (cur_node != nd_from) {
            ret.emplace_back(cur_node);
            cur_node = cur_node->predecessor;
        }
        ret.emplace_back(nd_from);
        std::reverse(ret.begin(), ret.end());
        // return a sequence of nodes of the shortest path
        return ret;
    }
    Action getAction(Direction car_dir, Node* nd_from, Node* nd_to) {
        // get the car action
        // return an action and the next direction of the car if the nd_to is the Successor of nd_from
        // If not, print error message and return Action::HALT
        if (!nd_from->isSuccessor(nd_to)) {
            std::cerr << "two nodes aren't connected!!" << std::endl;
            return Action::HALT;
        }
        else {
            auto next_dir = nd_from->getDirection(nd_to);
            if (car_dir == Direction::NORTH) {
                if (next_dir == Direction::NORTH) {
                    return Action::ADVANCE;
                } else if (next_dir == Direction::SOUTH) {
                    return Action::U_TURN;
                } else if (next_dir == Direction::WEST) {
                    return Action::TURN_LEFT;
                } else if (next_dir == Direction::EAST) {
                    return Action::TURN_RIGHT;
                }
            } else if (car_dir == Direction::SOUTH) {
                if (next_dir == Direction::NORTH) {
                    return Action::U_TURN;
                } else if (next_dir == Direction::SOUTH) {
                    return Action::ADVANCE;
                } else if (next_dir == Direction::WEST) {
                    return Action::TURN_RIGHT;
                } else if (next_dir == Direction::EAST) {
                    return Action::TURN_LEFT;
                }
            } else if (car_dir == Direction::WEST) {
                if (next_dir == Direction::NORTH) {
                    return Action::TURN_RIGHT;
                } else if (next_dir == Direction::SOUTH) {
                    return Action::TURN_LEFT;
                } else if (next_dir == Direction::WEST) {
                    return Action::ADVANCE;
                } else if (next_dir == Direction::EAST) {
                    return Action::U_TURN;
                }
            } else if (car_dir == Direction::EAST) {
                if (next_dir == Direction::NORTH) {
                    return Action::TURN_LEFT;
                } else if (next_dir == Direction::SOUTH) {
                    return Action::TURN_RIGHT;
                } else if (next_dir == Direction::WEST) {
                    return Action::U_TURN;
                } else if (next_dir == Direction::EAST) {
                    return Action::ADVANCE;
                }
            }
        }
        return Action::HALT;
    }
    std::vector<Action> getActions(std::vector<Node*>& nodes) {
        // given a sequence of nodes, return the corresponding action sequence
        std::vector<Action> ret;
        ret.emplace_back(Action::ADVANCE);
        Direction car_dir = nodes[0]->getDirection(nodes[1]);
        for (size_t i = 1; i < nodes.size() - 1; ++i) {
            ret.emplace_back(getAction(car_dir, nodes[i], nodes[i+1]));
            car_dir = nodes[i]->getDirection(nodes[i+1]);
        }
        return ret;
    }
    std::string actionsToString(std::vector<Action>& actions) {
        // cmds should be a string sequence like "fbrl....", use it as the input of BFS checklist #1
        constexpr char cmds[] = {'f', 'b', 'r', 'l', 's'};
        std::string ret;
        for (const auto& action : actions) {
            ret.push_back(cmds[static_cast<size_t>(action)-1]);
        }
        std::cout << ret << std::endl;
        return ret;
    }
};

int main(){
    Maze maze()
}