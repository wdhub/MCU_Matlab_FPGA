package testGame03;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public	class	Page01{
JFrame	frame;
JButton	button1;
JButton	button2;
JButton	button3;
JButton	button4;
JPanel	panelC;
JPanel	panelW;
JLabel	title;
JLabel	label;
JLabel	intro1;
JLabel	intro2;
JLabel	intro3;
JLabel	intro4;

public	void	go() {
	frame=new	JFrame();
	frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	frame.setSize(500, 500);
	frame.setVisible(true);
	
	button1=new	JButton("爽哥");
	button1.addActionListener(new B1Listener());
	button2=new	JButton("会旗");
	button2.addActionListener(new B2Listener());
	button3=new	JButton("辣条");
	button3.addActionListener(new B3Listener());
	button4=new	JButton("成为游戏角色");
	button4.addActionListener(new B4Listener());
	
	panelC=new	JPanel();
	panelW=new	JPanel();
	
	title=new	JLabel(Info.title);
	ImageIcon	image=new	ImageIcon(Info.logo);
	label = new JLabel(image);
	
	intro1=new	JLabel(Info.introSG);
	intro2=new	JLabel(Info.introHQ);
	intro3=new	JLabel(Info.introLT);
	intro4=new	JLabel("");

	panelC.setLayout(new BoxLayout(panelC, BoxLayout.Y_AXIS));
	panelC.add(label);
	panelC.add(button1);
	panelC.add(intro1);
	panelC.add(button2);
	panelC.add(intro2);
	panelC.add(button3);
	panelC.add(intro3);
	panelC.add(button4);
	panelC.add(intro4);
	panelW.add(title);
	
	frame.getContentPane().add(BorderLayout.CENTER,panelC);
	frame.getContentPane().add(BorderLayout.WEST,panelW);
	//frame.getContentPane().add(BorderLayout.NORTH,label);
}
public	class	B1Listener	implements	ActionListener{
	public	void	actionPerformed(ActionEvent	event) {
		P2SG	p2=new	P2SG();
		p2.turn2P3();//initial page03 
		p2.setUp();//some character-specific layouts and create the character
		frame.setVisible(false);
		p2.go();//interface of page02
	}
}
public	class	B2Listener	implements	ActionListener{
	public	void	actionPerformed(ActionEvent	event) {
		P2HQ	p2=new	P2HQ();
		p2.turn2P3();
		p2.setUp();
		frame.setVisible(false);
		p2.go();
	}
}
public	class	B3Listener	implements	ActionListener{
	public	void	actionPerformed(ActionEvent	event) {
			P2LT	p2=new	P2LT();
			p2.turn2P3();
			p2.setUp();
			frame.setVisible(false);
			p2.go();
		}
}
public	class	B4Listener	implements	ActionListener{
	public	void	actionPerformed(ActionEvent	event) {
			intro4.setText("没有！充钱！");
		}
}
}
