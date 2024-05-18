#include "file_loader.hh"
#include "memory.hh"
#include <iostream>

//Instructons
enum Ins {
	ADD,
	DUMP,
	EXIT,
};


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
		std::cerr << "Usage: " << argv[0] << " <File_Name> " << std::endl;
		std::exit(EXIT_FAILURE);
	}
	
	Memory memory(100);

	FileLoader input_file(argv[1]);
	for (std::string const& line : input_file.readAll()) {
		if (line == "ADD") {
			*memory.allocate() = ADD;
		}
		else if (line == "DUMP") {
			*memory.allocate() = DUMP;
		}
		else try {
			*memory.allocate() = uint8_t(std::stoi(line));
		}
		catch (...) {}
	}

	if (memory.usage() == 0) {
		std::cerr << "Memory is empty" << std::endl;
		std::exit(EXIT_FAILURE);

	}

	for (int index = 0; index < memory.usage(); ++index) {
		//Fetch
		registers::I = memory.at(index);
		//Decode
		if (registers::I == ADD) {
			//Execute
			registers::A = memory.at(++index);
			registers::B = memory.at(++index);
			registers::C = registers::A + registers::B;
		}
		//Decode
		else if (registers::I == DUMP) {
			//Execute
			auto const flags = std::cout.flags();
			std::hex(std::cout);
			for (int i = 0; i < memory.usage(); ++i) {
				std::cout << int(memory.at(i)) << ' ';
				if ((i + 1) % 4 == 0) {
					std::cout << std::endl;
				}
			}
			std::cout.setf(flags);
			std::cout << std::endl;

			std::cout << "Memory Usage: " << memory.usage() << "B" << std::endl;
			std::cout << "Registers: " << std::endl;
			std::cout << "\tA: " << registers::A << std::endl;
			std::cout << "\tB: " << registers::B << std::endl;
			std::cout << "\tC: " << registers::C << std::endl;
			std::cout << "\tI: " << registers::I << std::endl;

		}
		else if (registers::I == EXIT) {
			std::cout << "shutting down!" << std::endl;
			std::exit(EXIT_SUCCESS);
		}
		else {
			std::cout << "Illegal Instruction." << std::endl;
			std::exit(EXIT_FAILURE);
		}
	}
}
