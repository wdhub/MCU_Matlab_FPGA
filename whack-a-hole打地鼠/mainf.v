module mainf(//input clk1s,
			input [1:0] seq,
			input stop,
			input clr,
			input [1:0] button,
			output reg [6:0] disp_s0,
			output reg [6:0] disp_g0,
			output reg [6:0] disp_s1,
			output reg [6:0] disp_g1,
			output	led_t);

reg [3:0] s0,g0,s1,g1;//计数器输出的十位和个位
wire	result_0,	result_1;//判断是否在灯亮起且及时还未结束时击中

assign result_0=seq[0]&button[0]&(!stop);//仅当按下按键与指示序列分别对应时，result_0才为1.
assign led_t=button[1];
assign result_1=seq[1]&button[1]&(!stop);//仅当按下按键与指示序列分别对应时，result_1才为1.

always@(posedge result_1,negedge clr)//Mode-60记录得分。result1来一个上升沿，得一分。最多60分。
     begin
        if(!clr)
          begin
           s1<=4'h0;
           g1<=4'h0;
          end 
        else
           if (g1==4'h9)
            begin
              g1<=4'h0; 
              if (s1==4'h5)
                 begin
					s1<=4'h0;
				 end
              else
                 s1<=s1+1'b1; 
            end
           else
             g1<=g1+1'b1; 
     end

always@(s1)//display decoder
 begin
   case(s1)
   	4'h0:disp_s1<=7'b1000000;
   	4'h1:disp_s1<=7'b1111001;
	4'h2:disp_s1<=7'b0100100;
	4'h3:disp_s1<=7'b0110000;
	4'h4:disp_s1<=7'b0011001;
	4'h5:disp_s1<=7'b0010010;
	4'h6:disp_s1<=7'b0000010;
	4'h7:disp_s1<=7'b1111000;
	4'h8:disp_s1<=7'b0000000;
	4'h9:disp_s1<=7'b0010000;
    default:disp_s1<=7'b1111111;
    endcase
 end
always@(g1)//display decoder
 begin
   case(g1)
   	4'h0:disp_g1<=7'b1000000;
   	4'h1:disp_g1<=7'b1111001;
	4'h2:disp_g1<=7'b0100100;
	4'h3:disp_g1<=7'b0110000;
	4'h4:disp_g1<=7'b0011001;
	4'h5:disp_g1<=7'b0010010;
	4'h6:disp_g1<=7'b0000010;
	4'h7:disp_g1<=7'b1111000;
	4'h8:disp_g1<=7'b0000000;
	4'h9:disp_g1<=7'b0010000;
    default:disp_g1<=7'b1111111;
    endcase 
 end
always@(posedge result_0,negedge clr)//Mode-60记录得分。result0来一个上升沿，得一分。最多60分。
     begin
        if(!clr)
          begin
           s0<=4'h0;
           g0<=4'h0;
          end 
        else
           if (g0==4'h9)
            begin
              g0<=4'h0; 
              if (s0==4'h5)
                 begin
					s0<=4'h0;
				 end
              else
                 s0<=s0+1'b1; 
            end
           else
             g0<=g0+1'b1; 
     end

always@(s0)//display decoder
 begin
   case(s0)
   	4'h0:disp_s0<=7'b1000000;
   	4'h1:disp_s0<=7'b1111001;
	4'h2:disp_s0<=7'b0100100;
	4'h3:disp_s0<=7'b0110000;
	4'h4:disp_s0<=7'b0011001;
	4'h5:disp_s0<=7'b0010010;
	4'h6:disp_s0<=7'b0000010;
	4'h7:disp_s0<=7'b1111000;
	4'h8:disp_s0<=7'b0000000;
	4'h9:disp_s0<=7'b0010000;
    default:disp_s0<=7'b1111111;
    endcase
 end
always@(g0)//display decoder
 begin
   case(g0)
   	4'h0:disp_g0<=7'b1000000;
   	4'h1:disp_g0<=7'b1111001;
	4'h2:disp_g0<=7'b0100100;
	4'h3:disp_g0<=7'b0110000;
	4'h4:disp_g0<=7'b0011001;
	4'h5:disp_g0<=7'b0010010;
	4'h6:disp_g0<=7'b0000010;
	4'h7:disp_g0<=7'b1111000;
	4'h8:disp_g0<=7'b0000000;
	4'h9:disp_g0<=7'b0010000;
    default:disp_g0<=7'b1111111;
    endcase 
 end
endmodule