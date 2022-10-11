//
// Created by André Ribeiro on 11/10/2022.
//

// thief and the tree
// you have a non-binary tree, in which in one of the nodes, there is a thief
// the point is to traverse the tree in steps and collect the value inside the node
// the thief will do the same in direction to the root but when the thief passes by a node it consumes it, leaving it with 0
// find the best path to take which maximizes your sum

#include <vector>
#include <queue>
#include <iostream>

using namespace std;

struct Node {
    explicit Node(float init_value) {
        value = init_value;
    }

    float value;
    Node *parent{};
    vector<Node *> children;
    int level = 0;
};


int main() {
    // root
    Node root(1);
    // 1st layer
    Node n1(2);
    Node n2(3);
    // 2nd layer
    Node n3(4);
    Node n4(5);
    Node n5(6);
    Node n6(7);
    Node n7(8);
    // 3rd layer
    Node n8(9);
    Node n9(10);

    // root-1st layer
    root.children.push_back(&n1);
    root.children.push_back(&n2);
    n1.parent = &root;
    n2.parent = &root;

    // 1st-2nd layer
    n1.children.push_back(&n3);
    n1.children.push_back(&n4);
    n1.children.push_back(&n5);
    n2.children.push_back(&n6);
    n2.children.push_back(&n7);
    n3.parent = &n1;
    n4.parent = &n1;
    n5.parent = &n1;
    n6.parent = &n2;
    n7.parent = &n2;

    // 2nd-3rd layer
    n6.children.push_back(&n8);
    n6.children.push_back(&n9);
    n8.parent = &n6;
    n9.parent = &n6;

    // start with the thingies
    queue<Node *> queue;
    queue.push(&root);
    Node *thief_node = &n2;

    float mmax = 0;
    int current_level = 0;
    Node *final_node;

    while (!queue.empty()) {
        thief_node->value /= 2;
        Node *curr = queue.front();
        queue.pop();

        for (auto &i: curr->children) {
            queue.push(i);
            i->value = curr->value + i->value;
            i->level = curr->level + 1;
        }

        // calculate the max only on the leaf nodes
        if (curr->children.empty()) {
            mmax = max(curr->value, mmax);
            final_node = curr;
        }

        // next step
        if (current_level + 1 == curr->level) {
            // move thief
            thief_node->value = 0;
            if (thief_node->parent != nullptr) {
                thief_node = thief_node->parent;
            }
        }
    }
    cout << "max: " << mmax;
    cout << "level: " << final_node->level;
}
