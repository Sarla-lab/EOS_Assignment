#include <stdio.h>
#include <pthread.h>
struct array {
    int *arr;
    int size;
};
void* thread_func(void *param) {
    struct array *p = (struct array*)param;
    for (int i = 0; i < p->size - 1; i++) {
        for (int j = 0; j < p->size - i - 1; j++) {
            if (p->arr[j] > p->arr[j + 1]) {
                int temp = p->arr[j];
                p->arr[j] = p->arr[j + 1];
                p->arr[j + 1] = temp;
            }
        }
    }
    return NULL;
}
int main() {
    int n;
    printf("Enter size of array: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    struct array a = {arr, n};
    pthread_t tid;
    pthread_create(&tid, NULL, thread_func, &a);
    pthread_join(tid, NULL);
    printf("Sorted array:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
    return 0;
}
