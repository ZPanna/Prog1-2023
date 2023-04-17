#include <iostream>
#include <time.h>

using namespace std;

int pickRandom() {
    return rand() % 80 + 1;
}

int find(int* array, int len, int num) {
    for (int i = 0; i < len; i++) {
        if (array[i] == num) {
            return i;
        }
    }
    return -1;
}

int* nyeroszamok() {
    int* nums = new int[20];
    int count = 0;
    while (count < 20) {
        int candidate = pickRandom();
        if (find(nums, 20, candidate) == -1) {
            nums[count] = candidate;
            count++;
        }
    }
    return nums;
}

int multiplier(int type, int hits) {
    switch (type) {
        case 1: {
            if (hits == 1)
                return 2;
            return 0;
        }
        case 2: {
            if (hits == 2)
                return 6;
            return 0;
        }
        case 3: {
            if (hits == 2)
                return 1;
            if (hits == 3)
                return 15;
            return 0;
        }
        case 4: {
            if (hits == 3)
                return 2;
            if (hits == 4)
                return 100;
            return 0;
        }
        case 5: {
            if (hits == 3)
                return 2;
            if (hits == 4)
                return 10;
            if (hits == 5)
                return 200;
            return 0;
        }
        case 6: {
            if (hits == 4)
                return 3;
            if (hits == 5)
                return 20;
            if (hits == 6)
                return 500;
            return 0;
        }
        case 7: {
            if (hits == 4)
                return 2;
            if (hits == 5)
                return 6;
            if (hits == 6)
                return 60;
            if (hits == 7)
                return 5000;
            return 0;
        }
        case 8: {
            if (hits == 5)
                return 5;
            if (hits == 6)
                return 25;
            if (hits == 7)
                return 350;
            if (hits == 8)
                return 20000;
            return 0;
        }
        case 9: {
            if (hits == 5)
                return 3;
            if (hits == 6)
                return 12;
            if (hits == 7)
                return 100;
            if (hits == 8)
                return 1200;
            if (hits == 9)
                return 100000;
            return 0;
        }
        case 10: {
            if (hits == 5)
                return 1;
            if (hits == 6);
                return 3;
            if (hits == 7)
                return 30;
            if (hits == 8)
                return 350;
            if (hits == 9)
                return 8000;
            if (hits == 10)
                return 1000000;
            return 0;
        }
        default:
            return 0;
    }
}

int main() {
    srand(time(NULL));

    // nyerőszámok
    int* szamok = nyeroszamok();

    // fogadások bekérése
    std::cout << "Add meg a fogadásod" << std::endl;
    int count = 0;
    int fogadas[10] = {0};
    while (count < 10) {
        int input;
        std::cin >> input;
        if (input == 0) {
            break;
        } else if (input < 0 || input > 80) {
            std::cout << "értelmesen már" << std::endl;
        } else {
            fogadas[count] = input;
            count++;
        }
    }

    // fogadás kiértékelése
    cout << "A nyerőszámok: " << endl;
    for (int i = 0; i < 20; i++)
        std::cout << szamok[i] << " ";
    std::cout << std::endl;
    
    int type = find(fogadas, 10, 0);
    std::cout << "játéktípus: " << type << std::endl;

    int hits = 0;
    for (int i = 0; i < type; i++) {
        int num = fogadas[i];
        std::cout << i + 1 << ". szám: " << num;

        if (find(szamok, 20, num) != -1) {
            std::cout << " - TALÁLAT" << std::endl;
            hits++;
        } else {
            std::cout << std::endl;
        }
    }
    int szorzo = multiplier(type, hits);
    cout << "Nyeremény szorzó: " << szorzo << "x" << endl;
} 