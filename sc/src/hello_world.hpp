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

	sc_out<bool> led[4];
	sc_in<bool> key[4];

	sc_in<bool> touch;
	sc_out<bool> beep;

	sc_signal<sc_uint<32>> cnt;

	SC_CTOR(hello_world)
	{
		SC_THREAD(run);
		sensitive << clk.pos();
		async_reset_signal_is(rst,0);
	}

	void run()
	{
		cnt = 0;
		while(1)
		{
			wait();
			cnt = cnt.read() + 1;

			led[0] = cnt.read()[24];
			led[1] = cnt.read()[25];
			led[2] = cnt.read()[26];
			led[3] = cnt.read()[27];

			if(key[0] == 0)
				cnt = 0x00000000;

			if(key[1] == 0)
				cnt = 0xFFFFFFFF;

			if(key[2] == 0)
				cnt = 0xFCFFFFFF;

			if(key[3] == 0)
				cnt = 0xF3FFFFFF;


			beep = touch;
		}
	}
};

#endif//__HELLO_WORLD_HPP__
