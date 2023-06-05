#include <systemc.h>

#include "src/hello_world.hpp"
#include "src/counter.hpp"
#include "src/is_prime.hpp"
#include "src/fifo.hpp"
#include "src/uart_tx.hpp"
#include "src/uart_rx.hpp"
#include "src/pwm.hpp"

#include "src/divider.hpp"
#include "src/pll_test.hpp"

using namespace std;
using namespace sc_core;
using namespace sc_dt;

struct top: sc_module
{
	sc_in<bool> clk;
	sc_in<bool> rst;

	hello_world hw{"hw"};
	sc_signal<bool> key[4];
	sc_signal<bool> led[4];
	sc_signal<bool> touch;
	sc_signal<bool> beep;

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

	pwm pw{"pw"};
	sc_signal<sc_uint<8>> cycle_l;
	sc_signal<sc_uint<8>> cycle_h;
	sc_signal<bool> pwm_out;

	//pll_test pt{"pt"};
	//sc_signal<bool> clk_in[4];

    SC_CTOR(top)
    {
		SC_THREAD(run);
		sensitive << clk.pos();
		async_reset_signal_is(rst,0);

#define BIND(M,P) M.P(P)

		BIND(hw,clk);
		BIND(hw,rst);
		BIND(hw,key[0]);
		BIND(hw,key[1]);
		BIND(hw,key[2]);
		BIND(hw,key[3]);
		BIND(hw,led[0]);
		BIND(hw,led[1]);
		BIND(hw,led[2]);
		BIND(hw,led[3]);
		BIND(hw,touch);
		BIND(hw,beep);
		
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

		BIND(pw,clk);
		BIND(pw,rst);
		BIND(pw,cycle_l);
		BIND(pw,cycle_h);
		pw.out(pwm_out);

		//pt.clk_in[0](clk_in[0]);
		//pt.clk_in[1](clk_in[1]);
		//pt.clk_in[2](clk_in[2]);
		//pt.clk_in[3](clk_in[3]);
		//pt.rst(rst);
		//pt.led[0](led[0]);
		//pt.led[1](led[1]);
		//pt.led[2](led[2]);
		//pt.led[3](led[3]);
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

struct uart_tx_ctl: sc_module
{
	sc_in<bool> baud;
	sc_in<bool> rst;

	sc_in<bool> busy_tx;
	sc_out<bool> en_tx;
	sc_out<sc_uint<8>> data_tx;

	sc_in<sc_uint<8>> buffer[32];
	sc_in<sc_uint<8>> size;
	sc_in<bool> trigger;
	sc_out<bool> busy;

	SC_CTOR(uart_tx_ctl)
	{
		SC_THREAD(run);
		sensitive << baud.pos();
		async_reset_signal_is(rst,0);
	}

	void run()
	{
		en_tx = 0;
		data_tx = 0;
		busy = 0;

		while(1)
		{
			wait();

			if(busy_tx)
			{
				busy = 1;
				en_tx = 0;
			}
			else
			{
				busy = 0;
				en_tx = 0;

				if(trigger)
				{
					busy = 1;

					//buffer size 
					data_tx = buffer[0];
					en_tx = 1;
					wait();
					en_tx = 0;
				}
			}
		}
	}
};

struct uart_test_top: sc_module
{
	sc_in<bool> clk;
	sc_in<bool> rst;

	sc_out<bool> uart_txd;
	sc_in<bool> uart_rxd;

	sc_in<bool> key[4];

	divider bit_rate{"bit_rate"};
	sc_signal<uint32_t> cfg_bit_rate;
	sc_signal<bool> out_bit_rate;

	uart_tx ut{"ut"};
	sc_signal<bool> en;
	sc_signal<sc_uint<8>> data;
	sc_signal<bool> busy;

	uart_tx_ctl utc{"utc"};
	sc_signal<sc_uint<8>> utc_buffer[32];
	sc_signal<bool> utc_trigger;
	sc_signal<bool> utc_busy;
	sc_signal<sc_uint<8>> utc_size;

	SC_CTOR(uart_test_top)
	{
		bit_rate.in(clk);
		bit_rate.rst(rst);
		bit_rate.cfg(cfg_bit_rate);
		bit_rate.out(out_bit_rate);

		ut.clk(out_bit_rate);
		ut.rst(rst);
		ut.en(en);
		ut.data(data);
		ut.tx(uart_txd);
		ut.busy(busy);

		utc.baud(out_bit_rate);
		utc.rst(rst);
		utc.busy_tx(busy);
		utc.en_tx(en);
		utc.data_tx(data);
		for(int i=0;i<32;i++)
			utc.buffer[i](utc_buffer[i]);
		utc.trigger(utc_trigger);
		utc.busy(utc_busy);
		utc.size(utc_size);

		SC_THREAD(run);
		sensitive << clk.pos();
		async_reset_signal_is(rst,0);

		SC_THREAD(baud_run);
		sensitive << out_bit_rate.posedge_event();
		async_reset_signal_is(rst,0);
	}
	void run()
	{
		cfg_bit_rate = 217;
		while(1)
		{
			wait();
		}
	}

	sc_signal<bool> key_old[4];
	void baud_run()
	{
		data = 0;
		en = 0;

		key_old[0] = 0;
		key_old[1] = 0;
		key_old[2] = 0;
		key_old[3] = 0;
		while(1)
		{

			wait();

			if(key[0] != key_old[0])
			{
				if(key[0] == 0)
				{
					data = 65;
					en = 1;
					wait();
					en = 0;
				}
				else
				{
					data = 66;
					en = 1;
					wait();
					en = 0;
				}
			}

			key_old[0] = key[0];
			key_old[1] = key[1];
			key_old[2] = key[2];
			key_old[3] = key[3];

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

	sc_signal<bool> tx,rx,key[4];
	uart_test_top utt{"utt"};
	utt.clk(clk);
	utt.rst(rst);
	utt.uart_txd(tx);
	utt.uart_rxd(rx);
	utt.key[0](key[0]);
	utt.key[1](key[1]);
	utt.key[2](key[2]);
	utt.key[3](key[3]);

	rst = 1;
	sc_start(1,SC_NS);

	rst = 0;
	sc_start(1,SC_NS);

	rst = 1;

    sc_start(10000,SC_NS);
    return 0;
}

