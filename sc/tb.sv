module tb();

////////////////////////////////////////////////////////////////////////////////////

logic clk;
logic rst;

top t(clk,rst);

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

