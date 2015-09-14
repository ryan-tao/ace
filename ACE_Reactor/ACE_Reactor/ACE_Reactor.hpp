// ACE_Reactor.cpp : 定义控制台应用程序的入口点。
//
#pragma once
#include "stdafx.h"
#include "ace\Reactor.h"
#include "ace\Event_Handler.h"
#include "ace\Task.h"
#include "ace\SOCK_Acceptor.h"

#define PORT_NO 19998
typedef ACE_SOCK_Acceptor Acceptor;

class My_Accept_Handler;

class My_Input_Handler : public ACE_Event_Handler {
public:
	My_Input_Handler() {
		ACE_DEBUG((LM_DEBUG, "Input Constructor \n"));
	}

	int handle_input(ACE_HANDLE) override {
		peer_.recv_n(data, 12);
		ACE_DEBUG((LM_DEBUG, "%s \n", data));
	}

	ACE_HANDLE get_handle() {
		return this->peer_i().get_handle();
	}

	ACE_SOCK_Stream& peer_i()
	{
		return this->peer_;
	}

private:
	ACE_SOCK_Stream peer_;
	char data[12];
};

class My_Accept_Handler : public ACE_Event_Handler
{
public:
	My_Accept_Handler(ACE_Addr & addr)
	{
		this->open(addr);
	}

	int open(ACE_Addr & addr)
	{
		peer_acceptor.open(addr);
		return 0;
	}

	int handle_input(ACE_HANDLE handle) {
		My_Input_Handler* h = new My_Input_Handler();

		if (this->peer_acceptor.accept(h->peer_i(), 0, 0, 1) == -1)
			ACE_DEBUG((LM_DEBUG, "error in connection \n"));

		ACE_DEBUG((LM_DEBUG, "connection OK \n"));

		ACE_Reactor::instance()->register_handler(h, ACE_Event_Handler::READ_MASK);
		return -1;
	}

	ACE_HANDLE get_handle() const 
	{
		return this->peer_acceptor.get_handle();
	}

private:
	Acceptor peer_acceptor;
};