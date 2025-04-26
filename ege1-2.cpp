#include<graphics.h>
int main()
{
	initgraph(640,480,0);
	
    outtextxy(0,0,"计算机图形学");
    line(100,100,300,300);
    circle(200,200,100);
    rectangle(100,100,300,300);
    getch();
    cleardevice();
    int p[4*2]={300,50,100,396,500,396,300,50};
    drawpoly(4,p);
    xyprintf(100,400,"三角形：(%d,%d)-(%d,%d)-(%d,%d)",
	        p[0],p[1],p[2],p[3],p[4],p[5]);
	getch();
	
	closegraph();
	return 0;
}
