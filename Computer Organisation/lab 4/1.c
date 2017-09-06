#include <stdio.h>
int power(int x, unsigned int y)
{
    int temp;
    if( y == 0)
        return 1;
    temp = power(x, y/2);
    if (y%2 == 0)
        return temp*temp;
    else
        return x*temp*temp;
}
int count=0;
int read()
{
	FILE *p = fopen("hex.txt", "r");
	char str[8];
	char ch ;
	int num=0,i,j;
	int count2=0;
	while(count2!=count)
	{
		ch = fgetc(p);
		if(ch=='\n')
		{
			count2++;
			ch = fgetc(p);
		}
	}
	i=0;
  	while(ch!='\n')
  	{
  		str[i] = ch;
  		ch = fgetc(p);
  		i++;
  	}
  	int len =4;
  	int len2 = len-1,val;
  	i=0;j=4;
  	if(count==0)
  		i=1,j=5;
  	for(;i<j;i++)
  	{
  		if(str[i]=='0')
  			val = 0;
  		else if(str[i] =='1')
  			val = 1;
  		else if(str[i] =='2')
  			val = 2;
  		else if(str[i] =='3')
  			val = 3;
  	  	else if(str[i] =='4')
  			val = 4;
  		else if(str[i] =='5')
  			val = 5;
  		else if(str[i] =='6')
  			val = 6;
  		else if(str[i] =='7')
  			val = 7;
  		else if(str[i] =='8')
  			val = 8;
  		else if(str[i] =='9')
  			val = 9;
  		else if(str[i] =='A')
  			val = 10;
  		else if(str[i] =='B')
  			val = 11;
  		else if(str[i] =='C')
  			val = 12;
  		else if(str[i] =='D')
  			val = 13;
  		else if(str[i] =='E')
  			val = 14;
  		else if(str[i] =='F')
  			val = 15;
  		num += val*power(16,len2);
  		len2--;				  		
  	}
	count++;
	return num;
}

