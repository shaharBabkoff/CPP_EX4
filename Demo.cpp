
#include <iostream>
#include <string>
#include "Node.hpp"
#include "Tree.hpp"
#include "complex.h"
#include <SFML/Graphics.hpp>
class PreOrderIterator;
using namespace std;

int main()
{

    Node<string> root_node("hellow");
    Tree<string> tree; // Binary tree that contains doubles.
    tree.add_root(root_node);
    Node<string> n1("my");
    Node<string> n2("name");
    Node<string> n3("is");
    Node<string> n4("shahar");
    Node<string> n5("babkoff");

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);
    tree.print();
    cout << root_node.getChildren()[0]->getChildren().size() << "  num of grand" << endl;

    // The tree should look like:
    /**
     *       root = 1.1
     *     /       \
     *    1.2      1.3
     *   /  \      /
     *  1.4  1.5  1.6
     */

    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
    {
        cout << (*node)->getValue() << " ";
    } // prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6
    cout << endl;
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
    {
        cout << (*node)->getValue() << " ";
    } // prints: 1.4, 1.5, 1.2, 1.6, 1.3, 1.1
    cout << endl;
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
    {
        cout << (*node)->getValue() << " ";
    } // prints: 1.4, 1.2, 1.5, 1.1, 1.6, 1.3
    cout << endl;
    for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
    {
        cout << (*node)->getValue() << " ";
    } // prints: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6
    cout << endl;
    for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node)
    {
        cout << (*node)->getValue() << " ";
    } // prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6
    cout << endl;
    for (auto node : tree)
    {
        cout << node->getValue() << " ";
    } // same as BFS: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6
    cout << endl;
    // for (auto node = tree.begin_heap(); node != tree.end_heap(); ++node)
    // {
    //     std::cout << (*node)->getValue() << std::endl;
    // }
    // cout << tree; // Should print the graph using GUI.

    Node<double> root_node2(1.1);
    Tree<double, 3> tree2; // Binary tree that contains doubles.
    tree2.add_root(root_node2);
    Node<double> n22(1.2);
    Node<double> n23(1.3);
    Node<double> n24(1.4);
    Node<double> n25(1.5);
    Node<double> n26(1.6);
    Node<double> n27(1.7);
    Node<double> n28(1.8);
    Node<double> n29(1.9);
    Node<double> n30(2.0);
    Node<double> n31(2.1);
    Node<double> n32(2.2);

    tree2.add_sub_node(root_node2, n22);
    tree2.add_sub_node(root_node2, n23);
    tree2.add_sub_node(root_node2, n24);
    tree2.add_sub_node(n22, n25);
    tree2.add_sub_node(n22, n26);
    tree2.add_sub_node(n22, n27);
    tree2.add_sub_node(n22, n25);
    tree2.add_sub_node(n23, n28);
    tree2.add_sub_node(n24, n29);
    tree2.add_sub_node(n25, n30);
    tree2.add_sub_node(n25, n31);
    tree2.add_sub_node(n25, n32);
    tree2.print();
    tree2.visualize();
    cout << "pre order: \n";
    for (auto node = tree2.begin_pre_order(); node != tree2.end_pre_order(); ++node)
    {

        cout << (*node)->getValue() << " ";
    } // 1.1 1.2 1.5 1.3 1.6 1.4

    cout << endl;
    cout << "post order: \n";
    for (auto node = tree2.begin_post_order(); node != tree2.end_post_order(); ++node)
    {

        cout << (*node)->getValue() << " ";
    } // 1.1 1.2 1.5 1.3 1.6 1.4
    cout << endl;
    cout << "in order: \n";
    for (auto node = tree2.begin_in_order(); node != tree2.end_in_order(); ++node)
    {

        cout << (*node)->getValue() << " ";
    } // 1.1 1.2 1.5 1.3 1.6 1.4
    cout << endl;
    cout << "bfs: \n";
    for (auto node = tree2.begin_bfs_scan(); node != tree2.end_bfs_scan(); ++node)
    {

        cout << (*node)->getValue() << " ";
    } // 1.1, 1.2, 1.3, 1.4, 1.5, 1.6
    cout << endl;
    cout << "dfs: \n";
    for (auto node = tree2.begin_dfs_scan(); node != tree2.end_dfs_scan(); ++node)
    {

        cout << (*node)->getValue() << " ";
    } // 1.1 1.2 1.5 1.3 1.6 1.4
    cout << endl;
    cout << "default" << endl;
    for (auto node : tree2)
    {
        cout << node->getValue() << " ";
    } // 1.1, 1.2, 1.3, 1.4, 1.5, 1.6
    cout << endl;

    // Call myHeap with pre-order iterators
    // auto heap_begin = tree2.begin_pre_order();
    // auto heap_end = tree2.end_pre_order();
    // tree2.myHeap(heap_begin, heap_end);

    // // Print the heap
    // for (auto node = tree2.begin_heap(); node != tree2.end_heap(); ++node)
    // {
    //     std::cout << (*node)->getValue() << std::endl;
    // }

    // The tree should look like:
    /**
     *       root = 1.1
     *     /      |     \
     *    1.2    1.3    1.4
     *   /        |
     *  1.5      1.6
     */
}