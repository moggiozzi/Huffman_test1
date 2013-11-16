#include "tree.h"


//����������� ���� ������
bi_tree::bi_tree(long int x = 0, char sym_ = '!')
{
	this->item  = x;
	this->lchild = nullptr;
	this->rchild = nullptr;
	this->parent = nullptr;
	this->sym = sym_;
}

//���������� ����


//��������� �������� item
long int bi_tree::get_item() const
{
	return this->item;
}


//������� ������ ��� ������
bi_tree* bi_tree::createtree(std::priority_queue<bi_tree*, std::vector<bi_tree*>, compar> que_freq)
{
	//���������� ������
	while (que_freq.size() > 1)
	{
		//����� ����� ��������� �������
		bi_tree* buf1 = que_freq.top();
		//������� ������� �� �������
		que_freq.pop();
		//��������� ��������
		bi_tree* buf2 = que_freq.top();
		que_freq.pop();

		//������� ����� ����
		long int sum = buf1->item + buf2->item;
		bi_tree* sum_node  = new bi_tree(sum);

		//��������� ����
		sum_node->lchild = buf1;
		buf1->parent = sum_node;
		sum_node->rchild = buf2;
		buf2->parent = sum_node;
		que_freq.push(sum_node);
	}
	return que_freq.top();
}

//������� ������ � ������ ���������
std::vector<std::pair<std::vector<bool>,char>> bi_tree::traverse_tree()
{
	//����� ������, ������ ���� �������� (����� 1, ������ 0)
	std::vector<std::pair<std::vector<bool>,char>> result;
	//����������-�������� ��� ������ ������
	std::vector<bool> bufer;
	//��������� ���������
	bi_tree* node = this;
	//������� ��������� ����������, ���������� ��� ���������
	//���������� �� �������� ��� ���� ������� � ��������������� ������
	bool resize = true;
	//���������� ���������� � ������������ �������
	int count = 0;
	//�������� ���� ����
	bool left;
	//������� ������
	//������ ������� ����� �������
	//����� ����� 1, ������ 0
	while (node != nullptr)
	{
		//��������� ����� ����, ���� �� ����������, �� ���� �� ����
		if (node->lchild != nullptr) {
			//�������� ���������� �� �������� ����� �������
			if (resize) {
				//����������� �������������� ������ �� 1
				count++;
				//�������� ���������� ����������
				resize = false;
				result.resize(count);
				//�������� ��������� �������� � ������ �� ������
				result[count - 1].first = bufer; 
			}
			result[count - 1].first.push_back(0);
			bufer.push_back(0);
			node = node->lchild;
			result[count - 1].second = node->sym;
			left = true;
		} else if (node->rchild){	//���� ������
			//�������� ���������� �� �������� ����� �������
			if (resize) {
				//����������� �������������� ������ �� 1
				count++;
				//�������� ���������� ����������
				resize = false;
				result.resize(count);
				//�������� ��������� �������� � ������ �� ������
				result[count - 1].first = bufer; 
			}
			result[count - 1].first.push_back(1);
			bufer.push_back(1);
			node = node->rchild;
			result[count - 1].second = node->sym;
			left = false;
		} else { //���� ������ ����, �� �������� ����, � ������� ���������
			bi_tree* buf = node; //�������� �������� � �����
			node = node->parent; //�������� � ������������ ����
			
			delete buf;		 //�������� ���� �������, ���� ����� ��� �� ���������
			//����� ���� �������, � ������� ��� ����
			if (node == nullptr)
				break;
			if (left && (node->lchild != nullptr))
				node->lchild = nullptr;
			else
			{
				node->rchild = nullptr;
				left = true;
			}
			resize = true;		 //���������� ���������� 
			//��������� ����� �������� ���������� � ������ �� 1
			//��� ���������� ��� ��������� ������ �����
			if (bufer.size() > 0)
				bufer.pop_back();
		}
	}
	return result;
}