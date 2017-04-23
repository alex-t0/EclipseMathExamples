#include <iostream>

#include "include/Catch.h"
#include "sources/include/Cards.h"
#include "sources/include/CardGame.h"


class BaseClass {
    int m = 0;
public:
    void hello() const
    {
        std::cout << "Hello world, this is Base!\n";
    }
};
class DerivedClass : public BaseClass {
public:
	std::vector<Card> v;

    void hello() const {
    	Value s = v[0].GetValue();
        std::cout << "Hello world, this is Derived, card " << (int)s << "!\n";
    }
};

SCENARIO("Cards works fine", "[cards]") {
	GIVEN("Class casting")
	{
		DerivedClass d;
		d.v.push_back(Card{"5H"});

		// BaseClass b = d;
		BaseClass& br = d; // upcast via implicit conversion
	    br.hello();
	    DerivedClass &another_d = static_cast<DerivedClass&>(br); // downcast
	    another_d.hello();

	    ThreeOfAKindPokerResult derived { { Card{"5H"}, Card{"5S"}, Card{"5C"} }, { Card{"QS"}, Card{"TH"} } };
	    PokerResult& base = derived;
	    PokerResult base2 = derived;
	    ThreeOfAKindPokerResult& converted = static_cast<ThreeOfAKindPokerResult&>(base);
	    ThreeOfAKindPokerResult* converted2 = static_cast<ThreeOfAKindPokerResult*>(&base);
	    ThreeOfAKindPokerResult* converted3 = static_cast<ThreeOfAKindPokerResult*>(&base2);

	    Hand hand = { "6D", "6S", "3D", "6H", "6C" };
	    ThreeOfAKind tok;
	    PokerResult* result = tok.Test(hand);
	    // ThreeOfAKindPokerResult& tokResult = static_cast<ThreeOfAKindPokerResult&>(result);
	    // ThreeOfAKindPokerResult& tokResult2 = static_cast<ThreeOfAKindPokerResult&>(ref_result);

	    ThreeOfAKindPokerResult* rtokResult = static_cast<ThreeOfAKindPokerResult*>(result);
	    // ThreeOfAKindPokerResult* rtokResult2 = static_cast<ThreeOfAKindPokerResult*>(&ref_result);
	}

	GIVEN("Royal Flush check")
	{
		RoyalFlush rf_checker;

		Hand rf_hand1 = { "TD", "JD", "QD", "AD", "KD" };
		Hand rf_hand2 = { "QD", "AD", "TD", "JD", "KD" };

		PokerResult* r1 = rf_checker.Test(rf_hand1);
		REQUIRE(r1->success == true);
		PokerResult* r2 = rf_checker.Test(rf_hand2);
		REQUIRE(r2->success == true);

		Hand rf_hand3 = { "TD", "JD", "QD", "AD", "KH" };
		Hand rf_hand4 = { "9D", "AD", "TD", "JD", "KD" };

		PokerResult* r3 = rf_checker.Test(rf_hand3);
		REQUIRE(r3->success == false);
		PokerResult* r4 = rf_checker.Test(rf_hand4);
		REQUIRE(r4->success == false);

		delete r1;
		delete r2;
		delete r3;
		delete r4;
	}

	GIVEN("Straight Flush check")
	{
		StraightFlush sf_checker;

		Hand sf_hand1 = { "6D", "5D", "3D", "4D", "2D" };
		Hand sf_hand2 = { "QH", "JH", "TH", "8H", "9H" };

		PokerResult* r1 = sf_checker.Test(sf_hand1);
		REQUIRE(r1->success);
		PokerResult* r2 = sf_checker.Test(sf_hand2);
		REQUIRE(r2->success);

		Hand sf_hand3 = { "QH", "JH", "TS", "8H", "9H" };
		PokerResult* r3 = sf_checker.Test(sf_hand3);
		REQUIRE(!r3->success);

		delete r1;
		delete r2;
		delete r3;
	}

	GIVEN("Four of a kind poker result")
	{
		FourOfaKind fk_checker;

		Hand fk_hand1 = { "6D", "6S", "3D", "6H", "6C" };
		Hand fk_hand2 = { "AH", "AD", "TH", "AC", "AS" };

		PokerResult* r1 = fk_checker.Test(fk_hand1);
		REQUIRE(r1->success);
		PokerResult* r2 = fk_checker.Test(fk_hand2);
		REQUIRE(r2->success);

		delete r1;
		delete r2;
	}

	GIVEN("Full house")
	{
		FullHouse fh_checker;
		// FourOfaKind fk_checker;

		Hand fh_hand1 = { "6D", "6S", "3D", "3H", "6C" };
		Hand fh_hand2 = { "AH", "AD", "TH", "AC", "AS" };

		PokerResult* pr = fh_checker.Test(fh_hand1);
		REQUIRE(pr->success);
		delete pr;

		pr = fh_checker.Test(fh_hand2);
		REQUIRE(pr->success == false);
		delete pr;
		// REQUIRE(fh_checker.Test(fh_hand2).success);
	}

	GIVEN("Play examples")
	{
		{
			Hand hand1 = { Card{"5H"}, Card{"5C"}, Card{"AC"}, Card{"AS"}, Card{"5S"} };
			Hand hand2 = { Card{"2C"}, Card{"3S"}, Card{"6S"}, Card{"5D"}, Card{"4D"} };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(result);
		}

		{
			Hand hand1 = { Card{"5H"}, Card{"5C"}, Card{"AC"}, Card{"7S"}, Card{"5S"} };
			Hand hand2 = { Card{"2C"}, Card{"3S"}, Card{"6S"}, Card{"5D"}, Card{"4D"} };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(!result);
		}

		{
			Hand hand2 = { Card{"5H"}, Card{"5C"}, Card{"AC"}, Card{"7S"}, Card{"5S"} };
			Hand hand1 = { Card{"2C"}, Card{"3S"}, Card{"6S"}, Card{"5D"}, Card{"4D"} };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(result);
		}

		{
			Hand hand1 = { Card{"5H"}, Card{"5C"}, Card{"6S"}, Card{"7S"}, Card{"KD"} };
			Hand hand2 = { Card{"2C"}, Card{"3S"}, Card{"8S"}, Card{"8D"}, Card{"TD"} };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(!result);
		}

		{
			Hand hand1 = { Card{"5D"}, Card{"8C"}, Card{"9S"}, Card{"JS"}, Card{"AC"} };
			Hand hand2 = { Card{"2C"}, Card{"5C"}, Card{"7D"}, Card{"8S"}, Card{"QH"} };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(result);
		}

		{
			Hand hand1 = { Card{"2D"}, Card{"9C"}, Card{"AS"}, Card{"AH"}, Card{"AC"} };
			Hand hand2 = { Card{"3D"}, Card{"6D"}, Card{"7D"}, Card{"TD"}, Card{"QD"} };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(!result);
		}

		{
			Hand hand1 = { Card{"4D"}, Card{"6S"}, Card{"9H"}, Card{"QH"}, Card{"QC"} };
			Hand hand2 = { Card{"3D"}, Card{"6D"}, Card{"7H"}, Card{"QD"}, Card{"QS"} };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(result);
		}

		{
			Hand hand1 = { Card{"2H"}, Card{"2D"}, Card{"4C"}, Card{"4D"}, Card{"4S"} };
			Hand hand2 = { Card{"3C"}, Card{"3D"}, Card{"3S"}, Card{"9S"}, Card{"9D"} };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(result);
		}

		{
			Hand hand1 = { Card{"5D"}, Card{"JH"}, Card{"AC"}, Card{"5C"}, Card{"9S"} };
			Hand hand2 = { Card{"TS"}, Card{"4C"}, Card{"JD"}, Card{"8C"}, Card{"KS"} };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(result);
		}

		{
			Hand hand1 = { Card{"9C"}, Card{"KD"}, Card{"4H"}, Card{"AD"}, Card{"TD"} };
			Hand hand2 = { Card{"9S"}, Card{"4S"}, Card{"7D"}, Card{"6H"}, Card{"5D"} };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(result);
		}

		{
			Hand hand1 = { Card{"4C"}, Card{"7H"}, Card{"AS"}, Card{"3S"}, Card{"QD"} };
			Hand hand2 = { Card{"9H"}, Card{"3D"}, Card{"8C"}, Card{"2S"}, Card{"KH"} };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(result);
		}

		{
			Hand hand2 = { Card{"4C"}, Card{"7H"}, Card{"AS"}, Card{"3S"}, Card{"QD"} };
			Hand hand1 = { Card{"9H"}, Card{"3D"}, Card{"8C"}, Card{"2S"}, Card{"KH"} };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(!result);
		}

		{
			Hand hand1 = { Card{"4C"}, Card{"7D"}, Card{"AS"}, Card{"3S"}, Card{"QD"} };
			Hand hand2 = { Card{"5H"}, Card{"6H"}, Card{"7H"}, Card{"9H"}, Card{"8H"} };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(!result);
		}

		{
			Hand hand1 = { Card{"2D"}, Card{"7D"}, Card{"AD"}, Card{"JD"}, Card{"QD"} };
			Hand hand2 = { Card{"5H"}, Card{"6H"}, Card{"7H"}, Card{"9H"}, Card{"8H"} };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(!result);
		}

		{
			Hand hand2 = { Card{"2D"}, Card{"7D"}, Card{"AD"}, Card{"JD"}, Card{"QD"} };
			Hand hand1 = { Card{"5H"}, Card{"6H"}, Card{"7H"}, Card{"9H"}, Card{"8H"} };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(result);
		}

		{
			Hand hand1 = { Card{"7D"}, Card{"TS"}, Card{"9S"}, Card{"JD"}, Card{"8C"} };
			Hand hand2 = { Card{"5H"}, Card{"6H"}, Card{"7H"}, Card{"9H"}, Card{"8H"} };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(!result);
		}

		{
			Hand hand2 = { Card{"7D"}, Card{"TS"}, Card{"9S"}, Card{"JD"}, Card{"8C"} };
			Hand hand1 = { Card{"5H"}, Card{"6H"}, Card{"7H"}, Card{"9H"}, Card{"8H"} };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(result);
		}

		{
			Hand hand1 = { Card{"9H"}, Card{"9D"}, Card{"JD"}, Card{"3S"}, Card{"3C"} };
			Hand hand2 = { Card{"AH"}, Card{"6H"}, Card{"7H"}, Card{"4H"}, Card{"AC"} };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(result);
		}
	}

	GIVEN("Real poker")
	{
		{
			// 1
			Hand hand1 = { Card { "8C" }, Card { "TS" }, Card { "KC" }, Card { "9H" }, Card { "4S" } };
			Hand hand2 = { Card { "7D" }, Card { "2S" }, Card { "5D" }, Card { "3S" }, Card { "AC" } };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(!result);
		}

		{
			// 2
			Hand hand1 = { Card { "5C" }, Card { "AD" }, Card { "5D" }, Card { "AC" }, Card { "9C" } };
			Hand hand2 = { Card { "7C" }, Card { "5H" }, Card { "8D" }, Card { "TD" }, Card { "KS" } };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(result);
		}

		{
			// 3
			Hand hand1 = { Card { "3H" }, Card { "7H" }, Card { "6S" }, Card { "KC" }, Card { "JS" } };
			Hand hand2 = { Card { "QH" }, Card { "TD" }, Card { "JC" }, Card { "2D" }, Card { "8S" } };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(result);
		}

		{
			// 4
			Hand hand1 = { Card { "TH" }, Card { "8H" }, Card { "5C" }, Card { "QS" }, Card { "TC" } };
			Hand hand2 = { Card { "9H" }, Card { "4D" }, Card { "JC" }, Card { "KS" }, Card { "JS" } };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(!result);
		}

		{
			// 5
			Hand hand1 = { Card { "7C" }, Card { "5H" }, Card { "KC" }, Card { "QH" }, Card { "JD" } };
			Hand hand2 = { Card { "AS" }, Card { "KH" }, Card { "4C" }, Card { "AD" }, Card { "4S" } };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(!result);
		}

		{
			// 6
			Hand hand1 = { Card { "5H" }, Card { "KS" }, Card { "9C" }, Card { "7D" }, Card { "9H" } };
			Hand hand2 = { Card { "8D" }, Card { "3S" }, Card { "5D" }, Card { "5C" }, Card { "AH" } };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(result);
		}

		{
			// 7
			Hand hand1 = { Card { "6H" }, Card { "4H" }, Card { "5C" }, Card { "3H" }, Card { "2H" } };
			Hand hand2 = { Card { "3S" }, Card { "QH" }, Card { "5S" }, Card { "6S" }, Card { "AS" } };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(result);
		}

		{
			// 8
			Hand hand1 = { Card { "TD" }, Card { "8C" }, Card { "4H" }, Card { "7C" }, Card { "TC" } };
			Hand hand2 = { Card { "KC" }, Card { "4C" }, Card { "3H" }, Card { "7S" }, Card { "KS" } };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(!result);
		}

		{
			// 9
			Hand hand1 = { Card { "7C" }, Card { "9C" }, Card { "6D" }, Card { "KD" }, Card { "3H" } };
			Hand hand2 = { Card { "4C" }, Card { "QS" }, Card { "QC" }, Card { "AC" }, Card { "KH" } };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(!result);
		}

		{
			// 10
			Hand hand1 = { Card { "JC" }, Card { "6S" }, Card { "5H" }, Card { "2H" }, Card { "2D" } };
			Hand hand2 = { Card { "KD" }, Card { "9D" }, Card { "7C" }, Card { "AS" }, Card { "JS" } };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(result);
		}

		{
			// 11
			Hand hand1 = { Card { "AD" }, Card { "QH" }, Card { "TH" }, Card { "9D" }, Card { "8H" } };
			Hand hand2 = { Card { "TS" }, Card { "6D" }, Card { "3S" }, Card { "AS" }, Card { "AC" } };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(!result);
		}

		{
			// 12
			Hand hand1 = { Card { "2H" }, Card { "4S" }, Card { "5C" }, Card { "5S" }, Card { "TC" } };
			Hand hand2 = { Card { "KC" }, Card { "JD" }, Card { "6C" }, Card { "TS" }, Card { "3C" } };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(result);
		}

		{
			// 13
			Hand hand1 = { Card { "QD" }, Card { "AS" }, Card { "6H" }, Card { "JS" }, Card { "2C" } };
			Hand hand2 = { Card { "3D" }, Card { "9H" }, Card { "KC" }, Card { "4H" }, Card { "8S" } };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(result);
		}

		{
			// 14
			Hand hand1 = { Card { "KD" }, Card { "8S" }, Card { "9S" }, Card { "7C" }, Card { "2S" } };
			Hand hand2 = { Card { "3S" }, Card { "6D" }, Card { "6S" }, Card { "4H" }, Card { "KC" } };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(!result);
		}

		{
			// 15
			Hand hand1 = { Card { "3C" }, Card { "8C" }, Card { "2D" }, Card { "7D" }, Card { "4D" } };
			Hand hand2 = { Card { "9S" }, Card { "4S" }, Card { "QH" }, Card { "4H" }, Card { "JD" } };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(!result);
		}

		{
			// 16
			Hand hand1 = { Card { "8C" }, Card { "KC" }, Card { "7S" }, Card { "TC" }, Card { "2D" } };
			Hand hand2 = { Card { "TS" }, Card { "8H" }, Card { "QD" }, Card { "AC" }, Card { "5C" } };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(!result);
		}

		{
			// 17
			Hand hand1 = { Card { "3D" }, Card { "KH" }, Card { "QD" }, Card { "6C" }, Card { "6S" } };
			Hand hand2 = { Card { "AD" }, Card { "AS" }, Card { "8H" }, Card { "2H" }, Card { "QS" } };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(!result);
		}

		{
			// 18
			Hand hand1 = { Card { "6S" }, Card { "8D" }, Card { "4C" }, Card { "8S" }, Card { "6C" } };
			Hand hand2 = { Card { "QH" }, Card { "TC" }, Card { "6D" }, Card { "7D" }, Card { "9D" } };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(result);
		}

		{
			// 19
			Hand hand1 = { Card { "2S" }, Card { "8D" }, Card { "8C" }, Card { "4C" }, Card { "TS" } };
			Hand hand2 = { Card { "9S" }, Card { "9D" }, Card { "9C" }, Card { "AC" }, Card { "3D" } };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(!result);
		}

		{
			// 20
			Hand hand1 = { Card { "3C" }, Card { "QS" }, Card { "2S" }, Card { "4H" }, Card { "JH" } };
			Hand hand2 = { Card { "3D" }, Card { "2D" }, Card { "TD" }, Card { "8S" }, Card { "9H" } };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(result);
		}

		{
			// 405
			Hand hand1 = { Card { "4C" }, Card { "2S" }, Card { "AD" }, Card { "QS" }, Card { "6C" } };
			Hand hand2 = { Card { "9S" }, Card { "QD" }, Card { "TH" }, Card { "QH" }, Card { "5C" } };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(!result);
		}

		{
			// 406
			Hand hand1 = { Card { "8C" }, Card { "AD" }, Card { "QS" }, Card { "2D" }, Card { "2S" } };
			Hand hand2 = { Card { "KC" }, Card { "JD" }, Card { "KS" }, Card { "6C" }, Card { "JC" } };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(!result);
		}

		{
			// 407
			Hand hand1 = { Card { "8D" }, Card { "4D" }, Card { "JS" }, Card { "2H" }, Card { "5D" } };
			Hand hand2 = { Card { "QD" }, Card { "7S" }, Card { "7D" }, Card { "QH" }, Card { "TS" } };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(!result);
		}

		{
			// 408
			Hand hand1 = { Card { "6S" }, Card { "7H" }, Card { "3S" }, Card { "8C" }, Card { "8S" } };
			Hand hand2 = { Card { "9D" }, Card { "QS" }, Card { "8H" }, Card { "6C" }, Card { "9S" } };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(!result);
		}

		{
			// 409
			Hand hand1 = { Card { "4S" }, Card { "TC" }, Card { "2S" }, Card { "5C" }, Card { "QD" } };
			Hand hand2 = { Card { "4D" }, Card { "QS" }, Card { "6D" }, Card { "TH" }, Card { "6S" } };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(!result);
		}

		{
			// 410
			Hand hand1 = { Card { "3S" }, Card { "5C" }, Card { "9D" }, Card { "6H" }, Card { "8D" } };
			Hand hand2 = { Card { "4C" }, Card { "7D" }, Card { "TC" }, Card { "7C" }, Card { "TD" } };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(!result);
		}

		{
			// 411
			Hand hand1 = { Card { "AH" }, Card { "6S" }, Card { "AS" }, Card { "7H" }, Card { "5S" } };
			Hand hand2 = { Card { "KD" }, Card { "3H" }, Card { "5H" }, Card { "AC" }, Card { "4C" } };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(result);
		}

		{
			// 500
			Hand hand1 = { Card { "7S" }, Card { "6D" }, Card { "JC" }, Card { "QD" }, Card { "JH" } };
			Hand hand2 = { Card { "4C" }, Card { "6S" }, Card { "QS" }, Card { "2H" }, Card { "7D" } };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(result);
		}

		{
			// 501
			Hand hand1 = { Card { "8C" }, Card { "TD" }, Card { "JH" }, Card { "KD" }, Card { "2H" } };
			Hand hand2 = { Card { "5C" }, Card { "QS" }, Card { "2C" }, Card { "JS" }, Card { "7S" } };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(result);
		}

		{
			// 502
			Hand hand1 = { Card { "TC" }, Card { "5H" }, Card { "4H" }, Card { "JH" }, Card { "QD" } };
			Hand hand2 = { Card { "3S" }, Card { "5S" }, Card { "5D" }, Card { "8S" }, Card { "KH" } };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(!result);
		}

		{
			// 503
			Hand hand1 = { Card { "KS" }, Card { "KH" }, Card { "7C" }, Card { "2C" }, Card { "5D" } };
			Hand hand2 = { Card { "JH" }, Card { "6S" }, Card { "9C" }, Card { "6D" }, Card { "JC" } };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(!result);
		}

		{
			// 504
			Hand hand1 = { Card { "5H" }, Card { "AH" }, Card { "JD" }, Card { "9C" }, Card { "JS" } };
			Hand hand2 = { Card { "KC" }, Card { "2H" }, Card { "6H" }, Card { "4D" }, Card { "5S" } };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(result);
		}

		{
			// 505
			Hand hand1 = { Card { "AS" }, Card { "3C" }, Card { "TH" }, Card { "QC" }, Card { "6H" } };
			Hand hand2 = { Card { "9C" }, Card { "8S" }, Card { "8C" }, Card { "TD" }, Card { "7C" } };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(!result);
		}

		{
			// 561
			Hand hand1 = { Card { "AS" }, Card { "4C" }, Card { "5H" }, Card { "4D" }, Card { "6S" } };
			Hand hand2 = { Card { "KD" }, Card { "JC" }, Card { "3C" }, Card { "6H" }, Card { "2D" } };
			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(result);
		}

		{
			// 577
			Hand hand1 = { Card { "5H" }, Card { "2D" }, Card { "TC" }, Card { "AH" }, Card { "KS" } };
			Hand hand2 = { Card { "6D" }, Card { "7H" }, Card { "AD" }, Card { "8C" }, Card { "6H" } };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(!result);
		}

		{
			// 666
			Hand hand1 = { Card { "3C" }, Card { "2S" }, Card { "5C" }, Card { "6C" }, Card { "JD" } };
			Hand hand2 = { Card { "QS" }, Card { "2H" }, Card { "9D" }, Card { "7D" }, Card { "3H" } };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(!result);
		}

		{
			// 798
			Hand hand1 = { Card { "3C" }, Card { "QD" }, Card { "JS" }, Card { "9D" }, Card { "5S" } };
			Hand hand2 = { Card { "JC" }, Card { "AH" }, Card { "2H" }, Card { "TS" }, Card { "9H" } };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(!result);
		}

		{
			// 876
			Hand hand1 = { Card { "QD" }, Card { "TS" }, Card { "7D" }, Card { "AS" }, Card { "AC" } };
			Hand hand2 = { Card { "2C" }, Card { "TD" }, Card { "6H" }, Card { "8H" }, Card { "AH" } };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(result);
		}

		{
			// 877
			Hand hand1 = { Card { "6S" }, Card { "AD" }, Card { "8C" }, Card { "4S" }, Card { "9H" } };
			Hand hand2 = { Card { "8D" }, Card { "9D" }, Card { "KH" }, Card { "8S" }, Card { "3C" } };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(!result);
		}

		{
			// 878
			Hand hand1 = { Card { "QS" }, Card { "4D" }, Card { "2D" }, Card { "7S" }, Card { "KH" } };
			Hand hand2 = { Card { "JS" }, Card { "JC" }, Card { "AD" }, Card { "4C" }, Card { "3C" } };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(!result);
		}

		{
			// 943
			Hand hand1 = { Card { "JH" }, Card { "5H" }, Card { "KC" }, Card { "3C" }, Card { "TC" } };
			Hand hand2 = { Card { "5S" }, Card { "9H" }, Card { "4C" }, Card { "8H" }, Card { "9D" } };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(!result);
		}

		{
			// 944
			Hand hand1 = { Card { "8S" }, Card { "KC" }, Card { "5H" }, Card { "9H" }, Card { "AD" } };
			Hand hand2 = { Card { "KS" }, Card { "9D" }, Card { "KH" }, Card { "8D" }, Card { "AH" } };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(!result);
		}

		{
			// 997
			Hand hand1 = { Card { "AD" }, Card { "3D" }, Card { "TS" }, Card { "KS" }, Card { "7H" } };
			Hand hand2 = { Card { "JH" }, Card { "2D" }, Card { "JS" }, Card { "QD" }, Card { "AC" } };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(!result);
		}

		{
			// 998
			Hand hand1 = { Card { "9C" }, Card { "JD" }, Card { "7C" }, Card { "6D" }, Card { "TC" } };
			Hand hand2 = { Card { "6H" }, Card { "6C" }, Card { "JC" }, Card { "3D" }, Card { "3S" } };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(!result);
		}

		{
			// 999
			Hand hand1 = { Card { "QC" }, Card { "KC" }, Card { "3S" }, Card { "JC" }, Card { "KD" } };
			Hand hand2 = { Card { "2C" }, Card { "8D" }, Card { "AH" }, Card { "QS" }, Card { "TS" } };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(result);
		}

		{
			// 1000
			Hand hand1 = { Card { "AS" }, Card { "KD" }, Card { "3D" }, Card { "JD" }, Card { "8H" } };
			Hand hand2 = { Card { "7C" }, Card { "8C" }, Card { "5C" }, Card { "QD" }, Card { "6C" } };

			bool result = CardGame::Play(hand1, hand2);

			REQUIRE(result);
		}
	}
}
