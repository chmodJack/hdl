module tb();

reg clk;
reg rst;
reg [7:0] data[2];

////////////////////////////
reg [7:0] a,b,c;

adder ad(a,b,c);

initial
begin
	a = 6;
	b = 3;
end
////////////////////////////

import "DPI-C" function void dpic_init(input bit [7:0] in, output bit [7:0] out);
import "DPI-C" function void dpic_tick(input bit [7:0] in, output bit [7:0] out);

initial
begin
	$fsdbDumpfile("tb.fsdb");
	$fsdbDumpvars("+all");
	$fsdbDumpSVA();
	$fsdbDumpMDA();

	dpic_init(data[0],data[1]);

	clk = 0;
	rst = 1;
	#1;
	clk = 0;
	rst = 0;
	#1;
	clk = 0;
	rst = 1;
end

//clock
initial
begin
	forever
	begin
		#1;
		clk <= 0;
		#1;
		clk <= 1;
		dpic_tick(data[0],data[1]);
	end
end

endmodule
