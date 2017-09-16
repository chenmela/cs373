#include<iostream>
#include<cstdlib>
#include "TuringMachine.h"

int main(int argc, char** argv) {
	//Make sure command line arguments are valid
	if (argc != 4) {
		std::cout << "Please enter ./chen_p1 <machine_definition_filename> <input_string> <max_number_of_transitions>" << std::endl;
		return 0;
	}

	//Read in filename, input string, and max num transitions

	std::string filename = argv[1];
	std::string inputString = argv[2];
	int maxTransitions = atoi(argv[3]);
	TuringMachine* tm = new TuringMachine();
	tm->readInput(filename, inputString, maxTransitions);
	return 0;
}
