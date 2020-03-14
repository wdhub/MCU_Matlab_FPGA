package testGame03;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;

public abstract	class Page02{
	People	p1;
	P3Die	p3d;
	P3Win	p3w;
	String	normalFace;
	String	wayOfWork;
	String	name;
	String	showTitle;
	int		feedback;
	String[]	showState=new	String[4];
	String[]	showFace=new	String[4];
	
	JFrame	frame;
	JLabel	title;
	JLabel	rules;
	JLabel	state;
	JLabel	currentLive;
	JLabel	currentMoney;
	JLabel	face;
	JLabel	showPrice;
	JLabel	showCard;
	
	JLabel	LIVE;
	JLabel	MONEY;
	JPanel	panelE;
	JPanel	panelW;
	JPanel	panelN;
	JPanel	panelS;
	JPanel	panelC;
	
	JButton	WORK;
	JButton	card1;
	JButton	card2;
	JButton	card3;
	
	JList	price;
	JScrollPane scroller;
	String [] listEntries;
	public	void	go() {
		frame=new	JFrame();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setSize(500, 500);
		frame.setVisible(true);
		
		title=new	JLabel(showTitle);
		rules=new	JLabel(Info.rules);
		panelW=new	JPanel();
		panelW.setLayout(new BoxLayout(panelW, BoxLayout.Y_AXIS));
		panelW.add(title);
		panelW.add(rules);
		
		state=new	JLabel(Info.initialState);
		panelN=new	JPanel();
		panelN.add(state);
		
		ImageIcon	image=new	ImageIcon(normalFace);
		face=new	JLabel(image);
		panelS=new	JPanel();
		panelS.add(face);
		
		currentLive=new	JLabel("LIVE");
		currentMoney=new	JLabel("MONEY");
		LIVE=new	JLabel(p1.getMoney()+"");
		MONEY=new	JLabel(p1.getLive()+"");
		WORK=new	JButton(wayOfWork);
		showPrice=new	JLabel("给"+name+"几个小时的假吧？");
		showCard=new	JLabel(name+"会遇到什么呢？");
		card1=new	JButton("?");
		card2=new	JButton("?");
		card3=new	JButton("?");
		
		price=new	JList(Info.listEntries);
		scroller = new JScrollPane(price);
		scroller.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS);
		scroller.setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_NEVER);
		price.setVisibleRowCount(3);
		price.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		
		JPanel	pnl1=new	JPanel();
		pnl1.add(currentLive);
		pnl1.add(LIVE);
		JPanel	pnl2=new	JPanel();
		pnl2.add(currentMoney);
		pnl2.add(MONEY);
		JPanel	pnl3=new	JPanel();
		pnl3.add(card1);
		pnl3.add(card2);
		pnl3.add(card3);
		panelE=new	JPanel();
		panelE.setLayout(new BoxLayout(panelE, BoxLayout.Y_AXIS));
		panelE.add(pnl1);
		panelE.add(pnl2);
		panelE.add(WORK);
		panelE.add(showPrice);
		panelE.add(scroller);
		panelE.add(showCard);
		panelE.add(pnl3);
		
		WORK.addActionListener(new WorkListener());
		price.addListSelectionListener(new PriceListener());
		card1.addActionListener(new FListener());
		card2.addActionListener(new FListener());
		card3.addActionListener(new FListener());
		
		frame.getContentPane().add(BorderLayout.WEST,panelW);
		frame.getContentPane().add(BorderLayout.NORTH,panelN);
		frame.getContentPane().add(BorderLayout.SOUTH,panelS);
		frame.getContentPane().add(BorderLayout.EAST,panelE);
		                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
		
	}
	public	void	turn2P3() {
		p3w=new	P3Win();//create a Page03 of winning the game
		p3d=new	P3Die();//the opposite
		p3d.setUp();//layouts on the losing page03
		p3w.setUp();
		//layouts on the winning page03(common)
		//the character-specified ones are set up in P23G.setUp.etc
	}
	public	class	FListener	implements	ActionListener {
		public	void	actionPerformed(ActionEvent	event){
			boolean	flag=(!p1.decideBroke())&&(p1.decideLive());
			if(flag) {
				feedback=p1.FEED();
				state.setText(showState[feedback]);
				MONEY.setText((p1.getMoney()+""));
				LIVE.setText((p1.getLive()+""));
				ImageIcon	image=new	ImageIcon(showFace[feedback]);
				face.setIcon(image);
				
			}
			flag=!p1.decideLive();
			if(flag) {
				MONEY.setText((p1.getMoney()+""));
				LIVE.setText((p1.getLive()+""));
				try 
				{  
				Thread.currentThread();
				Thread.sleep(1000); 
				}  
				catch(Exception e){} 
				frame.setVisible(false);
				p3d.go();//the interface of Page03 in common
			}
			if(p1.decideWin()) {
				frame.setVisible(false);
				p3w.go();
			}
		}
	}
	
	public	class	WorkListener	implements	ActionListener {
		public	void	actionPerformed(ActionEvent	event) {
			if(p1.decideLive()) {
				p1.WORK();
				MONEY.setText((p1.getMoney()+""));
				LIVE.setText((p1.getLive()+""));
				
				state.setText("");
				ImageIcon	image=new	ImageIcon(normalFace);
				face.setIcon(image);
			}
			else {
				MONEY.setText((p1.getMoney()+""));
				LIVE.setText((p1.getLive()+""));
				try 
				{  
				Thread.currentThread();
				Thread.sleep(1000); 
				}  
				catch(Exception e){} 
				frame.setVisible(false);
				p3d.go();
			}
		}
	}
	
	public	class	PriceListener	implements	ListSelectionListener{
		public void valueChanged(ListSelectionEvent lse) {
			if( !lse.getValueIsAdjusting()) {
			String selection = (String)price.getSelectedValue();
			int	price=Integer.parseInt(selection);
			int	temp=p1.getMoney();
			if(price>temp) 
				state.setText("买不起哟");
			else {
			p1.price=price;
			}
			}
			
	}
	}

}