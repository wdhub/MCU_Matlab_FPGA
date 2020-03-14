module demo
	(input clk,
	 input clr,
	 input [1:0] button,
     output [6:0] disp1_s,
     output [6:0] disp1_g,
	 output [6:0] disp2_s,
     output [6:0] disp2_g,
	 output [6:0] disp3_s,
     output [6:0] disp3_g,
	 output	[1:0] led,
	 output	led_t);

wire carry;
wire clk1s;
wire	[1:0] test_seq;
reg temp;
wire clk100ms;
reg	clk2s;
wire	clk200ms;
wire	[1:0]	button_d;

//assign	led_t=button[0];//测试压敏电阻

always@(posedge clk1s,negedge clr)//4s counting
     begin
        if(!clr)
			clk2s<=1'b0;
        else
            clk2s<=~clk2s; 	
     end

assign	led[0]=test_seq[0];
assign	led[1]=test_seq[1];
assign	led_t=button_d[1];
tremble	ic5(.clk(clk100ms),.button(button),.clr(clr),.button_d(button_d));//去抖模块，输入10ms的clk,原button信号，输出去抖button信号
//sequenc	ic4(.clk1s(clk1s),.clr(clr),.seq(test_seq));//随机序列产生模块，输入clk,输出两位的seq序列
sequenc2 ic3(.clk(clk1s),.clr(clr),.seq(test_seq));//利用毛刺随机序列产生模块，输入clk,输出两位的seq序列。没有毛刺。。。
timer_60s ic1(.clk(clk),.clr(clr),.p(disp1_s),.q(disp1_g),.carry(carry),.clk1s(clk1s),.clk100ms(clk100ms),.clk200ms(clk200ms));
//时钟，输入clk,clr,输出数码管1（个位十位），1s信号
mainf ic2(.seq(test_seq),.stop(carry),.clr(clr),.button(button_d),
		 .disp_s0(disp2_s),.disp_g0(disp2_g),.disp_s1(disp3_s),.disp_g1(disp3_g));

endmodule