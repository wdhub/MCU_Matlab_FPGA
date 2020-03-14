package testGame03;

public class P2HQ extends	Page02{
	public	void	setUp() {
		normalFace="F:\\Download\\Java\\TestGame03\\images\\HQ\\normal_hq.png";
		wayOfWork="翻译外文书赚外快";
		name="会旗";
		p1=new	People();
		p1.initial();
		p3w.nameOfPic="F:\\Download\\Java\\TestGame03\\images\\HQ\\win_hq.png";
		String	r1="会旗获得了诺贝尔翻译学奖。";
		String	r2="一个专门为她的翻译作品设立的奖项。";
		String	r3="真是开山之举！";
		p3w.showResult="<html><body>"+r1+"<br>"+r2+"<br>"+r3+"<body></html>";
		p3d.nameOfPic="F:\\Download\\Java\\TestGame03\\images\\HQ\\sad_hq.png";
		String	r4="会旗弃你而去了。";
		String	r5="真是一手好牌，打得稀烂。";
		p3d.showResult="<html><body>"+r4+"<br>"+r5+"<body></html>";
		
		showState[1]="还没选择价格";
		showState[0]="会旗放稿件的U盘炸了";
		showState[2]="会旗看了一部好看的电影";
		showState[3]="在一个下雪的早上，会旗窝在伯川读完了一本好书";
		showFace[1]=normalFace;
		showFace[0]=p3d.nameOfPic;
		showFace[2]="F:\\Download\\Java\\TestGame03\\images\\HQ\\happy_hq.png";
		showFace[3]=showFace[2];
		
		showTitle="玉米地";
	}
	
}

