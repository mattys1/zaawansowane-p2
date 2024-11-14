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
};
