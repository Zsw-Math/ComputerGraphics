#include<graphics.h>
int main()
{
	initgraph(640,480,INIT_RENDERMANUAL);
	setbkcolor(WHITE); setcolor(BLUE);
	setlinestyle(SOLID_LINE,0.3);
	int x1,y1,x2,y2; bool move,leftdown;
	mouse_msg msg={0};
	for(;is_run();delay_fps(60))
	{
		move=leftdown=false;
		while(mousemsg())
		{
			msg=getmouse(); if(msg.is_move()) move=true;
			if(msg.is_left()&&msg.is_down()) leftdown=true;
		}
		if(!keystate(key_mouse_l)) continue;
		if(leftdown) { x1=x2=msg.x; y1=y2=msg.y; }
		else if(move) { x2=msg.x; y2=msg.y; }
		cleardevice(); line(x1,y1,x2,y2);
	}
	closegraph(); return 0;
} 
