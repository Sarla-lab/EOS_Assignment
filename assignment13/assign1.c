#include <stdio.h>
#include <pthread.h>
void* thread_func(void *param) {
    int *arr = (int*)param;
    for (int i = 0; i < 9; i++) {
        int min = i;
        for (int j = i + 1; j < 10; j++) {
            if (arr[j] < arr[min])
                min = j;
	}
        int temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
    }
    return NULL;
}
int main() {
    int arr[10];
    pthread_t tid;
    printf("Enter 10 integers:\n");
    for (int i = 0; i < 10; i++)
        scanf("%d", &arr[i]);
    pthread_create(&tid, NULL, thread_func, arr);
    pthread_join(tid, NULL);
    printf("Sorted array:\n");
    for (int i = 0; i < 10; i++)
        printf("%d ", arr[i]);
    printf("\n");
    return 0;
}
