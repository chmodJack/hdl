/*************************************************************************
    > File Name       : hello_world.hpp
    > Author          : chmodJack
    > Mail            : 158754845@qq.com 
    > GitHub          : https://github.com/chmodJack 
    > Created Time    : Wed May 31 16:39:12 2023
    > Description     : 
*************************************************************************/
#ifndef __HELLO_WORLD_HPP__
#define __HELLO_WORLD_HPP__

#include <systemc.h>
using namespace sc_core;
using namespace sc_dt;

struct hello_world: sc_module
{
	sc_in<bool> clk;
	sc_in<bool> rst;
	sc_out<bool> out;

	sc_signal<sc_uint<32>> cnt;

	SC_CTOR(hello_world)
	{
		SC_THREAD(run);
		sensitive << clk.pos();
		async_reset_signal_is(rst,0);

		SC_METHOD(out_logic);
		sensitive << cnt;
	}

	void run()
	{
		cnt = 0;
		while(1)
		{
			wait();
			cnt = cnt.read() + 1;
		}
	}

	void out_logic()
	{
		out = cnt.read()[15];
	}
};

#endif//__HELLO_WORLD_HPP__
