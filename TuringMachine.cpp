#include "TuringMachine.h"
#include<iostream>
#include<cstdlib>
#include<fstream>
#include<string>
#include<sstream>
#include<tuple>
#include<vector>
#include<iterator>

TuringMachine::TuringMachine() {
	currentIndex = 0;
}

void TuringMachine::readInput(std::string filename, std::string inputString, int maxTransitions) {
	std::ifstream file;
	//Do more extensive checks on file being open?
	file.open(filename);

	if (file.is_open()) {
		std::string line;
		while(std::getline(file, line)) {
			std::istringstream iss(line);

			//Variables pertaining to state lines
			std::string state;
			int stateNum;
			std::string stateType;
					
			//Variables pertaining to transition lines
			std::string transitionWord;
			int currentState;
			//Change these to chars?
			std::string currentSymbol;
			int nextState;
			std::string nextSymbol;
			//Change this to an enum of sorts?
			std::string direction;
			
			//Make a get length function
			//Make getters and setters
			//Figure out if it's a state or transition line by getting num of args in the line
			std::istringstream iss2(line);
			std::vector<std::string> vecOfWords((std::istream_iterator<std::string>(iss2)),
                                 std::istream_iterator<std::string>());
			int numArgs = vecOfWords.size();
			
			std::cout << "num args: " << numArgs << std::endl;
			std::cout << "line:" << line << std::endl;
			//If it's a state line, store data
			if (numArgs == 3) {
				if (!(iss >> state >> stateNum >> stateType)) {
					std::cout << "Invalid values in file." << std::endl;
					return;
				}
				if (stateType == "accept") {
					this->acceptStates.push_back(stateNum);
				}
				else if (stateType == "reject") {
					this->rejectStates.push_back(stateNum);
				}
				//Otherwise, if stateType == "start"
				else {
					std::cout << "hi" << std::endl;
					this->startState = stateNum;
				}
				//Add logic for startType == null?
			}

			//If it's a transition line, store data
			else if (numArgs == 6) {
				std::cout << line << std::endl;
				if (!(iss >> transitionWord >> currentState >> currentSymbol >> nextState >> nextSymbol >> direction)) {
					std::cout << "Invalid values in file." << std::endl;
					return;
				}
				std::tuple<int, std::string, int, std::string, std::string> transition 
					{currentState, currentSymbol, nextState, nextSymbol, direction};
				this->transitions.push_back(transition);
			}

			//If it's not a state or transition line, it's invalid
			else {
				std::cout << "Invalid line in file." << std::endl;
				return;
			}

			//Debug statements
			std::cout << "ACCEPT STATES:" << std::endl;
			for (int i = 0; i < acceptStates.size(); i++) {
				std::cout << i << ":" << acceptStates[i] << ", ";
			}
			std::cout << "\nREJECT STATES: " << std::endl;
			for (int i = 0; i < rejectStates.size(); i++) {
				std::cout << i << ":" << rejectStates[i] <<", ";
			}
			std::cout << "\nStart state: " << this->startState << std::endl;

			//More debug statements
			for (int i = 0; i < transitions.size(); i++) {
				std::cout << "Transition #" << i << ": currentState: " 
					<< std::get<0>(transitions[i]) << ", currentSymbol: "
					<< std::get<1>(transitions[i]) << ", nextState: "
					<< std::get<2>(transitions[i]) << ", nextSymbol: "
					<< std::get<3>(transitions[i]) << ", direction: "
					<< std::get<4>(transitions[i]) << std::endl;
			}
		}
			return;
	}
	else {
		std::cout << "Invalid filename." << std::endl;
		return;
	}
}

/*
class TuringMachine {
	private:
		std::vector<int> statesPassed;
		int currentIndex;
		std::vector<std::tuple<int, int, int, int, int>> transitions;
		std::vector<int> acceptStates;
		std::vector<int> rejectStates;
	public:
		TuringMachine();
		readTransitions();
 */
