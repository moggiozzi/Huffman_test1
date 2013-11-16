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
	//�����������
	bi_tree(long int x, char sym_);
	//����������
//	~bi_tree();
	//������� �������� ������ �� �������� ������� �� �����������
	static bi_tree* createtree(std::priority_queue<bi_tree*, std::vector<bi_tree*>, compar> que_freq);
//	friend class compar;
	long int get_item() const;
	//����� ������
	std::vector<std::pair<std::vector<bool>,char>> bi_tree::traverse_tree();
	
//����������
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
//����� ��������, ����������� ��� ��������� ������, ����������� � ������� � �����������

class compar
{
public:
	bool operator() ( const bi_tree* l1, const bi_tree* l2 )
	{
		return l1->get_item() > l2->get_item();
	}
};
