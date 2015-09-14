// ACE_Acceptor_Connector.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "ace\Init_ACE.h"
#include "Svc_Acceptor_Handler.hpp"

#define PORT_NUM 10101


typedef ACE_Acceptor<My_Svc_Handler, ACE_SOCK_ACCEPTOR> MyAcceptor;

int _tmain(int argc, _TCHAR* argv[])
{
	ACE::init();

	ACE_INET_Addr addr(PORT_NUM);

	MyAcceptor acceptor(addr, ACE_Reactor::instance());

	while (1) {
		ACE_Reactor::instance()->handle_events();
	}

	ACE::fini();

	return 0;
}

