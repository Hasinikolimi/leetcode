#define MOD 1000000007

int gcd(int a, int b) {
    while (b) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int subsequencePairCount(int* nums, int numsSize) {
    int maxVal = 0;
    for (int i = 0; i < numsSize; i++)
        if (nums[i] > maxVal)
            maxVal = nums[i];

    int size = maxVal + 1;

    long long **dp = (long long **)malloc(size * sizeof(long long *));
    long long **ndp = (long long **)malloc(size * sizeof(long long *));
    for (int i = 0; i < size; i++) {
        dp[i] = (long long *)calloc(size, sizeof(long long));
        ndp[i] = (long long *)calloc(size, sizeof(long long));
    }

    dp[0][0] = 1;

    for (int idx = 0; idx < numsSize; idx++) {
        int x = nums[idx];

        for (int i = 0; i < size; i++)
            memcpy(ndp[i], dp[i], size * sizeof(long long));

        for (int g1 = 0; g1 < size; g1++) {
            for (int g2 = 0; g2 < size; g2++) {
                long long cur = dp[g1][g2];
                if (!cur) continue;

                int ng1 = (g1 == 0) ? x : gcd(g1, x);
                ndp[ng1][g2] = (ndp[ng1][g2] + cur) % MOD;

                int ng2 = (g2 == 0) ? x : gcd(g2, x);
                ndp[g1][ng2] = (ndp[g1][ng2] + cur) % MOD;
            }
        }

        long long **tmp = dp;
        dp = ndp;
        ndp = tmp;
    }

    long long ans = 0;
    for (int g = 1; g < size; g++) {
        ans = (ans + dp[g][g]) % MOD;
    }

    for (int i = 0; i < size; i++) {
        free(dp[i]);
        free(ndp[i]);
    }
    free(dp);
    free(ndp);

    return (int)ans;
}