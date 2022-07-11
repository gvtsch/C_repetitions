#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main()
{
	int n;
    int m;
    float k;
    float l;
    
    scanf("%d %d", &n, &m);
    scanf("%f %f", &k, &l);
    
    printf("%d %d\n", n+m, n-m);
    printf("%.1f %.1f\n", k+l, k-l);
    
    return 0;
}
