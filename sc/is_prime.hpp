/*************************************************************************
    > File Name       : is_prime.hpp
    > Author          : chmodJack
    > Mail            : 158754845@qq.com 
    > GitHub          : https://github.com/chmodJack 
    > Created Time    : Tue May 30 01:23:03 2023
    > Description     : 
*************************************************************************/
#ifndef __IS_PRIME_HPP__
#define __IS_PRIME_HPP__

#include <systemc.h>
using namespace sc_core;
using namespace sc_dt;

struct is_prime: sc_module
{
	sc_in<sc_uint<32>> data;
	sc_out<bool> is_p;

	SC_CTOR(is_prime)
	{
		SC_METHOD(run);
		sensitive << data;
	}
	void run()
	{
		uint32_t a = data.read() / 2;
		uint32_t b = data.read() % 2;

		if(data.read() == 1)
		{
			is_p = 0;
		}
		else if(data.read() == 2)
		{
			is_p = 1;
		}
		else if(b == 0)
		{
			is_p = 0;
		}
		else
		{
			is_p = 1;

			for(uint32_t i = 3;i<=a;i++)
			{
				if((data.read() % i) == 0)
				{
					is_p = 0;
					break;
				}
			}
		}
	}
};

#endif//__IS_PRIME_HPP__
