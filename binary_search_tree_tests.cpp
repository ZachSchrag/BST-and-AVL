#include <iostream>
#include "binary_search_tree.h"
#include <sstream> // for print_tree tests

using std::cout, std::endl;

#define black   "\033[30m"
#define red     "\033[31m"
#define green   "\033[32m"
#define yellow  "\033[33m"
#define blue    "\033[34m"
#define magenta "\033[35m"
#define cyan    "\033[36m"
#define white   "\033[37m"
#define reset   "\033[m"

#define to_be ==
#define not_to_be !=
#define is to_be
#define is_not not_to_be

#define expect(X) try {\
  if (!(X)) {\
    std::cout << red "  [fail]" reset " (" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ") " << red << "expected " << #X << "." << reset << std::endl;\
  }\
} catch(...) {\
  std::cout << red "  [fail]" reset " (" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ") " << red << #X << " threw an unexpected exception." << reset << std::endl;\
}

#define assert(X) try {\
  if (!(X)) {\
    std::cout << red "  [fail]" reset " (" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ") " << red << "failed assertion that " << #X << "." << reset << std::endl;\
    std::abort();\
  }\
} catch(...) {\
  std::cout << red "  [fail]" reset " (" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ") " << red << #X << " assertion threw an unexpected exception." << reset << std::endl;\
}

#define expect_throw(X,E) {\
  bool threw_expected_exception = false;\
  try { X; }\
  catch(const E& err) {\
    threw_expected_exception = true;\
  } catch(...) {\
    std::cout << blue << "  [help] " << #X << " threw an incorrect exception." << reset << std::endl;\
  }\
  if (!threw_expected_exception) {\
    std::cout << red <<"  [fail]" << reset << " (" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ") " << red << "expected " << #X << " to throw " << #E <<"." << reset <<std::endl;\
  }\
}


int main() {
    // constructor / is_empty()
    {
        BinarySearchTree<int> intTree;
        expect(intTree.is_empty() to_be true);
        intTree.insert(1);
        expect(intTree.is_empty() to_be false);
        intTree.remove(1);
        expect(intTree.is_empty() to_be true);
    }

    // make_empty()
    {
        BinarySearchTree<int> intTree;
        intTree.insert(1);
        intTree.insert(2);
        intTree.make_empty();
        expect(intTree.is_empty() to_be true);
    }


    // insert
    {
        BinarySearchTree<int> intTree;
        intTree.insert(1);
        assert(intTree.getRoot() is_not nullptr);
        expect(intTree.getRoot()->value to_be 1);
        intTree.insert(2);
        assert(intTree.getRoot()->right is_not nullptr);
        expect(intTree.getRoot()->right->value to_be 2);
        intTree.insert(0);
        assert(intTree.getRoot()->left is_not nullptr);
        expect(intTree.getRoot()->left->value to_be 0);
        intTree.insert(-1);
        assert(intTree.getRoot()->left->left is_not nullptr);
        expect(intTree.getRoot()->left->left->value to_be -1);
        expect(intTree.getRoot()->left->left->left to_be nullptr);
        intTree.insert(-2);
        assert(intTree.getRoot()->left->left is_not nullptr);
        expect(intTree.getRoot()->left->left->value to_be -1);
        assert(intTree.getRoot()->left->left->left is_not nullptr);
        expect(intTree.getRoot()->left->left->left->value to_be -2);
        expect(intTree.getRoot()->left->left->left->left to_be nullptr);

        // duplicate insert
        intTree.insert(-2);
        assert(intTree.getRoot()->left->left is_not nullptr);
        expect(intTree.getRoot()->left->left->value to_be -1);
        assert(intTree.getRoot()->left->left->left is_not nullptr);
        expect(intTree.getRoot()->left->left->left->value to_be -2);
        expect(intTree.getRoot()->left->left->left->left to_be nullptr);
    }

    // remove
    {
        BinarySearchTree<int> intTree;
        intTree.insert(2);
        intTree.insert(1);
        intTree.insert(3);

        // confirm pre condition
        assert(intTree.getRoot() is_not nullptr);
        assert(intTree.getRoot()->left is_not nullptr);
        assert(intTree.getRoot()->right is_not nullptr);
        expect(intTree.getRoot()->value to_be 2);
        expect(intTree.getRoot()->left->value to_be 1);
        expect(intTree.getRoot()->right->value to_be 3);

        intTree.remove(3);
        assert(intTree.getRoot() is_not nullptr);
        expect(intTree.getRoot()->value to_be 2);
        expect(intTree.getRoot()->right to_be nullptr);
        assert(intTree.getRoot()->left is_not nullptr);
        expect(intTree.getRoot()->left->value to_be 1);

        intTree.remove(1);
        assert(intTree.getRoot() is_not nullptr);
        expect(intTree.getRoot()->value to_be 2);
        expect(intTree.getRoot()->right to_be nullptr);
        expect(intTree.getRoot()->left to_be nullptr);

        intTree.remove(2);
        expect(intTree.getRoot() to_be nullptr);
        expect(intTree.is_empty() to_be true);


        BinarySearchTree<int> intTree2;
        intTree2.insert(2);
        intTree2.insert(1);
        intTree2.insert(3);

        // confirm pre condition
        assert(intTree2.getRoot() is_not nullptr);
        assert(intTree2.getRoot()->left is_not nullptr);
        assert(intTree2.getRoot()->right is_not nullptr);
        expect(intTree2.getRoot()->value to_be 2);
        expect(intTree2.getRoot()->left->value to_be 1);
        expect(intTree2.getRoot()->right->value to_be 3);

        intTree2.remove(2);
        assert(intTree2.getRoot() is_not nullptr);
        expect(intTree2.getRoot()->value to_be 3);
        expect(intTree2.getRoot()->right to_be nullptr);
        assert(intTree2.getRoot()->left is_not nullptr);
        expect(intTree2.getRoot()->left->value to_be 1);

        intTree2.remove(3);
        assert(intTree2.getRoot() is_not nullptr);
        expect(intTree2.getRoot()->value to_be 1);
        expect(intTree2.getRoot()->right to_be nullptr);
        expect(intTree2.getRoot()->left to_be nullptr);

        intTree2.remove(1);
        expect(intTree2.getRoot() to_be nullptr);
        expect(intTree2.is_empty() to_be true);


        BinarySearchTree<int> intTree3;
        intTree3.insert(2);

        assert(intTree3.getRoot() is_not nullptr);
        expect(intTree3.getRoot()->right to_be nullptr);
        expect(intTree3.getRoot()->left to_be nullptr);

        intTree3.remove(2);
        expect(intTree3.getRoot() to_be nullptr);
        expect(intTree3.is_empty() to_be true);
    }


    // contains
    {
        BinarySearchTree<int> intTree;
        intTree.insert(2);
        intTree.insert(1);
        intTree.insert(3);

        expect(intTree.contains(0) to_be false);
        expect(intTree.contains(1) to_be true);
        expect(intTree.contains(2) to_be true);
        expect(intTree.contains(3) to_be true);
        expect(intTree.contains(4) to_be false);
    }

    // find_mind / find_max
    {
        BinarySearchTree<int> intTree;
        intTree.insert(2);
        intTree.insert(1);
        intTree.insert(3);

        expect(intTree.find_max() to_be 3);
        expect(intTree.find_min() to_be 1);


        BinarySearchTree<char> charTree;

        expect(charTree.is_empty() to_be true);
        expect_throw(charTree.find_min(), std::invalid_argument);
        expect_throw(charTree.find_max(), std::invalid_argument);
    }


    // copy constructor
    {
      BinarySearchTree<int> intTree;
      intTree.insert(2);
      intTree.insert(3);
      intTree.insert(1);

      BinarySearchTree<int> intTree2 = intTree;

      assert(intTree2.getRoot() is_not nullptr);
      expect(intTree2.getRoot()->value to_be 2);
      assert(intTree2.getRoot()->right is_not nullptr);
      assert(intTree2.getRoot()->left is_not nullptr);
      expect(intTree2.getRoot()->right->value to_be 3);
      expect(intTree2.getRoot()->left->value to_be 1);
      expect(intTree2.getRoot()->left->left to_be nullptr);
      expect(intTree2.getRoot()->left->right to_be nullptr);
      expect(intTree2.getRoot()->right->right to_be nullptr);
      expect(intTree2.getRoot()->right->left to_be nullptr);

      assert(intTree.getRoot() is_not nullptr);
      assert(intTree.getRoot()->left is_not nullptr);
      assert(intTree.getRoot()->right is_not nullptr);
      expect(intTree.getRoot() is_not intTree2.getRoot());
      expect(intTree.getRoot()->left is_not intTree2.getRoot()->left);
      expect(intTree.getRoot()->right is_not intTree2.getRoot()->right);
    }

    // copy assignment operator
    {
      BinarySearchTree<int> intTree;
      intTree.insert(2);
      intTree.insert(3);
      intTree.insert(1);

      BinarySearchTree<int> intTree2;
      intTree2.insert(1);
      intTree2.insert(3);

      intTree2 = intTree;

      assert(intTree2.getRoot() is_not nullptr);
      expect(intTree2.getRoot()->value to_be 2);
      assert(intTree2.getRoot()->right is_not nullptr);
      assert(intTree2.getRoot()->left is_not nullptr);
      expect(intTree2.getRoot()->right->value to_be 3);
      expect(intTree2.getRoot()->left->value to_be 1);
      expect(intTree2.getRoot()->left->left to_be nullptr);
      expect(intTree2.getRoot()->left->right to_be nullptr);
      expect(intTree2.getRoot()->right->right to_be nullptr);
      expect(intTree2.getRoot()->right->left to_be nullptr);

      assert(intTree.getRoot() is_not nullptr);
      assert(intTree.getRoot()->left is_not nullptr);
      assert(intTree.getRoot()->right is_not nullptr);
      expect(intTree.getRoot() is_not intTree2.getRoot());
      expect(intTree.getRoot()->left is_not intTree2.getRoot()->left);
      expect(intTree.getRoot()->right is_not intTree2.getRoot()->right);
    }


    // print tree
    {
      BinarySearchTree<int> intTree;
      intTree.insert(8);
      intTree.insert(4);
      intTree.insert(2);
      intTree.insert(10);
      /*
      expect tree to look like this
        10
      8
        4
          2
      */
     std::stringstream stream;
     intTree.print_tree(stream);
     expect(stream.str() to_be "  10\n8\n  4\n    2\n");


     BinarySearchTree<int> intTree2;
     intTree2.insert(6);
     intTree2.insert(12);
     intTree2.insert(10);
     intTree2.insert(15);
     intTree2.insert(3);
     intTree2.insert(4);
     intTree2.insert(1);
     intTree2.insert(20);
     /*
     expect tree to look like this
          20
        15
      12
        10
    6
        4
      3
        1
    
     */
     std::stringstream stream2;
     intTree2.print_tree(stream2);
     expect(stream2.str() to_be "      20\n    15\n  12\n    10\n6\n    4\n  3\n    1\n");


     BinarySearchTree<char> charTree;
     charTree.insert('c');
     charTree.insert('a');
     charTree.insert('b');
     charTree.insert('d');
     charTree.insert('e');
     /*
     expect tree to look like this
        e
      d
    c
        b
      a

     */
     std::stringstream stream3;
     charTree.print_tree(stream3);
     expect(stream3.str() to_be "    e\n  d\nc\n    b\n  a\n");
    }


    return 0;
}
