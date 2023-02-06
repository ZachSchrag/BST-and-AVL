all: bst bst_memory_errors avl avl_memory_errors

memory_erros: bst_memory_errors avl_memory_errors

clean: 
	rm -f *.gcov *.gcda *.gcno a.out

bst: clean binary_search_tree.h binary_search_tree_tests.cpp
	g++ -std=c++17 -Wall -Wextra -Weffc++ -pedantic-errors -g --coverage binary_search_tree_tests.cpp && ./a.out && gcov -mr binary_search_tree_tests.cpp

bst_memory_errors: clean binary_search_tree.h binary_search_tree_tests.cpp
	g++ -std=c++17 -Wall -Wextra -Weffc++ -pedantic-errors -g binary_search_tree_tests.cpp && valgrind --leak-check=full ./a.out

avl: clean avl_tree.h avl_tree_tests.cpp
	g++ -std=c++17 -Wall -Wextra -Weffc++ -pedantic-errors -g --coverage avl_tree_tests.cpp && ./a.out && gcov -mr avl_tree_tests.cpp

avl_memory_errors: clean avl_tree.h avl_tree_tests.cpp
	g++ -std=c++17 -Wall -Wextra -Weffc++ -pedantic-errors -g avl_tree_tests.cpp && valgrind --leak-check=full ./a.out
