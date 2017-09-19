#include "FBullCowGame.h"

FBullCowGame::FBullCowGame() { reset(); } // Default constructor

int32 FBullCowGame::getCurrentTry() const { return myCurrentTry; }
int32 FBullCowGame::getHiddenWordLength() const { return myHiddenWord.length(); }
bool FBullCowGame::isGameWon() const { return bGameisWon; }

void FBullCowGame::reset() {
	const FString HIDDEN_WORD = generateMyHiddenWord(); // <- See function for map of words.
	myHiddenWord = HIDDEN_WORD;
	myCurrentTry = 1;
	bGameisWon = false;
	return;
}

int32 FBullCowGame::getMaxTries() const {
	TMap <int32, int32> WordLengthToMaxTries { {3, 4}, {4, 7}, {5, 10}, {6, 15}, {7, 19} };
	return WordLengthToMaxTries[myHiddenWord.length()];
}

EGuessStatus FBullCowGame::checkGuessValidity(FString playerGuess) const { 
	if (!isIsogram(playerGuess)) { // If the guess isn't an isogram, return an error.
		return EGuessStatus::Not_Isogram;
	}
	else if (!isLowerCase(playerGuess) ) { // If the guess isn't all lowercase, return an error.
		return EGuessStatus::Not_Lowercase;
	}
	else if (playerGuess.length() != getHiddenWordLength() ) { // If the guess length is wrong, return an error.
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
			if (guess[GChar] == myHiddenWord[MHWChar]) { // If they're in the same place.
				if (MHWChar == GChar) bullCowCount.bulls++;
				else bullCowCount.cows++;
			}
		}
	}
	if (bullCowCount.bulls == getHiddenWordLength()) bGameisWon = true;
	else bGameisWon = false;
	return bullCowCount;
}

bool FBullCowGame::isIsogram(FString word) const {
	if (word.length() <= 1) { return true; }

	TMap<char, bool> letterSeen;
	for (auto letter : word) { // For all letters of the word.
		letter = tolower(letter); // Handle mixed case.
		if (letterSeen[letter]) { // If the letter is in the map.
			return false; // We do NOT have an isogram.
		}
		else letterSeen[letter] = true;
	}
	return true;
}

bool FBullCowGame::isLowerCase(FString word) const {
	if (word.length() == 0) return false;
	for (auto letter : word)
		if (!islower(letter)) return false; // if not lowercase.
	return true;
}

std::string FBullCowGame::generateMyHiddenWord() {
	srand(time(NULL));
	TMap<int32, std::string> myHiddenWordMap{ {1, "planet" }, {2, "planes"}, {3, "plants"} }; // TODO add more words.
	std::string randomWord = myHiddenWordMap[(rand() % 3) + 1];
	return randomWord;
}