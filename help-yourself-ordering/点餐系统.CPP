#include <stdio.h>
#include <string.h>
#define N 9
struct list
{	char name[50];
	float fee;
}item[]={"Grilled Jerk Ahi Tuna",15,"Scallops",13,"Crab Cake Sliders",13,"Shrimp Scampi Skewers",12,"Wonton Wrapped Shrimp",9,"Bruschetta",7,"Scotch Egg",4,"tax",0,"Amount due",0};
void showmenu(struct list item[])
{	int i;
	char a='$';
	printf("Welcome to WHO'S Inn\n");
	for(i=0;i<N-2;i++)
		printf("%d%-60s%c%.2f\n",i,item[i].name,a,item[i].fee);
}
void printcheck(struct list item[],int list[],int num[],int n)
{	int i;
	char a='$';
	printf("Welcome to WHO'S Inn.And here's your bill.\n");
	for(i=0;i<n;i++)
		printf("%-60s%c%.2f\n",item[list[i]].name,a,item[list[i]].fee*num[i]);
	printf("%-60s%c%.2f\n",item[N-2].name,a,item[N-2].fee);
	printf("%-60s%c%.2f\n",item[N-1].name,a,item[N-1].fee);
}
int getdata(int *p1,int *p2)
{	int count=1;
	printf("您要来点什么？\n");
	printf("请输入该菜名的序号和想要的份数，并用逗号隔开\n");
	scanf("%d,%d",p1,p2);
	p1++;p2++;
	for(;count<N-2;count++,p1++,p2++)
	{	printf("再要来点什么吗？\n若需要，请输入该菜名的序号和想要的份数，并用逗号隔开\n若不要，请输入：-1,-1\n");
		scanf("%d,%d",p1,p2);
		if(*p1==-1)
			break;
	}
	return(count);
}
void cal(struct list *p,int list[],int num[],int n)
{	int i;
	float total=0.0;
	for(i=0;i<n;i++)
		total+=(p+list[i])->fee*num[i];
	(p+N-2)->fee=(float)(0.05*total);
	(p+N-1)->fee=(float)(total*1.05);
}
void savef(struct list *p,int list[],int a,int n)
{	FILE *fp;
	int i;
	if((fp=fopen("G:\\COMP\\保存信息.txt","wb"))==NULL)
	{	fprintf(stdin,"CAN'T\n");
		return;
	}
	for(i=0;i<n;i++)
		fwrite(&p[list[i]],a,1,fp);
	fwrite(&p[7],a,1,fp);
	fwrite(&p[8],a,1,fp);
	fclose(fp);
}


void main()
{	int list[N-2],num[N-2],n,a;
	struct list *p=item;
	showmenu(item);
	n=getdata(list,num);
	cal(p,list,num,n);
	printcheck(item,list,num,n);
	a=sizeof(item[0]);
	savef(p,list,a,n);
}