/*************************************************************************
    > File Name       : src/divider.hpp
    > Author          : chmodJack
    > Mail            : 158754845@qq.com 
    > GitHub          : https://github.com/chmodJack 
    > Created Time    : Fri Jun  2 08:06:35 2023
    > Description     : 
*************************************************************************/
#ifndef __DIVIDER_HPP__
#define __DIVIDER_HPP__

struct divider: sc_module
{
	sc_in<bool> in;
	sc_in<bool> rst;
	sc_in<uint32_t> cfg;

	sc_out<bool> out;

	SC_CTOR(divider)
	{
		SC_THREAD(run);
		sensitive << in.pos();

		async_reset_signal_is(rst,0);
	}

	sc_signal<uint32_t> cnt;
	void run()
	{
		out = 0;
		cnt = 0;
		while(1)
		{
			wait();
			cnt = cnt + 1;
			if(cnt >= cfg)
			{
				cnt = 0;
				out = ! out;
			}
		}
	}
};

#endif//__DIVIDER_HPP__
