/**
 * @file FileTree.hpp
 * @brief A simple class to save and load a Binary Search Tree (BSTTree) from files.
 */

#pragma once

#include "BSTTree.hpp"
#include <fstream>
#include <vector>
#include <iostream>

template <typename T>
class FileTree {
public:
    /**
     * @brief Save the tree's elements to a text file.
     * @param filename The name of the file to save to.
     * @param elements A list of tree elements.
     */
    void save_to_text(const std::string& filename, const std::vector<T>& elements) {
        std::ofstream file(filename);
        if (!file) {
            std::cerr << "Error: Could not open file for writing.\n";
            return;
        }
        for (const auto& elem : elements) {
            file << elem << " ";
        }
    }

    /**
     * @brief Load elements from a text file into a tree.
     * @param filename The name of the file to read from.
     * @param tree The tree to populate.
     * @param elements A list to store the loaded elements.
     * @param append Whether to add to an existing tree or start fresh.
     */
    void load_from_text(const std::string& filename, BSTTree<T>& tree, std::vector<T>& elements, bool append = false) {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Error: Could not open file for reading.\n";
            return;
        }
        if (!append) {
            tree.delete_tree();
            elements.clear();
        }
        T value;
        while (file >> value) {
            elements.push_back(value);
            tree.add(value);
        }
    }

    /**
     * @brief Save the tree's elements to a binary file.
     * @param filename The name of the binary file.
     * @param elements A list of tree elements.
     */
    void save_to_binary(const std::string& filename, const std::vector<T>& elements) {
        std::ofstream file(filename, std::ios::binary);
        if (!file) {
            std::cerr << "Error: Could not open file for binary writing.\n";
            return;
        }
        size_t size = elements.size();
        file.write(reinterpret_cast<const char*>(&size), sizeof(size));
        for (const auto& elem : elements) {
            file.write(reinterpret_cast<const char*>(&elem), sizeof(T));
        }
    }

    /**
     * @brief Load elements from a binary file into a tree.
     * @param filename The name of the binary file to read.
     * @param tree The tree to populate.
     * @param elements A list to store the loaded elements.
     * @param append Whether to add to an existing tree or start fresh. Without this, tree would have to deleted manually.
     */
    void load_from_binary(const std::string& filename, BSTTree<T>& tree, std::vector<T>& elements, bool append = false) {
        std::ifstream file(filename, std::ios::binary);
        if (!file) {
            std::cerr << "Error: Could not open file for binary reading.\n";
            return;
        }
        if (!append) {
            tree.delete_tree();
            elements.clear();
        }
        size_t size = 0;
        file.read(reinterpret_cast<char*>(&size), sizeof(size));
        for (size_t i = 0; i < size; ++i) {
            T elem;
            file.read(reinterpret_cast<char*>(&elem), sizeof(T));
            elements.push_back(elem);
            tree.add(elem);
        }
    }
};