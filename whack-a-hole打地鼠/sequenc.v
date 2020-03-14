module sequenc
	(input clk1s,
	 input clr,
     output reg [1:0] seq);
//wire	temp;
//reg	led;
reg	[19:0] num;
//assign	temp=num[0]&num[19];//用来找毛刺，但是没找出来。
//assign	led_t=led;
always@(posedge clk1s,negedge clr)
//先用一串固定序列代替随机序列，再把伪随机序列生成模块实例化.序列直接控制二极管亮灭。序列每一秒变化一次。
begin	
	if(!clr)
		begin
		num<=20'b10011000100010011001;//10011000100010011001
		
		end
	else
		begin
		num<={num[0],num[19:1]};//循环右移序列，以最高两位做提示信号
		seq[0]<=num[19];
		seq[1]<=seq[0];
		end
end
//always@(posedge temp,negedge clr)
//begin	
//	if(!clr)
//		led<=0;
//	else
//		led<=~led;
//end
	
endmodule