#include <iostream>

using namespace std;

#if defined(_WIN32) || defined(_WIN64)
const bool osWindows = true;
const bool osLinux = false;
const bool osUnknown = false;
#else
const bool osWindows = false;
#ifdef __linux
const bool osLinux = true;
const bool osUnknown = false;
#else
const bool osLinux = false;
const bool osUnknown = true;
#endif
#endif

const char players[3]{ ' ', 'X', 'O' };
const char fieldX = 7, fieldY = 6;
char field[fieldX * fieldY];
char rowToWin = 4;

bool canClaim(int posX) {
    return posX < fieldX && field[posX] == 0;
}
void draw(char winner) {
    if (osLinux) { system("clear"); }
    if (osWindows) { system("cls"); }
    else { system("clear"); system("cls"); }

    for (int y = 0; y < fieldY; y++) {
        for (int x = 0; x < fieldX; x++) {
            cout << " " << players[field[y * fieldX + x]] << " ";
            if (x == fieldX - 1) {
                cout << endl;
            }
            else {
                cout << "|";
            }
        }
    }

    if (winner != 0) {
        if (winner >= 3) {
            cout << "\nThe game is over and no winner could be found!\n";
        }
        else {
            cout << "\nPlayer '" << players[winner] << "' won the game!\n";
        }
    }
    return;
}
char getInput() {
    char input = 0xFF;
    while (input < 0 || input > fieldX || !canClaim(input)) {
        char in = getchar();
        while (in != '\n' && getchar() != '\n') /* do nothing*/;
        input = in - '1';
    }
    return input;
}
bool claim(char player, char posX) {
    if (!canClaim(posX)) { return false; }
    for (int i = fieldX * (fieldY - 1) + posX; i >= 0; i -= fieldX) {
        if (field[i] == 0) {
            field[i] = player;
            i = (-1);
        }
    }
    return true;
}
char getWinner() {
    char rows[2]{ 0, 0 };
    // Waagerecht
    for (int y = 0; y < fieldY; y++) {
        for (int x = 0; x < fieldX; x++) {
            char f = field[y * fieldX + x];
            if (f == 1) {
                rows[0]++;
                rows[1] = 0;
            }
            else if (f == 2) {
                rows[1]++;
                rows[0] = 0;
            }
            else {
                rows[0] = 0;
                rows[1] = 0;
            }
            if (rows[0] >= rowToWin) {
                return 1;
            }
            else if (rows[1] >= rowToWin) {
                return 2;
            }
        }
    }
    rows[0] = 0;
    rows[1] = 0;
    // Senkrecht
    for (int x = 0; x < fieldX; x++) {
        for (int y = 0; y < fieldY; y++) {
            char f = field[y * fieldX + x];
            if (f == 1) {
                rows[0]++;
                rows[1] = 0;
            }
            else if (f == 2) {
                rows[1]++;
                rows[0] = 0;
            }
            else {
                rows[0] = 0;
                rows[1] = 0;
            }
            if (rows[0] >= rowToWin) {
                return 1;
            }
            else if (rows[1] >= rowToWin) {
                return 2;
            }
        }
    }
    rows[0] = 0;
    rows[1] = 0;
    // Diagonal links oben nach rechts unten
    for (int i = 0; i < fieldX * fieldY; i++) {
        if (field[i] == 1) {
            rows[0]++;
            i += fieldX;
        }
        else {
            rows[0] = 0;
        }
        if (rows[0] >= rowToWin) {
            return 1;
        }
    }
    for (int i = 0; i < fieldX * fieldY; i++) {
        if (field[i] == 2) {
            rows[1]++;
            i += fieldX;
        }
        else {
            rows[1] = 0;
        }
        if (rows[1] >= rowToWin) {
            return 2;
        }
    }
    rows[0] = 0;
    rows[1] = 0;
    // Diagonal rechts oben nach links unten
    for (int i = 0; i < fieldX * fieldY; i++) {
        if (field[i] == 1) {
            rows[0]++;
            i += fieldX - 2;
        }
        else {
            rows[0] = 0;
        }
        if (rows[0] >= rowToWin) {
            return 1;
        }
    }
    for (int i = 0; i < fieldX * fieldY; i++) {
        if (field[i] == 2) {
            rows[1]++;
            i += fieldX - 2;
        }
        else {
            rows[1] = 0;
        }
        if (rows[1] >= rowToWin) {
            return 2;
        }
    }
    rows[0] = 0;
    rows[1] = 0;

    return 0;
}

int main()
{
    for (int i = 0; i < fieldX * fieldY; i++) {
        field[i] = 0;
    }

    char winner = 0;
    while (winner == 0) {
        draw(winner);
        claim(1, getInput());
        winner = getWinner();
        if (winner == 0) {
            draw(winner);
            claim(2, getInput());
            winner = getWinner();
        }
    }
    draw(winner);

    getchar();
}
