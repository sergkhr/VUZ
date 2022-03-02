# Цена телефонного звонка следующая:
# первая минута звонка стоит min1 рублей,
# минута со второй по 10 включительно стоит min2_10 рублей,
# а начиная с 11 минуты – min11 рублей.
# Написать функцию phone_call(min1, min2_10, min11, s),
# которая возвращает максимальную длительность разговора,
# которую можно совершить, если на счету s рублей
#
# Пример:
# phone_call(3, 1, 2, 20) ==> 14

import traceback


def phone_call(min1, min2_10, min11, s):
    t = 0
    if(s >= min1):
        t = 1
        s -= min1
    else:
        return 0
    while(s >= min2_10 and t < 10):
        t += 1
        s -= min2_10
    if(t < 10):
        return t
    else:
        t += s // min11

    return t


# Тесты
try:
    assert phone_call(3,1,2,20) == 14
    assert phone_call(10,1,2,22) == 11
    assert phone_call(2,2,1,2) == 1
    assert phone_call(1,2,1,6) == 3
except AssertionError:
    print("TEST ERROR")
    traceback.print_exc()
else:
    print("TEST PASSED")
