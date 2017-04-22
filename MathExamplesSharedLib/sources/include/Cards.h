#ifndef CARDS_H
#define CARDS_H

#include <initializer_list>
#include <algorithm>
#include <iostream>

enum class Suite : char
{
    NotInitialized = 0, Spades = 1, Hearts = 2, Diamonds = 3, Clubs = 4
};

enum Value : char
{
    NotInitialized = 0, Two = 2, Three = 3, Four = 4, Five = 5, Six = 6, Seven = 7, Eight = 8, Nine = 9, Ten = 10, Jack = 11, Queen = 12, King = 13, Ace = 14
};

class Card
{
public:
    Card()
    {
        suite = Suite::NotInitialized;
        value = Value::NotInitialized;
    }

    Card(const Card& other)
    {
        suite = other.GetSuite();
        value = other.GetValue();
    }

    Card(std::string cardStr)
    {
        char val = cardStr[0];
        char s = cardStr[1];

        switch (s)
        {
            case 'S': suite = Suite::Spades; break;
            case 'H': suite = Suite::Hearts; break;
            case 'D': suite = Suite::Diamonds; break;
            case 'C': suite = Suite::Clubs; break;
        default: throw "Invalid suite";
        }

        switch (val)
        {
            case '2': value = Value::Two; break;
            case '3': value = Value::Three; break;
            case '4': value = Value::Four; break;
            case '5': value = Value::Five; break;
            case '6': value = Value::Six; break;
            case '7': value = Value::Seven; break;
            case '8': value = Value::Eight; break;
            case '9': value = Value::Nine; break;
            case 'T': value = Value::Ten; break;
            case 'J': value = Value::Jack; break;
            case 'Q': value = Value::Queen; break;
            case 'K': value = Value::King; break;
            case 'A': value = Value::Ace; break;
        default: throw "Invalid value";
        }
    }

    // ~Card() { }

    Suite GetSuite() const
    {
        return suite;
    }

    Value GetValue() const
    {
        return value;
    }

    bool operator==(const Card &other)
	{
    	return other.GetSuite() == this->GetSuite() && other.GetValue() == this->GetValue();
	}

    bool operator!=(const Card &other)
	{
		return other.GetSuite() != this->GetSuite() || other.GetValue() != this->GetValue();
	}

    friend std::ostream& operator<<(std::ostream& os, const Card& card);

private:
    Suite suite;
    Value value;
};

std::ostream& operator<<(std::ostream& os, const Card& card)
{
	std::string svalue = "";

	switch (card.GetSuite())
	{
		case Suite::Clubs:
			svalue = "C";
			break;
		case Suite::Diamonds:
			svalue = "D";
			break;
		case Suite::Hearts:
			svalue = "H";
			break;
		case Suite::Spades:
			svalue = "S";
			break;
		case Suite::NotInitialized:
			throw "Must be initialized";
	}

	int ivalue = (int)card.GetValue();
	if (ivalue < 10)
		os << ivalue;
	else
	{
		switch (ivalue)
		{
			case 10:
				os << "T";
				break;
			case 11:
				os << "J";
				break;
			case 12:
				os << "Q";
				break;
			case 13:
				os << "K";
				break;
			case 14:
				os << "A";
				break;
		}
	}

	os << svalue;

	return os;
}

class Hand
{
public:
    Hand(std::initializer_list<Card> cardsInit)
    {
        if (cardsInit.size() != 5) throw "Invalid hands size";

        for (auto& card : cardsInit)
            cards.push_back(card);
    }

    Hand(std::initializer_list<std::string> cardsStrs)
	{
		if (cardsStrs.size() != 5) throw "Invalid hands size";

		for (auto& card : cardsStrs)
			cards.push_back(Card {card});
	}

    /*Hand(Hand& other)
	{
		for (auto& card : other)
			cards.push_back(Card {card});
	}*/

    Card operator[](const int index) const
    {
        return cards[index];
    }

    std::vector<Card>::iterator begin()
    {
    	return cards.begin();
    }

    std::vector<Card>::iterator end()
    {
      	return cards.end();
    }

    friend std::ostream& operator<<(std::ostream& os, const Hand& h);
 private:
    std::vector<Card> cards;
};

std::ostream& operator<<(std::ostream& os, const Hand& h)
{
    os << h[0] << ' ' << h[1] << ' ' << h[2] << ' ' << h[3] << ' ' << h[4];
    return os;
}

class PokerResult {
public:
    PokerResult(bool value) : success{value} {}
    PokerResult() : success{false} {}
    bool success;
    virtual ~PokerResult() { }
};

class Poker {
public:
      virtual PokerResult* Test(const Hand hand) = 0;
      virtual ~Poker() {}
};

class RoyalFlush : public Poker {
public:
    PokerResult* Test(const Hand hand)
    {
        Suite s = hand[0].GetSuite();

        for (int i = 1; i < 5; i++)
        {
            if (s != hand[i].GetSuite()) return new PokerResult { false };
        }

        auto cardExists = [&](const Value v)
        {
            bool exists = false;
            for (int i = 0; i < 5; i++)
            {
                if (v == hand[i].GetValue())
                {
                    exists = true;
                    break;
                }
            }

            return exists;
        };

        return new PokerResult{cardExists(Value::Ten) && cardExists(Value::Jack) && cardExists(Value::Queen) && cardExists(Value::King) && cardExists(Value::Ace)};
    }
};

class StraightFlush : public Poker {
public:
    PokerResult* Test(const Hand hand)
    {
        Suite s = hand[0].GetSuite();

        for (int i = 1; i < 5; i++)
        {
            if (s != hand[i].GetSuite()) return new PokerResult { false };
        }

        std::vector<char> values = { hand[0].GetValue(), hand[1].GetValue(), hand[2].GetValue(), hand[3].GetValue(), hand[4].GetValue() };
        std::sort(values.begin(), values.end());

        for (int i = 0; i < 4; i++)
        {
            if (abs((int)values[i+1] - (int)values[i]) != 1) return new PokerResult { false };
        }

        return new PokerResult { true };
    }
};

class FourOfaKindPokerResult : public PokerResult
{
public:
    FourOfaKindPokerResult(std::initializer_list<Card> v, Card otherCard) : Four{v}, other {otherCard} { success = true; }
    FourOfaKindPokerResult(bool success) : PokerResult(success) {}
    std::vector<Card> Four;
    Card other;
    virtual ~FourOfaKindPokerResult() {}
};

class FourOfaKind : public Poker {
public:
    PokerResult* Test(const Hand hand)
    {
        std::vector<Card> three;
        for (int i = 0; i < 2; i++)
        {
            int notEqualsCount = 0;
            Card* otherPtr = nullptr;
            for (int j = 0; j < 5; j++)
            {
                if (i == j) continue;

                if(hand[i].GetValue() == hand[j].GetValue())
                    three.push_back(hand[i]);
                else
                {
                    notEqualsCount++;
                    if (otherPtr == nullptr)
                        otherPtr = new Card(hand[i]);
                }
            }

            if (notEqualsCount > 1)
                continue;
            else
            {
                if (three.size() != 3)
                    throw "this is impossible :) three != 3";

                return new FourOfaKindPokerResult { { hand[i], three[0], three[1], three[2] }, *otherPtr };
            }
        }

        return new FourOfaKindPokerResult { false };
    }
};

class Flush : public Poker {
public:
    PokerResult* Test(const Hand hand)
    {
        return new PokerResult { hand[0].GetSuite() == hand[1].GetSuite()
        	&& hand[1].GetSuite() == hand[2].GetSuite()
        	&& hand[2].GetSuite() == hand[3].GetSuite()
        	&& hand[3].GetSuite() == hand[4].GetSuite()};
    }
};

class Straight : public Poker {
public:
    PokerResult* Test(const Hand hand)
    {
    	std::vector<int> values = { hand[0].GetValue(), hand[1].GetValue(), hand[2].GetValue(), hand[3].GetValue(), hand[4].GetValue() };
    	std::sort(values.begin(), values.end());

    	for (unsigned int i = 0; i < values.size() - 1; i++)
    	{
    		if (abs(values[i] - values[i+1]) != 1)
    			return new PokerResult { false };
    	}

        return new PokerResult { true };
    }
};

class ThreeOfAKindPokerResult : public PokerResult
{
public:
	ThreeOfAKindPokerResult(std::initializer_list<Card> v, std::initializer_list<Card> u) : Three{v}, TwoOthers{u} { success = true; }
	ThreeOfAKindPokerResult(bool success) : PokerResult(success) {}
    std::vector<Card> Three;
    std::vector<Card> TwoOthers;
    virtual ~ThreeOfAKindPokerResult() { };
};

class ThreeOfAKind : public Poker {
public:
    PokerResult* Test(const Hand hand)
    {
    	// std::vector<int> values = { hand[0].GetVaue(), hand[1].GetVaue(), hand[2].GetVaue(), hand[3].GetVaue(), hand[4].GetVaue() };
    	// std::sort(values.begin(), values.end());

    	Hand handSorted = hand; // full copy of hand
    	std::sort(handSorted.begin(), handSorted.end(), [=](Card a, Card b)
    	{
    		return (int)a.GetValue() < (int)b.GetValue();
    	});

    	if ((handSorted[2].GetValue() == handSorted[3].GetValue()) && (handSorted[3].GetValue() == handSorted[4].GetValue()))
    	{
    		return new ThreeOfAKindPokerResult { { handSorted[2], handSorted[3], handSorted[4] }, { handSorted[0], handSorted[1] } };
    	}

    	if ((handSorted[1].GetValue() == handSorted[2].GetValue()) && (handSorted[2].GetValue() == handSorted[3].GetValue()))
		{
			return new ThreeOfAKindPokerResult { { handSorted[1], handSorted[2], handSorted[3] }, { handSorted[0], handSorted[4] } };
		}

    	if ((handSorted[0].GetValue() == handSorted[1].GetValue()) && (handSorted[1].GetValue() == handSorted[2].GetValue()))
		{
			return new ThreeOfAKindPokerResult { { handSorted[0], handSorted[1], handSorted[2] }, { handSorted[3], handSorted[4] } };
		}

        return new ThreeOfAKindPokerResult { false };
    }
};

class FullHousePokerResult : public PokerResult
{
public:
	FullHousePokerResult(std::initializer_list<Card> three, std::initializer_list<Card> pair) : Three{three}, Pair{pair} { success = true; }
	FullHousePokerResult(bool success) : PokerResult(success) {}
    std::vector<Card> Three;
    std::vector<Card> Pair;
    virtual ~FullHousePokerResult() { };
};

class FullHouse : public Poker {
public:
    PokerResult* Test(const Hand hand)
    {
    	std::vector<Card> pair;

    	ThreeOfAKind tok;
    	PokerResult* result = tok.Test(hand);
    	// ThreeOfAKindPokerResult& tokResult = static_cast<ThreeOfAKindPokerResult&>(ref_result);
    	ThreeOfAKindPokerResult* tokResult = static_cast<ThreeOfAKindPokerResult*>(result);

    	if (!tokResult->success)
    	{
    		delete result;
    		FullHousePokerResult *pr_return = new FullHousePokerResult { false };
    		return pr_return;
    	}

    	for (unsigned int i = 0; i < 5; i++)
    	{
    		if (hand[i] != tokResult->Three[0] && hand[i] != tokResult->Three[1] && hand[i] != tokResult->Three[2])
    		{
    			pair.push_back(hand[i]);
    		}
    	}

    	if (pair.size() != 2 || pair[0].GetValue() != pair[1].GetValue())
    	{
    		delete result;
    		return new FullHousePokerResult { false };
    	}

    	FullHousePokerResult* finalResult = new FullHousePokerResult { { tokResult->Three[0], tokResult->Three[1], tokResult->Three[2] }, { pair[0], pair[1] } };
    	delete result;
        return finalResult;
    }
};

class TwoPairsPokerResult : public PokerResult
{
public:
	TwoPairsPokerResult(std::initializer_list<Card> firstPair, std::initializer_list<Card> secondPair, Card other) : FirstPair{firstPair}, SecondPair{secondPair}, Other{other} { success = true; }
	TwoPairsPokerResult(bool success) : PokerResult(success) {}
    std::vector<Card> FirstPair;
    std::vector<Card> SecondPair;
    Card Other;
    virtual ~TwoPairsPokerResult() { }
};

class TwoPairs : public Poker {
public:
    PokerResult* Test(const Hand hand)
    {
    	std::vector<Card> pair1, pair2, others;

    	Hand handSorted = hand; // full copy of hand
    	std::sort(handSorted.begin(), handSorted.end(), [=](Card a, Card b)
    	{
    		return (int)a.GetValue() < (int)b.GetValue();
    	});

    	bool pair_found = false;
    	bool pair_count = 0;
    	for (int i = 4; i > 0; i--)
    	{
    		if (pair_found == true)
    		{
    			pair_found = false;
    			continue;
    		}

    		if (handSorted[i].GetValue() == handSorted[i - 1].GetValue())
    		{
    			std::vector<Card>& p = pair_count == 0 ? pair1 : pair2;
    			p.push_back(handSorted[i]);
    			p.push_back(handSorted[i - 1]);
    			pair_found = true;
    		}
    		else
    			others.push_back(handSorted[i]);
    	}

    	if (pair1.size() != 2 || pair2.size() != 2 || others.size() != 1)
    		return new TwoPairsPokerResult { false };

    	return new TwoPairsPokerResult { { pair1[0], pair1[1] }, { pair2[0], pair2[1] }, others[0] };
    }
};

class OnePairPokerResult : public PokerResult
{
public:
	OnePairPokerResult(std::initializer_list<Card> pair, std::initializer_list<Card> others) : Pair{pair}, Others{others} { success = true; }
	OnePairPokerResult(bool success) : PokerResult(success) {}
    std::vector<Card> Pair;
    std::vector<Card> Others;
    virtual ~OnePairPokerResult() { };
};

class OnePair : public Poker {
public:
    PokerResult* Test(const Hand hand)
    {
    	std::vector<Card> pair;
    	std::vector<Card> others;

    	Hand handSorted = hand; // full copy of hand
    	std::sort(handSorted.begin(), handSorted.end(), [=](Card a, Card b)
    	{
    		return (int)a.GetValue() < (int)b.GetValue();
    	});

    	bool pairFound = false;
    	for (int i = 4; i >= 0; i--)
    	{
    		if (pairFound == true)
    		{
    			pairFound = false;
    			continue;
    		}

    		if (i >= 1 && handSorted[i].GetValue() == handSorted[i - 1].GetValue())
    		{
    			pair.push_back(handSorted[i]);
    			pair.push_back(handSorted[i - 1]);
    			pairFound = true;
    		}
    		else
    		{
    			others.push_back(handSorted[i]);
    		}
    	}

    	if (pair.size() != 2)
    		return new OnePairPokerResult { false };

    	return new OnePairPokerResult { { pair[0], pair[1] }, { others[0], others[1], others[2] } };
    }
};

#endif // CARDS_H
