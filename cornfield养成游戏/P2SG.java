package testGame03;
public class P2SG extends	Page02{
	public	void	setUp() {
		normalFace="F:\\Download\\Java\\TestGame03\\images\\SG\\normal_sg.png";
		wayOfWork="给饺子店送外卖";
		name="爽哥";
		p1=new	People();
		p1.initial();
		p3w.nameOfPic="F:\\Download\\Java\\TestGame03\\images\\SG\\win_sg.jpg";
		String	r1="爽哥逐渐积累起了资金与人脉。";
		String	r2="开了一家饺子健身馆、健身餐饮一条龙？";
		String	r3="恭喜爽哥！";
		p3w.showResult="<html><body>"+r1+"<br>"+r2+"<br>"+r3+"<body></html>";
		p3d.nameOfPic="F:\\Download\\Java\\TestGame03\\images\\SG\\sad_sg.jpg";
		String	r4="爽哥你都养不活。";
		String	r5="真是一手好牌，打得稀烂。";
		p3d.showResult="<html><body>"+r4+"<br>"+r5+"<body></html>";
		
		showState[1]="还没选择价格";
		showState[0]="爽哥刚出西门就遇到了交通管制，又推着车回来了。";
		showState[2]="爽哥从西山揽胜下来，觉得非常休闲。";
		showState[3]="爽哥约到了松林环旅顺。";
		showFace[1]=normalFace;
		showFace[0]=p3d.nameOfPic;
		showFace[2]="F:\\Download\\Java\\TestGame03\\images\\SG\\happy_sg.png";
		showFace[3]=showFace[2];
		
		showTitle="玉米地";
	}
	
}
