#include <stdlib.h>

int gcd(int a, int b) {
    while (b != 0) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

long long gcdSum(int* nums, int numsSize) {
    int *prefixGcd = (int *)malloc(numsSize * sizeof(int));

    int mx = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > mx)
            mx = nums[i];
        prefixGcd[i] = gcd(nums[i], mx);
    }

    qsort(prefixGcd, numsSize, sizeof(int), compare);

    long long ans = 0;
    for (int i = 0; i < numsSize / 2; i++) {
        ans += gcd(prefixGcd[i], prefixGcd[numsSize - 1 - i]);
    }

    free(prefixGcd);
    return ans;
}
