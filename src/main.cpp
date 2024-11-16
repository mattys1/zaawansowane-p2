#include "BSTTree.hpp"
#include <print>

int main (int argc, char *argv[]) {
	BSTTree<int> tree(5);
	BSTTree<int> tree2;

	tree.add(2);
	tree.add(3);
	tree.add(10);
	tree.add(7);
	tree.add(1);

	std::println("Preorder traversal:");
	for(const auto item : tree.traverse_preorder()) {
		std::print("{},", item);
	}

	std::println();

	std::println("Inorder traversal:");
	for(const auto item : tree.traverse_inorder()) {
		std::print("{},", item);
	}

	std::println();

	std::println("Postorder: traversal:");
	for(const auto item : tree.traverse_postorder()) {
		std::print("{},", item);
	}

	std::println();

	std::println("Deleting 1 and 5");
	tree.delete_element(1);
	tree.delete_element(5);

	std::println("Preorder traversal:");
	for(const auto item : tree.traverse_preorder()) {
		std::print("{},", item);
	}

	std::println();

	std::println("Inorder traversal:");
	for(const auto item : tree.traverse_inorder()) {
		std::print("{},", item);
	}

	std::println();

	std::println("Postorder: traversal:");
	for(const auto item : tree.traverse_postorder()) {
		std::print("{},", item);
	}


	tree.delete_tree();

	tree.add(8);
	tree.add(2);
	tree.add(9);

	return 0;
}
