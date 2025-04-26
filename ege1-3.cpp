#include<graphics.h>
void Mandelbrot();
int main()
{
	initgraph(640,480);
	setbkcolor(WHITE); setcolor(RED); setfillcolor(GREEN);
	bar(100,100,300,200); 
	outtextxy(120,120,"无边框实心矩形");
	fillellipse(400,300,150,80);
	setbkmode(TRANSPARENT);
	outtextxy(350,300,"有边框实心椭圆");
	getch(); cleardevice(); Mandelbrot(); getch();
	closegraph(); return 0;
} 
void Mandelbrot()
{
	color_t c[6]={0xFF0000,0xFF,0xFF00,0xFF00FF,0xFFFF00,0xFFFF};
	int i,j,n,w=640, h=480, wc=411, hc=240; double x,y,t,cx,cy,d=3.0/h;
	for(i=0;i<w;i++) for(j=0;j<h;j++)
	{
		cx=(i-wc)*d; cy=(j-hc)*d; x=y=0;
		for(n=100;n>0;n--) { t=x*x-y*y+cx; y=2*x*y+cy; x=t; if(x*x+y*y>16) break; }
		putpixel(i,j,n>0?c[n%6]:EGERGB(0,0,0));
	}
}
