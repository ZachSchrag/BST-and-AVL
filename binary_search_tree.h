/*
 *  Implmentation of a templated Binary Search Tree using recursive methods
 *  Written by Zach Schrag
*/

#pragma once
#include <iostream> // print_tree

template <typename Comparable>
class BinarySearchTree {
    struct BinarySearchTreeNode {
        Comparable value;
        BinarySearchTreeNode* left;
        BinarySearchTreeNode* right;

        BinarySearchTreeNode() : value{}, left{nullptr}, right{nullptr} {}
        explicit BinarySearchTreeNode(const Comparable& value) : value{value}, left{nullptr}, right{nullptr} {}
        BinarySearchTreeNode(const Comparable& value, BinarySearchTreeNode* left, BinarySearchTreeNode* right) : value{value}, left{left}, right{right} {} 
    };

    BinarySearchTreeNode* root;

    // for rule of 3
    BinarySearchTreeNode* copy(const BinarySearchTreeNode* root) {
        if (!root) return nullptr;
        return new BinarySearchTreeNode(root->value, copy(root->left), copy(root->right));
    }

    void clear() {
        while(!is_empty())
            remove(find_min());
    }

    // recursive helper methods:
    bool contains(const Comparable& value, BinarySearchTreeNode* root) const {
        if (!root) return false;
        else if (value < root->value) return contains(value, root->left);
        else if (value > root->value) return contains(value, root->right);
        else return true; // if we got here it's not less than or greater than and it isn't nullptr so it must be the value we want
    }

    void insert(const Comparable& value, BinarySearchTreeNode* &root) {
        if (!root) root = new BinarySearchTreeNode(value);
        else if (value < root->value) insert(value, root->left);
        else if (value > root->value) insert(value, root->right);
        else return;
    }

    void remove(const Comparable& value, BinarySearchTreeNode* &root) {
        if (!root) return; // do nothing or throw exception. not sure yet

        if (value < root->value) remove(value, root->left);

        else if (value > root->value) remove(value, root->right);

        else if (root->left && root->right) {
            root->value = find_min(root->right);
            remove(root->value, root->right);
        } 

        else {
            BinarySearchTreeNode* old_root = root;
            if (root->left) root = root->left;
            else root = root->right;

            delete old_root;
        }
    }

    const Comparable& find_min(BinarySearchTreeNode* root) const {
        if (!root) throw std::invalid_argument("Tree is empty.");

        if ( !(root->left) ) return root->value;
        else return find_min(root->left);
    }

    const Comparable& find_max(BinarySearchTreeNode* root) const {
        if (!root) throw std::invalid_argument("Tree is empty.");

        if ( !(root->right) ) return root->value;
        else return find_max(root->right);
    }

    void print_tree(BinarySearchTreeNode* root, std::ostream& os = std::cout, unsigned int depth = 0) const {
        if (is_empty()) {
            os << "<empty>" << std::endl;
            return;
        }
        if (root->right) print_tree(root->right, os, depth + 1);
        os << std::string(depth * 2, ' ') << root->value << std::endl;
        if (root->left) print_tree(root->left, os, depth + 1);
    }

    public:
        BinarySearchTree() : root{nullptr} {}

        // modifers
        void insert(const Comparable& value) { insert(value, root); }
        void remove(const Comparable& value) { remove(value, root); }

        // searching
        bool contains(const Comparable& value) const { return contains(value, root); }
        const Comparable& find_min() const { return find_min(root); }
        const Comparable& find_max() const { return find_max(root); }
        
        // visualization
        void print_tree(std::ostream& os = std::cout) const { print_tree(root, os); }

        // capacity
        bool is_empty() const { return !root; }
        void make_empty() { clear(); }

        // rule of three
        BinarySearchTree(const BinarySearchTree& other) : root{} { root = copy(other.root); }
        ~BinarySearchTree() { clear(); }
        BinarySearchTree& operator=(const BinarySearchTree& rhs) {
            if (this != &rhs) {
                clear();
                root = copy(rhs.root);
            }
            return *this;
        }

        // FOR TESTING
        const BinarySearchTreeNode* getRoot() const { return root; }

};
