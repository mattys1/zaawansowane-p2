#pragma once

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

	void recursive_add(const T& element, Tree* node) {
		if(element >= node->contents) {
			if(node->right == nullptr) {
				node->right = new Tree(element);
				return;
			}

			recursive_add(element, node->right);
		} else {
			if(node->right == nullptr) {
				node->left = new Tree(element);
				return;
			}

			recursive_add(element, node->left);
		}	
	}

	// Searches for the lowest element
	Tree* find_min_child(Tree* node) {
		while (node->left != nullptr) {
			node = node->left;
		}
		return node;
	}

	Tree* recursive_remove(Tree* node, const T& element) {
		if (node == nullptr) {
			return node; // returns null if there's no element
		}

		if (element < node->contents) {
			node->left = recursive_remove(node->left, element); // Here it searches the left side of the tree provided the element is less than contents
		}
		else if (element > node->contents) {
			node->right = recursive_remove(node->right, element); // Same principle but searches the right side
		}
		else {
			// For nodes with one or no children
			if (node->left == nullptr) {
				Tree* temp = node->right;
				node->right = nullptr;
				delete node;
				return temp;
			}
			else if (node->right == nullptr) {
				Tree* temp = node->left;
				node->left = nullptr;
				delete node;
				return temp;
			}

			// For nodes with two and more children
			Tree* temp = find_min_child(node->right);
			node->contents = temp->contents;
			node->right = recursive_remove(node->right, temp->contents);
		}
		return node;
	}

public:
	BSTTree(const T& element): root { new Tree(element) } {}
	BSTTree(void): root { nullptr } {}
	~BSTTree() { delete root; }

	void add(const T& element) {
		if(root == nullptr) {
			root = new Tree(element);
			return;
		}

		recursive_add(element, root);
	}

	void remove(const T& element) {
		root = recursive_remove(root, element);
	}
};
