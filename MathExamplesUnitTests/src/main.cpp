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
	}
}
