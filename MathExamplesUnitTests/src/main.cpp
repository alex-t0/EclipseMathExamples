#include "include/Catch.h"
#include "sources/include/Cards.h"

SCENARIO("Cards works fine", "[cards]") {
	GIVEN("Royal Flush check")
	{
		RoyalFlush rf_checker;

		Hand rf_hand1 = { "TD", "JD", "QD", "AD", "KD" };
		Hand rf_hand2 = { "QD", "AD", "TD", "JD", "KD" };

		REQUIRE(rf_checker.Test(rf_hand1).success == true);
		REQUIRE(rf_checker.Test(rf_hand2).success == true);

		Hand rf_hand3 = { "TD", "JD", "QD", "AD", "KH" };
		Hand rf_hand4 = { "9D", "AD", "TD", "JD", "KD" };

		REQUIRE(rf_checker.Test(rf_hand3).success == false);
		REQUIRE(rf_checker.Test(rf_hand4).success == false);
		REQUIRE(!rf_checker.Test(rf_hand4).success);
	}

	GIVEN("Straight Flush check")
	{
		StraightFlush sf_checker;

		Hand sf_hand1 = { "6D", "5D", "3D", "4D", "2D" };
		Hand sf_hand2 = { "QH", "JH", "TH", "8H", "9H" };

		REQUIRE(sf_checker.Test(sf_hand1).success);
		REQUIRE(sf_checker.Test(sf_hand2).success);

		Hand sf_hand3 = { "QH", "JH", "TS", "8H", "9H" };
		REQUIRE(!sf_checker.Test(sf_hand3).success);
	}

	GIVEN("Four of a kind poker result")
	{
		FourOfaKind fk_checker;

		Hand fk_hand1 = { "6D", "6S", "3D", "6H", "6C" };
		Hand fk_hand2 = { "AH", "AD", "TH", "AC", "AS" };

		REQUIRE(fk_checker.Test(fk_hand1).success);
		REQUIRE(fk_checker.Test(fk_hand2).success);
	}

	GIVEN("Full house")
	{
		// FullHouse fh_checker;

		Hand fh_hand1 = { "6D", "6S", "3D", "6H", "6C" };
		Hand fh_hand2 = { "AH", "AD", "TH", "AC", "AS" };

		// REQUIRE(fh_checker.Test(fh_hand1).success);
		// REQUIRE(fh_checker.Test(fh_hand2).success);
	}
}
