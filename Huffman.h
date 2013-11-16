#pragma once
//Haffman's algorithm

//���������� ����������
#include <iostream>
#include <functional>
//������� � ������������
#include <queue>
//������������ ������(�����)
#include <map>
#include <algorithm>
#include <bitset>
#include "tree.h"


//��������� ��� �������� �������, � ��� �������� � ������
struct Freq_Letter{
	//������
	char ch;
	//�������
	int frequency;
	//��������� ����������� ��� ���������
	Freq_Letter(char ch_ = 'a', int frequency_ = 0): ch(ch_), frequency(frequency_){};
};


bool greaterFreqLet(const Freq_Letter& l1, const Freq_Letter& l2);


//������� ���������� ������������� ������, � ������� ����������
//char - ������, vector<bool> - ��� ������������� � ���� �����
//��������� ����������, ��������� � �������� ��������� string
void  Huffman_get_code(std::string in_file, std::string out_file);

//1 - ������� �����������, 0 - ������
bool writeHuffmancode(std::string file_in, std::string file_out, 
					  std::map<char, std::vector<bool>> code_map, long int count_sym);


//������ � ��������� � ���������� �����
bool Huffman_decode(std::string in_file, std::string out_file);