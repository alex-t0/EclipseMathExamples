#include "sources/include/Curious.h"
#include "include/CardCollection.h"
#include "sources/include/Cards.h"
#include "sources/include/CardGame.h"
#include "iostream"

using namespace std;

int main()
{
	/*Curious *c = new Curious();
	delete c;
	return 0;*/

	fill_hands1();
	fill_hands2();

	cout << "Hands1 size: " << hands1.size() << endl;
	cout << "Hands2 size: " << hands2.size() << endl;

	int winCount = 0;
	for (int i = 0; i < 1000; i++)
	{
		std::cout << i+1 << ") "  <<"Hand hand1 = { ";
		std::cout << "Card { \"" << hands1[i][0] << "\" }, ";
		std::cout << "Card { \"" << hands1[i][1] << "\" }, ";
		std::cout << "Card { \"" << hands1[i][2] << "\" }, ";
		std::cout << "Card { \"" << hands1[i][3] << "\" }, ";
		std::cout << "Card { \"" << hands1[i][4] << "\" } ";
		std::cout << "}; ";

		std::cout << "Hand hand2 = { ";
		std::cout << "Card { \"" << hands2[i][0] << "\" }, ";
		std::cout << "Card { \"" << hands2[i][1] << "\" }, ";
		std::cout << "Card { \"" << hands2[i][2] << "\" }, ";
		std::cout << "Card { \"" << hands2[i][3] << "\" }, ";
		std::cout << "Card { \"" << hands2[i][4] << "\" } ";
		std::cout << "}; ";

		if (CardGame::Play(hands1[i], hands2[i]))
		{
			winCount++;
			// std::cout << " win!";
		}

		std::cout << std::endl;
	}

	std::cout << "Win count = " << winCount << std::endl;

	return 0;
}
