#include "FBullCowGame.h"

FBullCowGame::FBullCowGame() { reset(); }

void FBullCowGame::reset() { 
	constexpr int32 MAX_TRIES = 8;
	myMaxTries = MAX_TRIES;

	const FString HIDDEN_WORD = "planet";
	myHiddenWord = HIDDEN_WORD;
	myCurrentTry = 1;
	return;
}
int32 FBullCowGame::getMaxTries() const { return myMaxTries; }

int32 FBullCowGame::getCurrentTry() const { return myCurrentTry; }

int FBullCowGame::getHiddenWordLength() const { return myHiddenWord.length(); }

bool FBullCowGame::isGameWon() const { 
	return false; 
}

EGuessStatus FBullCowGame::checkGuessValidity(FString playerGuess) const { 
	if (false) { // If the guess isn't an isogram, return an error
		return EGuessStatus::Not_Isogram;
	}
	else if (false) { // If the guess isn't all lowercase, return an error
		return EGuessStatus::Not_Lowercase;
	}
	else if (playerGuess.length() != getHiddenWordLength() ) { // If the guess length is wrong, return an error
		return EGuessStatus::Wrong_Length;
	}
	else return EGuessStatus::OK; // otherwise, return OK
}

// Recieves a valid guess, increments turn, and returns count.
FBullCowCount FBullCowGame::submitGuess(FString guess) {

	// Increment the turn number.
	myCurrentTry++;
	// Setup a return variable.
	FBullCowCount bullCowCount;
	// Loop through all letters in the guess.
	for (int32 MHWChar = 0; MHWChar < myHiddenWord.length(); MHWChar++) {
		// Compare letters against the hidden word.
		for (int32 GChar = 0; GChar < myHiddenWord.length(); GChar++) {
			if (guess[GChar] == myHiddenWord[MHWChar]) { // If they're in the same place
				if (MHWChar == GChar) bullCowCount.bulls++;
				else bullCowCount.cows++;
			}
		}
	}
	return bullCowCount;
}