module timer_60s(input clk,input clr,
     output reg [6:0] p,
     output reg [6:0] q,
	 output	reg carry,
	 output reg clk1s,
	 output reg clk100ms,
	 output reg clk200ms);//toggle once every second
	
reg	[21:0]	num1;
reg	[2:0]	num2;
//reg	[21:0]	num3;
reg [3:0] 	s,g;

always@(posedge clk100ms,negedge clr)//divider。得到200ms信号
     begin
        if(!clr)
           clk200ms<=1'b0;
        else
			clk200ms<=~clk200ms;
     end

 always@(posedge clk,negedge clr)//divider。得到100ms信号
     begin
        if(!clr)
          begin
           num1<=0;
           clk100ms<=1'b0;
          end 
        else
           if (num1<2499999)//24999999
             num1<=num1+1'b1; 
           else
             begin
              num1<=0;   
              clk100ms<=~clk100ms;
             end 
     end

always@(posedge clk100ms,negedge clr)//divider。得到1s信号
     begin
        if(!clr)
          begin
           num2<=0;
           clk1s<=1'b0;
          end 
        else
           if (num2<4)
             num2<=num2+1'b1; 
           else
             begin
              num2<=0;   
              clk1s<=~clk1s;
             end 
     end

always@(posedge clk1s,negedge clr)//Mode-60
     begin
        if(!clr)
          begin
           s<=4'h0;
           g<=4'h0;
		   carry<=1'b0;
          end 
        else
           if (g==4'h9)
            begin
              g<=4'h0; 
              if (s==4'h5)
                 begin
					s<=4'h0;
					carry<=1'b1;
				 end
              else
                 s<=s+1'b1; 
            end
           else
             g<=g+1'b1; 
     end

always@(s)//display decoder
 begin
   case(s)
   	4'h0:p<=7'b1000000;
   	4'h1:p<=7'b1111001;
	4'h2:p<=7'b0100100;
	4'h3:p<=7'b0110000;
	4'h4:p<=7'b0011001;
	4'h5:p<=7'b0010010;
	4'h6:p<=7'b0000010;
	4'h7:p<=7'b1111000;
	4'h8:p<=7'b0000000;
	4'h9:p<=7'b0010000;
    default:p<=7'b1111111;
    endcase
 end
always@(g)
 begin
   case(g)
   	4'h0:q<=7'b1000000;
   	4'h1:q<=7'b1111001;
	4'h2:q<=7'b0100100;
	4'h3:q<=7'b0110000;
	4'h4:q<=7'b0011001;
	4'h5:q<=7'b0010010;
	4'h6:q<=7'b0000010;
	4'h7:q<=7'b1111000;
	4'h8:q<=7'b0000000;
	4'h9:q<=7'b0010000;
    default:q<=7'b1111111;
    endcase 
 end

endmodule