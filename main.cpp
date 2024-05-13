#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <string>

//Instructons
enum Ins {
	ADD,
	DUMP,
	EXIT,
};

//Memory
int constexpr KMemLength = 100;
int8_t Memory[KMemLength];
int MemIndex = 0;

//Registers
namespace registers {
	int A;
	int B;
	int C;
	int I;
}


int main(int argc, char** argv)
{
	if (argc < 2) {
		std::cerr << "Usage: " << argv[0] << "<File_Name>" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	std::ifstream input_file(argv[1]);
	if (!input_file.is_open()) {
		std::cerr << "Couldn't find the file :( " << std::endl;
		std::exit(EXIT_FAILURE);
	}

	for (std::string line; std::getline(input_file, line);) {
		if (line == "ADD") {
			Memory[MemIndex++] = ADD;
		}
		else if (line == "DUMP") {
			Memory[MemIndex++] = DUMP;
		}
		else try {
			Memory[MemIndex++] = int8_t(std::stoi(line));
		}
		catch (...) {}
	}

	if (MemIndex == 0) {
		std::cerr << "Memory is empty" << std::endl;
		std::exit(EXIT_FAILURE);

	}

	for (int index = 0; index < MemIndex; ++index) {
		//Fetch
		registers::I = Memory[index];
		//Decode
		if (registers::I == ADD) {
			//Execute
			registers::A = Memory[++index];
			registers::B = Memory[++index];
			registers::C = registers::A + registers::B;
		}
		//Decode
		else if (registers::I == DUMP) {
			//Execute
			std::cout << "Memory Usage: " << MemIndex << "B" << std::endl;
			std::cout << "Registers: " << std::endl;
			std::cout << "\tA:" << registers::A << std::endl;
			std::cout << "\tB:" << registers::B << std::endl;
			std::cout << "\tC:" << registers::C << std::endl;
			std::cout << "\tI:";
			switch (registers::I) {
			case ADD:
				std::cout << "ADD" << std::endl;
				break;
			case DUMP:
				std::cout << "DUMP" << std::endl;
				break;
			case EXIT:
				std::cout << "EXIT" << std::endl;
				break;
			}

		}
		//Decode
		else if (registers::I == EXIT) {
			//Execute
			std::cout << "Shutting Down!" << std::endl;
			std::exit(EXIT_SUCCESS);
		}
		else {
			std::cout << "Illegal Instruction." << std::endl;
			std::exit(EXIT_FAILURE);
		}
	}

}
