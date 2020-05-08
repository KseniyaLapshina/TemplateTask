#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <functional>
#include <Windows.h>
#include <string>

template <typename T>
class binary_tree
{
private:
	typedef struct node {
		T value;
		node* left_child = nullptr;
		node* right_child = nullptr;
		node(T);
	} node;
	node* root_ = nullptr;
public:
	binary_tree();
	binary_tree(std::vector<T>);
	~binary_tree();
	
	bool insert(T);
	bool remove(T);

	int height();
	
	std::vector<T> values();
	std::vector<T> leaves();
	
	bool search(T);

	operator std::string();
};

template <typename T>
binary_tree<T>::node::node(T value) : value(value) {};


template <typename T>
binary_tree<T>::binary_tree() {}

template <typename T>
binary_tree<T>::binary_tree(std::vector<T> values)
{
	for (auto value : values)
		insert(value);
}

template <typename T>
binary_tree<T>::~binary_tree()
{
	std::function<void(node*)> helper = [&helper](node* current) -> void
	{
		if (current->left_child)
			helper(current->left_child);
		if (current->right_child)
			helper(current->right_child);
		delete current;
	};
	if (root_)
	helper(root_);
}

template <typename T>
bool binary_tree<T>::insert(T value)
{
	node* new_node = new node(value);
	std::function<void(node*)> helper = [&new_node, &helper](node* current) -> void
	{
		if (new_node->value > current->value)
			if (current->right_child)
				helper(current->right_child);
			else
				current->right_child = new_node;
		else
			if (current->left_child)
				helper(current->left_child);
			else
				current->left_child = new_node;
	};
	if (!root_)
	{
		root_ = new_node;
		return true;
	}
	if (search(value))
		return false;
	helper(root_);
	return true;
}

template <typename T>
bool binary_tree<T>::remove(T value)
{
	std::function<node*(node*, int)> helper = [&helper](node* current, int value) -> node*
	{
		if (!current)
			return current; 
		else if (value < current->value)
		{
			current->left_child = helper(current->left_child, value);
			return current;
		}
		else if (value > current->value)
		{
			current->right_child = helper(current->right_child, value);
			return current;
		}
		else
		{
			if (!current->left_child)
			{
				node* temp = current->right_child;
				delete current;
				return temp;
			}
			else if (!current->right_child)
			{
				node* temp = current->left_child;
				delete current;
				return temp;
			}
			else
			{
				std::function<node*(node*)> find_max = [](node* cur) -> node*
				{
					while (cur->right_child)
						cur = cur->right_child;
					return cur;
				};
				node* max_node = find_max(current->left_child);
				current->value = max_node->value;
				current->left_child = helper(current->left_child, max_node->value);
				return current;
			}
		}
	};
	if (!search(value))
		return false;
	helper(root_, value);
	return true;
}

template <typename T>
int binary_tree<T>::height()
{
	std::function<int(node*)> helper = [&helper](node* current) -> int
	{
		int left_height = (current->left_child) ? helper(current->left_child) : 0;
		int right_height = ((current->right_child) ? helper(current->right_child) : 0);
		return 1 + (left_height > right_height ? left_height : right_height);
	};
	if (!root_)
		return 0;
	return helper(root_);
}


template <typename T>
std::vector<T> binary_tree<T>::values()
{
	std::list<T> result_list;
	std::function<void(node*)> helper = [&result_list, &helper](node* current) -> void
	{
		if (current->left_child)
			helper(current->left_child);
		result_list.push_back(current->value);
		if (current->right_child)
			helper(current->right_child);
	};
	if (root_)
		helper(root_);
	std::vector<T> result_vector(std::begin(result_list), std::end(result_list));
	return result_vector;
}


template <typename T>
std::vector<T> binary_tree<T>::leaves()
{
	std::list<T> result_list;
	std::function<void(node*)> helper = [&result_list, &helper](node* current) -> void
	{
		if (current->left_child)
			helper(current->left_child);
		if (current->right_child)
			helper(current->right_child);
		if (!current->left_child && !current->right_child)
			result_list.push_back(current->value);
	};
	if (root_)
		helper(root_);
	std::vector<T> result_vector(std::begin(result_list), std::end(result_list));
	return result_vector;
}

template <typename T>
bool binary_tree<T>::search(T value)
{
	std::function<bool(node*)> helper = [value, &helper](node* current) -> bool
	{
		if (value == current->value) 
			return true;
		if (current->left_child && value < current->value)
			return helper(current->left_child);
		if (current->right_child && value > current->value)
			return helper(current->right_child);
		return false;
	};
	if (!root_)
		return false;
	return helper(root_);
}

template <typename T>
binary_tree<T>::operator std::string()
{
	std::string result;
	std::function<void(node*, int)> print = [&result, &print](node* current, int spaces) -> void
	{
		if (current->left_child)
			print(current->left_child, spaces + 3);
		result += std::string(spaces, ' ') + std::to_string(current->value) + '\n';
		if (current->right_child)
			print(current->right_child, spaces + 3);
	};
	if (!root_)
		return "Empty tree";
	print(root_, 0);
	return result;
}
