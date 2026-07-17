#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

int cmpInt(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int* gcdValues(int* nums, int numsSize, long long* queries, int queriesSize, int* returnSize) {
    int maxVal = 0;
    for (int i = 0; i < numsSize; i++)
        if (nums[i] > maxVal)
            maxVal = nums[i];

    int *freq = (int *)calloc(maxVal + 1, sizeof(int));
    for (int i = 0; i < numsSize; i++)
        freq[nums[i]]++;

    int *cnt = (int *)calloc(maxVal + 1, sizeof(int));

    // Count numbers divisible by d
    for (int d = 1; d <= maxVal; d++) {
        for (int j = d; j <= maxVal; j += d)
            cnt[d] += freq[j];
    }

    ll *exact = (ll *)calloc(maxVal + 1, sizeof(ll));

    // Inclusion-Exclusion
    for (int d = maxVal; d >= 1; d--) {
        ll c = cnt[d];
        exact[d] = c * (c - 1) / 2;
        for (int j = d + d; j <= maxVal; j += d)
            exact[d] -= exact[j];
    }

    ll *prefix = (ll *)calloc(maxVal + 1, sizeof(ll));
    for (int i = 1; i <= maxVal; i++)
        prefix[i] = prefix[i - 1] + exact[i];

    int *ans = (int *)malloc(sizeof(int) * queriesSize);

    for (int i = 0; i < queriesSize; i++) {
        ll k = queries[i] + 1; // Convert to 1-based

        int l = 1, r = maxVal;
        while (l < r) {
            int mid = (l + r) / 2;
            if (prefix[mid] >= k)
                r = mid;
            else
                l = mid + 1;
        }
        ans[i] = l;
    }

    free(freq);
    free(cnt);
    free(exact);
    free(prefix);

    *returnSize = queriesSize;
    return ans;
}