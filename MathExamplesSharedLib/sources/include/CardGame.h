/*
 * CardGame.h
 *
 *  Created on: Apr 22, 2017
 *      Author: alex-t
 */

#ifndef INCLUDE_CARDGAME_H_
#define INCLUDE_CARDGAME_H_

#include "Cards.h"

class CardGame {
public:
	CardGame();
	virtual ~CardGame();
	static bool Play(Hand hand1, Hand hand2);
};

#endif /* INCLUDE_CARDGAME_H_ */
