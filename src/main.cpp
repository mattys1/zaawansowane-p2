#include "BSTTree.hpp"

int main (int argc, char *argv[]) {
	BSTTree<int> tree(5);
	BSTTree<int> tree2;

	tree.add(2);
	tree.add(3);
	tree.add(10);
	tree.add(7);
	tree.add(1);

	tree.delete_tree();

	tree.add(8);
	tree.add(2);
	tree.add(9);

	return 0;
}
