#include "Huffman.h"
#include "tree.h"

#include <fstream>



bool greaterFreqLet(const Freq_Letter& l1, const Freq_Letter& l2)
{
	return l1.frequency > l2.frequency;
}

void  Huffman_get_code(std::string in_file, std::string out_file)
{
	//откроем файл на чтение
	std::ifstream infile;
	infile.open(in_file);
	//объ€вл€ем очередь с приоритетом
	std::priority_queue<bi_tree*, std::vector<bi_tree*>, compar> que_freq;
	//объ€вл€ем ассоциативный массив дл€ подсчета частот
	std::map<char, int> freq_map;
	//символьный буфер 
	char bufchar;
	long int count_symb = 0;
	//пишем частоты в ассоциативный массив
	while (infile.get(bufchar))
	{
		//считаем частоты
		count_symb++;
		freq_map[bufchar]++;
	}
	//рабочий буферный итератор
	std::map<char, int>::iterator cur;
	//запишем данные в очередь с приоритетом
	for (cur = freq_map.begin(); cur != freq_map.end(); cur++)
	{
		bi_tree* buf = new bi_tree(cur->second, cur->first);
		que_freq.push(buf);
	}
	//построим кодирующее дерево ’аффмана
	bi_tree* buf = new bi_tree(0, 'a');
	buf = bi_tree::createtree(que_freq);
	
	//построим кодирующую таблицу
	std::vector<std::pair<std::vector<bool>, char>> res;
	res = buf->traverse_tree();
	//ассоциативный массив дл€ хранени€ кодов
	std::map<char, std::vector<bool>> code_map;
	//вектор дл€ буфеного хранени€ алфавита
	std::vector<Freq_Letter> alphabet;
	for (int i = 0; i <res.size(); i++)
	{
		std::cout <<res.at(i).second <<'\t';
		for (int j = 0; j < res.at(i).first.size(); j++)
			std::cout <<res.at(i).first.at(j);
		std::cout<<std::endl;
	}
	//заполним ассоциативный массив дл€ хранени€ кодов
	for (int i = 0; i <res.size(); i++)
	{
		code_map[res.at(i).second] = res.at(i).first;
	}
	writeHuffmancode(in_file, out_file, code_map, count_symb);
	//заполним новый ассоциативный массив
	std::map<std::vector<bool>, char> codes;
	for (int i = 0; i <res.size(); i++)
	{
		codes[res.at(i).first] = res.at(i).second;
	}
}

//перегрузим вывод вектора bool
std::ostream& operator<<(std::ostream& stream, std::vector<bool> vec)
{
	for (int i = 0; i < vec.size(); i++)
		stream <<vec.at(i);
	return stream;
}

//1 - удачное кодирование, 0 - провал
bool writeHuffmancode(std::string file_in, std::string file_out, 
					  std::map<char, std::vector<bool>> code_map, long int count_sym)
{
	//откроем файл на чтение
	std::ifstream in(file_in);
	//откроем файл на запись
	std::ofstream out(file_out);
	//запишем заголовок
	for (std::map<char, std::vector<bool>>::iterator code_iter = code_map.begin();
		code_iter != code_map.end(); code_iter++)
	{
		out <<code_iter->second <<' ' <<code_iter->first <<' ';
	}
	//разделитель заголовка (карты дл€ дешифровки) и кодированных байтов
	//информации и передать информацию о количестве байт
	out <<'|'; out <<count_sym <<' ';
	//далее уже будет писатьс€ кодированный текст
	//рабоча€ переменна€, понадобитс€ нам при записи
	char buf = 0;
	unsigned char pos = 128;
	//читаем в нее
	char ch_in;
	while (in.get(ch_in))
	{
		std::vector<bool> code = code_map.at(ch_in);
		for (int i = 0; i <code.size(); i++)
		{
			if (code.at(i) == 1)
			{
				if (pos != 0)
				{
					buf = buf | pos;
					pos >>= 1;
				}
				else
				{
					pos = 128;
					if (buf == 26)
						buf = 1;
					out <<buf;
					buf = 0;
					buf = buf | pos;
					pos >>= 1;
				}
			}
			else
			{
				if (pos != 0)
				{
					buf = buf | 0;
					pos >>= 1;
				}
				else
				{
					pos = 128;
					if (buf == 26)
						buf = 1;
					out <<buf;
					buf = 0;
					buf = buf | 0;
					pos >>= 1;
				}
			}
		}
	}
	in.close(); out.close();
	return 0;
}

//чтение и кодировка в нормальную форму
bool Huffman_decode(std::string in_file, std::string out_file)
{
	//откроем файл на чтение (файл, в котором хран€тс€ закодированные данные)
	std::ifstream infile(in_file);
	//откроем файл на запись (файл, который будет иметь нормальный дл€ нас вид)
	std::ofstream outfile(out_file);
	//читаем заголовок файла
	char sym;
	infile.get(sym);
	//карта дл€ хранени€ векторов
	std::map<std::vector<bool>, char> code_map;
	std::vector<bool> codes;
	bool coders = true;
	while (sym !='|')
	{
		if (sym == '1')
		{
			codes.push_back(1);
		}
		else if (sym == '0')
		{
			codes.push_back(0);
		}
		else
		{
			//читаем ненужные пробелы
			infile.get(sym);
			code_map[codes] = sym;
			codes.clear();
			//читаем пробелы
			infile.get(sym);
		}
		infile.get(sym);
	}
	//прочтем сколько всего байт информации хранитс€ в файле
	long int count_sym;
	infile >>count_sym; infile.get(sym);
	//вектор дл€ хранени€ кода символа
	std::vector<bool> code;
	//буферна€ переменна€ дл€ хранени€ символа
//	char sym;
	//читаем пока есть символы в файле
	int j = 0; //счетчик прочитанных байт
	while (infile.get(sym))
	{
		if (sym == 1)
			sym = 26;
		//позици€ чтени€ бита
		unsigned char pos = 128; //pos = 0x1000000
		//разбираем байт символа
		for (int i = 0; i < 8; i++)
		{
			bool timesbit;
			//читаем бит символа
			if (sym >= 0)
				timesbit = sym & pos;
			else
			{
				unsigned char bu = 256 + (int)sym;
				timesbit = (bu) & pos;
			}
			pos >>= 1;
			//пишем бит символа в вектор
			code.push_back(timesbit);
			//проверим есть ли данна€ комбинации бит из вектора в карте
			std::map<std::vector<bool>, char>::iterator code_iter = 
				code_map.find(code);
			if (code_iter != code_map.end())
			{
				outfile <<code_iter->second;
				/*std::cout <<code_iter->second;*/
				j++;
				if (j >= count_sym)
				{
					infile.close(); outfile.close();
					return true;
				}
				code.clear();
			}
			if (code.size() > 64)
			{
				infile.close();
				outfile.close();
			//	throw("Epic fail!");
				std::cout <<"Epic fail\a\n";
				return false;
			}
		}
	}
	infile.close(); outfile.close();
	return true;
}

