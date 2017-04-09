#include <iostream>

#include "include/Catch.h"
#include "sources/include/Cards.h"


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

	    ThreeOfAKindPokerResult derived { { Card{"5H"}, Card{"5S"}, Card{"5C"} } };
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
}
