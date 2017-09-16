#include"TuringMachine.h"
#include<iostream>
#include<cstdlib>
#include<fstream>
#include<string>
#include<sstream>
#include<tuple>
#include<vector>
#include<iterator>

TuringMachine::TuringMachine() {
	currentIndex = 10000;
}

void TuringMachine::readInput(std::string filename, std::string inputString, int maxTransitions) {
	std::ifstream file;
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
			char currentSymbol;
			int nextState;
			char nextSymbol;
			char direction;
			
			//Make a get length function
			//Make getters and setters
			//Figure out if it's a state or transition line by getting num of args in the line
			std::istringstream iss2(line);
			std::vector<std::string> vecOfWords((std::istream_iterator<std::string>(iss2)),
                                 std::istream_iterator<std::string>());
			int numArgs = vecOfWords.size();
			
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
					this->startState = stateNum;
				}
				//Add logic for startType == null?
			}

			//If it's a transition line, store data
			else if (numArgs == 6) {
				if (!(iss >> transitionWord >> currentState >> currentSymbol >> nextState >> nextSymbol >> direction)) {
					std::cout << "Invalid values in file." << std::endl;
					return;
				}
				std::tuple<int, char, int, char, char> transition 
					{currentState, currentSymbol, nextState, nextSymbol, direction};
				this->transitions.push_back(transition);
			}

			//If it's not a state or transition line, it's invalid
			else {
				std::cout << "Invalid line in file." << std::endl;
				return;
			}

		}
	}
	else {
		std::cout << "Invalid filename." << std::endl;
		return;
	}
	int transitionsExecuted = 0;
	int currentState = startState;

	std::vector<char> inputStringVec(20000+inputString.length());
	//Convert input string to a vector with 10,000 blank spaces before and 10,000 blank spaces after
	for (int i = 0; i < 10000; i++) {
		inputStringVec.at(i) = '_';
	}
	for (int i = 10000; i < (((signed)inputString.length())+10000); i++) {
		inputStringVec.at(i) = inputString[i-10000];
	}
	for (int i = (((signed)inputString.length())+10000); i < (((signed)inputString.length())+20000); i++) {
		inputStringVec.at(i) = '_';
	}
	
	statesPassed.push_back(currentState);
	//As long as the state is not accept or reject state 
	//AND max num of transitions hasn't been reached
	while (transitionsExecuted < maxTransitions && 
			(!(isContainedIn(currentState,acceptStates)) && !(isContainedIn(currentState,rejectStates)))) {
		for (int i = 0; i < (signed)transitions.size(); i++) {
			//Find transition corresponding to current state and current symbol
			if (std::get<0>(transitions[i]) == currentState && 
					std::get<1>(transitions[i]) == inputStringVec.at(this->currentIndex)) {
				//Overwrite current symbol with next symbol
				inputStringVec.at(this->currentIndex) = std::get<3>(transitions[i]);
				//Move direction
				if (std::get<4>(transitions[i]) == 'R') {
					this->currentIndex++;
				}
				else {
					this->currentIndex--;
				}
				currentState = std::get<2>(transitions[i]);
				break;
			}
		}

		//Add to running list of states passed
		this->statesPassed.push_back(currentState);
		transitionsExecuted++;
	}
	
	if (isContainedIn(currentState, acceptStates)) {
		for (int i = 0; i < (signed)statesPassed.size(); i++) {
			//For last state, print "accept" and no arrow
			if (i == (signed)(this->statesPassed.size()-1)) {
				std::cout << statesPassed[i] << " accept" << std::endl;
			}
			//For every other state, print an arrow
			else {
				std::cout << statesPassed[i] << "->";
			}
		}
	}
	else if (isContainedIn(currentState, rejectStates)) {
		for (int i = 0; i < (signed)statesPassed.size(); i++) {
			//For last state, print "reject" and no arrow
			if (i == (signed)(statesPassed.size()-1)) {
				std::cout << statesPassed[i] << " reject" << std::endl;
			}
			//For every other state, print an arrow
			else {
				std::cout << statesPassed[i] << "->";
			}
		}
	}
	//If max transitions has been reached
	else {
		for (int i = 0; i < (signed)statesPassed.size(); i++) {
			//For last state, print "quit" and no arrow
			if (i == (signed)(statesPassed.size()-1)) {
				std::cout << statesPassed[i] << " quit" << std::endl;
			}
			//For every other state, print an arrow
			else {
				std::cout << statesPassed[i] << "->";
			}
		}
	}
	
	return;
}
bool TuringMachine::isContainedIn(int state, std::vector<int> statesVec) {
	for (int i = 0; i < (signed)statesVec.size(); i++) {
		if (statesVec[i] == state) {
			return true;
		}
	}
	return false;
}
