# Написать функцию mean_square(arr1,arr2), которая получает два целочисленных списка одинаковой длины,
# сравнивает значение каждого члена в одном списке с соответствующим элементом в другом, 
# возводит в квадрат разницу абсолютных значений между этими двумя значениями и возвращает 
# среднее значение квадратов каждой парой элементов. 
#
# Пример:
# mean_square([0, -1],[-1, 0]) ==> 1 --> ( (0-(-1))^2 + (-1-0)^2 ) / 2 = 1


import traceback


def mean_square(arr1,arr2):
    sum = 0
    for i in range(len(arr1)):
        sum += abs(arr1[i]-arr2[i])**2
    return (sum/len(arr1))


# Тесты
try:
    assert mean_square([1,2,3],[4,5,6]) == 9
    assert mean_square([10, 20, 10, 2],[10, 25, 5, -2]) == 16.5
    assert mean_square([0, -1],[-1, 0]) == 1
    assert mean_square([10, 10],[10, 10]) == 0
except AssertionError:
    print("TEST ERROR")
    traceback.print_exc()
else:
    print("TEST PASSED")
    
 #   Завершите функцию, которая