#include <stdint.h>

// @leet start
int reverse(int x)
{
    int ret = 0, neg = x < 0 ? 1 : 0;

    int d;
    while (x != 0) {
        d = x % 10;
        x /= 10;

        if (neg) {
            if (ret < INT32_MIN / 10) {
                return 0;
            }
            if (d < INT32_MIN - ret * 10) {
                return 0;
            }
        } else {
            if (ret > INT32_MAX / 10) {
                return 0;
            }
            if (d > INT32_MAX - ret * 10) {
                return 0;
            }
        }

        ret = ret * 10 + d;
    }

    return ret;
}
// @leet end
