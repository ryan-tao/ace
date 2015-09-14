#pragma once
#include "stdafx.h"
#include "ace\Timer_Queue.h"
#include "ace\Reactor.h"

#define NUMBER_TIMES 10

static int done = 0;
static int count = 0;

class Time_Handler : public ACE_Event_Handler
{
public:
	virtual int handle_timeout(const ACE_Time_Value &tv, const void *arg) {
		long current_count = long(arg);
		ACE_ASSERT(current_count == count);
		ACE_DEBUG((LM_DEBUG, "%d Timer #%d timed out at %d \n", count, current_count, tv.sec()));

		count++;

		if (count == 5) {
			count++;
		}

		if (current_count == NUMBER_TIMES - 1)
			done = 1;

		return 0;
	}
};