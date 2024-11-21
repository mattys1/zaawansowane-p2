#include "BSTTree.hpp"
#include "FileTree.hpp"
#include <print>
#include <iostream>
#include <string>


bool lauf()
{
    std::string input;
    std::cout << "\nDo you want to repeat? (type yes ocontinue, no to stop): ";
    std::cin >> input;
    do {
        if (input == "Yes" || input == "yes") {
            return true;
        }
        else if (input == "no" || input == "No") {
            return false;
        }
        else {
            std::cout << "insert ONLY yes or no";
            std::cin >> input;
        }
    } while (true);

}

int main(int argc, char* argv[]) {
    BSTTree<int> tree;
    BSTTree<int> tree2;
    FileTree<int> fileTree;
    std::vector<int> elements;

    int option;
    int option2;
    int value;
    std::println("List of options:");
    std::println("1 - add element | 2 - remove element | 3 - print traversal preordern");
    std::println("4 - print traversal inorder | 5 - print traversal postorder | 6 - export to file");
    std::println("7 - import from file | 8 - delete tree | 9 - fid path to element");
    std::println();
    do {
        std::print("What do you want to do? "), std::cin >> option;

        switch (option) {
        case 1:
            std::print("Insert element to add: ");
            std::cin >> value;
            tree.add(value);
            elements.push_back(value);
            break;

        case 2:
            std::print("Insert element to remove: ");
            std::cin >> value;
            tree.delete_element(value);
            break;

        case 3:
            std::print("Preorder traversal:\n");
            for (const auto& item : tree.traverse_preorder()) {
                std::print("{}, ", item);
            }
            std::print("\n");
            break;

        case 4:
            std::print("Inorder traversal:\n");
            for (const auto& item : tree.traverse_inorder()) {
                std::print("{}, ", item);
            }
            std::print("\n");
            break;

        case 5:
            std::print("Postorder traversal:\n");
            for (const auto& item : tree.traverse_postorder()) {
                std::print("{}, ", item);
            }
            std::print("\n");
            break;

        case 6:
            std::print("1 - To text | 2 - To binary\n");
            std::print("Do you want to export to text or binary file? ");
            std::cin >> option2;
            if (option2 == 1) {
                fileTree.save_to_text("tree.txt", elements);
                std::print("Tree saved to text file.\n");
            }
            else if (option2 == 2) {
                fileTree.save_to_binary("tree.bin", elements);
                std::print("Tree saved to binary file.\n");
            }
            break;

        case 7:
            std::print("1 - From text | 2 - From binary\n");
            std::print("Do you want to import from text or binary file? ");
            std::cin >> option2;
            if (option2 == 1) {
                fileTree.load_from_text("tree.txt", tree, elements);
                std::print("Tree loaded from text file.\n");
            }
            else if (option2 == 2) {
                fileTree.load_from_binary("tree.bin", tree, elements);
                std::print("Tree loaded from binary file.\n");
            }
            break;
        case 8:
            tree.delete_tree();
            std::print("Tree deleted.\n");
            break;

        case 9: {
            std::print("Input the value to search: "), std::cin >> value;
            auto path = tree.find_path(value);
            if (path.empty()) {
                std::print("Element not found.\n");
            }
            else {
                std::print("Path: ");
                for (const auto& item : path) {
                    std::print("{} ", item);
                }
                std::print("\n");
            }
        }
            break;
        

        default:
            std::print("Invalid option. Try again.\n");
            break;
        }
    } while (lauf());

    return 0;
}
