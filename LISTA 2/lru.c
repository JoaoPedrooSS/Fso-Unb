#include <stdio.h>
#include <stdlib.h>

#define MAX_PAGES 100000
#define MAX_FRAMES 100000

int main() {
    int num_frames, num_pages;
    scanf("%d %d", &num_frames, &num_pages);

    int pages[MAX_PAGES];
    for (int i = 0; i < num_pages; i++) {
        scanf("%d", &pages[i]);
    }

    int last_used[MAX_FRAMES], memory[MAX_FRAMES];
    int time = 0, page_faults = 0;

    for (int i = 0; i < num_frames; i++) {
        memory[i] = -1;
    }

    for (int i = 0; i < num_pages; i++) {
        int current_page = pages[i];
        int found_index = -1;

        for (int j = 0; j < num_frames; j++) {
            if (memory[j] == current_page) {
                found_index = j;
                break;
            }
        }

        if (found_index != -1) {
            last_used[found_index] = time;
        } else {
            int replace_index = 0;
            if (time < num_frames) {
                replace_index = time;
            } else {
                int oldest_time = last_used[0];
                for (int j = 1; j < num_frames; j++) {
                    if (last_used[j] < oldest_time) {
                        oldest_time = last_used[j];
                        replace_index = j;
                    }
                }
            }
            memory[replace_index] = current_page;
            last_used[replace_index] = time;
            page_faults++;
        }
        time++;
    }

    printf("%d\n", page_faults);
    return 0;
}
