#include <assert.h>
#include <stdio.h>
#include "macros.h"

int main(void)
{
    int i = 0;
    int arr[20];
    int* curr;

    assert(6 == MAX(6 > 1 ? 6 : 1, 5));
    assert(10.0f == MAX(10.0f, 5.0f));
    assert(10.0 == MAX(10.0, 5.0f));

    assert(5 == MIN(10, 5));
    assert(5 == MIN(10.0f, 5.0f));
    assert(5.0f == MIN(10.0, 5.0f));

    assert(1 == ABS(1));
    assert(1 == ABS(-1));
    assert(1.0f == ABS(1.0f));
    assert(1.0f == ABS(-1.0f));
    assert(1.0 == ABS(1.0));
    assert(1.0 == ABS(-1.0));

    curr = arr;

    RANGE(i, 1, 20) {
        *curr++ = i;
    }

    for (i = 1; i <= 20; i++) {
        assert(arr[i - 1] == i);
    }

    curr = arr;

    RANGE_DESC(i, 14, -5) {
        *curr++ = i;
    }

    for (i = 14; i >= -5; i--) {
        assert(arr[14 - i] == i);
    }

    SET(arr, 0, 20, 0);

    for (i = 0; i < 20; i++) {
        printf("%d ", arr[i]);
    }
    puts("");
    

    SET(arr, 5, 5, 100);
    
    for (i = 0; i < 5; i++) {
        assert(arr[i] == 0);
    }

    for (i = 0; i < 20; i++) {
        printf("%d ", arr[i]);
    }
    puts("");

    for (i = 5; i < 10; i++) {
        assert(arr[i] == 100);
    }

    for (i = 10; i < 20; i++) {
        assert(arr[i] == 0);
    }

    printf("NO ASSERT!");

    return 0;
}
