#include "Huffman.h"
#include "tree.h"

#include <fstream>



bool greaterFreqLet(const Freq_Letter& l1, const Freq_Letter& l2)
{
	return l1.frequency > l2.frequency;
}

void  Huffman_get_code(std::string in_file, std::string out_file)
{
	//������� ���� �� ������
	std::ifstream infile;
	infile.open(in_file);
	//��������� ������� � �����������
	std::priority_queue<bi_tree*, std::vector<bi_tree*>, compar> que_freq;
	//��������� ������������� ������ ��� �������� ������
	std::map<char, int> freq_map;
	//���������� ����� 
	char bufchar;
	long int count_symb = 0;
	//����� ������� � ������������� ������
	while (infile.get(bufchar))
	{
		//������� �������
		count_symb++;
		freq_map[bufchar]++;
	}
	//������� �������� ��������
	std::map<char, int>::iterator cur;
	//������� ������ � ������� � �����������
	for (cur = freq_map.begin(); cur != freq_map.end(); cur++)
	{
		bi_tree* buf = new bi_tree(cur->second, cur->first);
		que_freq.push(buf);
	}
	//�������� ���������� ������ ��������
	bi_tree* buf = new bi_tree(0, 'a');
	buf = bi_tree::createtree(que_freq);
	
	//�������� ���������� �������
	std::vector<std::pair<std::vector<bool>, char>> res;
	res = buf->traverse_tree();
	//������������� ������ ��� �������� �����
	std::map<char, std::vector<bool>> code_map;
	//������ ��� �������� �������� ��������
	std::vector<Freq_Letter> alphabet;
	for (int i = 0; i <res.size(); i++)
	{
		std::cout <<res.at(i).second <<'\t';
		for (int j = 0; j < res.at(i).first.size(); j++)
			std::cout <<res.at(i).first.at(j);
		std::cout<<std::endl;
	}
	//�������� ������������� ������ ��� �������� �����
	for (int i = 0; i <res.size(); i++)
	{
		code_map[res.at(i).second] = res.at(i).first;
	}
	writeHuffmancode(in_file, out_file, code_map, count_symb);
	//�������� ����� ������������� ������
	std::map<std::vector<bool>, char> codes;
	for (int i = 0; i <res.size(); i++)
	{
		codes[res.at(i).first] = res.at(i).second;
	}
}

//���������� ����� ������� bool
std::ostream& operator<<(std::ostream& stream, std::vector<bool> vec)
{
	for (int i = 0; i < vec.size(); i++)
		stream <<vec.at(i);
	return stream;
}

//1 - ������� �����������, 0 - ������
bool writeHuffmancode(std::string file_in, std::string file_out, 
					  std::map<char, std::vector<bool>> code_map, long int count_sym)
{
	//������� ���� �� ������
	std::ifstream in(file_in);
	//������� ���� �� ������
	std::ofstream out(file_out);
	//������� ���������
	for (std::map<char, std::vector<bool>>::iterator code_iter = code_map.begin();
		code_iter != code_map.end(); code_iter++)
	{
		out <<code_iter->second <<' ' <<code_iter->first <<' ';
	}
	//����������� ��������� (����� ��� ����������) � ������������ ������
	//���������� � �������� ���������� � ���������� ����
	out <<'|'; out <<count_sym <<' ';
	//����� ��� ����� �������� ������������ �����
	//������� ����������, ����������� ��� ��� ������
	char buf = 0;
	unsigned char pos = 128;
	//������ � ���
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

//������ � ��������� � ���������� �����
bool Huffman_decode(std::string in_file, std::string out_file)
{
	//������� ���� �� ������ (����, � ������� �������� �������������� ������)
	std::ifstream infile(in_file);
	//������� ���� �� ������ (����, ������� ����� ����� ���������� ��� ��� ���)
	std::ofstream outfile(out_file);
	//������ ��������� �����
	char sym;
	infile.get(sym);
	//����� ��� �������� ��������
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
			//������ �������� �������
			infile.get(sym);
			code_map[codes] = sym;
			codes.clear();
			//������ �������
			infile.get(sym);
		}
		infile.get(sym);
	}
	//������� ������� ����� ���� ���������� �������� � �����
	long int count_sym;
	infile >>count_sym; infile.get(sym);
	//������ ��� �������� ���� �������
	std::vector<bool> code;
	//�������� ���������� ��� �������� �������
//	char sym;
	//������ ���� ���� ������� � �����
	int j = 0; //������� ����������� ����
	while (infile.get(sym))
	{
		if (sym == 1)
			sym = 26;
		//������� ������ ����
		unsigned char pos = 128; //pos = 0x1000000
		//��������� ���� �������
		for (int i = 0; i < 8; i++)
		{
			bool timesbit;
			//������ ��� �������
			if (sym >= 0)
				timesbit = sym & pos;
			else
			{
				unsigned char bu = 256 + (int)sym;
				timesbit = (bu) & pos;
			}
			pos >>= 1;
			//����� ��� ������� � ������
			code.push_back(timesbit);
			//�������� ���� �� ������ ���������� ��� �� ������� � �����
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

