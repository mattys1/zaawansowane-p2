#pragma once

#include <iostream>
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

public:
	BSTTree(const T& element): root { new Tree(element) } {}
	~BSTTree() { delete root; }
};
