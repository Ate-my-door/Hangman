#include <iostream>
#include <array>
#include <random>

std::string getRandomWord(std::array<std::string, 64>&);
void displayBoard(const std::array<std::string, 7>&, const std::string&, const std::string&, const std::string&);
char getGuess(const std::string&);
bool playAgain();

int main()
{
	std::array<std::string, 7> hangmanpics
	{
		"  +---+  \n  |   |  \n      |  \n      |  \n      |  \n      |  \n=========\n",
		"  +---+  \n  |   |  \n  O   |  \n      |  \n      |  \n      |  \n=========\n",
		"  +---+  \n  |   |  \n  O   |  \n  |   |  \n      |  \n      |  \n=========\n",
		"  +---+  \n  |   |  \n  O   |  \n /|   |  \n      |  \n      |  \n=========\n",
		"  +---+  \n  |   |  \n  O   |  \n /|\\  |  \n      |  \n      |  \n=========\n",
		"  +---+  \n  |   |  \n  O   |  \n /|\\  |  \n /    |  \n      |  \n=========\n",
		"  +---+  \n  |   |  \n  O   |  \n /|\\  |  \n / \\  |  \n      |  \n=========\n"
	};
	std::array<std::string, 64> words
	{
		"ant",
		"baboon",
		"badger",
		"bat",
		"bear",
		"beaver",
		"camel",
		"cat",
		"clam",
		"cobra",
		"cougar",
		"coyote",
		"crow",
		"deer",
		"dog",
		"donkey",
		"duck",
		"eagle",
		"ferret",
		"fox",
		"frog",
		"goat",
		"goose",
		"hawk",
		"lion",
		"lizard",
		"llama",
		"mole",
		"monkey",
		"moose",
		"mouse",
		"mule",
		"newt",
		"otter",
		"owl",
		"panda",
		"parrot",
		"pigeon",
		"python",
		"rabbit",
		"ram",
		"rat",
		"raven",
		"rhino",
		"salmon",
		"seal",
		"shark",
		"sheep",
		"skunk",
		"sloth",
		"snake",
		"spider",
		"stork",
		"swan",
		"tiger",
		"toad",
		"trout",
		"turkey",
		"turtle",
		"weasel",
		"whale",
		"wolf",
		"wombat",
		"zebra"
	};
	std::string missedLetters{""};
	std::string correctLetters{""};
	std::string alreadyGuessed{""};
	std::string secretWord{getRandomWord(words)};
	bool gameIsDone{false};
	
	std::cout << "H A N G M A N\n";
	
	while (true)
	{
		displayBoard(hangmanpics, missedLetters, correctLetters, secretWord);
		
		// Let the player type in a letter.
		char guess{getGuess(missedLetters + correctLetters)};
		
		if (secretWord.find(guess) != std::string::npos)
		{
			correctLetters.push_back(guess);
			
			// Check if the player has won.
			bool foundAllLetters{true};
			
			for (int i{0}; i < secretWord.size(); i++)
			{
				if (correctLetters.find(secretWord[i]) == std::string::npos)
				{
					foundAllLetters = false;
					break;
				}
			}
			
			if (foundAllLetters)
			{
				std::cout << "Yes! The secret word is \"" << secretWord << "\"! You have won!\n";
				gameIsDone = true;
			}
		}
		else
		{
			missedLetters.push_back(guess);
			
			// Check if player has guessed too many times and lost.
			if (missedLetters.size() == (hangmanpics.size() - 1))
			{
				displayBoard(hangmanpics, missedLetters, correctLetters, secretWord);	
				std::cout << "You have run out of guesses!\nAfter " << missedLetters.size();
				std::cout << " missed guesses and " << correctLetters.size();
				std::cout << " correct guesses, the word was \"" << secretWord << "\".\n";	
				gameIsDone = true;
			}
			
		}
		
		// Ask the player if they want to play again (but only if the game is done).
		if (gameIsDone)
		{
			if (playAgain())
			{
				missedLetters = "";
				correctLetters = "";
				gameIsDone = false;
				secretWord = getRandomWord(words);
			}
			else
			{
				break;
			}
		}
	}
	
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////

std::string getRandomWord(std::array<std::string, 64>& w)
{
	// This function returns a random string from the passed array of strings.
	std::random_device rd;
	std::uniform_int_distribution<int> dist(0, static_cast<int>(w.size()) - 1);
	return (w[dist(rd)]);
}

void displayBoard(const std::array<std::string, 7>& hpics, const std::string& mis, const std::string& cor, const std::string& secr)
{
	std::cout << "\n\n";
	std::cout << hpics[mis.size()] << "\n";
	std::cout << "Missed letters: ";
	
	for (int i{0}; i < mis.size(); i++)
	{
		std::cout << mis[i] << ' ';
	}
		
	std::cout << '\n';
	
	std::string blanks(secr.size(), '_');
	
	for (int i{0}; i < secr.size(); i++)
	{
		if (cor.find(secr[i]) != std::string::npos)
		{
			blanks[i] = secr[i];
		}
	}
	
	for (int i{0}; i < blanks.size(); i++)
	{
		std::cout << blanks[i] << ' ';
	}
	
	std::cout << '\n';
}

char getGuess(const std::string& alreadyguessed)
{
	// Returns the letter the player entered. This function makes sure the player entered a single letter, and not something else.
	std::string s{""};
	static const std::string abc{"abcdefghijklmnopqrstuvwxyz"};
	
	while (true)
	{
		std::cout << "Guess a letter.\n";
		std::cin >> std::ws >> s;
		s[0] = std::tolower(s[0]);
		
		if (s.size() != 1)
		{
			std::cout << "Please enter a single letter.\n";
		}
		else if (alreadyguessed.find(s[0]) != std::string::npos)
		{
			std::cout << "You have already guessed that letter. Choose again.\n";
		}
		else if (abc.find(s[0]) == std::string::npos)
		{
			std::cout << "Please enter a LETTER.\n";
		}
		else
		{
			return s[0];
		}
	}
}

bool playAgain()
{
	// This function returns true if the player wants to play again, otherwise it returns false.
	std::string s;
	
	std::cout << "Do you want to play again? (yes or no)\n";
	std::cin >> std::ws >> s;
	return ((s[0] = tolower(s[0])) == 'y');
}
