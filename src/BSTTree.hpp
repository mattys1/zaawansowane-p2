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

	void recursive_add(const T& element, Tree* node, Tree* parentNode = nullptr) {
		if(node == nullptr) {
			node = new Tree(element);
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

public:
	BSTTree(const T& element): root { new Tree(element) } {}
	BSTTree(void): root { nullptr } {}
	~BSTTree() { delete root; }

	/// Add a single element to the tree
	///
	/// This operation happens recursively
	void add(const T& element) {
		recursive_add(element, root);
	}

	void delete_tree(void) {
		delete root;
		root = nullptr;
	}
};
