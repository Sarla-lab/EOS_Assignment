#include <stdio.h>
int main() {
    int pages[50], frame[10], count[10];
    int n, frames, i, j, k, pos, min, page_faults = 0, flag1, flag2;
    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter page reference string: ");
    for(i = 0; i < n; i++)
        scanf("%d", &pages[i]);
    printf("Enter number of frames: ");
    scanf("%d", &frames);
    for(i = 0; i < frames; i++) {
        frame[i] = -1;
        count[i] = 0;
    }
    printf("\nPage\t\tFrames\n");
    for(i = 0; i < n; i++) {
        flag1 = flag2 = 0;
        for(j = 0; j < frames; j++) {
            if(frame[j] == pages[i]) {
                count[j] = i + 1;   
                flag1 = flag2 = 1;
                break;
            }
        }
        if(flag1 == 0) {
            for(j = 0; j < frames; j++) {
                if(frame[j] == -1) {
                    frame[j] = pages[i];
                    count[j] = i + 1;
                    page_faults++;
                    flag2 = 1;
                    break;
                }
            }
        }
        if(flag2 == 0) {
            min = count[0];
            pos = 0;
            for(j = 1; j < frames; j++) {
                if(count[j] < min) {
                    min = count[j];
                    pos = j;
                }
            }
            frame[pos] = pages[i];
            count[pos] = i + 1;
            page_faults++;
        }        printf("%d\t\t", pages[i]);
        for(k = 0; k < frames; k++) {
            if(frame[k] != -1)
                printf("%d ", frame[k]);
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
