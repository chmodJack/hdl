/*************************************************************************
    > File Name       : counter.hpp
    > Author          : chmodJack
    > Mail            : 158754845@qq.com 
    > GitHub          : https://github.com/chmodJack 
    > Created Time    : Mon May 29 23:29:14 2023
    > Description     : 
*************************************************************************/
#ifndef __COUNTER_HPP__
#define __COUNTER_HPP__

#include <systemc.h>
using namespace sc_core;
using namespace sc_dt;

template<uint32_t WIDTH>
struct counter: sc_module
{
	sc_in<bool> clk;
	sc_in<bool> rst;
	sc_in<sc_uint<WIDTH>> max;

	sc_out<sc_uint<WIDTH>> cnt;
	sc_out<bool> carry;

	SC_CTOR(counter)
	{
		SC_THREAD(run);
		sensitive << clk.pos() << rst.neg();

		async_reset_signal_is(rst,0);
	}

	void run()
	{
		cnt = 0;
		carry = 0;
		while(1)
		{
			wait();
			cnt = cnt.read() + 1;
			carry = 0;
			if(cnt == max)
			{
				cnt = 0;
				carry = 1;
			}
		}
	}
};

#endif//__COUNTER_HPP__
