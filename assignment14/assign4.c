#include <stdio.h>
int main() {
    int pages[50], frames[10], ref[10];
    int n, f, i, j, pointer = 0, flag1, flag2, page_faults = 0;
    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter page reference string: ");
    for(i = 0; i < n; i++)
        scanf("%d", &pages[i]);
    printf("Enter number of frames: ");
    scanf("%d", &f);
    for(i = 0; i < f; i++) {
        frames[i] = -1;
        ref[i] = 0; 
    }
    printf("\nPage\t\tFrames\n");
    for(i = 0; i < n; i++) {
        flag1 = flag2 = 0;
        for(j = 0; j < f; j++) {
            if(frames[j] == pages[i]) {
                ref[j] = 1;  
                flag1 = flag2 = 1;
                break;
            }
        }
        if(flag1 == 0) {
            while(1) {
    		    if(frames[pointer] == -1) {
                    frames[pointer] = pages[i];
                    ref[pointer] = 1;
                    pointer = (pointer + 1) % f;
                    page_faults++;
                    flag2 = 1;
                    break;
                }
		else if(ref[pointer] == 0) {
                    frames[pointer] = pages[i];
                    ref[pointer] = 1;
                    pointer = (pointer + 1) % f;
                    page_faults++;
                    flag2 = 1;
                    break;
                }
		else {
                    ref[pointer] = 0;
                    pointer = (pointer + 1) % f;
                }
            }
        }
        printf("%d\t\t", pages[i]);
        for(j = 0; j < f; j++) {
            if(frames[j] != -1)
                printf("%d(%d) ", frames[j], ref[j]);
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
