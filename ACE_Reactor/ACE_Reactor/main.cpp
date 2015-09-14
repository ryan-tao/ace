#include "stdafx.h"
#include "ace\Init_ACE.h"

#include "Signal_Handler.hpp"

int _tmain(int argc, _TCHAR* argv[])
{
	ACE::init();

	My_Handler h;

	while (1) {
		ACE_Reactor::instance()->handle_events();
		ACE_DEBUG((LM_DEBUG, "handle_events() \n"));
		ACE_OS::sleep(3);
	}

	ACE::fini();
	return 0;
}