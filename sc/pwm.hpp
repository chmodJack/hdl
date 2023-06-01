/*************************************************************************
    > File Name       : pwm.hpp
    > Author          : chmodJack
    > Mail            : 158754845@qq.com 
    > GitHub          : https://github.com/chmodJack 
    > Created Time    : Thu Jun  1 11:01:33 2023
    > Description     : 
*************************************************************************/
#ifndef __PWM_HPP__
#define __PWM_HPP__

#include <systemc.h>
using namespace sc_core;
using namespace sc_dt;

struct pwm: sc_module
{
	sc_in<bool> clk;
	sc_in<bool> rst;

	sc_in<sc_uint<8>> cycle_l;
	sc_in<sc_uint<8>> cycle_h;

	sc_out<bool> out;

	uint8_t cnt;
	SC_CTOR(pwm)
	{
		SC_THREAD(run);
		sensitive << clk.pos();
		async_reset_signal_is(rst,0);
	}
	void run()
	{
		cnt = 0;
		out = 0;
		while(1)
		{
			wait();
			cnt = cnt + 1;

			if((out == 0) && (cnt == cycle_l.read()))
			{
				cnt = 0;
				out = 1;
			}

			if((out == 1) && (cnt == cycle_h.read()))
			{
				cnt = 0;
				out = 0;
			}
		}
	}
};

#endif//__PWM_HPP__
