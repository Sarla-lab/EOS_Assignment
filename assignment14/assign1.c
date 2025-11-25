#include <stdio.h>
int main() {
    int n, frames, i, j, k = 0, flag, page_faults = 0;
    int pages[50], temp[10];
    printf("Enter pages: ");
    scanf("%d", &n);
    printf("Enter reference string: ");
    for(i = 0; i < n; i++)
        scanf("%d", &pages[i]);
    printf("Enter frames: ");
    scanf("%d", &frames);
    for(i = 0; i < frames; i++)
        temp[i] = -1;
    printf("Page\t\tFrames\n");
    for(i = 0; i < n; i++) {
        flag = 0;
        for(j = 0; j < frames; j++) {
            if(temp[j] == pages[i]) {
                flag = 1;
                break;
            }
        }
        if(flag == 0) {
            temp[k] = pages[i];
            k = (k + 1) % frames;
            page_faults++;
        }
        printf("%d\t\t", pages[i]);
        for(j = 0; j < frames; j++) {
            if(temp[j] != -1)
                printf("%d ", temp[j]);
            else
                printf("- ");
        }
        if(flag == 0)
            printf("Page Fault\t\n");
        else
            printf("No Fault\t\n");
    }
    printf("Total Page Faults = %d\n", page_faults);
    return 0;
}
