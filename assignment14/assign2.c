#include <stdio.h>
int main() {
    int n, frames, i, j, k, flag1, flag2, flag3, pos, max, page_faults = 0;
    int pages[50], temp[10], future[10];
    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter page reference string: ");
    for(i = 0; i < n; i++)
        scanf("%d", &pages[i]);
    printf("Enter number of frames: ");
    scanf("%d", &frames);
    for(i = 0; i < frames; i++)
        temp[i] = -1;
    printf("\nPage\t\tFrames\n");
    for(i = 0; i < n; i++) {
        flag1 = flag2 = 0;
        for(j = 0; j < frames; j++) {
            if(temp[j] == pages[i]) {
                flag1 = flag2 = 1;
                break;
            }
        }
        if(flag1 == 0) {
            for(j = 0; j < frames; j++) {
                if(temp[j] == -1) {
                    temp[j] = pages[i];
                    flag2 = 1;
                    page_faults++;
                    break;
                }
            }
        }
        if(flag2 == 0) {
            flag3 = 0;
            for(j = 0; j < frames; j++) {
                future[j] = -1;
                for(k = i + 1; k < n; k++) {
                    if(temp[j] == pages[k]) {
                        future[j] = k;
                        break;
                    }
                }
            }
            for(j = 0; j < frames; j++) {
                if(future[j] == -1) {
                    pos = j;
                    flag3 = 1;
                    break;
                }
            }
            if(flag3 == 0) {
                max = future[0];
                pos = 0;
                for(j = 1; j < frames; j++) {
                    if(future[j] > max) {
                        max = future[j];
                        pos = j;
                    }
                }
            }

            temp[pos] = pages[i];
            page_faults++;
        }
        printf("%d\t\t", pages[i]);
        for(j = 0; j < frames; j++) {
            if(temp[j] != -1)
                printf("%d ", temp[j]);
            else
                printf("- ");
        }
        if(flag1 == 0)
            printf("\tPage Fault\n");
        else
            printf("\tNo Fault\n");
    }
    printf("\nTotal Page Faults = %d\n", page_faults);
    return 0;
}
