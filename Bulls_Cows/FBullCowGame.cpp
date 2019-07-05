#include "stdafx.h"
#include "FBullCowGame.h"
#include <map>
#define TMap std::map
using int32 = int;

FBullCowGame::FBullCowGame() {  Reset(); }



int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

bool FBullCowGame::IsGameWon() const { return BGameIsWon; }

int32 FBullCowGame::GetMaxTries() const 
{ 
	TMap<int32, int32>wordlengthTOmaxtry{ {3,4},{4,5},{5,7},{6,8} };
	return wordlengthTOmaxtry[MyHiddenWord.length()];
 }

void FBullCowGame::Reset()
{   
	
	const FString HIDDEN_WORD = "planet"; 
	MyHiddenWord = HIDDEN_WORD;
	BGameIsWon = false; //condition for resetting the gamewon condtion to false 
	MyCurrentTry = 1;
	
	return;
}





EGuessStatus FBullCowGame::CheckGuessValidity(FString guess) const
{
    //if guess is not an isogram
	if (!IsIsogram(guess)) {
		return EGuessStatus::Not_Isogram;
		//return not an isogram
	}
	//if guess is not lowercase
	else if (!IsLowerCase(guess)) {
		//return not an lowercase
		return EGuessStatus::Not_Lowercase;
	}
			//if guess is of wrong length 
	else if (guess.length() != GetHiddenWordLength()) {
		//return wrong length
		return EGuessStatus::Wrong_Length;
	}
	   //otherwise
	else {
		//return ok
		return EGuessStatus::OK;
	}

	  
}



//recieve a valid guess and increment turn and return counts
FBullCowCount FBullCowGame::SubmitValidGuess(FString guess)
{   
    
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length();//assuming same length as guess
	
	//loop through all letters in guess
	for (int32 MHChar = 0; MHChar < WordLength; MHChar++) {
		//compare the letters against the hidden word
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			//if guess letter is same as hidden word 
			if (guess[GChar] == MyHiddenWord[MHChar]) {
				if (MHChar == GChar)//if they at same position
				{

					BullCowCount.bull++;//the increase number of bulls
				}

				else {
					BullCowCount.cow++;  //increase number of cows 
				}

			}
			
		}
	}
	if (BullCowCount.bull == WordLength) {
		BGameIsWon = true;
	}
	else {
		BGameIsWon = false;
	}
		return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString word) const
{   
	if (word.length() <= 1) return true;
	TMap<char, bool> LetterSeen;
	for (auto letter : word)
	{   
		letter = tolower(letter);
		if (LetterSeen[letter])
		{
			return false;
		}
		else
		{
			LetterSeen[letter]=true;
		}
	}
	return true;
}

bool FBullCowGame::IsLowerCase(FString word) const
{
	for (auto letter : word)
	{
		if (!islower(letter))
		{
			return false;
		}
	}
}

