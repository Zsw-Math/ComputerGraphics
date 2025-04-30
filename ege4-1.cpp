#include<graphics.h>
struct Point { int x,y; };
bool getMessages(bool *pm,bool *pld,bool *prd,char *pch);
void drawPoly(Point a[],int *psize,bool leftdown,bool rightdown,bool move,char ch);
void refresh(Point a[],int n,char ch);
int main()
{
	Point a[50]={0}; int n=0; bool move,leftdown,rightdown; char ch='b';
	initgraph(640,480,INIT_RENDERMANUAL);
	setbkcolor(WHITE); setcolor(RED);setfillcolor(WHITE);
	for(;is_run;delay_fps(60))
	{
		if(!getMessages(&move,&leftdown,&rightdown,&ch)) continue;
		drawPoly(a,&n,leftdown,rightdown,move,ch);
	}
	closegraph(); return 0;
}
bool getMessages(bool *pm,bool *pld,bool *prd,char *pch)
{
	mouse_msg msg={0}; bool m=false; *pm=*pld=*prd=false;
	while(mousemsg()||kbhit())
	{
		m=true; if(kbhit()) { *pch=getch(); }
		if(mousemsg())
		{
			msg=getmouse();
			if(msg.is_move()) *pm=true;
			else if(msg.is_left()&&msg.is_down()) *pld=true;
			else if(msg.is_right()&&msg.is_down()) *prd=true;
		} 
	} return m;
}
void drawPoly(Point a[],int *psize,bool leftdown,bool rightdown,bool move,char ch)
{
	static bool start=true;
	if(rightdown) { start=true; refresh(a,*psize+1,ch); }
	else
	{
		if(leftdown&&start) { *psize=0; start=false; }
		if(start&&move) return;
		if(!start)
		{
			mousepos(&a[*psize].x,&a[*psize].y);
			if(leftdown) { (*psize)++; a[*psize]=a[*psize-1]; }
		}
	} refresh(a,*psize+1,ch);
}
void Bezier(Point p0,Point p1,Point p2,Point p3)
{
	double t,t1; int i,x,y;
	for(i=0;i<=20;i++)
	{
		t=i/20.0; t1=1-t;
		x=p0.x*t1*t1*t1+3*p1.x*t1*t1*t+3*p2.x*t1*t*t+p3.x*t*t*t+0.5;
		y=p0.y*t1*t1*t1+3*p1.y*t1*t1*t+3*p2.y*t1*t*t+p3.y*t*t*t+0.5;
		if(i!=0) lineto(x,y); else moveto(x,y);
	}
}
void drawBezier(Point p[],int n)
{
	Point b1=p[0],b2; setcolor(BLACK); if(n==2) { line(p[0].x,p[0].y,p[1].x,p[1].y); }
	for(int i=1;i+2<=n-1;i+=2)
	{
		if(i+3==n-1) { Bezier(b1,p[i+1],p[i+2],p[i+3]); }
		else if(i+2==n-1)
		{
			b2.x=(p[i+1].x+p[i+2].x)/2; b2.y=(p[i+1].y+p[i+2].y)/2;
			Bezier(b1,p[i+1],b2,p[i+2]);
		}
		else
		{
			b2.x=(p[i+2].x+p[i+3].x)/2; b2.y=(p[i+2].y+p[i+3].y)/2;
			Bezier(b1,p[i+1],p[i+2],b2); b1=b2;
		}
	} outtextxy(0,0,"BezierÇúÏß"); 
}
void BSpline(Point p0,Point p1,Point p2,Point p3)
{
	double t,t1,t2,t3; int i,x,y;
	for(i=0;i<=20;i++)
	{
		t=i/20.0; t1=1-t; t2=3*t*t*(t-2)+4; t3=-t2+3*t*t1+5;
		x=(p0.x*t1*t1*t1+p1.x*t2+p2.x*t3+p3.x*t*t*t)/6+0.5;
		y=(p0.y*t1*t1*t1+p1.y*t2+p2.y*t3+p3.y*t*t*t)/6+0.5;
		if(i!=0) lineto(x,y); else moveto(x,y);
	} 
}
void drawBSpline(Point p[],int n)
{
	p[n].x=p[n-1].x*2-p[n-2].x; p[n].y=p[n-1].y*2-p[n-2].y; 
	n++;
	Point pp={p[0].x*2-p[1].x,p[0].y*2-p[1].y};
	setcolor(BLACK); BSpline(pp,p[0],p[1],p[2]);
	for(int i=0;i+3<=n-1;i++) BSpline(p[i],p[i+1],p[i+2],p[i+3]);
	outtextxy(0,0,"BÑùÇúÏß");
}
void drawOutline(Point p[],int n)
{
	int i,d=3; setcolor(RED); moveto(p[0].x,p[0].y);
	for(i=1;i<n;i++) lineto(p[i].x,p[i].y);
	for(i=0;i<n;i++) fillellipse(p[i].x,p[i].y,d,d);
}
void refresh(Point a[],int n,char ch)
{
	cleardevice(); if(n<2) return;
	if(ch=='b') drawBezier(a,n);
	else if(ch=='s') drawBSpline(a,n);
	drawOutline(a,n);
}
