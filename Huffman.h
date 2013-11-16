#pragma once
//Haffman's algorithm

//подключаем библиотеки
#include <iostream>
#include <functional>
//очередь с приоритетами
#include <queue>
//ассоциатиный массив(карта)
#include <map>
#include <algorithm>
#include <bitset>
#include "tree.h"


//структура для хранения символа, с его частотой в тексте
struct Freq_Letter{
	//символ
	char ch;
	//частота
	int frequency;
	//определим конструктор для структуры
	Freq_Letter(char ch_ = 'a', int frequency_ = 0): ch(ch_), frequency(frequency_){};
};


bool greaterFreqLet(const Freq_Letter& l1, const Freq_Letter& l2);


//Функция возвращает ассоциативный массив, в котором содержится
//char - символ, vector<bool> - его представление в виде битов
//программа простейшая, принимает в качестве аргумента string
void  Huffman_get_code(std::string in_file, std::string out_file);

//1 - удачное кодирование, 0 - провал
bool writeHuffmancode(std::string file_in, std::string file_out, 
					  std::map<char, std::vector<bool>> code_map, long int count_sym);


//чтение и кодировка в нормальную форму
bool Huffman_decode(std::string in_file, std::string out_file);