module tb();

////////////////////////////////////////////////////////////////////////////////////

logic clk;
logic rst;
logic rx,en,busy;
logic [7:0] data;

uart_rx ur(clk,rst,rx,en,busy,data);

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

