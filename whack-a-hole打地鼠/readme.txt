硬件环境：	Altera DE2 Board
核心芯片：	CYCLONE II FPGA
引脚数目：	672
运行速度：	6
软件环境：	QUARTUS II
编程语言：	Verilog HDL
其他描述：	数字电路课程设计作品，作品名“打地鼠”。硬件电路由传感器模块和FPGA组成。60s打中多少次地鼠，得多少分。
文件目录：	demo.v		主程序
		tremble.v		防抖模块
		sequenc2.v	随机序列生成器
		timer_60s.v	计时器
		mainf.v		计分器


Hardware environment：	Altera DE2 Board
Core chip：		CYCLONE II FPGA
No. of pins：		672
Speed：			6
Software envoronment：	QUARTUS II
Language：		Verilog HDL
description：	This a game named WHACK-A-HOLE, built on digital circuit, sensor block and FPGA included. The more you hit in 60s, the higher point you got.
file menu：	demo.v		main
		tremble.v		trembling-handler, used as A/D
		sequenc2.v	random sequence generator
		timer_60s.v	timer-counter
		mainf.v		point-counter


	
