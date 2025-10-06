#include<reg51.h>
int x,y,z,i,j;
int sessioncount=0;
sbit rs=P0^1;
sbit rw=P0^2;
sbit en=P0^3;
sbit sw=P0^5;
unsigned char data1[]="Study Time";
unsigned char data4[]="Session 1";
unsigned char data5[]="Session 2";
unsigned char data6[]="Session 3";
unsigned char data7[]="Session 4";
unsigned char data2[]="Short Break";
unsigned char data3[]="Long Break";
unsigned int cmmd1[]={0x38,0x0E,0x01,0x06,0x80};
unsigned int cmmd2[]={0x38,0x0E,0x06,0xC0};
void delay()
{
   for(x=0;x<14;x++)
   {
	TMOD=0x01;
    TL0=0;
	TH0=0;
	TR0=1;
	while(TF0==0);
	TF0=0;
	TR0=0;
    }
}
void delay11()
{
	unsigned int x;
	for(x=0;x<30000;x++);
}
void cmm()
{
    rs=0;
	rw=0;
	en=1;
	delay11();
	en=0;
}
void dat()
{
     rs=1;
	 rw=0;
	 en=1;
	 delay11();
	 en=0;
}
void timer()
{ 
   for(y=0;y<37;y++)
   {
      if(y==0x0a | y==0x1a)
	  {
	     y=y+6;
	  }
	  P2=y;
	  delay();
    for(z=0;z<90;z++)
	  {
	    if(z==0x0a|z==0x1a|z==0x2a|z==0x3a|z==0x4a|z==0x5a)
		 {
		   z=z+6;
	    }
      P3=z;
      delay();
	  }
   }
   P2=y;
   P3=0;
 }
void shortbreak()
{
    for(i=0;i<5;i++)
	  {
	   P2=i;
		 delay();
	   for(j=0;j<90;j++)
	   {
	     if(j==0x0a|j==0x1a|j==0x2a|j==0x3a|j==0x4a|j==0x5a)
		 {
		    j=j+6;
		 }
		 P3=j;
		 delay();
	   }
   }
   P2=i;
   P3=0;
}
void longbreak()
{
    for(i=0;i<21;i++)
	  {
	   if(i==0x0a)
	   {
	      i=i+6;
	   }
	   P2=i;
		 delay();
	    for(j=0;j<90;j++)
	   {
	     if(j==0x0a|j==0x1a|j==0x2a|j==0x3a|j==0x4a|j==0x5a)
		 {
		    j=j+6;
		 }
		 P3=j;
		 delay();
	   }
    }
	  P2=i;
    P3=0;
 }
 void main()
 {
     int a,b,c,d,e,f,g,h;
     P2=P3=0;
	   while(1)
     {
		  if(sw==1)
	   {
      for(a=0;a<5;a++)
	    {
	     P1=cmmd1[a];
		   cmm();
	    }
	    for(b=0;b<11;b++)
	    {
	     P1=data1[b];
		   dat();
	    }
			for(g=0;g<4;g++)
	    {
	     P1=cmmd2[g];
		   cmm();
	    }
	    for(h=0;h<9;h++)
	    {
			 if(sessioncount==0)
			 {
	         P1=data4[h];
		       dat();
	     }
			 else if(sessioncount==1)
			 {
				    P1=data5[h];
		        dat();
			 }
			 else if(sessioncount==2)
			 {
				  P1=data6[h];
		       dat();
			 }
			 else
			 {
				 P1=data7[h];
		     dat();
			 }
		 }
	  timer();
		sessioncount=sessioncount+1;
		if(sessioncount%4==0)
	   {
	    for(e=0;e<5;e++)
	    {
	     P1=cmmd1[e];
		   cmm();
	    }
	    for(f=0;f<11;f++)
	    {
	     P1=data3[f];
		   dat();
	    }
	    longbreak();
	   }
	   else
	   {
	    for(c=0;c<5;c++)
	   {
	     P1=cmmd1[c];
		   cmm();
	   }
	   for(d=0;d<12;d++)
	   {
	      P1=data2[d];
		    dat();
	   }
	   shortbreak();
     }
		 if(sessioncount==4)
		 {
		 sessioncount=0;
		 }
    }
   }
}	 