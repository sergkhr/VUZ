import java.io.*;
import java.util.Scanner;
import java.math.*;

import static java.lang.Character.toUpperCase;

public class Main {

    static Scanner in = new Scanner(System.in);
    static String[][] matrix = {{"","","",""},{"","","",""},{"","","",""},{"","","",""}};
    static int[] mas = new int[16];

    public static void main(String[] args) {
        System.out.println("как вы хотите ввести матрицу: случайно или с клавиатуры?");
        int variant = 0;
        boolean goodInput;
        do {
            goodInput = true;
            System.out.println("пожалуйста введите 0 или 1: 0 - для случайной матрицы, 1 - для вводимой с клавиатуры");
            if(in.hasNextInt()){
                variant = in.nextInt(); //проверка наличия целого числа, если его нет то ввод считается некорректным
                in.nextLine();
            }
            else{
                in.nextLine();
                goodInput = false;
            }
        }while(!goodInput || (variant != 0 && variant != 1)); //если получено не значение 0 или 1, то ввод некорректен

        if(variant == 0) randomizeMatrix(); //вызов нужной подпрограммы в зависимости от выбора пользователя
        else insertMatrix();

        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                int tmp = lowerSystem(matrix[i][j]); //значения матрицы переводятся в 10сс и записываются в массив
                mas[4*i + j] = tmp;
            }
        }

        sortMas(); // вызов подпрограммы сортировки массива

        for(int i = 0; i < 8; i++){
            String tmp = upSystem(mas[i]); //значения из отсортированного массива переводятся в 16сс и записываются
            matrix[i%4][i/4] = tmp;        //в матрицу: первые 8 элементов - в левую часть, вторые - во вторую
            tmp = upSystem(mas[i+8]);
            matrix[(i+8) % 4][(i+8) / 4] = tmp;
        }

        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                System.out.print(matrix[i][j] + " "); //выводим матрицу
            }
            System.out.println();
        }
    }

    static void insertMatrix(){ //ввод матрицы пользователем и проверка корректности введенных данных
        String digits = "0123456789ABCDEF";
        String lowerdigits = "abcdef";
        boolean goodInput;
        do{
            goodInput = true;
            System.out.println("Введите матрицу построчно (4 строки по 4 числа в каждой), используйте строго\n" +
                               "по два символа на одно число. Разрешается использовать только десятичные\n" +
                               "цифры и символы из набора: A, B, C, D, E, F");
            for(int i = 0; i < 4; i++){
                for(int j = 0; i < 4; i++){
                    matrix[i][j] = "";
                }
            }
            for(int str = 0; str < 4 && goodInput; str++){

                String s = in.nextLine();

                for(int i = 0; i < s.length(); i++){
                    if(s.charAt(i) == ' '){
                        s = s.substring(0, i) + s.substring(i+1); //удаление пробелов из строки
                        i--;
                    }
                }

                if(s.length() == 8){
                    for(int i = 0; i < 8; i++){
                        if(lowerdigits.indexOf(s.charAt(i)) != -1){ //найденный символ нижнего регистра переводится
                            s = s.substring(0, i) + toUpperCase(s.charAt(i)) + s.substring(i+1); //в верхний
                        }

                        if(digits.indexOf(s.charAt(i)) != -1){ //если символ является цифрой то он записывается,
                            matrix[str][i/2] += s.charAt(i);   //в противном случае данные считаются некорректными
                        }
                        else{
                            goodInput = false;
                            break;
                        }
                    }
                }
                else{
                    goodInput = false;
                    break;
                }
            }
        }
        while(!goodInput);
    }

    static void randomizeMatrix(){ //создание случайной матрицы
        String digits = "0123456789ABCDEF";
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){ //заполняем матрицу случайными двузначными числами в 16сс
                matrix[i][j] = upSystem((int)(Math.random() * (255 - 16 + 1)) + 16); //16 - 255 в 16сс 10 - FF
            }
        }
    }

    static int lowerSystem(String num){ //перевод двузначного 16-ичного числа в 10-ичное
        String digits = "0123456789ABCDEF";
        int num10 = 16 * digits.indexOf(num.charAt(0)) + digits.indexOf(num.charAt(1));
        return num10;
    }

    static String upSystem(int num){ //перевод десятичного числа в пределах от 0 до 255 в 16-ичное число
        String digits = "0123456789ABCDEF";
        String num16 = "" + digits.charAt(num / 16) + digits.charAt(num % 16);
        return num16;
    }

    static void sortMas(){ //сортируем массив mas из 16 элементов
        for(int i = 0; i < 15; i++){
            for(int j = (i+1); j < 16; j++){
                if(mas[i] > mas[j]){
                    int tmp = mas[i];
                    mas[i] = mas[j]; //элементы меняются местами
                    mas[j] = tmp;
                }
            }
        }
    }
}
