#include <stdlib.h>
#include <string.h>

int cmp(const void *a, const void *b) {
    return strcmp(*(char **)b, *(char **)a);
}

char* makeLargestSpecial(char* s) {
    int n = strlen(s);
    if (n <= 2)
        return strdup(s);

    char **parts = (char **)malloc(n * sizeof(char *));
    int cnt = 0;

    int bal = 0;
    int start = 0;

    for (int i = 0; i < n; i++) {
        if (s[i] == '1')
            bal++;
        else
            bal--;

        if (bal == 0) {
            int len = i - start + 1;

            char *mid = (char *)malloc(len - 1);
            strncpy(mid, s + start + 1, len - 2);
            mid[len - 2] = '\0';

            char *inside = makeLargestSpecial(mid);
            free(mid);

            int m = strlen(inside);

            parts[cnt] = (char *)malloc(m + 3);
            parts[cnt][0] = '1';
            strcpy(parts[cnt] + 1, inside);
            parts[cnt][m + 1] = '0';
            parts[cnt][m + 2] = '\0';

            free(inside);
            cnt++;

            start = i + 1;
        }
    }

    qsort(parts, cnt, sizeof(char *), cmp);

    int total = 1;
    for (int i = 0; i < cnt; i++)
        total += strlen(parts[i]);

    char *ans = (char *)malloc(total);
    ans[0] = '\0';

    for (int i = 0; i < cnt; i++) {
        strcat(ans, parts[i]);
        free(parts[i]);
    }

    free(parts);

    return ans;
}