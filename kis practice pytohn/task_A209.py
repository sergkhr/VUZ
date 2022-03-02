# Написать функцию max_3_sum, которая возвращает наибольшую сумму трех подряд идущих элементов списка.
#
# Пример:
# max_3_sum([1,2,3,4,5]) ==> 12



import traceback


def max_3_sum(arr):
    if(len(arr) < 3):
        return 0
    else:
        sum = arr[0] + arr[1] + arr[2]
        maxsum = sum
        for i in range(3, len(arr)):
            sum = sum + arr[i] - arr[i-3]
            if(sum > maxsum):
                maxsum = sum
    return maxsum


# Тесты
try:
    assert max_3_sum([1, 2, 3, 4, 5]) == 12
    assert max_3_sum([10, 10, 30, 20, 10, 15, 30]) == 60
    assert max_3_sum([20, 10, -80, 10, 10, 15, 30]) == 55
    assert max_3_sum([10, -80, -10, -10, 15, -35, 20]) == 0

except AssertionError:
    print("TEST ERROR")
    traceback.print_exc()
else:
    print("TEST PASSED")