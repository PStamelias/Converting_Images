/*FILE:netpbm.c*/
#include<stdio.h>
int illegal(unsigned int ch)/*Checking if char is ascii Number*/
{
	if(ch!='0'&&ch!='1'&&ch!='2'&&ch!='3'&&ch!='4'&&ch!='5'&&ch!='6'&&ch!='7'&&ch!='8'&&ch!='9')
		return 1;
}
void print(unsigned int  n)
{
    // Remove the last digit and recur
    if (n/10)
        print(n/10);
 
    // Print the last digit
    putchar(n%10 + '0');
}
int main()
{
	int i;/*Loop Variable*/
	unsigned char t;/*Variable for printing the result in binary code*/
	unsigned int ch;/*Read Variable*/
	unsigned int ch1;/*Varible for N value*/
	int counter=0;/*P3 to P2 Variable*/
	int convertion;/* What type of conversion i will do.For example P6-P5*/
	int magic_namber=1;/*Format Variable*/
	int first_one=0;
	int first_two=0;
	int first_three=0;
	int first_four=0;
	int eimai_se_sxolio=0;/*In command*/
	int ipsos=0;/*N*/
	int platos=0;/*M*/
	int not_print=0;/*i dont want to to print to output some data*/
	int count_bytes=0;/*Counting how many bytes i have print*/
	unsigned int max_timh=0;/* Max Value of color value*/
	int how_many_bits=0;/*P5 to P4 counting how many bits  i have in last byte of each line*/
	int print_bytes=0;/*P5 to P4 counting how many bytes i have print*/
	int prev_byte=0;/*PreLast byte of  each Line*/
	unsigned int result;
	int new_entry=0;
	unsigned int R,G,B;/*Colors value in P3*/ 
	unsigned int Rbin;/*Color Value in P6*/
	unsigned int Gbin;/*Color Value in P6*/
	unsigned int Bbin;/*Color Value in P6*/
	unsigned int value;/* P5 value of binary type number*/
	unsigned int re=0b00000000;/*P5 to P4 output byte*/
	int count_bits=0;/*P5 to P4 for put 1 bit to finalBytte*/
	while((ch=getchar())!=EOF)/*Reading Byte by Byte until end of File*/
	{
		if(magic_namber==1)
		{
			if(ch!='P')
			{
				printf("Input Error\n");
				return -1;
			}	
			magic_namber=2;
		}
		else if(magic_namber==2)
		{
			if(ch=='1'|| ch=='4')
			{
				printf("Input Error\n");
				return -1;
			}
			else if(ch!='2'&&ch!='3'&&ch!='5'&&ch!='6')
			{
				printf("Input Error\n");
				return -1;
			}
			convertion=ch;/*Founding Magic Number*/
			ch=(int)ch-1;/*Print the  Number of new image*/
			magic_namber=3;
		}
		else if(magic_namber==3)
		{
			if(ch=='#')/*Command Line*/
			{	
				eimai_se_sxolio=1;
				continue;
			}
			else
			{
				if(eimai_se_sxolio==1)
				{
					if(ch=='\n')
						eimai_se_sxolio=0;/*Out of Command Line*/
					continue;
				}
			}
			if(first_one==0)/*Anyway i will have one white character*/
			{
				if(ch!='\n'&&ch!='\t'&&ch!=' ')
				{
					printf("Input Error\n");
					return -1;
				}
				first_one=1;
			}
			else
			{
				if(ch!=' '&&ch!='\t'&&ch!='\n')
				{
					magic_namber=4;
					if(illegal(ch)==1)
					{
						printf("Input Error\n");
						return -1;
					}
					ch1=ch;
					platos=ch1-'0';/*Founding the first character of Platos Number*/
				}
			}
		}
		else if(magic_namber==4)
		{
			if(ch!=' '&&ch!='\t'&&ch!='\n')
			{
				if(illegal(ch)==1)
				{
					printf("Input Error\n");
					return -1;
				}
				platos=platos*10+(ch-'0');/*Build platos digit by digit*/
			}
			else
				magic_namber=5;
		}
		else if(magic_namber==5)
		{
			if(ch!='\t'&&ch!='\n'&&ch!=' ')
			{
				first_three=1;
				ipsos=ipsos*10+(ch-'0');/*Building ipsos digit by digit*/
			}
			if((ch==' '||ch=='\t'||ch=='\n')&&first_three==1)
				magic_namber=6;
		}
		else if(magic_namber==6)
		{
			if(convertion=='2'||convertion=='5')/* P1 and P4 does not need Max number*/
				not_print=1;
			if(ch!='\t'&&ch!='\n'&&ch!=' ')
			{
				first_four=1;
				max_timh=max_timh*10+(ch-'0');/*Building max timh digit by digit*/
			}
			if((ch==' '||ch=='\t'||ch=='\n')&&first_four==1)
				magic_namber=7;
			if(magic_namber==7)
			{	
				result=0;
				if(ch!=' '&&ch!='\t'&&ch!='\n')/*Waiting at least one white character*/
				{
					printf("Input Error\n");
					return -1;
				}
			}
		}
		else 
		{
			if(convertion=='2')//P2 TO P1
			{	
				if(ch==' '||ch=='\t'||ch=='\n')
				{
					if(new_entry==0)
						result=0;
					else
					{
						if(result>max_timh)
						{
							printf("Input Error\n");
							return -1;
						}
						if((float)result>(float)(max_timh+1)/2)
							putchar('0');
						else
							putchar('1');
						new_entry=0;
						result=0;
					}
					putchar(ch);
				}
				else
				{
					new_entry=1;
					if(illegal(ch)==1)
					{
						printf("Input Error\n");
						return -1;
					}
					result=result*10+(ch-'0');
				}
				continue;
			}
			else if(convertion=='3')
			{	
				if(ch==' '||ch=='\n'||ch=='\t')
				{
					if(new_entry==0)
						result=0;
					else
					{
						if(result>max_timh)
						{
							printf("Input Error\n");
							return -1;
						}
						if(counter==0)
						{	
							R=result;
							result=0;
							new_entry=0;
						}
						else if(counter==1)
						{
							G=result;
							new_entry=0;
							result=0;
						}
						else if(counter==2)
						{
							B=result;
							result=0;
							unsigned int Final_Result=(299*R+587*G+114*B)/1000;
							print(Final_Result);
							putchar(ch);
							counter=-1;
							new_entry=0;
						}
						counter++;
					}
				}
				else
				{
					new_entry=1;
					if(illegal(ch)==1)
					{
						printf("Input Error\n");
						return -1;
					}
					result=result*10+(ch-'0');
				}
				continue;
			}
			else if(convertion=='5')
			{	
				if(platos%8!=0)
				{
					how_many_bits=platos%8;
					prev_byte=platos/8;
				}
				value=ch|0x00;
				if(value>max_timh)
				{
					printf("Input Error\n");
					return -1;
				}
				result=((float)value>(float)(max_timh+1)/2)?0:1;
				if(counter<8)
				{
					if(result==1)
						re|=1U<<(7-counter);
					if(prev_byte==count_bytes)
						count_bits++;
					if(count_bytes==prev_byte&&count_bits==how_many_bits)
					{
						for(i=0;i<8-how_many_bits;i++)/*Fill with bits 1 the byte*/
							re|=1U<<i;
						count_bits=0;
						count_bytes=0;
						counter=0;
						putchar(re);
						re=0b00000000;
						continue;
					}
					counter++;
				}
				if(counter==8)
				{
					putchar(re);
					count_bytes++;
					re=0b00000000;
					counter=0;
				}
				continue;
			}
			else if(convertion=='6')
			{	
				if(counter==0)
				{	
					Rbin=ch|0x00;
					if(Rbin>max_timh)
					{
						printf("Input Error\n");
						return -1;
					}
				}
				else if(counter==1)
				{	
					Gbin=ch|0x00;
					if(Gbin>max_timh)
					{
						printf("Input Error\n");
						return -1;
					}
				}
				else
				{
					Bbin=ch|0x00;
					if(Bbin>max_timh)
					{
						printf("Input Error\n");
						return -1;
					}
					int Final_Result=(299*Rbin+587*Gbin+114*Bbin)/1000;
					t=(char)Final_Result;
					putchar(t);
					counter=-1;
				}
				counter++;
				continue;
			}
		}
		if(not_print==0)
			putchar(ch);
	}
	return 0;
}