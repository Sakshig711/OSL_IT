#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void swap(int *a, int *b)
{
      int temp = *a;
      *a = *b;
      *b = temp;
}

int partition(int arr[], int low, int high)
{
      int pivot = arr[high];
      int i = low - 1;
      for (int j = low; j <= high - 1; j++)
      {
            if (arr[j] < pivot)
            {
                  i++;
                  swap(&arr[i], &arr[j]);
            }
      }
      swap(&arr[i + 1], &arr[high]);
      return i + 1;
}

void quickSort(int arr[], int low, int high)
{
      if (low < high)
      {
            int pi = partition(arr, low, high);
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
      }
}

void printArray(int arr[], int size)
{
      for (int i = 0; i < size; i++)
      {
            printf("%d ", arr[i]);
      }
      printf("\n");
}

void Zombie()
{
      pid_t pid = fork();
      if (pid < 0)
      {
            perror("fork");
            exit(1);
      }
      else if (pid == 0)
      {
            printf("Child process %d started, parent process is %d.\n", getpid(), getppid());
            exit(0);
      }
      else
      {
            printf("Parent process %d created child process %d.\n", getpid(), pid);
            sleep(3);
            system("ps -eo pid,ppid,state,cmd | grep defunct");
            printf("Parent process %d is terminating.\n", getpid());
      }
      sleep(5);
}

void Orphan()
{
      pid_t pid = fork();
      if (pid < 0)
      {
            perror("fork");
            exit(1);
      }
      else if (pid == 0)
      {
            sleep(3);
            printf("Child process %d started, parent process is %d.\n", getpid(), getppid());
            system("ps -eo pid,ppid,state,cmd | grep a.out");
            printf("Child process %d finished, now adopted by init (PID: %d).\n", getpid(), getppid());
      }
      else
      {
            printf("Parent process %d created child process %d.\n", getpid(), pid);
            system("ps -eo pid,ppid,state,cmd | grep a.out");
            printf("Parent process %d is terminating.\n", getpid());
            exit(0);
      }
      sleep(3);
}

void SortByWaitCall(int arr[], int n)
{
      pid_t pid = fork();
      if (pid < 0)
      {
            perror("fork failed");
            exit(1);
      }
      else if (pid == 0)
      {
            printf("Child process sorting with Quick Sort...\n");
            quickSort(arr, 0, n - 1);
            printf("Child process sorted array: ");
            printArray(arr, n);
            printf("Child process (PID: %d) finished.\n", getpid());
            exit(0);
      }
      else
      {
            printf("Parent process sorting with Quick Sort...\n");
            quickSort(arr, 0, n - 1);
            printf("Array sorted and wait called\n");
            int status;
            pid_t child_pid = wait(&status);
            if (child_pid < 0)
            {
                  perror("wait failed");
            }
            else
            {
                  printf("Parent process (PID: %d) waited for child process (PID: %d)\n", getpid(), child_pid);
            }
      }
}

int main()
{
      int n, i, c;
      printf("Enter number of integers to sort: ");
      scanf("%d", &n);
      int arr[n];
      printf("Enter the integers:\n");
      for (i = 0; i < n; i++)
      {
            scanf("%d", &arr[i]);
      }
      printf("Enter choice: 1. Zombie 2. Orphan 3. Using wait and sort\n");
      scanf("%d", &c);
      switch (c)
      {
      case 1:
            Zombie();
            break;
      case 2:
            Orphan();
            break;
      case 3:
            SortByWaitCall(arr, n);
            break;
      default:
            printf("Invalid choice\n");
            break;
      }
      return 0;
}
