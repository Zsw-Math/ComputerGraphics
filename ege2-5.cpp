#include<graphics.h>
using namespace std;
struct pointwid { int xleft,xright,y; };
struct stack { int n; pointwid a[50]; } s={0};
void Floodfill2(int x,int y,color_t fill,color_t bd); 
int main()
{ 
    initgraph(640,480);
    int poly[7*2]={100,100,100,300,250,450,400,300,400,100,250,250,100,100};
    setcolor(WHITE); setlinestyle(SOLID_LINE,0,3);
    drawpoly(7,poly); getch();
    Floodfill2(250,350,GREEN,WHITE); getch(); closegraph(); return 0;
}
void Floodfill2(int x,int y,color_t fill,color_t bd)
{ 
    color_t c; const int mm=0xFFFFFF;
    pointwid pt,pt2; int xleft,xright;
    fill=fill&mm; bd=bd&mm;
    while((c=getpixel(x,y)&mm)!=fill&&c!=bd) x--; x++; pt.xleft=x;
    while((c=getpixel(x,y)&mm)!=fill&&c!=bd) x++; pt.xright=x-1; pt.y=y;
    s.a[s.n++]=pt;
	while(s.n!=0)
   { 
        pt=s.a[--s.n];
        for(x=pt.xright;x>=pt.xleft;x--) putpixel(x,pt.y,fill); 
        for(y=pt.y-1;y<=pt.y+1;y+=2)
        { 
		    xleft=pt.xleft; xright=pt.xright;
            if((c=getpixel(xright,y)&mm)!=fill&&c!=bd)
            { 
			    while(c!=fill&&c!=bd) { xright++; c=getpixel(xright,y)&mm; }
                xright--;
            }
            if((c=getpixel(xleft,y)&mm)!=fill&&c!=bd)
            { 
			    while(c!=fill&&c!=bd) { xleft--; c=getpixel(xleft,y)&mm; }
                xleft++;
            }
            for(pt2.y=y,x=xright;x>=xleft;) 
            { 
			    while(x>=xleft&&((c=getpixel(x,y)&mm)==fill||c==bd))x--; 
                if(x<xleft) break;
                pt2.xright=x; while((c=getpixel(x,y)&mm)!=fill&&c!=bd) x--;
                pt2.xleft=x+1; s.a[s.n++]=pt2;
            } 
        }
    }
}
