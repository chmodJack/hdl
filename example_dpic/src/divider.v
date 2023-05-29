module divider(input clk, input rst, input [7:0] div, output reg out);

reg [7:0] cnt;

always@(posedge clk or negedge rst)
begin
	if(rst == 0)
	begin
		out <= 0;
		cnt <= 0;
	end
	else
	begin
		cnt <= cnt + 1;
		if(cnt == div)
		begin
			out <= ~out;
			cnt <= 0;
		end
	end
end

endmodule
