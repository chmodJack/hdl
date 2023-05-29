module tb();

reg clk;
reg rst;

////////////////////////////////////////////////////////////////////////////////////

reg en;
reg [7:0] data;
reg tx;
reg busy;

uart_tx ut(clk,rst,en,data,tx,busy);

initial begin
	data <= 0;
	en <= 0;
end

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
