#include <math.h>

// @leet start
int numOfSubarrays(int* arr, int arrSize)
{
    int result = 0;

    // sum keeps track of the current accumulative sum
    // the counts keep track of all the sums up to an element with each parity
    int sum = 0, even_sum_count = 1, odd_sum_count = 0;

    // For each element, update the accumulative sum and check its parity. To
    // calculate the sum of each subarray, you would need to take the
    // difference of the current sum and the sum of elements before the
    // subarray. However, since we are only interested in if this difference is
    // odd or not, we just need to know if the two numbers have different
    // parities. This is why simply adding the number of sums with the opposite
    // parity than the current sum effectively calculates the number of odd
    // subarrays up to the current element.
    for (int i = 0; i < arrSize; i++) {
        sum += arr[i];
        if (sum % 2 == 0) {
            result += odd_sum_count;
            even_sum_count++;
        } else {
            result += even_sum_count;
            odd_sum_count++;
        }

        // handle large results:
        result %= ((int)pow(10., 9.) + 7);
    }

    return result;
}
// @leet end
