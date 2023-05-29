#include <systemc.h>

#include "counter.hpp"
#include "uart_tx.hpp"
#include "fifo.hpp"
#include "is_prime.hpp"

struct top: sc_module 
{
	sc_signal<bool> clk;
	sc_signal<bool> rst;

	uart_tx ut{"ut"};
	sc_signal<bool> en;
	sc_signal<sc_uint<8>> data;
	sc_signal<bool> tx;
	sc_signal<bool> busy;

	fifo ff{"ff"};
	sc_signal<sc_uint<8>> data_i;
	sc_signal<bool> en_r;
	sc_signal<bool> en_w;
	sc_signal<sc_uint<8>> data_o;
	sc_signal<bool> full;
	sc_signal<bool> empty;
	sc_signal<bool> ack_r;
	sc_signal<bool> ack_w;

	counter<8> cn{"cn"};
	sc_signal<sc_uint<8>> max;
	sc_signal<sc_uint<8>> cnt;
	sc_signal<bool> carry;


    SC_CTOR(top)
    {
		SC_THREAD(run);
		async_reset_signal_is(rst,0);

#define BIND(M,P) M.P(P)
		BIND(ut,clk);
		BIND(ut,rst);
		BIND(ut,en);
		BIND(ut,data);
		BIND(ut,tx);
		BIND(ut,busy);

		BIND(ff,clk);
		BIND(ff,rst);
		BIND(ff,data_i);
		BIND(ff,en_r);
		BIND(ff,en_w);
		BIND(ff,data_o);
		BIND(ff,full);
		BIND(ff,empty);
		BIND(ff,ack_r);
		BIND(ff,ack_w);

		BIND(cn,clk);
		BIND(cn,rst);
		BIND(cn,max);
		BIND(cn,cnt);
		BIND(cn,carry);
#undef BIND
    }

	void run()
	{
		while(1)
		{
			clk = !clk;
			wait();
		}
	}
};

struct top_prime: sc_module 
{
	sc_signal<bool> clk;
	sc_signal<bool> rst;

	counter<32> cn{"cn"};
	sc_signal<sc_uint<32>> max;
	sc_signal<sc_uint<32>> cnt;
	sc_signal<bool> carry;

	is_prime ip{"ip"};
	sc_signal<bool> is_p;

    SC_CTOR(top_prime)
    {
		SC_THREAD(run);
		async_reset_signal_is(rst,0);

#define BIND(M,P) M.P(P)
		BIND(cn,clk);
		BIND(cn,rst);
		BIND(cn,max);
		BIND(cn,cnt);
		BIND(cn,carry);

		ip.data(cnt);
		ip.is_p(is_p);
#undef BIND
    }

	void run()
	{
		while(1)
		{
			clk = !clk;
			wait();
		}
	}
};
 
int sc_main (int argc, char **argv)
{
    top_prime top_inst("top_inst");
    sc_start();
    return 0;
}
