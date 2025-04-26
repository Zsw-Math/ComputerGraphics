#include<graphics.h>
int main()
{
	initgraph(640,480,INIT_RENDERMANUAL);
	setbkcolor(WHITE); setcolor(BLUE); setfont(50,0,"宋体");
	const char *p; char ch='\0';
	for(;ch!=key_esc;delay_fps(60))
	{
		if(kbhit()) ch=getch();
		if(ch=='A') p="苹果"; 
		else if(ch=='B') p="香蕉";
		else p="其他";
		outtextxy(160,125,p); 
	}
	closegraph(); return 0;
}
