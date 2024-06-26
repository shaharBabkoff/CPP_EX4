#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <iostream>

template <typename T>
class Node
{
private:
    T value;
    std::vector<Node<T> *> children_; // List of pointers to child nodes

public:
    Node(T val) : value(val) {}
    ~Node() {}
    void clearChildren()
    {
        children_.clear();
    }
    void addChild(Node<T> *child)
    {
        children_.push_back(child);
    }
    int getCurrentChildrenNum() const
    {
        return children_.size();
    }
    T getValue() const
    {
        return value;
    }
    const std::vector<Node<T> *> &getChildren()
    {
        return children_;
    }
    void print(int depth = 0) const
    {
        std::cout << std::string(depth * 2, ' ') << value << " (" << children_.size() << " children)" << std::endl;
        for (auto *child : children_)
        {
            child->print(depth + 1);
        }
    }
};

#endif // NODE_HPP
