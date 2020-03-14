package version01_1;

import java.awt.*;
import java.awt.event.*;
import java.awt.geom.Line2D;
import java.util.*;

import javax.swing.*;

public class GUI {
	JFrame	frame;
	JButton	buttonC;
	JPanel	panel;
	JPanel	container;
	JLabel	labelT;
	JLabel	labelC;
	Thread	t;
	LineListener	liner;
	static	Player		player;
	public	void	initial() {
		player=new	Player();
		player.initial();
	}
	public	void	go() {
		frame=new	JFrame();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setSize(Info.sizeGame, Info.sizeGame);
		frame.setVisible(true);
		
		buttonC=new	JButton("connect");
		buttonC.addActionListener(new ConnectListener());
		
		labelT=new	JLabel("time: "+(100-player.getTime())/10);
		labelC=new	JLabel("");
		
		container=new	JPanel();
		container.add(labelT);
		container.add(labelC);
	
		panel=new	JPanel();
		panel.setBackground(Color.WHITE);
		Dimension preferredSize=new	Dimension(Info.sizeLimit,Info.sizeLimit);
		panel.setPreferredSize(preferredSize);
		liner=new	LineListener();
		panel.addKeyListener(liner);
		panel.setFocusable(true);

		frame.getContentPane().add(BorderLayout.NORTH,panel);
		frame.getContentPane().add(BorderLayout.SOUTH,buttonC);
		frame.getContentPane().add(BorderLayout.WEST,container);
	}
	public	class	ConnectListener	implements	ActionListener{
		public	void	actionPerformed(ActionEvent	event) {
		
		}
	}
	public	class	LineListener	implements	KeyListener{
		public void keyPressed(KeyEvent e) {
			if(t!=null)
				t.interrupt();
		}
		
		public void keyReleased(KeyEvent e) {
			if(!player.returnFlag()) {
				t=new	Thread(new Job4line(e.getKeyCode()));
				t.start();
			}
		}
		public void keyTyped(KeyEvent arg0) {
		}
	}
	public class Job4line implements	Runnable{
		private	int	code;
		public	Job4line(int code) {
			this.code=code;
		}
		public void	run() {
			try {
				String	condition="alive";
				while(true) {
					int[]	x=new	int[4];
					int	x1=player.getTrace().get(player.getTrace().size()-1)[2];//start from the end of last line
					int	y1=player.getTrace().get(player.getTrace().size()-1)[3];
					x[0]=x1;
					x[1]=y1;
					x[2]=x[0];
					x[3]=x[1];
					switch(code) {
					case KeyEvent.VK_DOWN:x[3]=x[1]+5;break;
					case KeyEvent.VK_UP:x[3]=x[1]-5;break;
					case KeyEvent.VK_RIGHT:x[2]=x[0]+5;break;
					case KeyEvent.VK_LEFT:x[2]=x[0]-5;break;
					default:break;
				}
					if(player.ishitted(x)) {
						condition="hitted the frame!";
						labelC.setText(condition);
						break;
					}
					if(player.isbitten(x, player.getTrace())) {
						condition="bitten by yourself!";
						labelC.setText(condition);
						break;
					}
					if(player.timeUp()){
						condition="time's up!";
						labelC.setText(condition);
						break;
					}
					Graphics	pen=panel.getGraphics();
					pen.drawLine(x[0], x[1], x[2], x[3]);
					int	temp=(100-player.getTime())/10;
					labelT.setText("time: "+temp);
					
					player.addTrace(x);
					player.addTime();//sleeps once adds once
					
					Thread.sleep(50);
				}
			} catch (InterruptedException e) {
				
			}
			
		}

	}	
}
