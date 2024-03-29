// Bulls_Cows.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include <string>
#include "FBullCowGame.h"

using int32 = int;
using FText = std::string; 
void PrintIntro();
void PlayGame();
bool AskToPlayAgain();
FText GetValidGuess();
FBullCowGame BCGame;// instantiate a new game
void PrintGameSummary();

int main()
{   
	bool bPlayAgain = false;
	do{  
	   PrintIntro();
	   PlayGame(); 
	   bPlayAgain=AskToPlayAgain();
	} while (bPlayAgain);
	return 0;//exit applicaton 
}

//introduction to the game
void PrintIntro() {
	std::cout << "\n\n welcome to bulls and cows " << std::endl;
	std::cout << "can you guess a " << BCGame.GetHiddenWordLength() << " letter isogram for me ?" << std::endl;
	return;
}

void PlayGame()
{   
	BCGame.Reset();

	//loop for number of turns player gets to guess
	 
	int32 MaxTries = BCGame.GetMaxTries();
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)//while loop for checking if player won the game.
	{
		FText Guess = GetValidGuess();
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);//  submit all the valid guess and recieve count

		std::cout << "Number of bulls = " << BullCowCount.bull ;
		std::cout << " . Number of cows = " << BullCowCount.cow << std::endl;

		std::cout << std::endl;
	}
	//summary of the game
	PrintGameSummary();
}

bool AskToPlayAgain()
{
	std::cout << "do you want to play again with same hidden word (yes/no) \n";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'Y' || Response[0] == 'y');
	
	
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Well Done - You Won !\n";
	}
	else
	{
		std::cout << "Bad Luck - You Failed !\n";
	}
}

// enter the guess 
FText GetValidGuess() 
{   
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". enter your guess : ";
		FText Guess = "";
		std::getline(std::cin, Guess);
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "please enter a " << BCGame.GetHiddenWordLength() << " letter isogram " << std::endl;
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "please enter an isogram" << std::endl;
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "please enter all lowercase letters" << std::endl;
			break;
		default:
			return Guess;
		}
		
	} while (Status != EGuessStatus::OK);//keep looping till we get no errors
}