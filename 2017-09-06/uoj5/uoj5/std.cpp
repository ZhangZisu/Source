#include<cstdio>
char a[1000010];long long b,c,d,e[1000010],f[1000010],g;int main(){scanf("%lld",&b);while(b--){scanf("%s",a);c=d=-1;g=1;f[0]=1;e[0]=-1;for (int i=1;a[i];i++) {while(~c&&a[i]!=a[c+1])c=e[c];if(a[i]==a[c+1])c++;e[i]=c;f[i]=f[c]+1;while(~d&&a[i]!=a[d+1])d=e[d];if(a[i]==a[d+1])d++;int h=(i+1)>>1;while(d+1>h)d=e[d];g*=f[d]+1;g%=1000000007;}printf("%lld\n", g);}return 0;}