package version01_1;

import java.util.*;
import	java.awt.geom.*;

public class Player {
	private	int		time;
	private	ArrayList<int[]> trace;
	private	boolean		hitFlag=false;
	private	boolean	biteFlag=false;
	private	boolean	endFlag=false;
	
	public	void	initial() {
		trace = new ArrayList<int[]>();
		int[]	line=new	int[4];
		for(int i=0;i<4;i++) {
		line[i]= Info.midPoint;
		}
		trace.add(line);
		time=0;
		
	}
	
	public	int	getTime() {
		return	time;
	}
	public	void	addTime() {
		time++;
	}
	
	public	ArrayList<int[]>	getTrace() {
		return	trace;
	}
	
	public	void	addTrace(int[] line) {
		trace.add(line);
	}
	
	public	boolean	ishitted(int[] line) {
		for(int i:line) {
			if(i<=0||i>=Info.sizeLimit) {
				hitFlag=true;
				break;
			}
		}
		return	hitFlag;
	}
	public	boolean	isbitten(int[] line,ArrayList<int[]> trace) {
		boolean	temp1;
		boolean	notConnected;
		for(int[] i:trace) {
			int	distance=(int) Line2D.ptLineDist( i[0], i[1], i[2], i[3], line[0], line[1]);
			notConnected=(distance!=0);//not connected
				if(notConnected) {
					temp1=Line2D.linesIntersect(line[0], line[1],line[2],line[3], i[0], i[1], i[2], i[3]);
					if(temp1) {
						biteFlag=true;
						break;
					}
				}
		}
		return	biteFlag;
	}
	public	boolean	timeUp() {
		if(time>Info.time) 
			endFlag=true;
		return	endFlag;
	}
	public	boolean	returnFlag() {
		return	hitFlag&&biteFlag&&endFlag;
	}
}
