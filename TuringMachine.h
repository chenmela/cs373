#ifndef TURING_MACHINE_H
#define TURING_MACHINE_H

#include<iostream>
#include<cstdlib>
#include<vector>
#include<tuple>
#include<string>

class TuringMachine {
	private:
		int startState;
		std::vector<int> statesPassed;
		int currentIndex;
		std::vector<std::tuple<int, std::string, int, std::string, std::string>> transitions;
		std::vector<int> acceptStates;
		std::vector<int> rejectStates;
	public:
		TuringMachine();
		void readInput(std::string filename, std::string inputString, int maxTransitions);
};

#endif
