package testGame03;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public abstract class Page03{
		String	nameOfPic;
		String	showResult;
		JFrame	frame;
		JLabel	title;
		JLabel	face;
		JButton	button;
		JLabel	result;
		JPanel	panelC;
		JPanel	panelW;
		JPanel	panelS;
		public	void	go() {
			frame=new	JFrame();
			frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
			frame.setSize(500, 500);
			frame.setVisible(true);
			
			ImageIcon	image= new ImageIcon(nameOfPic);
			face=new	JLabel(image);
			result=new	JLabel(showResult);
			panelC=new	JPanel();
			panelC.setLayout(new BoxLayout(panelC, BoxLayout.Y_AXIS));
			panelC.add(result);
			panelC.add(face);
			
			title=new	JLabel(Info.title);
			panelW=new	JPanel();
			panelW.add(title);
			
			button=new	JButton("再来一局");
			button.addActionListener(new	Listener());
			panelS=new	JPanel();
			panelS.add(button);
			
			frame.getContentPane().add(BorderLayout.CENTER,panelC);
			frame.getContentPane().add(BorderLayout.WEST,panelW);
			frame.getContentPane().add(BorderLayout.SOUTH,panelS);
		}
		public	class	Listener	implements	ActionListener{
			public void actionPerformed(ActionEvent event) {
				Page01 p1 = new Page01 ();
				frame.setVisible(false);
				p1.go();
				
				}
		}
		
}
