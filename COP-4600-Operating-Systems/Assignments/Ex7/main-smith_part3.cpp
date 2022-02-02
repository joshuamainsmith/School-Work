#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main(int argc, char* argv[]) {

    if (argc != 6) {
        printf("Exactly 5 arguments required\n");
    }

    /*
    fd[0] from parent to c1
    fd[1] from c1 to c2
    fd[2] from c2 to parent
    fd[3] from c1 to parent
    */
    int fd[4][2];
    int nums[5];
    int median = 0;

    for (int i = 0; i < 4; i++) {
        if (pipe(fd[i]) < 0) {
            return 1;
        }
    }

    int c1 = fork();
    
    if (c1 < 0) {
        return 1;
    }

    int c2 = fork();

    if (c2 < 0) {
        return 1;
    }

    if (c1 == 0) {
        // First Child Process

        close(fd[0][1]);
        close(fd[1][0]);
        close(fd[2][0]);
        close(fd[2][1]);
        close(fd[3][0]);

        // read from parent
        read(fd[0][0], &nums, sizeof(nums));

        // sort ints
        sort(nums, nums + 5);

        // write to parent
        write(fd[3][1], &nums, sizeof(nums));
        // write to c2
        write(fd[1][1], &nums, sizeof(nums));

        close(fd[0][0]);
        close(fd[1][1]);
        close(fd[3][1]);

        return 0;
    }    

    if (c2 == 0) {
        // Second Child process

        close(fd[0][0]);
        close(fd[0][1]);
        close(fd[1][1]);
        close(fd[2][0]);
        close(fd[3][0]);
        close(fd[3][1]);

        // read from c1
        read(fd[1][0], &nums, sizeof(nums));

        // median is always argv[2]
        median = nums[2];
        
        // write to parent
        write(fd[2][1], &median, sizeof(median));

        close(fd[1][0]);
        close(fd[2][1]);
        return 0;
    }

    // Parent process

        close(fd[0][0]);
        close(fd[1][0]);
        close(fd[1][1]);
        close(fd[2][1]);
        close(fd[3][1]);

        for(int i = 0; i <= 4; i++){
            nums[i] = atoi(argv[i+1]);
        }

        // write to c1
        write(fd[0][1], &nums, sizeof(nums));

        // read from c2
        read(fd[2][0], &median, sizeof(median));
        printf("Median: %d\n", median);

        close(fd[2][0]);

        // read from c1
        read(fd[3][0], &nums, sizeof(nums));

        printf("Sorted: ");

        for(int i = 0; i <= 4; i++){
            printf("%d ", nums[i]);
        }

        printf("\n");

        close(fd[0][1]);
        close(fd[2][0]);
        close(fd[3][0]);

        // wait for child procs to finish
        waitpid(c1, NULL, 0);
        waitpid(c2, NULL, 0);

    return 0;
}
