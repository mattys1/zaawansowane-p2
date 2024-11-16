#pragma once

#include <ranges>
#include <vector>
#include <algorithm>

template <typename T>
class BSTTree {
private:
	struct Tree {
		T contents;
		Tree* parent;
		Tree* left;
		Tree* right;

		Tree(T _contents, Tree* _parent = nullptr, Tree* _left = nullptr, Tree* _right = nullptr):
			contents { _contents },
			parent { _parent },
			left { _left },
			right { _right } {}

		~Tree() {
			delete left;
			delete right;
		}
	};

	Tree* root;

	void recursive_add(const T& element, Tree* node, Tree* parentNode = nullptr) {
		if(node == nullptr) {
			node = new Tree(element);

			if(parentNode == nullptr) {
				return;
			}

			node->parent = parentNode;

			if(node->contents >= parentNode->contents) {
				parentNode->right = node;
			} else {
				parentNode->left = node;
			}

			return;
		}

		if(element >= node->contents) {
			recursive_add(element, node->right, node);
		} else {
			recursive_add(element, node->left, node);
		}	
	}

	void preorder_traverse_recursive(Tree* node, std::vector<Tree*>& traversedTrees) {
		if(node == nullptr) {
			return;
		}

		traversedTrees.push_back(node);

		preorder_traverse_recursive(node->left, traversedTrees);
		preorder_traverse_recursive(node->right, traversedTrees);
	}

	void inorder_traverse_recursive(Tree* node, std::vector<Tree*>& traversedTrees) {
		if(node == nullptr) {
			return;
		}

		inorder_traverse_recursive(node->left, traversedTrees);

		traversedTrees.push_back(node);

		inorder_traverse_recursive(node->right, traversedTrees);
	}

	void postorder_traverse_recursive(Tree* node, std::vector<Tree*>& traversedTrees) {
		if(node == nullptr) {
			return;
		}

		postorder_traverse_recursive(node->left, traversedTrees);
		postorder_traverse_recursive(node->right, traversedTrees);

		traversedTrees.push_back(node);
	}

public:
	BSTTree(const T& element): root { new Tree(element) } {}
	BSTTree(void): root { nullptr } {}
	~BSTTree() { delete root; }

	/// Add a single element to the tree
	/// @param element element of T to insert to the tree
	///
	/// This operation happens recursively
	void add(const T& element) {
		recursive_add(element, root);
	}

	void delete_tree(void) {
		delete root;
		root = nullptr;
	}

	/// Traverse the tree in the preorder direction and return a vector the contents of each node
	/// @return preordered vector of the elements of the tree
	std::vector<T> traverse_preorder(void) {
		std::vector<Tree*> traversedTrees;
	
		preorder_traverse_recursive(root, traversedTrees);

		return traversedTrees | std::ranges::views::transform([](const Tree* tree) { return tree->contents; }) | std::ranges::to<std::vector>(); 
	}

	/// Traverse the tree in the inorder direction and return a vector the contents of each node
	/// @return inordered vector of the elements of the tree
	std::vector<T> traverse_inorder() {
		std::vector<Tree*> traversedTrees;

		inorder_traverse_recursive(root, traversedTrees);

		return traversedTrees | std::ranges::views::transform([](const Tree* tree) { return tree->contents; }) | std::ranges::to<std::vector>(); 
	}

	/// Traverse the tree in the postorder direction and return a vector the contents of each node
	/// @return postordered vector of the elements of the tree
	std::vector<T> traverse_postorder() {
		std::vector<Tree*> traversedTrees;

		postorder_traverse_recursive(root, traversedTrees);

		return traversedTrees | std::ranges::views::transform([](const Tree* tree) { return tree->contents; }) | std::ranges::to<std::vector>(); 
	}

	/// Delete an element of a given value
	/// @param value The value of an element that is to be deleted.
	///
	/// This does not differentiate between unique elements of the same value
	int delete_element(T value) {
		std::vector<Tree*> traversedTrees;
		inorder_traverse_recursive(root, traversedTrees);
		auto elementOfValueIterator = std::find_if(traversedTrees.begin(), traversedTrees.end(), 
											 [&value](const Tree* tree) { return tree->contents == value;});

		if(elementOfValueIterator == traversedTrees.end()) {
			return -1;
		}

		Tree* elementOfValue { *elementOfValueIterator };

		if(elementOfValue->left == nullptr && elementOfValue->right == nullptr) {
			if(elementOfValue->parent != nullptr) {
				if(elementOfValue->parent->left == elementOfValue) {
					elementOfValue->parent->left = nullptr;
				} else {
					elementOfValue->parent->right = nullptr;
				}
			}

			delete elementOfValue;
		} else {
			Tree* successor = *std::next(elementOfValueIterator);

			if(successor->parent != nullptr) {
				if(successor->parent->left == successor) {
					successor->parent->left = nullptr;
				} else {
					successor->parent->right = nullptr;
				}
			}

			elementOfValue->contents = successor->contents;
			delete successor;
		}

		return 0;
	}
};
