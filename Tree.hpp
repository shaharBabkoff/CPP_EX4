#ifndef TREE_HPP
#define TREE_HPP

#include "Node.hpp"
#include <vector>
#include <queue>
#include <stack>
#include <utility>
#include <iostream>
#include "Node.hpp"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <sstream> // Include for stringstream

template <typename T, int K = 2>
class Tree
{
private:
    Node<T> *root_;

    void drawTree(sf::RenderWindow &window, Node<T> *node, float x, float y, float offset, int depth, int maxDepth)
    {
        if (!node)
            return;

        // Draw the node (circle)
        sf::CircleShape circle(20);
        circle.setFillColor(sf::Color::Cyan);
        circle.setPosition(x, y);

        // Load a font for displaying the node value
        sf::Font font;
        if (!font.loadFromFile("Arimo-Italic-VariableFont_wght.ttf"))
        {
            // Error handling
        }
        std::stringstream ss;
        ss.precision(2);
        ss << std::fixed << node->getValue();
        std::string valueStr = ss.str();

        // Draw the node value (text)
        sf::Text text;
        text.setFont(font);
        text.setString(valueStr);
        text.setCharacterSize(15);
        text.setFillColor(sf::Color::Black);
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f,
                       textRect.top + textRect.height / 2.0f);
        text.setPosition(x + circle.getRadius(), y + circle.getRadius());

        window.draw(circle);
        window.draw(text);

        // Draw lines and recursively draw children
        const std::vector<Node<T> *> &children = node->getChildren();
        float childOffset = offset / 2;
        float verticalSpacing = 600.0 / (maxDepth + 1);

        for (size_t i = 0; i < children.size(); ++i)
        {
            float childX = x + (i - (children.size() - 1) / 2.0) * offset;
            float childY = y + verticalSpacing;

            sf::Vertex line[] =
                {
                    sf::Vertex(sf::Vector2f(x + 20, y + 20), sf::Color::Cyan),
                    sf::Vertex(sf::Vector2f(childX + 20, childY), sf::Color::Cyan)};

            window.draw(line, 2, sf::Lines);
            drawTree(window, children[i], childX, childY, childOffset, depth + 1, maxDepth);
        }
    }

    int calculateMaxDepth(Node<T> *node)
    {
        if (!node)
            return 0;
        int maxDepth = 0;
        for (Node<T> *child : node->getChildren())
        {
            int depth = calculateMaxDepth(child);
            if (depth > maxDepth)
                maxDepth = depth;
        }
        return maxDepth + 1;
    }

public:
    void visualize()
    {
        sf::RenderWindow window(sf::VideoMode(1200, 800), "Tree Visualization");
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear(sf::Color::White);
            int maxDepth = calculateMaxDepth(root_);
            drawTree(window, root_, window.getSize().x / 2, 20, window.getSize().x / 4, 0, maxDepth);
            window.display();
        }
    }
    Tree() : root_(nullptr) {}
    ~Tree() {}
    void add_root(Node<T> &node)
    {
        root_ = &node;
    }
    void deleteTree(Node<T> *node)
    {
        if (node)
        {
            for (Node<T> *child : node->getChildren())
            {
                deleteTree(child);
            }
            delete node;
        }
    }
    void add_sub_node(Node<T> &parent, Node<T> &child)
    {
        //std::cout << "current children: " << parent.getCurrentChildrenNum() << " K=" << K << std::endl;
        if (parent.getCurrentChildrenNum() < K)
        {

            parent.addChild(&child); // Now correctly adds the new node
            //std::cerr << "add_sub_node succesfully" << std::endl;
        }
        else
        {
            std::cerr << "Cannot add more children or invalid parent/child." << std::endl;
        }
    }
    Node<T> *get_root() const
    {
        return root_;
    }
    void print()
    {
        root_->print();
    }
    class PreOrderIterator
    {
    private:
        std::stack<Node<T> *> stack_;

    public:
        PreOrderIterator(Node<T> *root)
        {
            if (root)
                stack_.push(root);
        }

        bool operator!=(const PreOrderIterator &other) const
        {
            return !(*this == other);
        }

        bool operator==(const PreOrderIterator &other) const
        {
            return stack_ == other.stack_;
        }

        const PreOrderIterator &operator++()
        {
            if (stack_.empty())
            {
                return *this;
            }

            Node<T> *current = stack_.top();
            stack_.pop();
            // Push children to the stack in reverse order for correct traversal
            for (auto i = current->getChildren().rbegin(); i != current->getChildren().rend(); ++i)
            {
                stack_.push(*i);
            }
            return *this;
        }

        Node<T> *operator*() const
        {
            return stack_.top();
        }
    };
    class PostOrderIterator
    {
    private:
        std::stack<Node<T> *> traversalStack;
        std::stack<Node<T> *> outputStack;

    public:
        PostOrderIterator(Node<T> *root)
        {
            if (root)
            {
                traversalStack.push(root);
                while (!traversalStack.empty())
                {
                    Node<T> *node = traversalStack.top();
                    traversalStack.pop();
                    outputStack.push(node);
                    const auto &children = node->getChildren();
                    for (Node<T> *child : children)
                    {
                        traversalStack.push(child);
                    }
                }
            }
        }

        bool operator!=(const PostOrderIterator &other) const
        {
            return !outputStack.empty();
        }

        const PostOrderIterator &operator++()
        {
            if (!outputStack.empty())
            {
                outputStack.pop();
            }
            return *this;
        }

        Node<T> *operator*() const
        {
            return outputStack.empty() ? nullptr : outputStack.top();
        }
    };
    class InOrderIterator
    {
    private:
        std::stack<Node<T> *> nodeStack;
        Node<T> *currentNode;

        void pushLeftmost(Node<T> *node)
        {
            while (node)
            {
                nodeStack.push(node);
                if (!node->getChildren().empty())
                {
                    node = node->getChildren().front(); // Push all the way down to the leftmost child
                }
                else
                {
                    break;
                }
            }
        }

    public:
        InOrderIterator(Node<T> *root) : currentNode(root)
        {
            pushLeftmost(root);
        }

        bool operator!=(const InOrderIterator &other) const
        {
            return !nodeStack.empty();
        }

        const InOrderIterator &operator++()
        {
            if (!nodeStack.empty())
            {
                Node<T> *topNode = nodeStack.top();
                nodeStack.pop();
                const auto &children = topNode->getChildren();
                if (children.size() > 1)
                {
                    pushLeftmost(children[1]); // For k-ary, push the second child and its leftmost descendants
                }
            }
            return *this;
        }

        Node<T> *operator*() const
        {
            return nodeStack.top();
        }
    };
    class BFSIterator
    {
    private:
        std::queue<Node<T> *> nodeQueue;

    public:
        BFSIterator(Node<T> *root)
        {
            if (root)
            {
                nodeQueue.push(root);
            }
        }

        bool operator!=(const BFSIterator &other) const
        {
            return !nodeQueue.empty();
        }

        const BFSIterator &operator++()
        {
            if (!nodeQueue.empty())
            {
                Node<T> *current = nodeQueue.front();
                nodeQueue.pop();
                for (Node<T> *child : current->getChildren())
                {
                    nodeQueue.push(child);
                }
            }
            return *this;
        }

        Node<T> *operator*() const
        {
            return nodeQueue.front();
        }
    };
    class DFSIterator
    {
    private:
        std::stack<Node<T> *> nodeStack;

    public:
        DFSIterator(Node<T> *root)
        {
            if (root)
            {
                nodeStack.push(root);
            }
        }

        bool operator!=(const DFSIterator &other) const
        {
            return !nodeStack.empty();
        }

        const DFSIterator &operator++()
        {
            if (!nodeStack.empty())
            {
                Node<T> *current = nodeStack.top();
                nodeStack.pop();
                for (auto it = current->getChildren().rbegin(); it != current->getChildren().rend(); ++it)
                {
                    nodeStack.push(*it);
                }
            }
            return *this;
        }

        Node<T> *operator*() const
        {
            return nodeStack.top();
        }
    };
    class HeapIterator
    {
    private:
        std::vector<Node<T> *> heap;
        size_t currentIndex;

        void buildHeap(Node<T> *root)
        {
            std::queue<Node<T> *> nodeQueue;
            if (root)
                nodeQueue.push(root);
            while (!nodeQueue.empty())
            {
                Node<T> *current = nodeQueue.front();
                nodeQueue.pop();
                heap.push_back(current);
                for (Node<T> *child : current->getChildren())
                {
                    nodeQueue.push(child);
                }
            }
            std::make_heap(heap.begin(), heap.end(), [](Node<T> *a, Node<T> *b)
                           { return a->getValue() > b->getValue(); });
        }

    public:
        HeapIterator(Node<T> *root) : currentIndex(0)
        {
            buildHeap(root);
        }

        bool operator!=(const HeapIterator &other) const
        {
            return currentIndex < heap.size();
        }

        const HeapIterator &operator++()
        {
            if (currentIndex < heap.size())
            {
                std::pop_heap(heap.begin(), heap.end() - currentIndex, [](Node<T> *a, Node<T> *b)
                              { return a->getValue() > b->getValue(); });
                ++currentIndex;
            }
            return *this;
        }

        Node<T> *operator*() const
        {
            return heap.front();
        }
    };

    void myHeap()
    {
        if (!root_)
            return;

        std::vector<Node<T> *> nodes;
        std::queue<Node<T> *> q;
        q.push(root_);

        while (!q.empty())
        {
            Node<T> *current = q.front();
            q.pop();
            nodes.push_back(current);

            for (Node<T> *child : current->getChildren())
            {
                q.push(child);
            }
        }

        std::make_heap(nodes.begin(), nodes.end(), [](Node<T> *a, Node<T> *b)
                       { return a->getValue() > b->getValue(); });

        root_ = nodes.empty() ? nullptr : nodes.front();

        for (size_t i = 0; i < nodes.size(); ++i)
        {
            size_t leftChildIndex = 2 * i + 1;
            size_t rightChildIndex = 2 * i + 2;

            nodes[i]->clearChildren();
            if (leftChildIndex < nodes.size())
            {
                nodes[i]->addChild(nodes[leftChildIndex]);
            }
            if (rightChildIndex < nodes.size())
            {
                nodes[i]->addChild(nodes[rightChildIndex]);
            }
        }
    }
    // Method to begin Pre-Order traversal based on K value
    auto begin_pre_order() const
    {
        if constexpr (K == 2)
        {
            return PreOrderIterator(root_);
        }
        else
        {
            return DFSIterator(root_);
        }
    }

    // Method to end Pre-Order traversal based on K value
    auto end_pre_order() const
    {
        if constexpr (K == 2)
        {
            return PreOrderIterator(nullptr);
        }
        else
        {
            return DFSIterator(nullptr);
        }
    }

    // Method to begin Post-Order traversal based on K value
    auto begin_post_order() const
    {
        if constexpr (K == 2)
        {
            return PostOrderIterator(root_);
        }
        else
        {
            return DFSIterator(root_);
        }
    }

    // Method to end Post-Order traversal based on K value
    auto end_post_order() const
    {
        if constexpr (K == 2)
        {
            return PostOrderIterator(nullptr);
        }
        else
        {
            return DFSIterator(nullptr);
        }
    }

    // Method to begin In-Order traversal based on K value
    auto begin_in_order() const
    {
        if constexpr (K == 2)
        {
            return InOrderIterator(root_);
        }
        else
        {
            return DFSIterator(root_);
        }
    }

    // Method to end In-Order traversal based on K value
    auto end_in_order() const
    {
        if constexpr (K == 2)
        {
            return InOrderIterator(nullptr); // End iterator with empty stack
        }
        else
        {
            return DFSIterator(nullptr);
        }
    }

    BFSIterator begin_bfs_scan() const
    {
        return BFSIterator(root_);
    }

    BFSIterator end_bfs_scan() const
    {
        return BFSIterator(nullptr); // End iterator with empty queue
    }
    DFSIterator begin_dfs_scan() const
    {
        return DFSIterator(root_);
    }

    DFSIterator end_dfs_scan() const
    {
        return DFSIterator(nullptr); // End iterator with empty stack
    }

    // Default iterator for range-based for loops (BFS)
    BFSIterator begin() const
    {
        return begin_bfs_scan();
    }

    BFSIterator end() const
    {
        return end_bfs_scan();
    }
    HeapIterator begin_heap()
    {
        return HeapIterator(root_);
    }

    HeapIterator end_heap()
    {
        return HeapIterator(nullptr);
    }
};

#endif