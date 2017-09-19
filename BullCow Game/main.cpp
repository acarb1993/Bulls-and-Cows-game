/* This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all 
user interaction. For game logic, see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string; // The type FText is now an alias for type string.
using int32 = int; // The type int32 is now an alias for type int.

void printIntro();
void playGame();
void printGameSummary();

FText getValidGuess();

bool askToPlayAgain();

FBullCowGame BCGame; // Instantiate a new game, which we re-use across plays

int main() {
	do {
		printIntro();
		playGame();
		printGameSummary();
	} while (askToPlayAgain() );
	return 0;
}

void printIntro() {
	std::cout << "\nWelcome to Bulls and Cows, a fun word game.\n";
	std::cout << "Can you guess the " << BCGame.getHiddenWordLength()
		<< " letter isogram I'm thinking of?\n\n";
}

// Plays a single game to completion.
void playGame() {
	BCGame.reset();
	int32 maxTries = BCGame.getMaxTries();

	// Loop for number of turns asking for guesses.
	while (!BCGame.isGameWon() && (BCGame.getCurrentTry() <= maxTries) ) { 
		FText guess = getValidGuess(); 

		// Submit valid guesss to the game and recieve counts.
		FBullCowCount bullCowCount = BCGame.submitValidGuess(guess);
		std::cout << "Bulls = " << bullCowCount.bulls;
		std::cout << ". Cows = " << bullCowCount.cows << "\n\n";
	}
}

// Loop continually until the user gives a valid guess.
FText getValidGuess() {
	FText guess = "";
	EGuessStatus status = EGuessStatus::Invalid_Status;
	do {
		// Get a guess from the player.
		int32 currentTry = BCGame.getCurrentTry();
		std::cout << "Try " << currentTry << " of " << BCGame.getMaxTries() << ". Enter your guess: ";
		std::getline(std::cin, guess);

		// Check status and give feedback.
		status = BCGame.checkGuessValidity(guess);
		switch (status) {
		case EGuessStatus::Wrong_Length:
			std::cerr << "Please enter a " << BCGame.getHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cerr << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cerr << "Please enter a word in all lowercase.\n\n";
		    break;
		default:
			break;
		}
	} while (status != EGuessStatus::OK); // Keep looping until we get no errors.
	return guess;
}

bool askToPlayAgain() {
	std::cout << "Do you want to play again? ";
	FText response = "";
	std::getline(std::cin, response);

	return (response[0] == 'y' || response[0] == 'Y');
}

void printGameSummary() {
	if (BCGame.isGameWon() ) {
		std::cout << "YOU DID IT! - YOU WON! \\(^ o ^ )/ \n" << std::endl;
	}
	else std::cout << "Better luck next time!\n" << std::endl;
}