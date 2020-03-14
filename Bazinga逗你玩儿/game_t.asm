 .model	small
.386
data	segment
	ad59	equ	20h
	ad55	equ	210h
	ad53	equ	220h		;芯片选址
	ad09	equ	200h
	adled	equ	230h
	scale	equ	04h
	level	db	0
	N2		equ	1000		;控制延时，N1*N2
	temp	dw	?
	count	db	?			;用于保存ADC结果
	ledcode	db	3fh,	06h,	5bh,	4fh,	66h,	6dh,	7dh,	07h,	7fh,	67h,	77h,	7ch,	39h,	5eh,	79h,	71h

data	ends
ss_seg	segment
	dw	100	dup(?)
ss_seg	ends
;中断有错
code	segment
	assume	cs:code,	ds:data,	ss:ss_seg
	main	proc	far
	mov	ax,	data
	mov	ds,	ax
	cli						;关中断
	;芯片初始化
	call	INIT8255
	call	INIT8253
	call	INTVECT
	sti
	;test
						;开中断
	LOOP3:
	jmp	LOOP3			;动态停机
	
	mov	ax,	4c00h
	int	21h
	main	endp

INIT8255	proc
	mov	al,	90h;CW，A口输入，BC口输出，方式0.
	mov	dx,	ad55+3
	out	dx,	al
	ret
INIT8255	endp

INIT8253	proc
	mov	al,	16h
	mov	dx,	ad53+3
	out	dx,	al		;CNT0,方波，BCD码计数，只读低字节
	ret
INIT8253	endp

INTVECT	proc
	;设置主片中断屏蔽字
	in	al,	ad59+1		;8259地址
	and	al,	11011111b		;仅IR5有效
	out	ad59+1,	al
	;设置中断向量表
	push	ds
	mov	ax,	0			;不能直接对reg赋值
	mov	ds,	ax
	lea	ax,	cs:	INT1		;获取中断服务程序地址
	mov	si,	35H			;中断类型码
	mov	cl,	2
	shl	si,	cl			;入口地址物理地址
	mov	ds:[si],	ax		;入口地址内容是子程序地址
	push	cs				;cs不能做源操作数，所以要用堆栈
	pop	ax
	mov	ds:[si+2],	ax		;中断向量表的cs值
	pop	ds				;恢复ds
	ret
INTVECT	endp

delay1s	proc				;主频是多大不重要
	mov	al,	count
	mov	ah,	scale
	mul	ah
	mov	cx,	ax
	LOOP1:
	mov	temp,	cx
	mov	cx,		N2
	LOOP2:
	nop
	nop
	loop	LOOP2
	mov	cx,	temp
	loop	LOOP1
	ret
delay1s	endp

sound	proc
	mov	dx,	ad55+1
	in	al,	dx
	or	al,	01h
	out	dx,	al	;PB0=1
	ret
sound	endp

change1	proc
	call	ADC_con
	mov	dx,	ad53
	mov	al,	count
	out	dx,	al
	ret
change1	endp

stop	proc
	mov	dx,	ad55+1
	in	al,	dx
	and	al,	0FEh
	out	dx,	al	;PB0=0
	ret
stop	endp

INT1	proc	far
	;保护现场
	push	ax
	push	cx
	push	dx
	push	si
	push	bx
	call	change1		;由电位器控制音调
	call	level_pro
	call	disp
	call	delay1s
	
	mov	dx,	ad55
	in	al,	dx		;读PA数据
	and	al,	01H
	cmp	al,	01h
	je	stop1				;为1，不发声
	call	sound	
	jmp	next
	stop1:
	call	stop		
	next:
	;EOI
	mov	al,	20h
	mov	dx,	ad59
	out	dx,	al	
	;恢复现场
	pop	bx
	pop	si
	pop	dx
	pop	cx
	pop	ax
	iret
INT1	endp
ADC_con	proc				;转换结果存于count.电位器建议参数：1.2v-4v
	;启动ADC
	mov	dx,	ad09
	out	dx,	al
	;EOC
	mov	dx,	ad09+2
	l1:
	;读状态，判断转换完成与否
	in	al,	dx
	test	al,	01h
	jz	L1
	;读数据
	mov	dx,	ad09+1
	in	al,	dx
	mov	count,	al
	;CPU等待
	nop
	nop
	ret
ADC_con	endp

level_pro	proc
	mov	ax,	0
	mov	al,	count
	mov	bl,	100
	div	bl
	mov	level,	al
	mov	al,	03h
	sub	al,	level
	mov	level,	al
	ret
level_pro	endp

disp	proc
	lea	si,	ledcode
	mov	bx,	si
	mov	ah,	0
	add	bx,	ax
	mov	al,	[bx]
	mov	dx,	adled
	out	dx,	al
	mov	al,	02h
	inc	dx
	nop	
	out	dx,	al
	nop
	nop	
	ret
disp	endp

code	ends
end	main
