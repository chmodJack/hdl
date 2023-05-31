#include <systemc.h>

#include "hello_world.hpp"
#include "counter.hpp"
#include "is_prime.hpp"
#include "fifo.hpp"
#include "uart_tx.hpp"
#include "uart_rx.hpp"

struct top: sc_module
{
	sc_in<bool> clk;
	sc_in<bool> rst;

	hello_world hw{"hw"};
	sc_signal<bool> out;

	counter<32> cn{"cn"};
	sc_signal<sc_uint<32>> max;
	sc_signal<sc_uint<32>> cnt;
	sc_signal<bool> carry;

	is_prime ip{"ip"};
	sc_signal<bool> is_p;

	fifo ff{"ff"};
	sc_signal<sc_uint<8>> data_i;
	sc_signal<bool> en_r;
	sc_signal<bool> en_w;
	sc_signal<sc_uint<8>> data_o;
	sc_signal<bool> full;
	sc_signal<bool> empty;
	sc_signal<bool> ack_r;
	sc_signal<bool> ack_w;

	uart_tx ut{"ut"};
	sc_signal<bool> en_tx;
	sc_signal<sc_uint<8>> data_tx;
	sc_signal<bool> tx;
	sc_signal<bool> busy_tx;

	uart_rx ur{"ur"};
	sc_signal<bool> en_rx;
	sc_signal<sc_uint<8>> data_rx;
	sc_signal<bool> rx;
	sc_signal<bool> busy_rx;

    SC_CTOR(top)
    {
		SC_THREAD(run);
		sensitive << clk.pos();
		async_reset_signal_is(rst,0);

#define BIND(M,P) M.P(P)

		BIND(hw,clk);
		BIND(hw,rst);
		BIND(hw,out);
		
		BIND(cn,clk);
		BIND(cn,rst);
		BIND(cn,max);
		BIND(cn,cnt);
		BIND(cn,carry);

		ip.data(cnt);
		ip.is_p(is_p);

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

		BIND(ut,clk);
		BIND(ut,rst);
		ut.en(en_tx);
		ut.data(data_tx);
		BIND(ut,tx);
		ut.busy(busy_tx);

		BIND(ur,clk);
		BIND(ur,rst);
		ur.en(en_rx);
		ur.data(data_rx);
		BIND(ur,rx);
		ur.busy(busy_rx);

#undef BIND
    }

	void run()
	{
		max = 0x233;
		data_i = 0x666;

		en_r = 0;
		en_w = 0;

		en_tx = 0;
		data_tx = 0;

		rx = 0;

		while(1)
		{
			wait();
		}
	}
};

int sc_main (int argc, char **argv)
{
	sc_clock clk{"clk", sc_time(1, SC_NS)};
	sc_signal<bool> rst;

	top top{"top"};
	top.clk(clk);
	top.rst(rst);

	rst = 1;
	sc_start(1,SC_NS);

	rst = 0;
	sc_start(1,SC_NS);

	rst = 1;

    sc_start(10000,SC_NS);
    return 0;
}

