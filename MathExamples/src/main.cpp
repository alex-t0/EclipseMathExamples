#include "sources/include/Curious.h"
#include "include/CardCollection.h"
#include "sources/include/Cards.h"
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
		auto cleanResults = [=](PokerResult* r1, PokerResult* r2)
		{
			delete r1;
			delete r2;
		};

		auto cardSortFunc = [=](Card a, Card b)
		{
			return (int)a.GetValue() < (int)b.GetValue();
		};

		RoyalFlush rf;
		PokerResult *pr1 = rf.Test(hands1[i]), *pr2 = rf.Test(hands2[i]);

		if (!pr1->success && pr2->success)
		{
			cleanResults(pr1, pr2);
			continue;
		}

		if (pr1->success && !pr2->success)
		{
			cleanResults(pr1, pr2);
			winCount++;
			continue;
		}

		cleanResults(pr1, pr2);

		StraightFlush sf;

		pr1 = sf.Test(hands1[i]);
		pr2 = sf.Test(hands2[i]);

		if (!pr1->success && pr2->success)
		{
			cleanResults(pr1, pr2);
			continue;
		}

		if (pr1->success && !pr2->success)
		{
			cleanResults(pr1, pr2);
			winCount++;
			continue;
		}

		if (pr1->success && pr2->success)
		{
			Hand copyHand1 = hands1[i];
			Hand copyHand2 = hands2[i];

	    	std::sort(copyHand1.begin(), copyHand1.end(), cardSortFunc);
	    	std::sort(copyHand2.begin(), copyHand2.end(), cardSortFunc);

	    	if ((int)copyHand1[4].GetValue() > (int)copyHand2[4].GetValue())
	    	{
	    		winCount++;
	    		cleanResults(pr1, pr2);
	    		continue;
	    	}
	    	else
	    	{
	    		cleanResults(pr1, pr2);
	    		continue;
	    	}
		}

		cleanResults(pr1, pr2);

		FourOfaKind fok;

		pr1 = fok.Test(hands1[i]);
		pr2 = fok.Test(hands2[i]);

		if (!pr1->success && pr2->success)
		{
			cleanResults(pr1, pr2);
			continue;
		}

		if (pr1->success && !pr2->success)
		{
			cleanResults(pr1, pr2);
			winCount++;
			continue;
		}

		if (pr1->success && pr2->success)
		{
			FourOfaKindPokerResult* fokResult1 = static_cast<FourOfaKindPokerResult*>(pr1);
			FourOfaKindPokerResult* fokResult2 = static_cast<FourOfaKindPokerResult*>(pr2);

			if ((int)fokResult1->Four[0].GetValue() > (int)fokResult2->Four[0].GetValue()
				||
				(int)fokResult1->other.GetValue() > (int)fokResult2->other.GetValue())
			{
				cleanResults(pr1, pr2);
				winCount++;
				continue;
			}
			else
			{
				cleanResults(pr1, pr2);
				continue;
			}
		}

		cleanResults(pr1, pr2);

		FullHouse fh;

		pr1 = fh.Test(hands1[i]);
		pr2 = fh.Test(hands2[i]);

		if (!pr1->success && pr2->success)
		{
			cleanResults(pr1, pr2);
			continue;
		}

		if (pr1->success && !pr2->success)
		{
			cleanResults(pr1, pr2);
			winCount++;
			continue;
		}

		if (pr1->success && pr2->success)
		{
			FullHousePokerResult* fhResult1 = static_cast<FullHousePokerResult*>(pr1);
			FullHousePokerResult* fhResult2 = static_cast<FullHousePokerResult*>(pr2);

			if ((int)fhResult1->Three[0].GetValue() > (int)fhResult2->Three[0].GetValue())
			{
				cleanResults(pr1, pr2);
				winCount++;
				continue;
			}
			else
			{
				cleanResults(pr1, pr2);
				continue;
			}

			if ((int)fhResult1->Pair[0].GetValue() > (int)fhResult2->Pair[0].GetValue())
			{
				cleanResults(pr1, pr2);
				winCount++;
				continue;
			}
			else
			{
				cleanResults(pr1, pr2);
				continue;
			}
		}

		cleanResults(pr1, pr2);
		// delete pr1;
		// delete pr2;

		Flush f;

		pr1 = f.Test(hands1[i]);
		pr2 = f.Test(hands2[i]);

		if (!pr1->success && pr2->success)
		{
			cleanResults(pr1, pr2);
			continue;
		}

		if (pr1->success && !pr2->success)
		{
			cleanResults(pr1, pr2);
			winCount++;
			continue;
		}

		if (pr1->success && pr2->success)
		{
			Hand copyHand1 = hands1[i];
			Hand copyHand2 = hands2[i];

			std::sort(copyHand1.begin(), copyHand1.end(), cardSortFunc);
			std::sort(copyHand2.begin(), copyHand2.end(), cardSortFunc);

			if ((int)copyHand1[4].GetValue() > (int)copyHand2[4].GetValue())
			{
				winCount++;
				cleanResults(pr1, pr2);
				continue;
			}
		}

		cleanResults(pr1, pr2);

		Straight s;
		pr1 = s.Test(hands1[i]);
		pr2 = s.Test(hands2[i]);

		if (!pr1->success && pr2->success)
		{
			cleanResults(pr1, pr2);
			continue;
		}

		if (pr1->success && !pr2->success)
		{
			cleanResults(pr1, pr2);
			winCount++;
			continue;
		}

		if (pr1->success && pr2->success)
		{
			Hand copyHand1 = hands1[i];
			Hand copyHand2 = hands2[i];

			std::sort(copyHand1.begin(), copyHand1.end(), cardSortFunc);
			std::sort(copyHand2.begin(), copyHand2.end(), cardSortFunc);

			if ((int)copyHand1[4].GetValue() > (int)copyHand2[4].GetValue())
			{
				winCount++;
				cleanResults(pr1, pr2);
				continue;
			}
			else
			{
				cleanResults(pr1, pr2);
				continue;
			}
		}

		cleanResults(pr1, pr2);

		ThreeOfAKind tok;
		pr1 = tok.Test(hands1[i]);
		pr2 = tok.Test(hands2[i]);

		if (!pr1->success && pr2->success)
		{
			cleanResults(pr1, pr2);
			continue;
		}

		if (pr1->success && !pr2->success)
		{
			cleanResults(pr1, pr2);
			winCount++;
			continue;
		}

		if (pr1->success && pr2->success)
		{
			ThreeOfAKindPokerResult* tokResult1 = static_cast<ThreeOfAKindPokerResult*>(pr1);
			ThreeOfAKindPokerResult* tokResult2 = static_cast<ThreeOfAKindPokerResult*>(pr2);

			if ((int)tokResult1->Three[0].GetValue() > (int)tokResult2->Three[0].GetValue())
			{
				winCount++;
				cleanResults(pr1, pr2);
				continue;
			}
			else
			{
				cleanResults(pr1, pr2);
				continue;
			}
		}

		cleanResults(pr1, pr2);

		TwoPairs tp;

		pr1 = tp.Test(hands1[i]);
		pr2 = tp.Test(hands2[i]);

		if (!pr1->success && pr2->success)
		{
			cleanResults(pr1, pr2);
			continue;
		}

		if (pr1->success && !pr2->success)
		{
			cleanResults(pr1, pr2);
			winCount++;
			continue;
		}

		if (pr1->success && pr2->success)
		{
			TwoPairsPokerResult* tpResult1 = static_cast<TwoPairsPokerResult*>(pr1);
			TwoPairsPokerResult* tpResult2 = static_cast<TwoPairsPokerResult*>(pr2);

			if ((int)tpResult1->FirstPair[0].GetValue() > (int)tpResult2->FirstPair[0].GetValue())
			{
				winCount++;
				cleanResults(pr1, pr2);
				continue;
			}
			else
			{
				cleanResults(pr1, pr2);
				continue;
			}

			if ((int)tpResult1->SecondPair[0].GetValue() > (int)tpResult2->SecondPair[0].GetValue())
			{
				winCount++;
				cleanResults(pr1, pr2);
				continue;
			}
			else
			{
				cleanResults(pr1, pr2);
				continue;
			}

			if ((int)tpResult1->Other.GetValue() > (int)tpResult2->Other.GetValue())
			{
				winCount++;
				cleanResults(pr1, pr2);
				continue;
			}
			else
			{
				cleanResults(pr1, pr2);
				continue;
			}
		}

		cleanResults(pr1, pr2);

		OnePair op;

		pr1 = op.Test(hands1[i]);
		pr2 = op.Test(hands2[i]);

		if (!pr1->success && pr2->success)
		{
			cleanResults(pr1, pr2);
			continue;
		}

		if (pr1->success && !pr2->success)
		{
			cleanResults(pr1, pr2);
			winCount++;
			continue;
		}

		if (pr1->success && pr2->success)
		{
			OnePairPokerResult* opResult1 = static_cast<OnePairPokerResult*>(pr1);
			OnePairPokerResult* opResult2 = static_cast<OnePairPokerResult*>(pr2);

			if ((int)opResult1->Pair[0].GetValue() > (int)opResult2->Pair[0].GetValue())
			{
				winCount++;
				cleanResults(pr1, pr2);
				continue;
			}
			else
			{
				cleanResults(pr1, pr2);
				continue;
			}

			std::sort(opResult1->Others.begin(), opResult1->Others.end(), cardSortFunc);
			std::sort(opResult2->Others.begin(), opResult2->Others.end(), cardSortFunc);

			bool firstWin = false;
			for (unsigned int i = 2; i >= 0; i--)
			{
				if ((int)opResult1->Others[i].GetValue() > (int)opResult2->Others[i].GetValue())
				{
					firstWin = true;
					break;
				}
				else if ((int)opResult1->Others[i].GetValue() == (int)opResult2->Others[i].GetValue())
				{
					continue;
				}
				else
				{
					break;
				}
			}

			if (firstWin == true)
			{
				winCount++;
				cleanResults(pr1, pr2);
				continue;
			}
			else
			{
				cleanResults(pr1, pr2);
				continue;
			}
		}

		cleanResults(pr1, pr2);

		Hand maxValueCopyHand1 = hands1[i];
		Hand maxValueCopyHand2 = hands2[i];

		std::sort(maxValueCopyHand1.begin(), maxValueCopyHand1.end(), cardSortFunc);
		std::sort(maxValueCopyHand2.begin(), maxValueCopyHand2.end(), cardSortFunc);

		bool firstWinByMostValuedCard = false;
		for (unsigned int i = 4; i >= 0; i--)
		{
			if ((int)maxValueCopyHand1[i].GetValue() > (int)maxValueCopyHand2[i].GetValue())
			{
				firstWinByMostValuedCard = true;
				break;
			}
			else if ((int)maxValueCopyHand1[i].GetValue() == (int)maxValueCopyHand2[i].GetValue())
			{
				continue;
			}
			else
			{
				break;
			}
		}

		if (firstWinByMostValuedCard == true)
		{
			winCount++;
			continue;
		}
		else
		{
			continue;
		}
	}

	std::cout << "Win count = " << winCount << std::endl;

	return 0;
}
