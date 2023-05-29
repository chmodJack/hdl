/*************************************************************************
    > File Name       : fifo.hpp
    > Author          : chmodJack
    > Mail            : 158754845@qq.com 
    > GitHub          : https://github.com/chmodJack 
    > Created Time    : Mon May 29 23:28:36 2023
    > Description     : 
*************************************************************************/
#ifndef __FIFO_HPP__
#define __FIFO_HPP__

#include <systemc.h>
using namespace sc_core;
using namespace sc_dt;

struct fifo: sc_module
{
	sc_in<bool> clk;
	sc_in<bool> rst;

	sc_in<sc_uint<8>> data_i;

	sc_in<bool> en_r;
	sc_in<bool> en_w;

	sc_out<sc_uint<8>> data_o;

	sc_out<bool> full;
	sc_out<bool> empty;

	sc_out<bool> ack_r;
	sc_out<bool> ack_w;

	sc_uint<8> buffer[8];
	uint8_t head;
	uint8_t tail;

	SC_CTOR(fifo)
	{
		SC_THREAD(run);
		sensitive << clk.pos() << rst.neg();

		async_reset_signal_is(rst,0);
	}

	void run()
	{
		data_o = 0;
		full = 0;
		empty = 1;
		ack_r = 0;
		ack_w = 0;

		head = 0;
		tail = 0;

		for(int i=0;i<8;i++)
			buffer[i] = 0;

		while(1)
		{
			wait();

			if(en_r && not empty)
			{
				data_o = buffer[head];
				head = head + 1;

				if(head == 8)
					head = 0;

				if(head == tail)
					empty = 1;

				ack_r = 1;
				full = 0;
			}
			else
			{
				ack_r = 0;
			}

			if(en_w && not full)
			{
				buffer[tail] = data_i;
				tail = tail + 1;

				if(tail == 8)
					tail = 0;

				if(tail == head)
					full = 1;

				ack_w = 1;
				empty = 0;
			}
			else
			{
				ack_w = 0;
			}
		}
	}
};

#endif//__FIFO_HPP__
