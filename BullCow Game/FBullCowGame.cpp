#include "FBullCowGame.h"

FBullCowGame::FBullCowGame() { reset(); }

void FBullCowGame::reset() { 
	constexpr int32 MAX_TRIES = 8;
	myMaxTries = MAX_TRIES;

	const FString HIDDEN_WORD = "planet";
	myHiddenWord = HIDDEN_WORD;
	myCurrentTry = 1;
	bGameisWon = false;
	return;
}

int32 FBullCowGame::getMaxTries() const { return myMaxTries; }
int32 FBullCowGame::getCurrentTry() const { return myCurrentTry; }
int32 FBullCowGame::getHiddenWordLength() const { return myHiddenWord.length(); }
bool FBullCowGame::isGameWon() const { return bGameisWon; }

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
FBullCowCount FBullCowGame::submitValidGuess(FString guess) {
	myCurrentTry++;
	FBullCowCount bullCowCount;
	// Loop through all letters in the hideen word.
	for (int32 MHWChar = 0; MHWChar < myHiddenWord.length(); MHWChar++) {
		// Compare letters against the guess.
		for (int32 GChar = 0; GChar < myHiddenWord.length(); GChar++) {
			if (guess[GChar] == myHiddenWord[MHWChar]) { // If they're in the same place
				if (MHWChar == GChar) bullCowCount.bulls++;
				else bullCowCount.cows++;
			}
		}
	}
	if (bullCowCount.bulls == getHiddenWordLength()) bGameisWon = true;
	else bGameisWon = false;
	return bullCowCount;
}