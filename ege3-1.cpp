#include<graphics.h>
#include<math.h>
struct Point{ int x,y; };
bool getMessages(bool *pm,bool *pld,bool *prd,char *pch);
void drawPoly(Point a[],Point b[],int *psize,bool leftdown,bool rightdown);
void moving(Point a[],Point b[],int n,bool leftdown,bool move,Point *ppre);
void rotate(Point a[],Point b[],int n,bool leftdown,bool move,Point base[]);
int main()
{
	Point a[50]={0},b[50]={0},pre={0,0},base[2]={0};
	int n=0; bool move,leftdown,rightdown; char ch='d';
	initgraph(640,480,INIT_RENDERMANUAL);
	setbkcolor(WHITE); setcolor(RED);
	for( ;is_run();delay_fps(60))
	{
		if(!getMessages(&move,&leftdown,&rightdown,&ch)) continue;
		switch(ch)
		{
			case 'd':drawPoly(a,b,&n,leftdown,rightdown); break;
			case 'm':moving(a,b,n,leftdown,move,&pre); break;
			case 'r':rotate(a,b,n,leftdown,move,base); break;
		}
	}
	closegraph();
	return 0;
}
bool getMessages(bool *pm,bool *pld,bool *prd,char *pch)
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
void refresh(Point a[],int n)
{
	cleardevice(); moveto(a[0].x,a[0].y);
	for(int i=1;i<n;i++) lineto(a[i].x,a[i].y);
}
void drawPoly(Point a[],Point b[],int *psize,bool leftdown,bool rightdown)
{
	if(rightdown) { *psize=0; refresh(a,0); }
	else if(leftdown)
	{
		mousepos(&a[*psize].x,&a[*psize].y); (*psize)++;
		for(int i=0;i<*psize;i++) b[i]=a[i]; refresh(b,*psize);
	}
}
void moving(Point a[],Point b[],int n,bool leftdown,bool move,Point *ppre)
{
	if(leftdown)
	{
		refresh(b,n); mousepos(&(ppre->x),&(ppre->y));
		for(int i=0;i<n;i++) a[i]=b[i];
	}
	else if(keystate(key_mouse_l)&&move)
	{
		int x,y; mousepos(&x,&y); x=x-ppre->x;y=y-ppre->y;
		for(int i=0;i<n;i++) { b[i].x=a[i].x+x; b[i].y=a[i].y+y; } refresh(b,n);
	}
}
void rotate(Point a[],Point b[],int n,bool leftdown,bool move,Point base[])
{
	static int idx=0;
	if(leftdown)
	{
		if(idx==2) idx=0;mousepos(&base[idx].x,&base[idx].y); idx++;
		for(int i=0;i<n;i++) a[i]=b[i];
	}
	else if(keystate(key_mouse_l)&&move&&idx==2)
	{
		int x,y; double t1,t2,c,s,xx1,yy1,xx2,yy2;
		mousepos(&x,&y);
		xx1=base[1].x-base[0].x; yy1=base[1].y-base[0].y;
		xx2=x-base[0].x; yy1=y-base[0].y;
		t1=sqrt(xx1*xx1+yy1*yy1); t2=sqrt(xx2*xx2+yy2*yy2);
		c=(xx1*xx2+yy1*yy2)/(t1*t2); s=sqrt(1-c*c);
		if(xx1*yy2-xx2*yy1<0) s=-s;
		for(int i=0;i<n;i++)
		{
			xx1=a[i].x-base[0].x; yy1=a[i].y-base[0].y;
			b[i].x=xx1*c-yy1*s+base[0].x; b[i].y=xx1*s+yy1*c+base[0].y;
		}
		refresh(b,n);
	}
}
