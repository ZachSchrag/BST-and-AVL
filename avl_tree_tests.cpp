#include <iostream>
#include "avl_tree.h"
#include <sstream>

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

    // constructor / is_empty
    {
        AVLTree<int> intTree;
        expect(intTree.is_empty() to_be true);
        expect(intTree.getRoot() to_be nullptr);
    }


    // make_empty
    {
        AVLTree<int> intTree;
        intTree.insert(1);
        intTree.insert(2);
        intTree.insert(0);
        expect(intTree.is_empty() to_be false);
        intTree.make_empty();
        expect(intTree.is_empty() to_be true);
    }


    // insert
    {
        AVLTree<int> intTree;
        intTree.insert(1);
        assert(intTree.getRoot() is_not nullptr);
        expect(intTree.getRoot()->value to_be 1);
        expect(intTree.getRoot()->height to_be 1);

        intTree.insert(2);
        expect(intTree.getRoot()->value to_be 1);
        expect(intTree.getRoot()->height to_be 2);
        assert(intTree.getRoot()->right is_not nullptr);
        expect(intTree.getRoot()->right->value to_be 2);
        expect(intTree.getRoot()->right->height to_be 1);

        // expect single left rotation
        intTree.insert(3);
        assert(intTree.getRoot() is_not nullptr);
        assert(intTree.getRoot()->left is_not nullptr);
        assert(intTree.getRoot()->right is_not nullptr);
        expect(intTree.getRoot()->value to_be 2);
        expect(intTree.getRoot()->height to_be 2);
        expect(intTree.getRoot()->left->value to_be 1);
        expect(intTree.getRoot()->left->height to_be 1);
        expect(intTree.getRoot()->right->value to_be 3);
        expect(intTree.getRoot()->right->height to_be 1);

        // insert to prepare a right rotation
        intTree.insert(0);
        assert(intTree.getRoot() is_not nullptr);
        expect(intTree.getRoot()->value to_be 2);
        expect(intTree.getRoot()->height to_be 3);
        assert(intTree.getRoot()->left is_not nullptr);
        expect(intTree.getRoot()->left->value to_be 1);
        expect(intTree.getRoot()->left->height to_be 2);
        assert(intTree.getRoot()->right is_not nullptr);
        expect(intTree.getRoot()->right->value to_be 3);
        expect(intTree.getRoot()->right->height to_be 1);
        assert(intTree.getRoot()->left->left is_not nullptr);
        expect(intTree.getRoot()->left->left->value to_be 0);
        expect(intTree.getRoot()->left->left->height to_be 1);

        // expect single right rotation 
        intTree.insert(-1);
        assert(intTree.getRoot() is_not nullptr);
        expect(intTree.getRoot()->value to_be 2);
        expect(intTree.getRoot()->height to_be 3);
        assert(intTree.getRoot()->left is_not nullptr);
        expect(intTree.getRoot()->left->value to_be 0);
        expect(intTree.getRoot()->left->height to_be 2);
        assert(intTree.getRoot()->right is_not nullptr);
        expect(intTree.getRoot()->right->value to_be 3);
        expect(intTree.getRoot()->right->height to_be 1);
        assert(intTree.getRoot()->left->left is_not nullptr);
        expect(intTree.getRoot()->left->left->value to_be -1);
        expect(intTree.getRoot()->left->left->height to_be 1);
        assert(intTree.getRoot()->left->right is_not nullptr);
        expect(intTree.getRoot()->left->right->value to_be 1);
        expect(intTree.getRoot()->left->left->height to_be 1);

        // insert to prepare for double left rotation
        intTree.insert(5);
        assert(intTree.getRoot() is_not nullptr);
        expect(intTree.getRoot()->value to_be 2);
        expect(intTree.getRoot()->height to_be 3);
        assert(intTree.getRoot()->left is_not nullptr);
        expect(intTree.getRoot()->left->value to_be 0);
        expect(intTree.getRoot()->left->height to_be 2);
        assert(intTree.getRoot()->right is_not nullptr);
        expect(intTree.getRoot()->right->value to_be 3);
        expect(intTree.getRoot()->right->height to_be 2);
        assert(intTree.getRoot()->left->left is_not nullptr);
        expect(intTree.getRoot()->left->left->value to_be -1);
        expect(intTree.getRoot()->left->left->height to_be 1);
        assert(intTree.getRoot()->left->right is_not nullptr);
        expect(intTree.getRoot()->left->right->value to_be 1);
        expect(intTree.getRoot()->left->right->height to_be 1);
        assert(intTree.getRoot()->right->right is_not nullptr);
        expect(intTree.getRoot()->right->right->value to_be 5);
        expect(intTree.getRoot()->right->right->height to_be 1);

        // insert to open place to cause double left rotation
        intTree.insert(-3);
        assert(intTree.getRoot() is_not nullptr);
        expect(intTree.getRoot()->value to_be 2);
        expect(intTree.getRoot()->height to_be 4);
        assert(intTree.getRoot()->left is_not nullptr);
        expect(intTree.getRoot()->left->value to_be 0);
        expect(intTree.getRoot()->left->height to_be 3);
        assert(intTree.getRoot()->right is_not nullptr);
        expect(intTree.getRoot()->right->value to_be 3);
        expect(intTree.getRoot()->right->height to_be 2);
        assert(intTree.getRoot()->left->left is_not nullptr);
        expect(intTree.getRoot()->left->left->value to_be -1);
        expect(intTree.getRoot()->left->left->height to_be 2);
        assert(intTree.getRoot()->left->right is_not nullptr);
        expect(intTree.getRoot()->left->right->value to_be 1);
        expect(intTree.getRoot()->left->right->height to_be 1);
        assert(intTree.getRoot()->right->right is_not nullptr);
        expect(intTree.getRoot()->right->right->value to_be 5);
        expect(intTree.getRoot()->right->right->height to_be 1);
        assert(intTree.getRoot()->left->left->left is_not nullptr);
        assert(intTree.getRoot()->left->left->left->value to_be -3);
        assert(intTree.getRoot()->left->left->left->height to_be 1);

        // expect double left rotation
        intTree.insert(-2);
        assert(intTree.getRoot() is_not nullptr);
        expect(intTree.getRoot()->value to_be 2);
        expect(intTree.getRoot()->height to_be 4);
        assert(intTree.getRoot()->left is_not nullptr);
        expect(intTree.getRoot()->left->value to_be 0);
        expect(intTree.getRoot()->left->height to_be 3);
        assert(intTree.getRoot()->right is_not nullptr);
        expect(intTree.getRoot()->right->value to_be 3);
        expect(intTree.getRoot()->right->height to_be 2);
        assert(intTree.getRoot()->left->left is_not nullptr);
        expect(intTree.getRoot()->left->left->value to_be -2);
        expect(intTree.getRoot()->left->left->height to_be 2);
        assert(intTree.getRoot()->left->right is_not nullptr);
        expect(intTree.getRoot()->left->right->value to_be 1);
        expect(intTree.getRoot()->left->right->height to_be 1);
        assert(intTree.getRoot()->right->right is_not nullptr);
        expect(intTree.getRoot()->right->right->value to_be 5);
        expect(intTree.getRoot()->right->right->height to_be 1);
        assert(intTree.getRoot()->left->left->left is_not nullptr);
        assert(intTree.getRoot()->left->left->left->value to_be -3);
        assert(intTree.getRoot()->left->left->left->value to_be -3);
        assert(intTree.getRoot()->left->left->left->height to_be 1);
        assert(intTree.getRoot()->left->left->right is_not nullptr);
        assert(intTree.getRoot()->left->left->right->value to_be -1);
        assert(intTree.getRoot()->left->left->right->height to_be 1);

        // expect double right rotation
        intTree.insert(4);
        assert(intTree.getRoot() is_not nullptr);
        expect(intTree.getRoot()->value to_be 2);
        expect(intTree.getRoot()->height to_be 4);
        assert(intTree.getRoot()->left is_not nullptr);
        expect(intTree.getRoot()->left->value to_be 0);
        expect(intTree.getRoot()->left->height to_be 3);
        assert(intTree.getRoot()->right is_not nullptr);
        expect(intTree.getRoot()->right->value to_be 4);
        expect(intTree.getRoot()->right->height to_be 2);
        assert(intTree.getRoot()->left->left is_not nullptr);
        expect(intTree.getRoot()->left->left->value to_be -2);
        expect(intTree.getRoot()->left->left->height to_be 2);
        assert(intTree.getRoot()->left->right is_not nullptr);
        expect(intTree.getRoot()->left->right->value to_be 1);
        expect(intTree.getRoot()->left->right->height to_be 1);
        assert(intTree.getRoot()->right->right is_not nullptr);
        expect(intTree.getRoot()->right->right->value to_be 5);
        expect(intTree.getRoot()->right->right->height to_be 1);
        assert(intTree.getRoot()->left->left->left is_not nullptr);
        assert(intTree.getRoot()->left->left->left->value to_be -3);
        assert(intTree.getRoot()->left->left->left->height to_be 1);
        assert(intTree.getRoot()->left->left->right is_not nullptr);
        assert(intTree.getRoot()->left->left->right->value to_be -1);
        assert(intTree.getRoot()->left->left->right->height to_be 1);
        assert(intTree.getRoot()->right->left is_not nullptr);
        assert(intTree.getRoot()->right->left->value to_be 3);
        assert(intTree.getRoot()->right->left->height to_be 1);
    }


    // remove
    {
        AVLTree<int> intTree;
        intTree.insert(6);
        intTree.insert(5);
        intTree.insert(7);
        intTree.insert(3);
        intTree.insert(8);
        intTree.insert(2);
        intTree.insert(9);
        intTree.insert(1);
        intTree.insert(10);

        // confirm pre condition
        assert(intTree.getRoot() is_not nullptr);
        expect(intTree.getRoot()->value to_be 6);
        expect(intTree.getRoot()->height to_be 4);
        assert(intTree.getRoot()->left is_not nullptr);
        expect(intTree.getRoot()->left->value to_be 3);
        expect(intTree.getRoot()->left->height to_be 3);
        assert(intTree.getRoot()->right is_not nullptr);
        expect(intTree.getRoot()->right->value to_be 8);
        expect(intTree.getRoot()->right->height to_be 3);
        assert(intTree.getRoot()->left->left is_not nullptr);
        expect(intTree.getRoot()->left->left->value to_be 2);
        expect(intTree.getRoot()->left->left->height to_be 2);
        assert(intTree.getRoot()->left->right is_not nullptr);
        expect(intTree.getRoot()->left->right->value to_be 5);
        expect(intTree.getRoot()->left->right->height to_be 1);
        assert(intTree.getRoot()->right->right is_not nullptr);
        expect(intTree.getRoot()->right->right->value to_be 9);
        expect(intTree.getRoot()->right->right->height to_be 2);
        assert(intTree.getRoot()->right->left is_not nullptr);
        assert(intTree.getRoot()->right->left->value to_be 7);
        assert(intTree.getRoot()->right->left->height to_be 1);
        assert(intTree.getRoot()->left->left->left is_not nullptr);
        assert(intTree.getRoot()->left->left->left->value to_be 1);
        assert(intTree.getRoot()->left->left->left->height to_be 1);
        assert(intTree.getRoot()->right->right->right is_not nullptr);
        assert(intTree.getRoot()->right->right->right->value to_be 10);
        assert(intTree.getRoot()->right->right->right->height to_be 1);


        // expect single right rotation
        intTree.remove(5);
        assert(intTree.getRoot() is_not nullptr);
        expect(intTree.getRoot()->value to_be 6);
        expect(intTree.getRoot()->height to_be 4);
        assert(intTree.getRoot()->left is_not nullptr);
        expect(intTree.getRoot()->left->value to_be 2);
        expect(intTree.getRoot()->left->height to_be 2);
        assert(intTree.getRoot()->right is_not nullptr);
        expect(intTree.getRoot()->right->value to_be 8);
        expect(intTree.getRoot()->right->height to_be 3);
        assert(intTree.getRoot()->left->left is_not nullptr);
        expect(intTree.getRoot()->left->left->value to_be 1);
        expect(intTree.getRoot()->left->left->height to_be 1);
        assert(intTree.getRoot()->left->right is_not nullptr);
        expect(intTree.getRoot()->left->right->value to_be 3);
        expect(intTree.getRoot()->left->right->height to_be 1);
        assert(intTree.getRoot()->right->right is_not nullptr);
        expect(intTree.getRoot()->right->right->value to_be 9);
        expect(intTree.getRoot()->right->right->height to_be 2);
        assert(intTree.getRoot()->right->left is_not nullptr);
        assert(intTree.getRoot()->right->left->value to_be 7);
        assert(intTree.getRoot()->right->left->height to_be 1);
        assert(intTree.getRoot()->right->right->right is_not nullptr);
        assert(intTree.getRoot()->right->right->right->value to_be 10);
        assert(intTree.getRoot()->right->right->right->height to_be 1);

        // expect single left rotation
        intTree.remove(7);
        assert(intTree.getRoot() is_not nullptr);
        expect(intTree.getRoot()->value to_be 6);
        expect(intTree.getRoot()->height to_be 3);
        assert(intTree.getRoot()->left is_not nullptr);
        expect(intTree.getRoot()->left->value to_be 2);
        expect(intTree.getRoot()->left->height to_be 2);
        assert(intTree.getRoot()->right is_not nullptr);
        expect(intTree.getRoot()->right->value to_be 9);
        expect(intTree.getRoot()->right->height to_be 2);
        assert(intTree.getRoot()->left->left is_not nullptr);
        expect(intTree.getRoot()->left->left->value to_be 1);
        expect(intTree.getRoot()->left->left->height to_be 1);
        assert(intTree.getRoot()->left->right is_not nullptr);
        expect(intTree.getRoot()->left->right->value to_be 3);
        expect(intTree.getRoot()->left->right->height to_be 1);
        assert(intTree.getRoot()->right->right is_not nullptr);
        expect(intTree.getRoot()->right->right->value to_be 10);
        expect(intTree.getRoot()->right->right->height to_be 1);
        assert(intTree.getRoot()->right->left is_not nullptr);
        assert(intTree.getRoot()->right->left->value to_be 8);
        assert(intTree.getRoot()->right->left->height to_be 1);
    }

    // contains
    {
        AVLTree<int> intTree;
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
        AVLTree<int> intTree;
        intTree.insert(2);
        intTree.insert(1);
        intTree.insert(3);

        expect(intTree.find_max() to_be 3);
        expect(intTree.find_min() to_be 1);


        AVLTree<char> charTree;
        expect(charTree.is_empty() to_be true);
        expect_throw(charTree.find_min(), std::invalid_argument);
        expect_throw(charTree.find_max(), std::invalid_argument);
    }

    // copy constructor / copy assignment operator
    {
      AVLTree<int> intTree;
      intTree.insert(1);
      intTree.insert(2);
      intTree.insert(3);

      AVLTree<int> intTree2 = intTree;

      expect(intTree.getRoot() not_to_be intTree2.getRoot());
      assert(intTree2.getRoot() is_not nullptr);
      assert(intTree2.getRoot() is_not nullptr);
      assert(intTree2.getRoot()->left is_not nullptr);
      assert(intTree2.getRoot()->right is_not nullptr);
      expect(intTree2.getRoot()->value to_be 2);
      expect(intTree2.getRoot()->left->value to_be 1);
      expect(intTree2.getRoot()->right->value to_be 3);

      
      AVLTree<int> intTree3;
      intTree3.insert(1);
      intTree3.insert(2);
      intTree3.insert(3);

      AVLTree<int> intTree4;
      intTree4.insert(1);
      intTree4 = intTree3;

      expect(intTree3.getRoot() not_to_be intTree4.getRoot());
      assert(intTree3.getRoot() is_not nullptr);
      assert(intTree3.getRoot() is_not nullptr);
      assert(intTree3.getRoot()->left is_not nullptr);
      assert(intTree3.getRoot()->right is_not nullptr);
      expect(intTree3.getRoot()->value to_be 2);
      expect(intTree3.getRoot()->left->value to_be 1);
      expect(intTree3.getRoot()->right->value to_be 3);
    }

    // print tree
    {
        AVLTree<int> intTree;
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
        expect(stream.str() to_be "    10\n  8\n4\n  2\n");
    }

    return 0;
}
