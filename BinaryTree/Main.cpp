#include "binary_tree.h"

int main()
{
	binary_tree<int> tree;

	std::cout << std::endl << "Testing insert" << std::endl;
	for (int i = 0; i < 25; i++)
	{
		const int value = rand() % 20 + 1;
		if (tree.insert(value))
			std::cout << value << " inserted" << std::endl;
		else
			std::cout << value << " already in a tree" << std::endl;
	}	

	std::cout << std::endl << "Testing printing" << std::endl;
	std::cout << "Print tree" << std::endl << std::string(tree) << std::endl;

	std::cout << "Testing searches" << std::endl;
	for (int i = 0; i < 10; i++)
	{
		const int value = rand() % 20 + 1;
		if (tree.search(value))
			std::cout << value << " is in a tree" << std::endl;
		else
			std::cout << value << " is not in a tree" << std::endl;
	}

	std::cout << std::endl << "Getting all nodes and printing them out" << std::endl;
	for (auto value : tree.values())
		std::cout << value << " ";
	std::cout << std::endl;

	std::cout << std::endl << "Getting all leaves and printing them out" << std::endl;
	for (auto value : tree.leaves())
		std::cout << value << " ";
	std::cout << std::endl;

	std::cout << std::endl << "Testing removes" << std::endl;
	for (int i = 0; i < 15; i++)
	{
		const int value = rand() % 20 + 1;
		if (tree.remove(value))
			std::cout << value << " is removed" << std::endl;
		else
			std::cout << value << " is not in a tree" << std::endl;
		std::cout << "Print tree" << std::endl << std::string(tree) << std::endl;
	}
}