#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <regex>
using namespace std;

class Train {

private:

    string PATH = "info.txt";
    int fileLinesCount = CountLinesInFile(PATH);
    string* time_string = new string[fileLinesCount];
    float* time_float = new float[fileLinesCount];
    struct trainInfo {
        char flightNum[5];
        string destination;
        string time;
        float time_formatted;
        int seatsAmount;
    } train[50];

public:

    int CountLinesInFile(string filename)
    {
        ifstream F(filename, ios::in);

        if (!F)
        {
            return -1;
        }

        int count = 0;
        char buffer[1000];

        while (!F.eof())
        {
            count++;
            F.getline(buffer, 1000);
        }
        F.close();
        return count;
    }


    void inputData() {
        ofstream TI;
        TI.open("info.txt", fstream::app);

        if (TI.is_open()) {
            system("cls");
            cout << "Файл открыт." << endl << endl;
            cout << "Введите количество рейсов: ";
            int amountOfFlights = 0;
            cin >> amountOfFlights;

            for (int i = 0; i < amountOfFlights; i++) {
                system("cls");
                cout << "Введите рейс номер " << i + 1 << endl;
                cout << "Введите номер поезда (5 цифр): ";
                cin >> train[i].flightNum;
                TI << "Номер рейса: " << train[i].flightNum << " - ";

                cout << "Введите пункт назначения поезда: ";
                cin >> train[i].destination;
                TI << "Пункт назначения: " << train[i].destination << " - ";

                cout << "Введите время отправления (21.00): ";
                cin >> train[i].time;
                TI << "Время отправки: " << train[i].time << " - ";

                cout << "Введите количество свободных мест в поезде: ";
                cin >> train[i].seatsAmount;
                TI << "Количество свободных мест: " << train[i].seatsAmount << endl;

                cout << "Рейс добавлен!" << endl;

                TI.close();
            }
        }
        else {
            cout << "Ошибка при открытии файла." << endl;
        }
    }


    void separation() {
        int el = 0;
        const char SEP = ' ';
      
        fstream TI;
        TI.open(PATH);
        if (TI.is_open()) {
            string str;
            while (!TI.eof()) {
                string str = "";
                getline(TI, str);

                int i = 0;
                
                string temp;
                istringstream ist(str);
                while (getline(ist, temp, SEP)) {

                    i++;
                    if (i == 11) {
                        time_string[el] = temp;
                        el++;
                    }        
                }           
            }
            

        }
        else {
            cout << "Ошибка при открытии файла." << endl;
        }

        for (int i = 0; i < fileLinesCount; i++) {
            time_float[i] = strtof(time_string[i].c_str(), nullptr);
        }
    }

    float* time_sort() {

        for (int i = 0; i < fileLinesCount - 1; i++) {
            int min_index = i;
            for (int j = i + 1; j < fileLinesCount; j++) {
                if (time_float[j] < time_float[min_index]) {
                    min_index = j;
                }
            }

            float temp;
            temp = time_float[i];
            time_float[i] = time_float[min_index];
            time_float[min_index] = temp;

        }
        return time_float;
    }


    bool linear_search(float time) {
        
        for (int i = 0; i < fileLinesCount; i++) {
            if (time_float[i] == time) {
                return true;
            }
        }
        return false;
    }

    int fileLines() {
        return fileLinesCount;
    }

    bool binary_search(float arr[], float key, int left, int right) { // key - искомое число, left - начало, right - конец.
        if (right < left)
            return false;
        else if (left == right)
            if (time_float[left] == key)
                return true;
            else
                return false;
        else {
            int middle = left + (right - left) / 2;
            if (key < time_float[middle])
                return binary_search(time_float, key, left, middle);
            else if (key > time_float[middle])
                return binary_search(time_float, key, middle + 1, right);
            else
                return true;
        }
    }

};

int main()
{
    bool appendFlights;
    cout << "Вы хотите добавить новые рейсы? (1 - да, 0 - нет): ";
    cin >> appendFlights;
    Train first;
    if (appendFlights) {
        first.inputData();
    }
    
    
    first.separation();
    bool isActive = true;
    while (isActive) {

        float findingTime = 0;
        cout << "Какое время вы хотите найти? (21.00): ";
        cin >> findingTime;
        int number = 0;
        cout << "Каким поиском вы хотите воспользоваться: " << endl << "\t1 - линейный поиск." << endl << "\t2 - двоичный поиск." << endl;
        cin >> number;
        system("cls");
        
        switch (number) {
        case 1: if (first.linear_search(findingTime)) {
            cout << "Время найдено!" << endl;
        }
              else {
            cout << "Время не найдено!" << endl;
        }
              break;
        case 2: if (first.binary_search(first.time_sort(), findingTime, 0, first.fileLines())) {
            cout << "Время найдено!" << endl;
        }
              else {
            cout << "Время не найдено!" << endl;
        }
              break;
        default: cout << "Ошибка." << endl;
        }
        cout << "Хотите найти еще какое нибудь время? (1 - да, 0 - нет): ";
        cin >> isActive;
        system("cls");
    }
}
