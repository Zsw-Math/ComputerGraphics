#include<graphics.h>
struct Point{ int x,y; };
void drawPoly(Point a[],int &n,bool leftdown,bool rightdown);
void ClipPoly(Point a[],int &n);
int left=100,top=50,right=400,bottom=300;
int main()
{
	initgraph(640,480,INIT_RENDERMANUAL);
	setbkcolor(WHITE); setcolor(RED); setfillcolor(GREEN);
	Point a[50]; int n=0; bool leftdown,rightdown; mouse_msg msg={0};
	bar(left,top,right,bottom); setlinestyle(SOLID_LINE,0,2);
	for(;is_run();delay_fps(60))
	{
		rightdown=leftdown=false;
		while(mousemsg())
		{
			msg=getmouse();
			if(msg.is_left()&&msg.is_down()) leftdown=true;
			if(msg.is_right()&&msg.is_down()) rightdown=true;	
		}
		cleardevice(); bar(left,top,right,bottom);
		drawPoly(a,n,leftdown,rightdown);
	}
	closegraph(); return 0;
}
void drawPoly(Point a[],int &n,bool leftdown,bool rightdown)
{
	static int rButton=0;
	if(leftdown)
	{
		if(rButton>0) { rButton=0; n=0; }
		mousepos(&a[n].x,&a[n].y); n++;
	}
	else if(rightdown)
	{
		rButton++;
		if(rButton==1) a[n++]=a[0];
		if(rButton==2) ClipPoly(a,n);
	}
	moveto(a[0].x,a[0].y);
	for(int i=1;i<n;i++) lineto(a[i].x,a[i].y);
}
void ClipPoly(Point a[],int &n)
{
	Point dir[4]={{-1,0},{0,-1},{1,0},{0,1}};
	Point ePt[4]={{left,0},{0,top},{right,0},{0,bottom}};
	int n2,k,i; double t,ss,pp; Point v1,v2,pt,a2[50];
	for(k=0;k<4;k++)
	{
		v2.x=a[0].x-ePt[k].x; v2.y=a[0].y-ePt[k].y;
		pp=v2.x*dir[k].x+v2.y*dir[k].y;
		for(n2=0,i=1;i<n;i++)
		{
			v1=v2; v2.x=a[i].x-ePt[k].x; v2.y=a[i].y-ePt[k].y;
			ss=pp; pp=v2.x*dir[k].x+v2.y*dir[k].y;
			if(ss*pp<0)
			{
				t=-ss/(pp-ss);
				pt.x=a[i].x-(1-t)*(v2.x-v1.x);
				pt.y=a[i].y-(1-t)*(v2.y-v1.y);
				a2[n2++]=pt; 
			}
			if(pp<=0) { a2[n2++]=a[i]; }
		}
		for(i=0;i<n;i++) a[i]=a2[i];
		a[n2]=a[0];n=n2+1;
	}
}
