#include <iostream>
#include <string>

#define HEIGHT 10
#define WIDTH 10

class Torpedo {
    int board[WIDTH][HEIGHT] = {0};

public:
    void init(std::string data) {
        int x = -1;
        int y = -1;
        bool letter = false;
        for (const char& c : data) {
            if (c >= 65 && c <= 74) {
                if (x != -1 && y != -1) {
                    board[x][y] = 1;
                } 
                // betű
                x = c - 65;
                letter = true;
            } else {
                // szám
                if (letter) {
                    y = c - 49;
                } else {
                    y = 9;
                }
                letter = false;
            }
        }
        board[x][y] = 1;
    }

    void are_ships_destroyed(std::string data) {
        int x = -1;
        int y = -1;
        bool letter = false;
        for (const char& c : data) {
            if (c >= 65 && c <= 74) {
                if (x != -1 && y != -1) {
                    board[x][y] = 2;
                } 
                // betű
                x = c - 65;
                letter = true;
            } else {
                // szám
                if (letter) {
                    y = c - 49;
                } else {
                    y = 9;
                }
                letter = false;
            }
        }
        board[x][y] = 2;
    }

    void show() {
        std::cout << "\t A  B  C  D  E  F  G  H  I  J" << std::endl;
        for (int y = 0; y < HEIGHT; y++) {
            std::cout << y + 1 << "\t";
            for (int x = 0; x < WIDTH; x++) {
                int cell = board[x][y];
                switch (cell) {
                    case 0:
                        std::cout << " . ";
                        break;
                    case 1:
                        std::cout << " X ";
                        break;
                    case 2:
                        std::cout << " * ";
                        break;
                }
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    Torpedo t;
    //t.init("A3A5A4C10B10A10F1E1");
    //t.are_ships_destroyed("B6B10E10C5");
    std::cout << "Add meg a hajók helyzetét: ";
    std::string hajok;
    std::cin >> hajok;
    t.init(hajok);
    std::cout << "Add meg a lövéseket: ";
    std::string bombak;
    std::cin >> bombak;
    t.are_ships_destroyed(bombak);
    t.show();
}