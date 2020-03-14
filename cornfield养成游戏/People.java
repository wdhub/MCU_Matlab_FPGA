package testGame03;


public class People {
	private	int		Money;
	private	int		Live;
	private	boolean	isLiving;
	private	boolean	win;
	private	boolean	isBroke;
	public	int		card;
	public	int		price;
	public	int		delta;
	public	void	initial() {
		Money=Info.initialM;
		Live=Info.initialL;
		isLiving=true;
		win=false;
		isBroke=false;
		card=0;
		price=0;
		delta=0;
	}
	public	int		getMoney() {
		return	Money;
	}
	public	int		getLive() {
		return	Live;
	}
	public	boolean	decideLive() {
		if(Live<=0) {
			isLiving=false;
		}
		return	isLiving;
	}
	public	boolean	decideWin() {
		if(Live>=Info.winThread) {
			win=true;
		}
		return	win;
	}
	public	boolean	decideBroke() {
		if(Money<=0) {
			isBroke=true;
		}
		return	isBroke;
	}
	public	int	FEED() {
		int	fb=1;
		int[]	array= {-1,2,5};
		int rnd=(int)(Math.random() * 2);
		card=array[rnd];
		delta=card*price;
		Live+=delta;
		Money-=price;
		price=0;
		if(delta>0) {
			if(delta>=10) 
				fb=3;
			else
				fb=2;	
		}
		else {
			if(delta==0)
				fb=1;
			else
				fb=0;
		}
		return	fb;
	}
	public	void	WORK() {
		Live--;
		Money++;
	}
	
}

