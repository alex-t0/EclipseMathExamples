/*
 * CardGame.cpp
 *
 *  Created on: Apr 22, 2017
 *      Author: alex-t
 */

#include "include/CardGame.h"
#include "include/Cards.h"

CardGame::CardGame() {
	// TODO Auto-generated constructor stub

}

CardGame::~CardGame() {
	// TODO Auto-generated destructor stub
}

bool CardGame::Play(Hand hand1, Hand hand2)
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
	PokerResult *pr1 = rf.Test(hand1), *pr2 = rf.Test(hand2);

	if (!pr1->success && pr2->success)
	{
		cleanResults(pr1, pr2);
		return false;
	}

	if (pr1->success && !pr2->success)
	{
		cleanResults(pr1, pr2);
		return true;
	}

	cleanResults(pr1, pr2);

	StraightFlush sf;

	pr1 = sf.Test(hand1);
	pr2 = sf.Test(hand2);

	if (!pr1->success && pr2->success)
	{
		cleanResults(pr1, pr2);
		return false;
	}

	if (pr1->success && !pr2->success)
	{
		cleanResults(pr1, pr2);
		return true;
	}

	if (pr1->success && pr2->success)
	{
		Hand copyHand1 = hand1;
		Hand copyHand2 = hand2;

		std::sort(copyHand1.begin(), copyHand1.end(), cardSortFunc);
		std::sort(copyHand2.begin(), copyHand2.end(), cardSortFunc);

		if ((int)copyHand1[4].GetValue() > (int)copyHand2[4].GetValue())
		{
			cleanResults(pr1, pr2);
			return true;
		}
		else
		{
			cleanResults(pr1, pr2);
			return false;
		}
	}

	cleanResults(pr1, pr2);

	FourOfaKind fok;

	pr1 = fok.Test(hand1);
	pr2 = fok.Test(hand2);

	if (!pr1->success && pr2->success)
	{
		cleanResults(pr1, pr2);
		return false;
	}

	if (pr1->success && !pr2->success)
	{
		cleanResults(pr1, pr2);
		return true;
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
			return true;
		}
		else
		{
			cleanResults(pr1, pr2);
			return false;
		}
	}

	cleanResults(pr1, pr2);

	FullHouse fh;

	pr1 = fh.Test(hand1);
	pr2 = fh.Test(hand2);

	if (!pr1->success && pr2->success)
	{
		cleanResults(pr1, pr2);
		return false;
	}

	if (pr1->success && !pr2->success)
	{
		cleanResults(pr1, pr2);
		return true;
	}

	if (pr1->success && pr2->success)
	{
		FullHousePokerResult* fhResult1 = static_cast<FullHousePokerResult*>(pr1);
		FullHousePokerResult* fhResult2 = static_cast<FullHousePokerResult*>(pr2);

		if ((int)fhResult1->Three[0].GetValue() > (int)fhResult2->Three[0].GetValue())
		{
			cleanResults(pr1, pr2);
			return true;
		}
		else
		{
			cleanResults(pr1, pr2);
			return false;
		}

		if ((int)fhResult1->Pair[0].GetValue() > (int)fhResult2->Pair[0].GetValue())
		{
			cleanResults(pr1, pr2);
			return true;
		}
		else
		{
			cleanResults(pr1, pr2);
			return false;
		}
	}

	cleanResults(pr1, pr2);
	// delete pr1;
	// delete pr2;

	Flush f;

	pr1 = f.Test(hand1);
	pr2 = f.Test(hand2);

	if (!pr1->success && pr2->success)
	{
		cleanResults(pr1, pr2);
		return false;
	}

	if (pr1->success && !pr2->success)
	{
		cleanResults(pr1, pr2);
		return true;
	}

	if (pr1->success && pr2->success)
	{
		Hand copyHand1 = hand1;
		Hand copyHand2 = hand2;

		std::sort(copyHand1.begin(), copyHand1.end(), cardSortFunc);
		std::sort(copyHand2.begin(), copyHand2.end(), cardSortFunc);

		if ((int)copyHand1[4].GetValue() > (int)copyHand2[4].GetValue())
		{
			cleanResults(pr1, pr2);
			return true;
		}
	}

	cleanResults(pr1, pr2);

	Straight s;
	pr1 = s.Test(hand1);
	pr2 = s.Test(hand2);

	if (!pr1->success && pr2->success)
	{
		cleanResults(pr1, pr2);
		return false;
	}

	if (pr1->success && !pr2->success)
	{
		cleanResults(pr1, pr2);
		return true;
	}

	if (pr1->success && pr2->success)
	{
		Hand copyHand1 = hand1;
		Hand copyHand2 = hand2;

		std::sort(copyHand1.begin(), copyHand1.end(), cardSortFunc);
		std::sort(copyHand2.begin(), copyHand2.end(), cardSortFunc);

		if ((int)copyHand1[4].GetValue() > (int)copyHand2[4].GetValue())
		{
			cleanResults(pr1, pr2);
			return true;
		}
		else
		{
			cleanResults(pr1, pr2);
			return false;
		}
	}

	cleanResults(pr1, pr2);

	ThreeOfAKind tok;
	pr1 = tok.Test(hand1);
	pr2 = tok.Test(hand2);

	if (!pr1->success && pr2->success)
	{
		cleanResults(pr1, pr2);
		return false;
	}

	if (pr1->success && !pr2->success)
	{
		cleanResults(pr1, pr2);
		return true;
	}

	if (pr1->success && pr2->success)
	{
		ThreeOfAKindPokerResult* tokResult1 = static_cast<ThreeOfAKindPokerResult*>(pr1);
		ThreeOfAKindPokerResult* tokResult2 = static_cast<ThreeOfAKindPokerResult*>(pr2);

		if ((int)tokResult1->Three[0].GetValue() > (int)tokResult2->Three[0].GetValue())
		{
			cleanResults(pr1, pr2);
			return true;
		}

		if ((int)tokResult1->Three[0].GetValue() < (int)tokResult2->Three[0].GetValue())
		{
			cleanResults(pr1, pr2);
			return false;
		}

		for (int i = 1; i >=0; i++)
		{
			if ((int)tokResult1->TwoOthers[i].GetValue() > (int)tokResult2->TwoOthers[i].GetValue())
			{
				cleanResults(pr1, pr2);
				return true;
			}

			if ((int)tokResult1->TwoOthers[i].GetValue() < (int)tokResult2->TwoOthers[i].GetValue())
			{
				cleanResults(pr1, pr2);
				return false;
			}
		}
	}

	cleanResults(pr1, pr2);

	TwoPairs tp;

	pr1 = tp.Test(hand1);
	pr2 = tp.Test(hand2);

	if (!pr1->success && pr2->success)
	{
		cleanResults(pr1, pr2);
		return false;
	}

	if (pr1->success && !pr2->success)
	{
		cleanResults(pr1, pr2);
		return true;
	}

	if (pr1->success && pr2->success)
	{
		TwoPairsPokerResult* tpResult1 = static_cast<TwoPairsPokerResult*>(pr1);
		TwoPairsPokerResult* tpResult2 = static_cast<TwoPairsPokerResult*>(pr2);

		if ((int)tpResult1->FirstPair[0].GetValue() > (int)tpResult2->FirstPair[0].GetValue())
		{
			cleanResults(pr1, pr2);
			return true;
		}

		if ((int)tpResult1->FirstPair[0].GetValue() < (int)tpResult2->FirstPair[0].GetValue())
		{
			cleanResults(pr1, pr2);
			return false;
		}

		/*else
		{
			cleanResults(pr1, pr2);
			return false;
		}*/

		if ((int)tpResult1->SecondPair[0].GetValue() > (int)tpResult2->SecondPair[0].GetValue())
		{
			cleanResults(pr1, pr2);
			return true;
		}

		if ((int)tpResult1->SecondPair[0].GetValue() < (int)tpResult2->SecondPair[0].GetValue())
		{
			cleanResults(pr1, pr2);
			return false;
		}

		/*else
		{
			cleanResults(pr1, pr2);
			return false;
		}*/

		if ((int)tpResult1->Other.GetValue() > (int)tpResult2->Other.GetValue())
		{
			cleanResults(pr1, pr2);
			return true;
		}
		else
		{
			cleanResults(pr1, pr2);
			return false;
		}
	}

	cleanResults(pr1, pr2);

	OnePair op;

	pr1 = op.Test(hand1);
	pr2 = op.Test(hand2);

	if (!pr1->success && pr2->success)
	{
		cleanResults(pr1, pr2);
		return false;
	}

	if (pr1->success && !pr2->success)
	{
		cleanResults(pr1, pr2);
		return true;
	}

	if (pr1->success && pr2->success)
	{
		OnePairPokerResult* opResult1 = static_cast<OnePairPokerResult*>(pr1);
		OnePairPokerResult* opResult2 = static_cast<OnePairPokerResult*>(pr2);

		if ((int)opResult1->Pair[0].GetValue() > (int)opResult2->Pair[0].GetValue())
		{
			cleanResults(pr1, pr2);
			return true;
		}

		if ((int)opResult1->Pair[0].GetValue() < (int)opResult2->Pair[0].GetValue())
		{
			cleanResults(pr1, pr2);
			return false;
		}
		/*else
		{
			cleanResults(pr1, pr2);
			return false;
		}*/

		if ((int)opResult1->Pair[0].GetValue() == (int)opResult2->Pair[0].GetValue())
		{
			std::sort(opResult1->Others.begin(), opResult1->Others.end(), cardSortFunc);
			std::sort(opResult2->Others.begin(), opResult2->Others.end(), cardSortFunc);

			bool firstWin = false;
			for (int i = 0; i <= 2; i++)
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
				/*else
				{
					break;
				}*/
			}

			if (firstWin == true)
			{
				cleanResults(pr1, pr2);
				return true;
			}
			else
			{
				cleanResults(pr1, pr2);
				return false;
			}
		}
	}

	cleanResults(pr1, pr2);

	Hand maxValueCopyHand1 = hand1;
	Hand maxValueCopyHand2 = hand2;

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
		return true;
	}
	else
	{
		return false;
	}
}

