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

	Tree root;

	void recursive_add(const T& element, Tree* node) {

	}

public:
	void add(const T& element) {
		recursive_add(element, root);
	}
};