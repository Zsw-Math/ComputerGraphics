# include <graphics.h>
using namespace std;
struct Node
{ 
    int ymax,x; double dx; Node *next;
    Node(int ymm=0,int xx=0,double dxx=0);
    Node(const Node &nd);
    Node *insert(Node *head);
    Node *del(Node *head);
    static void exchange(Node *pt1,Node *pt2);
    static void delAll(Node *head);
};
Node **createET(int n,int p[ ],int &Ymi,int &Yma); 
void Fillpoly2(int n,int p[ ]);
int main( )
{ 
    initgraph(640,480);
    int poly[6*2]={100,100, 100,300, 250,450, 400,300, 400,100, 250,250};
    setcolor(YELLOW); setfillcolor(BLUE); setlinestyle(SOLID_LINE,0,3);
    Fillpoly2(6,poly); getch(); closegraph(); return 0;
}
Node **createET(int n,int p[ ],int &Ymi,int &Yma)
{ 
    int i,j,x0,y0,x1,y1,x,y,ymax; double dxx; Node *pt,**ET;
    for(Ymi=Yma=p[1],i=1;i<2*n;i+=2) 
    { if(p[i]>Yma) Yma=p[i]; else if(p[i]<Ymi) Ymi=p[i]; }
    ET=new Node*[Yma-Ymi+1]; ET=ET-Ymi;
    for(i=Ymi;i<=Yma;i++) ET[i]=0; 
    for(i=0;i<n;i++) 
    { 
	    x0=p[2*i]; y0=p[2*i+1];
        j=(i+1)%n; x1=p[2*j]; y1=p[2*j+1];
        if(y0==y1) continue; 
        if(y0<y1) { x=x0; y=y0; ymax=y1; } 
        else { x=x1; y=y1; ymax=y0; }
        dxx=double(x1-x0)/(y1-y0); pt=new Node(ymax-1,x,dxx);
        ET[y]=pt->insert(ET[y]); 
    }
    return ET;
}
void Fillpoly2(int n,int p[ ])
{ 
    int Ymi,Yma,x,y,i; color_t fillcolor=getfillcolor();
    Node **ET=createET(n,p,Ymi,Yma),*AET=0,*pt,*pt2; 
    for(y=Ymi;y<=Yma;y++)
    { 
	    for(pt=ET[y];pt!=0;pt=pt->next) 
        { pt2=new Node(*pt); AET=pt2->insert(AET); }
        for(pt2=AET;pt2!=0&&pt2->next!=0;pt2=pt2->next) 
        { x=pt2->x; pt2=pt2->next; while(x<=pt2->x) { putpixel(x,y,fillcolor); x++; } }
        for(pt2=AET;pt2!=0; ) 
        { 
		    if(pt2->ymax==y) 
            { pt=pt2; pt2=pt2->next; AET=pt->del(AET); delete pt; }
            else { pt2->x+=pt2->dx; pt2=pt2->next; } 
        }
        for(pt2=AET;pt2!=0&&pt2->next!=0; )
        { 
		    pt=pt2; pt2=pt2->next; double v1,v2;
            v1=pt->x*1000.0+pt->dx,v2=pt2->x*1000.0+pt2->dx; 
            if(v1>v2) Node::exchange(pt,pt2) ; 
        }
    }
    moveto(p[2*n-2],p[2*n-1]); for(i=0;i<n;i++) lineto(p[2*i],p[2*i+1]);
    Node::delAll(AET); for(y=Ymi;y<=Yma;y++) Node::delAll(ET[y]); 
    delete[ ](ET+Ymi); 
}
Node::Node(int ymm,int xx,double dxx) 
{ ymax=ymm;x=xx;dx=dxx;next=0; }
Node::Node(const Node &nd)
{ ymax=nd.ymax; x=nd.x; dx=nd.dx; next=0; }
Node *Node::insert(Node *head) 
{ 
    Node tmp,*p1=&tmp,*p2=head; tmp.next=head;
    while(p2&&!(x<p2->x||x==p2->x&&dx<p2->dx)){ p1=p2; p2=p2->next; }
    p1->next=this; this->next=p2; return tmp.next;
}
Node *Node::del(Node *head) 
{ 
    Node tmp,*p1=&tmp,*p2=head; tmp.next=head; 
    while(p2&&p2!=this) { p1=p2;p2=p2->next; }
    if(p2==this){ p1->next=p2->next; }
    return tmp.next;
}
void Node::exchange(Node *pt1,Node *pt2) 
{ 
    int k=pt1->ymax; pt1->ymax=pt2->ymax; pt2->ymax=k;
    k=pt1->x; pt1->x=pt2->x; pt2->x=k;
    double t=pt1->dx; pt1->dx=pt2->dx; pt2->dx=t; 
}
void Node::delAll(Node *head) 
{ for(Node *pt=head;pt!=0;pt=head) { head=head->next; delete pt; } }
