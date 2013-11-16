#include "tree.h"


//конструктор узла дерева
bi_tree::bi_tree(long int x = 0, char sym_ = '!')
{
	this->item  = x;
	this->lchild = nullptr;
	this->rchild = nullptr;
	this->parent = nullptr;
	this->sym = sym_;
}

//деструктор узла


//возращаем значение item
long int bi_tree::get_item() const
{
	return this->item;
}


//создаем дерево для частот
bi_tree* bi_tree::createtree(std::priority_queue<bi_tree*, std::vector<bi_tree*>, compar> que_freq)
{
	//построение дерева
	while (que_freq.size() > 1)
	{
		//берем самый маленький элемент
		bi_tree* buf1 = que_freq.top();
		//убираем элемент из очереди
		que_freq.pop();
		//повторяем операцию
		bi_tree* buf2 = que_freq.top();
		que_freq.pop();

		//создаем новый узел
		long int sum = buf1->item + buf2->item;
		bi_tree* sum_node  = new bi_tree(sum);

		//продолжим пути
		sum_node->lchild = buf1;
		buf1->parent = sum_node;
		sum_node->rchild = buf2;
		buf2->parent = sum_node;
		que_freq.push(sum_node);
	}
	return que_freq.top();
}

//обойдем дерево и вернем результат
std::vector<std::pair<std::vector<bool>,char>> bi_tree::traverse_tree()
{
	//обход дерево, строим коды хаффмана (влево 1, вправо 0)
	std::vector<std::pair<std::vector<bool>,char>> result;
	//переменная-помощник для обхода дерева
	std::vector<bool> bufer;
	//начальное положение
	bi_tree* node = this;
	//рабочая булевская переменная, необходима для выяснения
	//необходимо ли добавить еще один элемент в резузльтирующий вектор
	bool resize = true;
	//количество переменных в результируем векторе
	int count = 0;
	//проверка куда идем
	bool left;
	//обходим дерево
	//дерево обходим слева направо
	//влево пишем 1, вправо 0
	while (node != nullptr)
	{
		//проверяем левый узел, если он существует, то идем по нему
		if (node->lchild != nullptr) {
			//проверим необходимо ли добавить новый элемент
			if (resize) {
				//увеличиваем результирующий вектор на 1
				count++;
				//обнуляем контроллер добавления
				resize = false;
				result.resize(count);
				//присвоим начальное значение в вектор из буфера
				result[count - 1].first = bufer; 
			}
			result[count - 1].first.push_back(0);
			bufer.push_back(0);
			node = node->lchild;
			result[count - 1].second = node->sym;
			left = true;
		} else if (node->rchild){	//идем вправо
			//проверим необходимо ли добавить новый элемент
			if (resize) {
				//увеличиваем результирующий вектор на 1
				count++;
				//обнуляем контроллер добавления
				resize = false;
				result.resize(count);
				//присвоим начальное значение в вектор из буфера
				result[count - 1].first = bufer; 
			}
			result[count - 1].first.push_back(1);
			bufer.push_back(1);
			node = node->rchild;
			result[count - 1].second = node->sym;
			left = false;
		} else { //если некуда идти, то обнуляем узел, в котором находимся
			bi_tree* buf = node; //сохраним значение в буфер
			node = node->parent; //вернемся в родительский узел
			
			delete buf;		 //исходный узел занулим, чтоб вновь там не очутиться
			//убьем того ребенка, в котором уже были
			if (node == nullptr)
				break;
			if (left && (node->lchild != nullptr))
				node->lchild = nullptr;
			else
			{
				node->rchild = nullptr;
				left = true;
			}
			resize = true;		 //контроллер обновления 
			//уменьшаем число значений переменных в буфере на 1
			//это необходимо для избежания лишних кодов
			if (bufer.size() > 0)
				bufer.pop_back();
		}
	}
	return result;
}