module counter(input clk, input rst, input [7:0] max, output reg [7:0] out);

always@(posedge clk or negedge rst)
begin
	if(rst == 0)
		out <= 0;
	else
	begin
		out <= out + 1;
		if(out == max)
			out <= 0;
	end
end

endmodule
