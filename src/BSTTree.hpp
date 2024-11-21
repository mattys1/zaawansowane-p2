/**
 * @file BSTTree.hpp
 * @brief Binary Search Tree (BST) implementation for storing and manipulating elements of type T.
 */

#pragma once

#include <ranges>
#include <vector>
#include <algorithm>

 /**
  * @class BSTTree
  * @brief A Binary Search Tree (BST) implementation for managing elements of type T.
  *
  * This class provides functionality to add, traverse, and delete elements from a binary search tree.
  * The tree supports recursive traversal methods (preorder, inorder, postorder) and maintains its structure
  * based on standard BST rules.
  *
  * @tparam T The type of elements to be stored in the tree.
  */
template <typename T>
class BSTTree {
private:
    /**
     * @brief Represents a single node in the Binary Search Tree.
     */
    struct Tree {
        T contents;      ///< The data contained in the node.
        Tree* parent;    ///< Pointer to the parent node.
        Tree* left;      ///< Pointer to the left child.
        Tree* right;     ///< Pointer to the right child.

        /**
         * @brief Constructs a Tree node with given parameters.
         * @param _contents The value to be stored in the node.
         * @param _parent Pointer to the parent node (default is nullptr).
         * @param _left Pointer to the left child (default is nullptr).
         * @param _right Pointer to the right child (default is nullptr).
         */
        Tree(T _contents, Tree* _parent = nullptr, Tree* _left = nullptr, Tree* _right = nullptr) :
            contents{ _contents }, parent{ _parent }, left{ _left }, right{ _right } {
        }

        /**
         * @brief Destructor to clean up dynamically allocated child nodes.
         */
        ~Tree() {
            delete left;
            delete right;
        }
    };

    Tree* root; ///< Pointer to the root node of the tree.

    /**
     * @brief Recursively adds an element to the tree.
     * @param element The element to be added.
     * @param node Reference to the current node being inspected.
     * @param parentNode Pointer to the parent of the current node (default is nullptr).
     */
    void recursive_add(const T& element, Tree*& node, Tree* parentNode = nullptr) {
        if (node == nullptr) {
            node = new Tree(element);
            if (parentNode == nullptr) {
                return;
            }
            node->parent = parentNode;
            if (node->contents >= parentNode->contents) {
                parentNode->right = node;
            }
            else {
                parentNode->left = node;
            }
            return;
        }
        if (element >= node->contents) {
            recursive_add(element, node->right, node);
        }
        else {
            recursive_add(element, node->left, node);
        }
    }

    /**
     * @brief Recursively performs preorder traversal of the tree.
     * @param node Pointer to the current node being visited.
     * @param traversedTrees Vector to store pointers to visited nodes.
     */
    void preorder_traverse_recursive(Tree* node, std::vector<Tree*>& traversedTrees) const {
        if (node == nullptr) {
            return;
        }
        traversedTrees.push_back(node);
        preorder_traverse_recursive(node->left, traversedTrees);
        preorder_traverse_recursive(node->right, traversedTrees);
    }

    /**
     * @brief Recursively performs inorder traversal of the tree.
     * @param node Pointer to the current node being visited.
     * @param traversedTrees Vector to store pointers to visited nodes.
     */
    void inorder_traverse_recursive(Tree* node, std::vector<Tree*>& traversedTrees) const {
        if (node == nullptr) {
            return;
        }
        inorder_traverse_recursive(node->left, traversedTrees);
        traversedTrees.push_back(node);
        inorder_traverse_recursive(node->right, traversedTrees);
    }

    /**
     * @brief Recursively performs postorder traversal of the tree.
     * @param node Pointer to the current node being visited.
     * @param traversedTrees Vector to store pointers to visited nodes.
     */
    void postorder_traverse_recursive(Tree* node, std::vector<Tree*>& traversedTrees) const {
        if (node == nullptr) {
            return;
        }
        postorder_traverse_recursive(node->left, traversedTrees);
        postorder_traverse_recursive(node->right, traversedTrees);
        traversedTrees.push_back(node);
    }

public:
    /**
     * @brief Constructs a BSTTree with an initial element.
     * @param element The initial element to be stored in the root node.
     */
    BSTTree(const T& element) : root{ new Tree(element) } {}

    /**
     * @brief Constructs an empty BSTTree.
     */
    BSTTree() : root{ nullptr } {}

    /**
     * @brief Destructor to clean up dynamically allocated nodes in the tree.
     */
    ~BSTTree() { delete root; }

    /**
     * @brief Adds an element to the tree.
     * @param element The element to insert into the tree.
     *
     * This operation is performed recursively.
     */
    void add(const T& element) {
        recursive_add(element, root);
    }

    /**
     * @brief Deletes all nodes in the tree, resetting it to an empty state.
     */
    void delete_tree() {
        delete root;
        root = nullptr;
    }

    /**
     * @brief Performs a preorder traversal of the tree.
     * @return A vector containing the elements of the tree in preorder.
     */
    std::vector<T> traverse_preorder() const {
        std::vector<Tree*> traversedTrees;
        preorder_traverse_recursive(root, traversedTrees);
        return traversedTrees | std::ranges::views::transform([](const Tree* tree) { return tree->contents; }) | std::ranges::to<std::vector>();
    }

    /**
     * @brief Performs an inorder traversal of the tree.
     * @return A vector containing the elements of the tree in inorder.
     */
    std::vector<T> traverse_inorder() const {
        std::vector<Tree*> traversedTrees;
        inorder_traverse_recursive(root, traversedTrees);
        return traversedTrees | std::ranges::views::transform([](const Tree* tree) { return tree->contents; }) | std::ranges::to<std::vector>();
    }

    /**
     * @brief Performs a postorder traversal of the tree.
     * @return A vector containing the elements of the tree in postorder.
     */
    std::vector<T> traverse_postorder() const {
        std::vector<Tree*> traversedTrees;
        postorder_traverse_recursive(root, traversedTrees);
        return traversedTrees | std::ranges::views::transform([](const Tree* tree) { return tree->contents; }) | std::ranges::to<std::vector>();
    }

    /**
     * @brief Deletes the first element with a specified value from the tree.
     * @param value The value of the element to be deleted.
     *
     * The operation does not differentiate between duplicate elements with the same value.
     * @return 0 if the element was successfully deleted, -1 if the element was not found.
     */
    int delete_element(T value) {
        std::vector<Tree*> traversedTrees;
        inorder_traverse_recursive(root, traversedTrees);
        auto elementOfValueIterator = std::find_if(traversedTrees.begin(), traversedTrees.end(),
            [&value](const Tree* tree) { return tree->contents == value; });
        if (elementOfValueIterator == traversedTrees.end()) {
            return -1;
        }
        Tree* elementOfValue{ *elementOfValueIterator };
        if (elementOfValue->left == nullptr && elementOfValue->right == nullptr) {
            if (elementOfValue->parent != nullptr) {
                if (elementOfValue->parent->left == elementOfValue) {
                    elementOfValue->parent->left = nullptr;
                }
                else {
                    elementOfValue->parent->right = nullptr;
                }
            }
            delete elementOfValue;
        }
        else {
            Tree* successor = *std::next(elementOfValueIterator);
            if (successor->parent != nullptr) {
                if (successor->parent->left == successor) {
                    successor->parent->left = nullptr;
                }
                else {
                    successor->parent->right = nullptr;
                }
            }
            elementOfValue->contents = successor->contents;
            delete successor;
        }
        return 0;
    }
};
