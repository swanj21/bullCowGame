/*
  This is the main class for the Bull Cow game, which handles the following 
    - Printing the introduction
    - Playing the game (main game loop)
    - Calling the FBullCowGame class to get a valid guess
    - Ask the user to play again
*/

#pragma once

#include "FBullCowGame.h"

#include <iostream>
#include <string>

// Making syntax Unreal-friendly
using FText = std::string;

void PrintIntro(int32 maxGuesses);
void PlayGame(int32 MAX_GUESSES);
FText GetValidGuess();
bool AskToPlayAgain();

FBullCowGame BCGame;

int main() {
    const int32 MAX_GUESSES = BCGame.GetMaxTries();
    bool isPlaying = true;

    PrintIntro(MAX_GUESSES);

    while (isPlaying) {
        PlayGame(MAX_GUESSES);
        isPlaying = AskToPlayAgain();
    }
	return 0;
}

/*
  Print the introduction to the game
*/
void PrintIntro(int32 maxGuesses) {
    // TODO: New introduction with a description of what is going on and what needs to be done
    std::cout << "Welcome to Bulls and Cows!\n";
    std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram in time?\n";
}

/*
  Main game loop
*/
void PlayGame(int32 MAX_GUESSES) {
    BCGame.Reset();

    int32 totalGuesses = 0;
    FText guess = "";

    // TODO: Change this main loop to go through each of the words in the letter that the user has to figure out.
    while (totalGuesses < MAX_GUESSES) {
        guess = GetValidGuess();

        FBullCowCount bullCowCount = BCGame.SubmitValidGuess(guess);
        /* TODO: Change this from displaying Bulls and Cows to directly telling the user how many letters are correct
           and in the correct position and correct but in the wrong position. 
        */
        std::cout << "Bulls: " << bullCowCount.bulls << "\nCows: " << bullCowCount.cows << "\n";
            
        // TODO: Don't check if the game is won, check if the word is guessed correctly
        if (BCGame.IsGameWon(bullCowCount.bulls)) {
            // TODO: Print the current guess summary, not the game summary.
            BCGame.PrintGameSummary(true);
            break;
        }

        totalGuesses++;
    }

    if (totalGuesses == MAX_GUESSES) {
        BCGame.PrintGameSummary(false);
    }

    // TODO: Once the game is complete, then print the game summary with the words they got correct and
    //       spaces for the words they got wrong
}

/*
  Get a valid guess from the user
*/ 
FText GetValidGuess() {
    FText guess = "";
    bool isValid = false;

    while (!isValid) {
        std::cout << "\nYou are on guess " << BCGame.GetCurrentTry() << " out of " << BCGame.GetMaxTries() << ".  Make your guess: ";
        std::getline(std::cin, guess);

        EGuessStatus guessStatus = BCGame.ValidateGuess(guess);

        switch (guessStatus) {
            case EGuessStatus::OK:
                isValid = true;
                break;
            case EGuessStatus::NOT_ISOGRAM: // TODO: The words won't be isograms anymore, remove this case 
                std::cout << "Please enter an isogram(a word with no repeating letters)";
                break;
            case EGuessStatus::NOT_LOWERCASE:
                std::cout << "Please enter a word that is all lowercase";
                break;
            case EGuessStatus::WRONG_LENGTH:
                std::cout << "Please enter a word with " << BCGame.GetHiddenWordLength() << " characters";
                break;
            case EGuessStatus::UNKNOWN:
                std::cout << "Unknown error!";
                break;
            default: 
                break;
        }
    }
    return guess;
}

/*
  Ask the user to play again
*/
bool AskToPlayAgain() {
    FText response = "";

    std::cout << "Do you want to play again?(y for yes) ";
    std::getline(std::cin, response);

    return (response[0] == 'y' || response[0] == 'Y');
}