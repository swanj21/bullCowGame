/*
  The header file for the BullCowGame class

  This game takes a guess from the user and makes sure it is a valid guess, then determines how many characters 
  are correct and in the correct position(Bull) or correct but in the wrong position(Cow).

  The user has x number of guesses for each word, and if they get it wrong then they are not able to see 
  that specific word at the end.  If they get it right, it is unlocked for viewing once the game is complete.
*/

#pragma once

#include <string>
#include <map>
#define TMap std::map // Making the map Unreal-friendly

// Making syntax Unreal-friendly
using int32 = int;
using FString = std::string;

struct FBullCowCount {
    int32 bulls = 0;
    int32 cows = 0;
};

enum class EGuessStatus {
    NOT_ISOGRAM,
    NOT_LOWERCASE,
    OK,
    WRONG_LENGTH,
    UNKNOWN
};

class FBullCowGame {
public:
    FBullCowGame();

    void Reset();
    void Reset(int32 currentTry, int32 maxTries, FString hiddenWord);
    bool IsGameWon(int32 bulls) const; // TODO: Change this to be IsWordGuessed()
    EGuessStatus ValidateGuess(FString guess);
    FBullCowCount SubmitValidGuess(FString guess);
    void PrintGameSummary(bool isWon) const;

    // TODO: Between the hyphens all need to be implemented
    // ------------------
    void PrintGuessSummary() const;
    // ------------------
        
    int32 GetHiddenWordLength() const;

    int32 GetCurrentTry() const;
    void SetCurrentTry(int32 currentTry);
    int32 GetMaxTries() const;
    void SetMaxTries(int32 maxTries);
    FString GetHiddenWord() const;
    void SetHiddenWord(FString hiddenWord);

private:
    int32 currentTry;
    int32 maxTries;
    FString hiddenWord;

    bool IsIsogram(FString word) const;
    bool IsLowercase(FString word) const;
};