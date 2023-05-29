#include <systemc.h>

struct uart_tx: sc_module
{
	sc_in<bool> clk;
	sc_in<bool> rst;

	sc_in<bool> en;
	sc_in<sc_uint<8>> data;

	sc_out<bool> tx;
	sc_out<bool> busy;

	SC_CTOR(uart_tx)
	{
		SC_THREAD(run);
		sensitive << clk.pos() << rst.neg();

		async_reset_signal_is(rst,0);
	}
	void run()
	{
		tx = 1;
		busy = 0;

		while(1)
		{
			wait();

			if(en)
			{
				busy = 1;
				tx = 0;	wait();
				tx = data.read()[0]; wait();
				tx = data.read()[1]; wait();
				tx = data.read()[2]; wait();
				tx = data.read()[3]; wait();
				tx = data.read()[4]; wait();
				tx = data.read()[5]; wait();
				tx = data.read()[6]; wait();
				tx = data.read()[7]; wait();
				tx = 1;busy = 0;
			}
		}
	}
};
 
struct fifo: sc_module
{
	sc_in<bool> clk;
	sc_in<bool> rst;

	sc_in<sc_uint<8>> data_i;

	sc_in<bool> en_r;
	sc_in<bool> en_w;

	sc_out<sc_uint<8>> data_o;

	sc_out<bool> full;
	sc_out<bool> empty;

	sc_out<bool> ack_r;
	sc_out<bool> ack_w;

	sc_uint<8> buffer[8];
	uint8_t head;
	uint8_t tail;

	SC_CTOR(fifo)
	{
		SC_THREAD(run);
		sensitive << clk.pos() << rst.neg();

		async_reset_signal_is(rst,0);
	}

	void run()
	{
		data_o = 0;
		full = 0;
		empty = 1;
		ack_r = 0;
		ack_w = 0;

		head = 0;
		tail = 0;

		for(int i=0;i<8;i++)
			buffer[i] = 0;

		while(1)
		{
			wait();

			if(en_r && not empty)
			{
				data_o = buffer[head];
				head = head + 1;

				if(head == 8)
					head = 0;

				if(head == tail)
					empty = 1;

				ack_r = 1;
				full = 0;
			}
			else
			{
				ack_r = 0;
			}

			if(en_w && not full)
			{
				buffer[tail] = data_i;
				tail = tail + 1;

				if(tail == 8)
					tail = 0;

				if(tail == head)
					full = 1;

				ack_w = 1;
				empty = 0;
			}
			else
			{
				ack_w = 0;
			}
		}
	}
};

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
#undef BIND
    }

	void run()
	{
		rst = 1;
		wait();
		rst = 0;
		wait();
		rst = 1;
		wait();
		while(1)
		{
			clk = !clk;
			wait();
		}
	}
};
 
int sc_main (int argc, char **argv) 
{
    top top_inst("top_inst");
    sc_start();
    return 0;
}
