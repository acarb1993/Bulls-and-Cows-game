#ifndef FBULLCOWGAME_H
#define FBULLCOWGAME_H

#include<string>
#include <map>
#include <random>
#include <ctime>

#define TMap std::map // Copying the standard from unreal engine

using FString = std::string; // The type FString is now an alias for type string, to make unreal friendly.
using int32 = int; // The type int32 is now an alias for type int, to make unreal friendly.

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
	int32 getHiddenWordLength() const;

	bool isGameWon() const;
	EGuessStatus checkGuessValidity(FString) const; 

	void reset();
	FBullCowCount submitValidGuess(FString playerGuess);

private:
	// See constructor for initialization.
	int32 myCurrentTry;
	int32 myMaxTries;
	FString myHiddenWord;
	bool bGameisWon;

	bool isIsogram(FString word) const;
	bool isLowerCase(FString word) const;
	std::string generateMyHiddenWord();
};

#endif
