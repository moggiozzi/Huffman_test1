#include "Huffman.h"
#include <string>

using std::string;

int main(int argc, string argv[])
{
	std::map<char, std::vector<bool>> res;
	Huffman_get_code(argv[1], argv[2]);
	Huffman_decode(argv[2], "goodnewlol");
	//все сработало отлично, мы просто молодцы
	system("pause");
	return EXIT_SUCCESS;
}