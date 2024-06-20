// #ifndef TREE_CPP
// #define TREE_CPP

// #include "Tree.hpp"

// template <typename T, int K>
// Tree<T, K>::Tree() : root_(nullptr) {}

// template <typename T, int K>
// Tree<T, K>::~Tree() {}

// template <typename T, int K>
// void Tree<T, K>::add_root(Node<T> &node)
// {
//     root_ = &node;
// }

// template <typename T, int K>
// void Tree<T, K>::deleteTree(Node<T> *node)
// {
//     if (node)
//     {
//         for (Node<T> *child : node->getChildren())
//         {
//             deleteTree(child);
//         }
//         delete node;
//     }
// }

// template <typename T, int K>
// void Tree<T, K>::add_sub_node(Node<T> &parent, Node<T> &child)
// {
//     std::cout << "current children: " << parent.getCurrentChildrenNum() << " K=" << K << std::endl;
//         if (parent.getCurrentChildrenNum() < K)
//         {

//             parent.addChild(&child); // Now correctly adds the new node
//             std::cerr << "add_sub_node succesfully" << std::endl;
//         }
//         else
//         {
//             std::cerr << "Cannot add more children or invalid parent/child." << std::endl;
//         }
// }

// template <typename T, int K>
// Node<T> *Tree<T, K>::get_root() const
// {
//     return root_;
// }

// template <typename T, int K>
// void Tree<T, K>::print()
// {
//     if (root_)
//     {
//         root_->print();
//     }
//     else
//     {
//         std::cout << "Tree is empty." << std::endl;
//     }
// }

// template <typename T, int K>
// void Tree<T, K>::visualize()
// {
//     sf::RenderWindow window(sf::VideoMode(1200, 800), "Tree Visualization");

//     while (window.isOpen())
//     {
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             if (event.type == sf::Event::Closed)
//                 window.close();
//         }

//         window.clear(sf::Color::White);
//         drawTree(window, root_, 600, 50, 400); // Initial position and offset
//         window.display();
//     }
// }

// template <typename T, int K>
// void Tree<T, K>::drawTree(sf::RenderWindow &window, Node<T> *node, float x, float y, float offset)
// {
//     if (!node)
//         return;

//     // Draw the node (circle)
//     sf::CircleShape circle(30);
//     circle.setFillColor(sf::Color::Black);
//     circle.setPosition(x, y);

//     // Load a font for displaying the node value
//     sf::Font font;
//     if (!font.loadFromFile("arial.ttf"))
//     {
//         // Handle font loading error
//         std::cerr << "Failed to load font \"arial.ttf\"" << std::endl;
//         return;
//     }

//     // Convert node value to string
//     std::stringstream ss;
//     ss.precision(2);
//     ss << std::fixed << node->getValue();
//     std::string valueStr = ss.str();

//     // Draw the node value (text)
//     sf::Text text;
//     text.setFont(font);
//     text.setString(valueStr);
//     text.setCharacterSize(20);
//     text.setFillColor(sf::Color::White);

//     // Center the text in the circle
//     sf::FloatRect textRect = text.getLocalBounds();
//     text.setOrigin(textRect.left + textRect.width / 2.0f,
//                    textRect.top + textRect.height / 2.0f);
//     text.setPosition(x + circle.getRadius(), y + circle.getRadius());

//     // Draw the circle and text
//     window.draw(circle);
//     window.draw(text);

//     // Draw lines and recursively draw children
//     const std::vector<Node<T> *> &children = node->getChildren();
//     for (size_t i = 0; i < children.size(); ++i)
//     {
//         float childX = x + (i - (children.size() - 1) / 2.0) * offset;
//         float childY = y + 150;

//         sf::Vertex line[] =
//             {
//                 sf::Vertex(sf::Vector2f(x + circle.getRadius(), y + circle.getRadius()), sf::Color::Black),
//                 sf::Vertex(sf::Vector2f(childX + circle.getRadius(), childY), sf::Color::Black)};

//         window.draw(line, 2, sf::Lines);
//         drawTree(window, children[i], childX, childY, offset / 2);
//     }
// }

// #endif
