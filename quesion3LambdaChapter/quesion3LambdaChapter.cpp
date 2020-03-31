#include <iostream>
#include <random>
#include <ctime>
#include <vector>



namespace config {
	constexpr int multiplierMin{ 2 };
	constexpr int multiplierMax{ 4 };
	constexpr int maximumWrongAnswers{ 4 };
}

int getRandomNumber(const int &min, const int &max) {
	static std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
	return std::uniform_int_distribution{ min, max }(mt);
}


int getInteger() {
	int x{};
	while (true) {
		std::cout << "> ";
		std::cin >> x;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(32767, '\n');
			std::cout << "Invalid input, please try again.\n";
		}
		else {
			std::cin.ignore(32767, '\n');
			return x;
		}
	}
}

std::vector<int> generateInitialNumbers(int startNumber, int &numbers) {
	std::vector<int> result(numbers);
	for (int i{ 0 }; i < numbers; i++) {
		result[i] = startNumber*startNumber;
		startNumber++;
	}
	std::cout << "I generated " << numbers << " square numbers.\n";
	return result;
}

void generateFinalNumbers(std::vector<int> &initialNumbers, int &randomNumber) {
	for (int i{ 0 }; i < initialNumbers.size(); i++) {
		initialNumbers[i] = initialNumbers[i] * randomNumber;
	}
	std::cout << "I multiplied them by " << randomNumber << '\n';
}




int main() {

	// CONFIG VARIABLES, AND INITIAL CONFIG NUMBERS
	int startNumber{};
	int howMany{};
	int randomNumber{ getRandomNumber(config::multiplierMin, config::multiplierMax) };
	int userGuess{};

	// INPUT REQUEST
	std::cout << "Start number: ";
	startNumber = getInteger();
	std::cout << "How many numbers: ";
	howMany = getInteger();


	// NUMBERS GENERATOR
	std::vector<int> numbers{ generateInitialNumbers(startNumber, howMany) };
	generateFinalNumbers(numbers, randomNumber);
	

	std::cout << "Do you know what each number is?\n";
	while (true) {
		userGuess = getInteger();
		auto numberFound{ std::find_if(numbers.begin(), numbers.end(), [&userGuess](int generatedNumber) {
			                                                           return(userGuess == generatedNumber);
	    }) };
		
		if (numberFound == numbers.end()) {
			std::cout << userGuess << " is wrong. ";
			auto nearestNumber{ std::find_if(numbers.begin(), numbers.end(), [&userGuess](int generatedNumber) {
				return(userGuess - generatedNumber < 4 || generatedNumber - userGuess < 4);
			}) };
			if (nearestNumber != numbers.end()) {
				std::cout << "Try " << *nearestNumber << " next time\n";
			}
			break;
		}
		else {
			numbers.erase(numberFound);
			if (numbers.size() != 0) {
				std::cout << "Nice !" << numbers.size() << " left\n";
			}
			else {
				std::cout << "Nice ! You found all numbers, good job. :) \n";
				break;
			}
		}
	}
	return 0;
}