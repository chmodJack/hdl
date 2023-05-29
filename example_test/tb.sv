module tb();

////////////////////////////////////////////////////////////////////////////////////

logic clk;
logic rst;

//logic en,tx,busy;
//logic [7:0] data;
//uart_tx ut(clk,rst,en,data,tx,busy);

logic [7:0] data_i;
logic [7:0] data_o;
logic en_r;
logic en_w;
logic ack_r;
logic ack_w;
logic full;
logic empty;

fifo ff(clk,rst,data_i,en_r,en_w,data_o,full,empty,ack_r,ack_w);

////////////////////////////////////////////////////////////////////////////////////

initial begin
	$fsdbDumpfile("tb.fsdb");
	$fsdbDumpvars("+all");
	$fsdbDumpSVA();
	$fsdbDumpMDA();

	#1 rst <= 1;
	#1 rst <= 0;
	#1 rst <= 1;
	#1 clk <= 0;

	forever	begin
		#1 clk <= ~clk;
	end
end

endmodule

