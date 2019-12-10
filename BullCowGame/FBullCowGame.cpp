#pragma once

#include "FBullCowGame.h"

#include <iostream>

FBullCowGame::FBullCowGame() {
    Reset();
}

void FBullCowGame::Reset() {
    currentTry = 1;
    maxTries = GetMaxTries();
    hiddenWord = "planet";
}

void FBullCowGame::Reset(int32 currentTry, int32 maxTries, FString hiddenWord) {
    this->currentTry = currentTry;
    this->maxTries = maxTries;
    this->hiddenWord = hiddenWord;
}

bool FBullCowGame::IsGameWon(int32 bulls) const {
    return bulls == GetHiddenWordLength();
}

EGuessStatus FBullCowGame::ValidateGuess(FString guess) {
    if (!IsLowercase(guess)) {
        return EGuessStatus::NOT_LOWERCASE;
    }
    if (!IsIsogram(guess)) { // TODO: This can be removed, we aren't only dealing with isograms anymore.
        return EGuessStatus::NOT_ISOGRAM;
    }
    if (guess.length() != GetHiddenWordLength()) {
        return EGuessStatus::WRONG_LENGTH;
    }
    if (guess.length() == GetHiddenWordLength()) {
        return EGuessStatus::OK;
    }

    return EGuessStatus::UNKNOWN;
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString guess) {
    FBullCowCount bullCowCount;
    int32 hiddenWordLength = GetHiddenWordLength();
    int32 guessLength = guess.length();

    // TODO: Change this from a linear scan to using a TMap.contains()
    for (int32 i = 0; i < hiddenWordLength; i++) {
        if (hiddenWord[i] == guess[i]) {
            bullCowCount.bulls++;
        } else {
            for (int32 j = 0; j < guessLength; j++) {
                if ((i != j) && (hiddenWord[i] == guess[j])) {
                    bullCowCount.cows++;
                }
            }
        }
    }

    currentTry++;
    return bullCowCount;
}

void FBullCowGame::PrintGameSummary(bool isWon) const {
    if (isWon) {
        std::cout << "\nYou won!\n";
    } else {
        std::cout << "\nBad luck!  Maybe next time.\n";
    }
}

int32 FBullCowGame::GetHiddenWordLength() const {
    return hiddenWord.length();
}

// Return if the given word is an isogram
bool FBullCowGame::IsIsogram(FString word) const {
    TMap<char, bool> letterFound;

    for (char letter : word) {
        letter = tolower(letter);
        if (letterFound[letter]) {
            return false;
        } else {
            letterFound[letter] = true;
        }
    }
    return true;
}

// Return if the given word is lowercase
bool FBullCowGame::IsLowercase(FString word) const {
    for (char letter : word) {
        if (!islower(letter)) {
            return false;
        }
    }

    return true;
}

int32 FBullCowGame::GetCurrentTry() const {
    return currentTry;
}

void FBullCowGame::SetCurrentTry(int32 currentTry) {
    this->currentTry = currentTry;
}

int32 FBullCowGame::GetMaxTries() const {
    TMap<int32, int32> wordLengthToMaxTries{ { 3,5 }, { 4,7 }, { 5,10 }, { 6,15 }, {7, 22} };

    return wordLengthToMaxTries[GetHiddenWordLength()];
}

void FBullCowGame::SetMaxTries(int32 maxTries) {
    this->maxTries = maxTries;
}

FString FBullCowGame::GetHiddenWord() const {
    return hiddenWord;
}

void FBullCowGame::SetHiddenWord(FString hiddenWord) {
    this->hiddenWord = hiddenWord;
}
