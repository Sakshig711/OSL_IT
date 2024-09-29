#include <stdio.h>

int main()
{
    int n, m, i, j, k;

    // Taking number of processes and resources from user input
    printf("Enter the number of processes: ");
    scanf("%d", &n); // Number of processes
    
    printf("Enter the number of resources: ");
    scanf("%d", &m); // Number of resources

    // Declare matrices and arrays based on user input
    int alloc[n][m], max[n][m], avail[m], f[n], ans[n], ind = 0;

    // Taking Allocation Matrix input
    printf("Enter the allocation matrix:\n");
    for (i = 0; i < n; i++) {
        printf("Process %d:\n", i);
        for (j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    // Taking Max Need Matrix input
    printf("Enter the max need matrix:\n");
    for (i = 0; i < n; i++) {
        printf("Process %d:\n", i);
        for (j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Taking Available Resources input
    printf("Enter the available resources:\n");
    for (i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
    }

    // Initialize the finished array
    for (k = 0; k < n; k++) {
        f[k] = 0;
    }

    // Calculate Need Matrix
    int need[n][m];
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    int y = 0;
    for (k = 0; k < n; k++) {
        for (i = 0; i < n; i++) {
            if (f[i] == 0) {

                int flag = 0;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]){
                        flag = 1;
                        break;
                    }
                }

                if (flag == 0) {
                    ans[ind++] = i;
                    for (y = 0; y < m; y++) {
                        avail[y] += alloc[i][y];
                    }
                    f[i] = 1;
                }
            }
        }
    }

    // Check if system is in a safe state
    int flag = 1;
    for (i = 0; i < n; i++) {
        if (f[i] == 0) {
            flag = 0;
            printf("The system is not safe.\n");
            break;
        }
    }

    // If system is safe, print the safe sequence
    if (flag == 1) {
        printf("Following is the SAFE Sequence:\n");
        for (i = 0; i < n - 1; i++) {
            printf("P%d -> ", ans[i]);
        }
        printf("P%d\n", ans[n - 1]);
    }

    return 0;
}
