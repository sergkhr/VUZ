# Создать список (коллекция фильмов), состоящий из словарей (фильмы). Словари должны содержать как минимум 5 полей
# (например, номер, название, год выхода...). В список добавить хотя бы 10 словарей.
# Конструкция вида:
# films = [{"id" : 123456, "title" : "Титаник", "year" : "1997",...} , {...}, {...}, ...]
# Реализовать функции:
# – вывода информации о всех фильмах;
# – вывода информации о фильме по введенному с клавиатуры номеру;
# – вывода количества фильмов, новее введённого года;
# – обновлении всей информации о фильме по введенному номеру;
# – удалении фильма по номеру.
# Провести тестирование функций.

def film_by_id(id):
    for f in films:
        if(f.get("id") == id):
            print(f.items())


def all_info():
    for f in films:
        print(f.items())


def film_newer_than(year):
    kol = 0
    for f in films:
        if(f.get("year") > year):
            kol += 1
    print(kol)


def update_info(id):
    for f in films:
        if(f.get("id") == id):
            print("insert new info on title")
            f["title"] = input()
            print("insert new info on year")
            f["year"] = int(input())
            print("insert new info on who is staring")
            f["staring"] = input()
            print("insert new info on length in minutes")
            f["length"] = int(input())


def delete_film_by_id(id):
    for f in films:
        if(f.get("id") == id):
            films.remove(f)


films = [{
        "id" : 1,
        "title" : "first",
        "year" : 2013,
        "staring" : "your teammates",
        "length" : 93
    },
    {
        "id" : 2,
        "title" : "second",
        "year" : 1964,
        "staring" : "ralph",
        "length" : 82
    },
    {
        "id" : 3,
        "title" : "third",
        "year" : 2018,
        "staring" : "grand canyon",
        "length" : 127
    },
    {
        "id" : 4,
        "title" : "fourth",
        "year" : 2077,
        "staring" : "kianu",
        "length" : 45
    },
    {
        "id" : 5,
        "title" : "fifth",
        "year" : 1666,
        "staring" : "queen of England",
        "length" : 73
    },
    {
        "id" : 6,
        "title" : "sixth",
        "year" : 1988,
        "staring" : "bubblegum",
        "length" : 90
    },
    {
        "id" : 7,
        "title" : "seventh",
        "year" : 2000,
        "staring" : "aliens",
        "length" : 25
    },
    {
        "id" : 8,
        "title" : "8-s",
        "year" : 563,
        "staring" : "the pope",
        "length" : 2
    },
    {
        "id" : 9,
        "title" : "nineth",
        "year" : 666,
        "staring" : "devil himself",
        "length" : 666
    },
    {
        "id" : 10,
        "title" : "tenth",
        "year" : 1783,
        "staring" : "Jack",
        "length" : 109
    }]

all_info()
print()
film_by_id(1)
print()
film_newer_than(1800)
print()
delete_film_by_id(1)
delete_film_by_id(3)
all_info()
print()
update_info(2)
print()
film_by_id(2)