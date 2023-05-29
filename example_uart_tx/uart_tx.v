module uart_tx(input clk, input rst, input en, input [7:0] data, output reg tx, output reg busy);

reg [3:0] status;

assign busy = (status == 0) ? 0 : 1;

always@(posedge clk or negedge rst) begin
	if(rst == 0) begin
		tx <= 1;
		status <= 0;
		status <= 3;
	end else begin

		case(status)

			0: begin
				if(en) begin
					tx <= 0;
					status <= 1;
				end else begin
					tx <= 1;
					status <= 0;
				end
			end

			1: begin
				tx <= data[0];
				status <= 2;
			end

			2: begin
				tx <= data[1];
				status <= 3;
			end

			3: begin
				tx <= data[2];
				status <= 4;
			end

			4: begin
				tx <= data[3];
				status <= 5;
			end

			5: begin
				tx <= data[4];
				status <= 6;
			end

			6: begin
				tx <= data[5];
				status <= 7;
			end

			7: begin
				tx <= data[6];
				status <= 8;
			end

			8: begin
				tx <= data[7];
				status <= 9;
			end

			9: begin
				tx <= 1;
				status <= 0;
			end

		endcase

	end
end

endmodule
