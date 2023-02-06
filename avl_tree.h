/*
 *  Implmentation of a templated AVL Tree using recursive methods
 *  Written by Zach Schrag
*/

#pragma once
#include <iostream>

template <typename Comparable>
class AVLTree {
    struct AVLNode {
        Comparable value;
        AVLNode* left;
        AVLNode* right;
        int height;

        AVLNode() : value{}, left{nullptr}, right{nullptr}, height{1} {}
        explicit AVLNode(const Comparable& value) : value{value}, left{nullptr}, right{nullptr}, height{1} {}
        AVLNode(const Comparable& value, AVLNode* left, AVLNode* right, int height) : value{value}, left{left}, right{right}, height{height} {}
    };

    AVLNode* root;

    // rule of three helper methods
    AVLNode* copy(const AVLNode* root) {
        if (!root) return nullptr;
        return new AVLNode(root->value, copy(root->left), copy(root->right), root->height);
    }
    
    void clear() {
        while(!is_empty())
            remove(find_min());
    }

    // helper method for rebalance methods - must avoid trying nullptr->height
    int height(const AVLNode* node) const { return !node ? 0 : node->height; }

    // methods for rebalancing
    void single_left_rotation(AVLNode* &root) {
        AVLNode* right_child = root->right;
        root->right = right_child->left;
        right_child->left = root;

        right_child->height = (height(right_child->left) > height(right_child->right) ? height(right_child->left) : height(right_child->right)) + 1;
        root->height = (height(root->left) > height(root->right) ? height(root->left) : height(root->right)) + 1;

        root = right_child;
    }

    void single_right_rotation(AVLNode* &root) {
        AVLNode* left_child = root->left;
        root->left = left_child->right;
        left_child->right = root;

        left_child->height = (height(left_child->left) > height(left_child->right) ? height(left_child->left) : height(left_child->right)) + 1;
        root->height = (height(root->left) > height(root->right) ? height(root->left) : height(root->right)) + 1;

        root = left_child;
    }

    void double_left_rotation(AVLNode* &root) {
        single_right_rotation(root->right);
        single_left_rotation(root);
    }

    void double_right_rotation(AVLNode* &root) {
        single_left_rotation(root->left);
        single_right_rotation(root);
    }

    void rebalance(AVLNode* &root) {
        if (!root) return;

        if (height(root->left) - height(root->right) > 1) {
            if (height(root->left->left) >= height(root->left->right)) single_right_rotation(root);
            else double_right_rotation(root);
        }
        else if (height(root->right) - height(root->left) > 1) {
            if (height(root->right->right) >= height(root->right->left)) single_left_rotation(root);
            else double_left_rotation(root);
        }
        
        root->height = (height(root->left) > height(root->right) ? height(root->left) : height(root->right)) + 1;
    }

    // helper methods for public methods
    bool contains(const Comparable& value, const AVLNode* root) const {
        if (!root) return false;
        else if (value < root->value) return contains(value, root->left);
        else if (value > root->value) return contains(value, root->right);
        else return true; 
    }

    const Comparable& find_min(const AVLNode* root) const {
        if (!root) throw std::invalid_argument("Tree is empty.");

        if ( !(root->left) ) return root->value;
        else return find_min(root->left);
    }

    const Comparable& find_max(const AVLNode* root) const {
        if (!root) throw std::invalid_argument("Tree is empty.");

        if ( !(root->right) ) return root->value;
        else return find_max(root->right);
    }

    void print_tree(AVLNode* root, std::ostream& os = std::cout, unsigned int depth = 0) const {
        if (is_empty()) {
            os << "<empty>" << std::endl;
            return;
        }
        if (root->right) print_tree(root->right, os, depth + 1);
        os << std::string(depth * 2, ' ') << root->value << std::endl;
        if (root->left) print_tree(root->left, os, depth + 1);
    }

    void insert(const Comparable& value, AVLNode* &root) {
        if (!root) root = new AVLNode(value);
        else if (value < root->value) insert(value, root->left);
        else if (value > root->value) insert(value, root->right);
        rebalance(root);
    }

    void remove(const Comparable& value, AVLNode* &root) {
        if (!root) return;

        if (value < root->value) remove(value, root->left);

        else if (value > root->value) remove(value, root->right);

        else if (root->left && root->right) {
            root->value = find_min(root->right);
            remove(root->value, root->right);
        } 

        else {
            AVLNode* old_root = root;
            if (root->left) root = root->left;
            else root = root->right;

            delete old_root;
        }

        rebalance(root);
    }

    public:
        AVLTree() : root{nullptr} {}

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


        AVLTree(const AVLTree& other) : root{} { root = copy(other.root); }
        ~AVLTree() { clear(); }
        AVLTree& operator=(const AVLTree& rhs) {
            if (this != &rhs) {
                clear();
                root = copy(rhs.root);
            }
            return *this;
        }

        // FOR TESTING
        const AVLNode* getRoot() const { return root; }
};
