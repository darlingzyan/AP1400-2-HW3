#ifndef BST_H
#define BST_H
#include <iostream>
#include <functional>
#include <queue>

class BST {
public:
    class Node {
    public:
        Node(int value, Node* left, Node* right) noexcept;
        Node() noexcept;
        Node(const Node& node) noexcept;
        int value;
        Node* left;
        Node* right;
    };
    BST() noexcept;
    BST(const BST& tree);
    BST(BST&& other) noexcept;
    Node*& get_root();
    void bfs(std::function<void(Node*& node)> func);
    size_t length();
    bool add_node(int value);
    Node** find_node(int value);
    Node** find_parrent(int value);
    Node** find_successor(int value);
    bool delete_node(int value);
    BST& operator++();     // ++bst
    BST operator++(int);   // bst++
    BST& operator=(const BST& other);
    BST& operator=(BST&& other) noexcept;
    template<typename... Args>
    BST(Args... values) : root(nullptr) {
        (add_node(values), ...);
    }
    ~BST();
    friend std::ostream& operator<<(std::ostream& os, const BST& bst);
    friend std::ostream& operator<<(std::ostream& os, const BST::Node& n);
private:
    Node* root;
};
 bool operator>(const BST::Node& n, int num) noexcept;
 bool operator>=(const BST::Node& n, int num) noexcept;
 bool operator<(const BST::Node& n, int num) noexcept;
 bool operator<=(const BST::Node& n, int num) noexcept;
 bool operator==(const BST::Node& n, int num) noexcept;
 bool operator>(int num, const BST::Node& n) noexcept;
 bool operator>=(int num, const BST::Node& n) noexcept;
 bool operator<(int num, const BST::Node& n) noexcept;
 bool operator<=(int num, const BST::Node& n) noexcept;
 bool operator==(int num, const BST::Node& n) noexcept;

#endif // BST_H
