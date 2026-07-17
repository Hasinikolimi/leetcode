int myAtoi(char *s) {
    int i = 0, sign = 1;
    int result = 0;

    while (s[i] == ' ')
        i++;

    if (s[i] == '+' || s[i] == '-') {
        if (s[i] == '-')
            sign = -1;
        i++;
    }

    while (s[i] >= '0' && s[i] <= '9') {
        int digit = s[i] - '0';

        if (sign == 1) {
            if (result > INT_MAX / 10 ||
                (result == INT_MAX / 10 && digit > 7))
                return INT_MAX;

            result = result * 10 + digit;
        } else {
            if (result < INT_MIN / 10 ||
                (result == INT_MIN / 10 && digit > 8))
                return INT_MIN;

            result = result * 10 - digit;
        }

        i++;
    }

    return result;
}