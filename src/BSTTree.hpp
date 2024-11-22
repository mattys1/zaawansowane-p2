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
  * @tparam T The type of elements to be stored in the tree.
  */
template <typename T>
class BSTTree {
private:
    /**
     * @brief Represents a single node in the Binary Search Tree.
     */
    struct Tree {
        T contents;
        Tree* parent;
        Tree* left;  
        Tree* right;

        /**
         * @brief Constructs a Tree node with given parameters.
         * @param _contents The value to be stored in the node.
         * @param _parent Pointer to the parent node.
         * @param _left Pointer to the left child.
         * @param _right Pointer to the right child.
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

    Tree* root;

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
     * @brief Traverse the tree in the preorder direction and return a vector the contents of each node.
     * @return Preordered vector of the elements of the tree.
     */
    std::vector<T> traverse_preorder() const {
        std::vector<Tree*> traversedTrees;
        preorder_traverse_recursive(root, traversedTrees);
        return traversedTrees | std::ranges::views::transform([](const Tree* tree) { return tree->contents; }) | std::ranges::to<std::vector>();
    }

    /**
     * @brief Traverse the tree in the inorder direction and return a vector the contents of each node.
     * @return Inordered vector of the elements of the tree.    
     */
    std::vector<T> traverse_inorder() const {
        std::vector<Tree*> traversedTrees;
        inorder_traverse_recursive(root, traversedTrees);
        return traversedTrees | std::ranges::views::transform([](const Tree* tree) { return tree->contents; }) | std::ranges::to<std::vector>();
    }

    /**
     * @brief Traverse the tree in the postorder direction and return a vector the contents of each node.
     * @return Postordered vector of the elements of the tree.
     */
    std::vector<T> traverse_postorder() const {
        std::vector<Tree*> traversedTrees;
        postorder_traverse_recursive(root, traversedTrees);
        return traversedTrees | std::ranges::views::transform([](const Tree* tree) { return tree->contents; }) | std::ranges::to<std::vector>();
    }

    /**
     * @brief Delete an element of a given value.
     * @param value The value of the element to be deleted.
     * 
     * This does not differentiate between unique elements of the same value.
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
        } else {
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


    /**
    * @brief Finds the path to a value in a binary search tree.
    *
    * @tparam T The type of the tree values.
    * @param value The value to find.
    * @return std::vector<T> Path to the value or empty if not found.
    */
    std::vector<T> find_path(const T& value) {
        std::vector<T> path;
        Tree* curr = root;

        while (root != nullptr) {
            path.push_back(curr->contents);

            if (curr->contents == value) {
                return path;
            }
            else if (value < curr->contents) {
                curr = curr->left;
            }
            else {
                curr = curr->right;
            }
        }
        return {};
    }

};
