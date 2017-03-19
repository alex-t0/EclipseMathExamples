#ifndef CARDS_H
#define CARDS_H

#include <initializer_list>
#include <algorithm>

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
        value = other.GetVaue();
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

    ~Card() { }

    Suite GetSuite() const
    {
        return suite;
    }

    Value GetVaue() const
    {
        return value;
    }

private:
    Suite suite;
    Value value;
};

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

    Card operator[](const int index)
    {
        return cards[index];
    }

private:
    std::vector<Card> cards;
};

class PokerResult {
public:
    PokerResult(bool value) : success{value} {}
    PokerResult() : success{false} {}
    bool success;
};

class Poker {
public:
      virtual PokerResult Test(Hand hand) = 0;
      virtual ~Poker() {}
};

class RoyalFlush : public Poker {
public:
    PokerResult Test(Hand hand)
    {
        Suite s = hand[0].GetSuite();

        for (int i = 1; i < 5; i++)
        {
            if (s != hand[i].GetSuite()) return PokerResult{false};
        }

        auto cardExists = [&](const Value v)
        {
            bool exists = false;
            for (int i = 0; i < 5; i++)
            {
                if (v == hand[i].GetVaue())
                {
                    exists = true;
                    break;
                }
            }

            return exists;
        };

        return PokerResult{cardExists(Value::Ten) && cardExists(Value::Jack) && cardExists(Value::Queen) && cardExists(Value::King) && cardExists(Value::Ace)};
    }
};

class StraightFlush : public Poker {
public:
    PokerResult Test(Hand hand)
    {
        Suite s = hand[0].GetSuite();

        for (int i = 1; i < 5; i++)
        {
            if (s != hand[i].GetSuite()) return PokerResult { false };
        }

        std::vector<char> values = { hand[0].GetVaue(), hand[1].GetVaue(), hand[2].GetVaue(), hand[3].GetVaue(), hand[4].GetVaue() };
        std::sort(values.begin(), values.end());

        for (int i = 0; i < 4; i++)
        {
            if (abs((int)values[i+1] - (int)values[i]) != 1) return PokerResult { false };
        }

        return PokerResult { true };
    }
};

class FourOfaKindPokerResult : public PokerResult
{
public:
    FourOfaKindPokerResult(std::initializer_list<Card> v, Card otherCard) : Four{v}, other {otherCard} { success = true; }
    FourOfaKindPokerResult(bool success) : PokerResult(success) {}
    std::vector<Card> Four;
    Card other;
    // ~FourOfaKindPokerResult() {}
};

class FourOfaKind : public Poker {
public:
    PokerResult Test(Hand hand)
    {
        std::vector<Card> three;
        for (int i = 0; i < 2; i++)
        {
            int notEqualsCount = 0;
            Card* otherPtr = nullptr;
            for (int j = 0; j < 5; j++)
            {
                if (i == j) continue;

                if(hand[i].GetVaue() == hand[j].GetVaue())
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

                return FourOfaKindPokerResult { { hand[i], three[0], three[1], three[2] }, *otherPtr };
            }
        }

        return FourOfaKindPokerResult { false };
    }
};

#endif // CARDS_H
