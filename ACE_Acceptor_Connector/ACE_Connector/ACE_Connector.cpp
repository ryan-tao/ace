// ACE_Connector.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Svc_Connector_Handler.hpp"

typedef ACE_Connector<My_Svc_Handler, ACE_SOCK_CONNECTOR> MyConnector;

int _tmain(int argc, _TCHAR* argv[])
{
	ACE_INET_Addr addr(10101, "localhost");

	My_Svc_Handler * h = new My_Svc_Handler;

	MyConnector conn;

	if (conn.connect(h, addr) == -1)
		ACE_ERROR((LM_ERROR, "%P|%t, %p", "Connection Failed"));

	while (1) {
		ACE_Reactor::instance()->handle_events();
	}

	return 0;
}

