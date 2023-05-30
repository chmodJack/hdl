/*************************************************************************
    > File Name       : uart_rx.hpp
    > Author          : chmodJack
    > Mail            : 158754845@qq.com 
    > GitHub          : https://github.com/chmodJack 
    > Created Time    : Tue May 30 12:08:59 2023
    > Description     : 
*************************************************************************/
#ifndef __UART_RX_HPP__
#define __UART_RX_HPP__

#include<systemc.h>
using namespace sc_core;
using namespace sc_dt;

struct uart_rx: sc_module
{
	sc_in<bool> clk;
	sc_in<bool> rst;
	sc_in<bool> rx;

	sc_out<bool> en;
	sc_out<bool> busy;
	sc_out<sc_uint<8>> data;


	sc_uint<8> buf;

	SC_CTOR(uart_rx)
	{
		SC_THREAD(run);
		sensitive << clk.pos() << rst.neg();

		async_reset_signal_is(rst,0);
	}
	void run()
	{
		busy = 0;
		data = 0;
		en = 0;

		while(1)
		{
			wait();
			en = 0;
			busy = 0;

			if(rx == 0)
			{
				busy = 1;
				wait();

				buf[0] = rx; wait();
				buf[1] = rx; wait();
				buf[2] = rx; wait();
				buf[3] = rx; wait();
				buf[4] = rx; wait();
				buf[5] = rx; wait();
				buf[6] = rx; wait();
				buf[7] = rx; wait();

				if(rx.read() == 1)
					en = 1;
				else
					en = 0;

				busy = 0;
				data = buf;
			}
		}
	}
};

#endif//__UART_RX_HPP__
