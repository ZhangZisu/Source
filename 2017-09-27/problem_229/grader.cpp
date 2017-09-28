/* This is sample grader for the contestant */
#include <stdio.h>
#include "boxes.h"
static int n,k,l;
static int a[10000005];
static inline int Read(){
	int x=0;char p=getchar();
	while(!(p<='9'&&p>='0'))p=getchar();
	while(p<='9'&&p>='0')x*=10,x+=p-48,p=getchar();
	return x;
}
static void outans(long long x){
	if(x<10){putchar('0'+x);return;}
	outans(x/10);putchar('0'+(x%10));
}
int main(){
	n=Read();k=Read();l=Read();
	for(int i=0;i<n;i++)a[i]=Read();
	long long ans=delivery(n,k,l,a);
	if(ans<0){putchar('-');ans=-ans;}
	outans(ans);
	return 0;
}



