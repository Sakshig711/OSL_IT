#include<stdio.h>
#include <stdbool.h>
bool search(int key, int fr[], int fn)
{
    for (int i = 0; i < fn; i++)
        if (fr[i] == key)
            return true;
    return false;
}

void fifo(int arr[], int n, int fn)
{
	int v[fn];
	v[0] = arr[0];
	int miss;
	for(int i=1; i<n; i++)
	{
		bool ans = search(arr[i],v,fn);
		if(ans) miss++;
		else
		{
			v[i%fn] = arr[i];
		}
	}
	printf("Hit :%d\n Miss:%d",n-miss,miss);
}

int isValid(int arr[], int i, int j)
{
	int temp[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
	
	for(int k=i; k<=j; k++)
	{
		if(temp[arr[k]%10] == -1)
		{
			temp[arr[k]%10] = arr[k];
		}
		else 
		{
			//printf("%d",arr[k]);
			return 0;
		}
	}
	return 1;
}
void LRU(int arr[], int n, int fn)
{
	int i=0,j=fn-1;
	int fault;
	while(j <=n)
	{
		fault+= isValid(arr,i,j);
		i++,j++;
	}
	
	printf("%d",fault);
}

int main()
{
    int pg[]  = {7, 0, 1, 2,
               0, 3, 0, 4, 2, 3, 0, 3, 2, 1,
               2, 0, 1, 7, 0, 1};
    int pn = sizeof(pg) / sizeof(pg[0]);
    int fn = 3;
    LRU(pg, pn, fn);
    return 0;
}
