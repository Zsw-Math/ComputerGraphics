#include<graphics.h>
void Boundaryfill(int x,int y,color_t fill,color_t bd);
int main()
{
	initgraph(640,480);
	setbkcolor(WHITE); setcolor(RED);
	circle(200,200,50); getch();
	Boundaryfill(200,200,GREEN,RED);
	getch(); closegraph(); return 0;
 } 
void Boundaryfill(int x,int y,color_t fill,color_t bd)
{
	color_t color=getpixel(x,y)&0xFFFFFF;
	fill=fill&0xFFFFFF; bd=bd&0xFFFFFF;
	if(color!=fill&&color!=bd)
	{
		putpixel(x,y,fill);
		Boundaryfill(x,y-1,fill,bd); Boundaryfill(x,y+1,fill,bd);
		Boundaryfill(x-1,y,fill,bd); Boundaryfill(x+1,y,fill,bd);
	}
}
