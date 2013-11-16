#pragma once
#include <queue>
#include "Huffman.h"
#include <vector>

//class for binary tree

//bool compar(bi_tree* l1, bi_tree* l2);

class compar;

class bi_tree
{
public:
	//конструктор
	bi_tree(long int x, char sym_);
	//деструктор
//	~bi_tree();
	//функция создания дерева из заданной очереди по приоритетам
	static bi_tree* createtree(std::priority_queue<bi_tree*, std::vector<bi_tree*>, compar> que_freq);
//	friend class compar;
	long int get_item() const;
	//обход дерева
	std::vector<std::pair<std::vector<bool>,char>> bi_tree::traverse_tree();
	
//переменные
private:
	long int item;
	char sym;
	bi_tree* parent;
	bi_tree* lchild;
	bi_tree* rchild;
};





//bool compar(bi_tree* l1, bi_tree* l2)
//{
//	return l1->get_item() > l2->get_item();
//}
//класс функтора, необходимый для сравнения частот, понадобится в очереди с приоритетом

class compar
{
public:
	bool operator() ( const bi_tree* l1, const bi_tree* l2 )
	{
		return l1->get_item() > l2->get_item();
	}
};
