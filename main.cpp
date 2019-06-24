#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <vector>
#include <windows.h>
using namespace std;

void coutFile(vector <int> &data, fstream &file) {
    string path;
    cout << "Введите название файла (без расширения .txt): ";
    cin >> path;
    file.open(path + ".txt", ios::in);
    if (!file.is_open()) { // Проверка на наличие нужного файла
        cout << "Данного файла не существует.";
        system("pause");
        return;
    }
    else {
        int ptr;
        while (!file.eof()) {
            file >> ptr;
            data.push_back(ptr);
        }
    }
    cout << "Файл считан" << endl;
    file.close();
}

int _max(vector <int> data) { // Нахождение Максимума
    int max = data[0];
    for (int i = 1; i < data.size(); i++)
    {
        if (data[i] > max)
            max = data[i];
    }
    return max;
}

int _min(vector<int>data) { // Нахождение Минимума
    int min = data[0];
    for (int i = 1; i < data.size(); i++) {
        if (data[i] < min)
            min = data[i];
    }
    return min;
}
float median(vector <int> data) { // Нахождение Медианы
    while(1) {
        bool swap = true;
        for (int j = 0; j < data.size() - 1; ++j) { // Сортировка массива пузырьком
            if (data[j] < data[j + 1]) {
                swap = false;
                int tmp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = tmp;
            }
        }
        if (swap)
            break;
    }
    if (data.size() % 2 != 0) { // Если нечетное количество элементов
        return data[(int)data.size() / 2];
    }
    else { // Если четное количество элементов
        size_t index = data.size() / 2;
        return ((float)(data[index - 1] + data[index]) / 2.0);
    }
}

float average(vector<int>data) { // Нахождение Среднего Значения
    float average = 0;
    for (int i = 0; i < data.size(); i++) {
        average += data[i];
    }
    return average / data.size();
}

int percentile(vector <int> data, float stepen)
{
    vector <int> mas(data.size());
    for (int i = 0; i < mas.size(); ++i) {
        mas[i] = data[i];
    }
    while(1) {
        bool swap = true;
        for (int j = 0; j < mas.size() - 1; ++j) {
            if (mas[j] > mas[j + 1]) {
                swap = false;
                int tmp = mas[j];
                mas[j] = mas[j + 1];
                mas[j + 1] = tmp;
            }
        }
        if (swap)
            break;
    }
    int prc = mas[(int)floor(mas.size() * stepen)];
    mas.clear();
    return prc;
}

int  main() {
    /*setlocale(LC_ALL, "Russian"); // Компилятор не хочет видеть кирилицу, добавил два варианта на всякий случай
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);*/
    fstream file;
    vector <int> vect;
    coutFile(vect, file);
    cout << "90 percentile <" << percentile(vect,0.9) << ">" << endl;
    cout << "median <" << median(vect) << ">" << endl;
    cout << "average <" << average(vect) << ">" << endl;
    cout << "max <" << _max(vect) << ">" << endl;
    cout << "min <" << _min(vect) << ">" << endl;
    system("pause");
    vect.clear();
    return 0;
}