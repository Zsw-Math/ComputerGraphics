#include<graphics.h>
struct Point { int x,y; };
bool getMessages(bool *pm,bool *pld,bool *prd,char*pch);
void drawPoly(Point a[],int *psize,bool leftdown,bool rightdown,bool move,char ch);
int main()
{
	Point a[50]={0}; int n=0; char ch='b';
	bool move,leftdown,rightdown;
	initgraph(640,480,INIT_RENDERMANUAL);
	setbkcolor(WHITE); setcolor(RED);
	for(;is_run();delay_fps(60))
	{
		if(!getMessages(&move,&leftdown,&rightdown,&ch)) continue;
		drawPoly(a,&n,leftdown,rightdown,move,ch);
	}
	closegraph(); return 0;
}

bool getMessages(bool *pm,bool *pld,bool *prd,char*pch)
{
	mouse_msg msg={0}; bool m=false;
	*pm=*pld=*prd=false;
	while(mousemsg()||kbhit())
	{
		m=true;
		if(kbhit()) { *pch=getch(); }
		if(mousemsg())
		{
			msg=getmouse();
			if(msg.is_move()) *pm=true;
			else if(msg.is_left()&&msg.is_down()) *pld=true;
			else if(msg.is_right()&&msg.is_down()) *prd=true;
		}
	}
	return m;
}
void drawPoly(Point a[],int *psize,bool leftdown,bool rightdown,bool move,char ch)
{
	static bool start=true;
	if(rightdown) { start=true; }
	else
	{
		if(leftdown&&start) { *psize=0; start=false; }
		if(start&&move) return;
		if(!start)
		{
			mousepos(&a[*psize].x,&a[*psize].y);
			if(leftdown) { (*psize)++;a[*psize]=a[*psize-1]; }
		}
	}
	if(ch=='s') setlinestyle(SOLID_LINE,0,1);
	else if(ch=='c') setlinestyle(CENTER_LINE,0,1);
	else if(ch=='d') setlinestyle(DOTTED_LINE,0,1);
	cleardevice(); moveto(a[0].x,a[0].y);
	for(int i=1;i<*psize;i++) lineto(a[i].x,a[i].y);
}
