/*************************************************************************
    > File Name       : uart_tx.hpp
    > Author          : chmodJack
    > Mail            : 158754845@qq.com 
    > GitHub          : https://github.com/chmodJack 
    > Created Time    : Mon May 29 23:28:13 2023
    > Description     : 
*************************************************************************/
#ifndef __UART_TX_HPP__
#define __UART_TX_HPP__

#include <systemc.h>
using namespace sc_core;
using namespace sc_dt;

struct uart_tx: sc_module
{
	sc_in<bool> clk;
	sc_in<bool> rst;

	sc_in<bool> en;
	sc_in<sc_uint<8>> data;

	sc_out<bool> tx;
	sc_out<bool> busy;

	SC_CTOR(uart_tx)
	{
		SC_THREAD(run);
		sensitive << clk.pos();

		async_reset_signal_is(rst,0);
	}
	void run()
	{
		tx = 1;
		busy = 0;

		while(1)
		{
			wait();

			if(en)
			{
				busy = 1;
				tx = 0;	wait();
				tx = data.read()[0]; wait();
				tx = data.read()[1]; wait();
				tx = data.read()[2]; wait();
				tx = data.read()[3]; wait();
				tx = data.read()[4]; wait();
				tx = data.read()[5]; wait();
				tx = data.read()[6]; wait();
				tx = data.read()[7]; wait();
				tx = 1;busy = 0;
			}
		}
	}
};

#endif//__UART_TX_HPP__
