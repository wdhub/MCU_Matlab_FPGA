package testGame03;

public class P2LT extends	Page02{
	public	void	setUp() {
		normalFace="F:\\Download\\Java\\TestGame03\\images\\LT\\normal_LT.jpg";
		wayOfWork="化物所搬砖";
		name="辣条";
		p1=new	People();
		p1.initial();
		p3w.nameOfPic="F:\\Download\\Java\\TestGame03\\images\\LT\\win_LT.jpg";
		String	r1="靠着往日的积累，";
		String	r2="辣条登山了14座海拔8000米以上的高峰。";
		String	r3="人称“辣十四”。";
		p3w.showResult="<html><body>"+r1+"<br>"+r2+"<br>"+r3+"<body></html>";
		p3d.nameOfPic="F:\\Download\\Java\\TestGame03\\images\\LT\\sad_LT.jpg";
		String	r4="辣条你都养不活。";
		String	r5="真是一手好牌，打得稀烂。";
		p3d.showResult="<html><body>"+r4+"<br>"+r5+"<body></html>";
		
		showState[1]="还没选择价格";
		showState[0]="导师突然打电话给辣条，语气非常不妙";
		showState[2]="辣条打了一盘游戏";
		showState[3]="辣条r发现了一条有趣的徒步线路";
		showFace[1]=normalFace;
		showFace[0]=p3d.nameOfPic;
		showFace[2]="F:\\Download\\Java\\TestGame03\\images\\LT\\happy_LT.jpg";
		showFace[3]=showFace[2];
		
		showTitle="苞米地";
		
	}
	
}

