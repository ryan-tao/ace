#pragma once
#include "stdafx.h"
#include "ace/Event_Handler.h"
#include "ace/Reactor.h"
#include "ace/Synch.h"
#include "ace/Thread_Manager.h"

class My_Handler : public ACE_Event_Handler
{
public:
	My_Handler() {
		ACE_DEBUG((LM_DEBUG, "Got open \n"));
		activate_threads();
		ACE_Reactor::instance()->max_notify_iterations(5);
	}

	void activate_threads() {
		ACE_Thread_Manager::instance()->spawn((ACE_THR_FUNC)svc_start, (void*)this);
	}

	void svc()
	{
		for (int i = 0; i < 10; i++) {
			ACE_Reactor::instance()->notify(this, ACE_Event_Handler::READ_MASK);
			ACE_DEBUG((LM_DEBUG, "Notified %d \n", i));
		}	
	}

	int handle_input(ACE_HANDLE) {
		ACE_DEBUG((LM_DEBUG, "Got notification # %d \n", no));
		no++;
		return 0;
	}

	static int svc_start(void* arg);

private:
	static int no;
};

int My_Handler::no = 1;

int My_Handler::svc_start(void* arg) {
	My_Handler* h = (My_Handler*)arg;
	h->svc();
	return -1;
}