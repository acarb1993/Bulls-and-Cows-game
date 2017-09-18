#ifndef FBULLCOWGAME_H
#define FBULLCOWGAME_H

#include<string>

using FString = std::string; // The type FString is now an alias for type string.
using int32 = int; // The type int32 is now an alias for type int.

// All values initialized to 0
struct FBullCowCount {
	int32 bulls = 0;
	int32 cows = 0;
};

enum class EGuessStatus {
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase,
};

class FBullCowGame {
public:
	FBullCowGame(); // Constructor

	int32 getMaxTries() const; 
	int32 getCurrentTry() const;
	int getHiddenWordLength() const;
	bool isGameWon() const;
	EGuessStatus checkGuessValidity(FString) const; 

	void reset(); // TODO make a more rich return value.
	FBullCowCount submitValidGuess(FString playerGuess);

private:
	// See constructor for initialization.
	int32 myCurrentTry;
	int32 myMaxTries;
	FString myHiddenWord;
	bool bGameisWon;
};

#endif
