#include<graphics.h>
int main()
{
	initgraph(640,480,INIT_RENDERMANUAL);
	setbkcolor(WHITE); setcolor(BLUE); setfont(50,0,"����");
	const char *p; char ch='\0';
	for(;ch!=key_esc;delay_fps(60))
	{
		if(kbhit()) ch=getch();
		if(ch=='A') p="ƻ��"; 
		else if(ch=='B') p="�㽶";
		else p="����";
		outtextxy(160,125,p); 
	}
	closegraph(); return 0;
}
