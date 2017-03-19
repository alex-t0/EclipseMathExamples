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
}
