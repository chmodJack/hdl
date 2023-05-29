module tb();

////////////////////////////////////////////////////////////////////////////////////

logic clk;
logic rst;

logic [31:0] max;
logic [31:0] cnt;
logic carry;
counter cn(clk,rst,max,cnt,carry);

logic is_p;
is_prime ip(cnt,is_p);

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

