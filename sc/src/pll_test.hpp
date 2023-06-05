/*************************************************************************
    > File Name       : src/pll_test.hpp
    > Author          : chmodJack
    > Mail            : 158754845@qq.com 
    > GitHub          : https://github.com/chmodJack 
    > Created Time    : Fri Jun  2 07:52:53 2023
    > Description     : 
*************************************************************************/
#ifndef __PLL_TEST_HPP__
#define __PLL_TEST_HPP__

struct pll_test: sc_module
{
	sc_in<bool> clk_in[4];
	sc_in<bool> rst;

	sc_out<bool> led[4];

	divider d0{"d0"};
	divider d1{"d1"};
	divider d2{"d2"};
	divider d3{"d3"};

	sc_signal<uint32_t> cfg0;
	sc_signal<uint32_t> cfg1;
	sc_signal<uint32_t> cfg2;
	sc_signal<uint32_t> cfg3;

	SC_CTOR(pll_test)
	{
		SC_THREAD(run);
		async_reset_signal_is(rst,0);

		d0.in(clk_in[0]);
		d1.in(clk_in[1]);
		d2.in(clk_in[2]);
		d3.in(clk_in[3]);

		d0.rst(rst);
		d1.rst(rst);
		d2.rst(rst);
		d3.rst(rst);

		d0.cfg(cfg0);
		d1.cfg(cfg1);
		d2.cfg(cfg2);
		d3.cfg(cfg3);

		d0.out(led[0]);
		d1.out(led[1]);
		d2.out(led[2]);
		d3.out(led[3]);
	}

	void run()
	{
		cfg0 = 1000 * 1000 * 600;
		cfg1 = 1000 * 1000 * 400;
		cfg2 = 1000 * 1000 * 200;
		cfg3 = 1000 * 1000 * 100;

		while(1)
		{
			wait();
		}
	}
};

#endif//__PLL_TEST_HPP__
