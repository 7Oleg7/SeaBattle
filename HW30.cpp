#include <iostream>
#include <ctime>
#include <chrono>
#include <string>
#include <windows.h>
using namespace std;

const string red = "\033[31m";
const string yellow = "\033[33m";
const string blue = "\033[34m";
const string nul = "\033[0m";
const string green = "\033[32m";

void clear() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

class SeaBattle {
private:
    string letters[5] = { "A","B","C","D","E" };
    char numbers[5] = { '1','2','3','4','5' };
    char functionfield[5][5];
    bool functionships[5][5] = { false };
    char playerfield[5][5];
    char botfield[5][5];
    bool playerships[5][5] = { false };
    bool botships[5][5] = { false };
    char playerfieldbattle[5][5] = { '~' };
    char botfieldbattle[5][5] = { '~' };
    int placetype, placesidehor, placesidever;
    bool hor = false, ver = false;
    int x, y;
    bool next;
    int shiptype;
    int turns;
    int playerbattleshipcounter=0, playercruisercounter=0, playerdestroyercounter=0, playerboatcounter=0;
    int botbattleshipcounter=0, botcruisercounter=0, botdestroyercounter=0, botboatcounter=0;
    int playerdestroy = 0, botdestroy = 0;
    int playercruisercoordinates1[3], playercruisercoordinates2[3], playercruiser1, playercruiser2;
    int playerdestroyercoordinates1[2], playerdestroyercoordinates2[2], playerdestroyercoordinates3[2], playerdestroyer1, playerdestroyer2, playerdestroyer3;
    int botcruisercoordinates1[3], botcruisercoordinates2[3], botcruiser1, botcruiser2;
    int botdestroyercoordinates1[2], botdestroyercoordinates2[2], botdestroyercoordinates3[2], botdestroyer1, botdestroyer2, botdestroyer3;
    bool player = false, bot = false;
    bool switchturn=false;
public:
    void FirstFieldView() {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                functionfield[i][j] = '~';
                functionships[i][j] = false;
            }
        }
    }
    void ChangePlayerField() {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                playerfield[i][j] = functionfield[i][j];
                playerships[i][j] = functionships[i][j];
            }
        }
    }
    void ChangeBotField() {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                botfield[i][j] = functionfield[i][j];
                botships[i][j] = functionships[i][j];
            }
        }
    }
    void PrintPlayerField() {
        cout << "  ";
        for (int i = 0; i < 5; i++) {
            cout << letters[i] << " ";
        }
        cout << endl;
        for (int i = 0; i < 5; i++) {
            cout << i + 1 << " ";
            for (int j = 0; j < 5; j++) {
                cout << playerfield[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
        cout << "\n\n";
    }
    void PlayerShipsPlace() {
        int ships = 10;
        int coordinates = 0;
        int battleship = 1, cruiser = 2, destroyer = 3, boats = 4;
        char cinX;
        string cinY;
        bool backcoordinates = false, backplacetype = false;
        /*while (ships > 0) {
            clear();
            ChangePlayerField();
            PrintPlayerField();
            player = true;
            next = false;
            backplacetype = false;
            backcoordinates = false;
            cout << "Выберете тип корабля для размещения:\n1 - Линкор (осталось " << battleship << ")\n";
            cout << "2 - Крейсер (осталось " << cruiser << ")\n3 - Эсминец (осталось " << destroyer << ")\n";
            cout << "4 - Торпедные катера (осталось " << boats << ")\nВаш выбор: ";
            while (true) {
                cin >> shiptype;
                if (shiptype < 1 || shiptype>4) {
                    cout << red << "\nНедопустимый тип корабля!\n\n" << nul;
                    continue;
                }
                if (shiptype == 1 && battleship == 0 || shiptype == 2 && cruiser == 0 || shiptype == 3 && destroyer == 0 || shiptype == 4 && boats == 0) {
                    cout << red << "\nДанный тип уже полностью размещён!\n\n" << nul;
                    continue;
                }
                else break;
            }
            while (backcoordinates == false && backcoordinates != true) {
                backplacetype = false;
                while (true) {
                    cout << "\nВведите координаты размещения корабля (строка, столбец) / (x=0, y=0 => Вернуться к выбору типа): ";
                    while (true) {
                        cin >> cinX >> cinY;
                        if (cinX == '0' && cinY == "0") {
                            backcoordinates = true;
                            backplacetype = true;
                            break;
                        }
                        if (cinX < '1' || cinX > '5') {
                            cout << red <<  "Недопустимый номер строки!\n\n" << nul;
                            continue;
                        }
                        else if (cinY < "A" || cinY > "E") {
                            cout << red << "Недопустимая буква столбца!\n\n" << nul;
                            continue;
                        }
                        else break;
                    }
                    for (int i = 0; i < 5; i++) {
                        if (cinX == numbers[i]) x = i;
                        if (cinY == letters[i]) y = i;
                    }
                    if (playerships[x][y] == true) {
                        cout << red << "\nДанная клетка уже занята другим кораблём!\n\n" << nul;
                        continue;
                    }
                    else break;
                }
                while (backplacetype == false && backplacetype != true) {
                    if (shiptype != 4) {
                        cout << "Каким способом разместить корабль:\n1 - По горизонтали\n2 - По вертикали\n3 - Вернуться к выбору типа корабля\nВаш выбор: ";
                        while (true) {
                            cin >> placetype;
                            if (placetype < 1 || placetype>3) {
                                cout << "Несуществующий вариант!\n";
                                continue;
                            }
                            else break;
                        }
                        if (placetype == 3) {
                            backplacetype = true;
                            backcoordinates = true;
                            break;
                        }
                        else if (placetype == 1) {
                            cout << "В какую сторону (относительно координаты) разместить корабль:\n1 - Влево\n2 - Вправо\nВаш выбор: ";
                            while (true) {
                                cin >> placesidehor;
                                if (placesidehor < 1 || placesidehor>2) {
                                    cout << "Несуществующий вариант!\n";
                                    continue;
                                }
                                else break;
                            }
                        }
                        else if (placetype == 2) {
                            cout << "В какую сторону (относительно координаты) разместить корабль:\n1 - Вверх\n2 - Вниз\nВаш выбор: ";
                            while (true) {
                                cin >> placesidever;
                                if (placesidever < 1 || placesidever>2) {
                                    cout << "Несуществующий вариант!\n";
                                    continue;
                                }
                                else break;
                            }
                        }
                        CheckPlacePossibility();
                    }
                    if (next == true || shiptype == 4) {
                        SetShipPlace();
                        ChangePlayerField();
                        if (shiptype == 1) battleship--;
                        if (shiptype == 2) cruiser--;
                        if (shiptype == 3) destroyer--;
                        if (shiptype == 4) boats--;
                        ships--;
                        backplacetype = backcoordinates = true;
                        break;
                    }
                    if (next == false) {
                        cout << red << "\nТаким способом данный корабль разместить невозможно!\n\n" << nul;
                        backplacetype = false;
                        continue;
                    }
                }
            }
        }*/
        player = false;
        bot = true;
        if (bot == true && player == false) {
            FirstFieldView();
            ChangeBotField();
            cout << "Поле бота:\n\n";
            BotShipsPlace();
            PrintBotField();
        }
        bot = false;
        /*clear();
        StartGame();*/
    }
    void StartGame() {
        int start, exit;
        cout << "Поля обеих сторон сформированы. Готовы начать? (1 - Да/2 - Нет)\nВаш выбор: ";
        while (true) {
            cin >> start;
            if (start < 1 || start>2) {
                cout << "Несуществующий вариант!\n";
                continue;
            }
            else break;
        }
        if (start == 2) {
            cout << "Выберете вариант:\n1 - Осуществить новое создание поля\n2 - Выход из программы\nВаш выбор: ";
            while (true) {
                cin >> exit;
                if (exit < 1 || exit>2) {
                    cout << "Несуществующий вариант!\n";
                    continue;
                }
                if (exit == 2) return;
                else {
                    clear();
                    FirstFieldView();
                    PlayerShipsPlace();
                }
            }
        }
        else {
            clear();
            Game();
        }
    }
    void PrintPlayerBattleField() {
        cout << "  ";
        for (int i = 0; i < 5; i++) {
            cout << letters[i] << " ";
        }
        cout << endl;
        for (int i = 0; i < 5; i++) {
            cout << i + 1 << " ";
            for (int j = 0; j < 5; j++) {
                cout << playerfieldbattle[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
        cout << "\n\n";
    }
    void PrintBotBattleField() {
        cout << "  ";
        for (int i = 0; i < 5; i++) {
            cout << letters[i] << " ";
        }
        cout << endl;
        for (int i = 0; i < 5; i++) {
            cout << i + 1 << " ";
            for (int j = 0; j < 5; j++) {
                cout << botfieldbattle[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
        cout << "\n\n";
    }
    void Game() {
        int starter;
        string turnname;
        starter = 1 + rand() % 2;
        turns = 1;
        if (turns == 1) {
            if (starter == 1) turnname = green, "Игрок", nul;
            if (starter == 2) turnname = red, "Бот", nul;
            cout << "По жребию начинает: " << turnname << "!" << endl;
        }
        while (playerdestroy!=10 || botdestroy!=10) {
            cout << "Ходит " << turnname << "\n\n";
            if (starter == 1 || switchturn == false || turnname=="Игрок") {
                PlayerTurn();
                turns++;
                switchturn = true;
                continue;
            }
            if (starter == 2 || switchturn == true || turnname == "Бот") {
                BotTurn();
                turns++;
                switchturn = false;
                continue;
            }
        }
        if (playerdestroy == 10) {
            cout << "\n\nПобедил " << green << " ИГРОК" << nul << "!\n\n";
            cout << "Партия состоялась за " << yellow << turns << nul << " ходов!\n\n";
        }
        if (botdestroy == 10) {
            cout << "\n\nПобедил " << red << " БОТ" << nul << "!\n\n";
            cout << "Партия состоялась за " << yellow << turns << nul << " ходов!\n\n";
        }
        return;
    }
    void CheckBotsDestroyedCruisers() {
        int counter = 0;
        int hits = 0;
        for (int i = playercruisercoordinates1[counter]; i < playercruisercoordinates1[counter+3]; i++) {
            if (botfieldbattle[playercruiser1][i] == 'X') hits++;
            else if (botfieldbattle[i][playercruiser1] == 'X') hits++;
        }
        for (int i = playercruisercoordinates2[counter]; i < playercruisercoordinates2[counter + 3]; i++) {
            if (botfieldbattle[playercruiser1][i] == 'X') hits++;
            else if (botfieldbattle[i][playercruiser2] == 'X') hits++;
        }
        if (hits == 3) {
            cout << "Вы уничтожили крейсер противника!\n";
            playerdestroy++;
        }
    }
    void CheckBotsDestroyedDestroyers() {
        int counter = 0;
        int hits = 0;
        for (int i = playerdestroyercoordinates1[counter]; i < playerdestroyercoordinates1[counter + 2]; i++) {
            if (botfieldbattle[playerdestroyer1][i] == 'X') hits++;
            else if (botfieldbattle[i][playerdestroyer1] == 'X') hits++;
        }
        for (int i = playerdestroyercoordinates2[counter]; i < playerdestroyercoordinates2[counter + 2]; i++) {
            if (botfieldbattle[playerdestroyer1][i] == 'X') hits++;
            else if (botfieldbattle[i][playerdestroyer2] == 'X') hits++;
        }
        if (hits == 2) {
            cout << "Вы уничтожили эсминец противника!\n";
            playerdestroy++;
        }
    }
    void CheckPlayersDestroyedCruisers() {
        int counter = 0;
        int hits = 0;
        for (int i = botcruisercoordinates1[counter]; i < botcruisercoordinates1[counter + 3]; i++) {
            if (playerfieldbattle[botcruiser1][i] == 'X') hits++;
            else if (playerfieldbattle[i][botcruiser1] == 'X') hits++;
        }
        for (int i = botcruisercoordinates2[counter]; i < botcruisercoordinates2[counter + 3]; i++) {
            if (playerfieldbattle[botcruiser1][i] == 'X') hits++;
            else if (playerfieldbattle[i][botcruiser2] == 'X') hits++;
        }
        if (hits == 3) {
            cout << "Бот уничтожил ваш крейсер!\n";
            botdestroy++;
        }
    }
    void CheckPlayersDestroyedDestroyers() {
        int counter = 0;
        int hits = 0;
        for (int i = botdestroyercoordinates1[counter]; i < botdestroyercoordinates1[counter + 2]; i++) {
            if (playerfieldbattle[botdestroyer1][i] == 'X') hits++;
            else if (playerfieldbattle[i][botdestroyer1] == 'X') hits++;
        }
        for (int i = botdestroyercoordinates2[counter]; i < botdestroyercoordinates2[counter + 2]; i++) {
            if (playerfieldbattle[botdestroyer1][i] == 'X') hits++;
            else if (playerfieldbattle[i][botdestroyer2] == 'X') hits++;
        }
        if (hits == 2) {
            cout << "Бот уничтожил ваш эсминец!\n";
            botdestroy++;
        }
    }
    void PlayerTurn() {
        char cinX;
        string cinY;
        string ishit;
        string goalobj;
        int counter = 0;
        x = 0;
        y = 0;
        PrintBotBattleField();
        cout << "Ход " << turns << ":\n\nВведите координаты, по которым будет нанесён удар: ";
        while (true) {
            while (true) {
                cin >> cinX >> cinY;
                if (cinX < '1' || cinX > '5') {
                    cout << red << "Недопустимый номер строки!\n\n" << nul;
                    continue;
                }
                else if (cinY < "A" || cinY > "E") {
                    cout << red << "Недопустимая буква столбца!\n\n" << nul;
                    continue;
                }
                else break;
            }
            for (int i = 0; i < 5; i++) {
                if (cinX == numbers[i]) x = i;
                if (cinY == letters[i]) y = i;
            }
            if (botfieldbattle[x][y] == 'o' || botfieldbattle[x][y] == 'X') {
                cout << red << "\n\nВы уже осуществляли удар по данной клетке!\n\n" << nul;
                continue;
            }
            else {
                clear();
                break;
            }
        }
        if (botships[x][y] == true) {
            ishit = "Вы попали в ";
            botfieldbattle[x][y] = 'X';
            if (botfield[x][y] == 'Л') {
                goalobj = " ЛИНКОР";
                playerbattleshipcounter++;
            }
            else if (botfield[x][y] == 'К') {
                goalobj = " КРЕЙСЕР";
                playercruisercounter++;
                CheckBotsDestroyedCruisers();
            }
            else if (botfield[x][y] == 'Э') {
                goalobj = " ЭСМИНЕЦ";
                playerdestroyercounter++;
                CheckBotsDestroyedDestroyers();
            }
            else if (botfield[x][y] == 'Т') {
                goalobj = " ТОРПЕДНЫЙ КАТЕР";
                playerboatcounter++;
            }
        }
        else if (botships[x][y] == false) {
            ishit = "Вы попали ";
            goalobj = "мимо";
            botfieldbattle[x][y] = 'o';
        }
        cout << "\n\n";
        PrintBotBattleField();
        cout << "\n\n" << ishit << goalobj << "!\n\n";
        if (playerboatcounter == 1) {
            cout << "Вы уничтожили торпедный катер противника!\n";
            playerdestroy++;
            playerboatcounter = 0;
        }
        if (playerbattleshipcounter == 4) {
            cout << "Вы уничтожили линкор противника!\n\n";
            playerdestroy++;
            playerbattleshipcounter = 0;
        }
        Game();
    }
    void BotTurn() {
        string ishit;
        string goalobj;
        int x, y;
        while (true) {
            x = 0, y = 0;
            x = 1 + rand() % 5;
            y = 1 + rand() % 5;
            if (playerfieldbattle[x][y] == 'o' || playerfieldbattle[x][y] == 'X') continue;
            else break;
        }
        if (playerships[x][y] == true) {
            ishit = "Бот попал в ";
            playerfieldbattle[x][y] = 'X';
            if (playerfield[x][y] == 'Л') {
                goalobj = " ЛИНКОР";
                botbattleshipcounter++;
            }
            else if (playerfield[x][y] == 'К') {
                goalobj = " КРЕЙСЕР";
                botcruisercounter++;
                CheckPlayersDestroyedCruisers();
            }
            else if (playerfield[x][y] == 'Э') {
                goalobj = " ЭСМИНЕЦ";
                botdestroyercounter++;
                CheckPlayersDestroyedDestroyers();
            }
            else if (playerfield[x][y] == 'Т') {
                goalobj = " ТОРПЕДНЫЙ КАТЕР";
                botboatcounter++;
            }
        }
        else if (playerfield[x][y] == false) {
            ishit = "Бот попал ";
            goalobj = "мимо";
            playerfieldbattle[x][y] = 'o';
        }
        cout << "\n\n";
        PrintPlayerBattleField();
        cout << "\n\n" << ishit << goalobj << "!\n\n";
        if (botboatcounter == 1) {
            cout << "Бот уничтожил ваш торпедный катер!\n";
            botdestroy++;
            botboatcounter = 0;
        }
        if (botbattleshipcounter == 4) {
            cout << "Бот уничтожил ваш линкор!\n\n";
            botdestroy++;
            botbattleshipcounter = 0;
        }
        Game();
    }
    void CheckPlacePossibility() {
        int posplace = 0;
        if (shiptype == 1) {
            if (placetype == 1) {
                if (placesidehor == 1) {
                    if (y - 4 >= 0) {
                        for (int i = y; i > y - 4; i--) {
                            if (functionships[x][i] == false) posplace++;
                        }
                        if (posplace == 4) next = true;
                        else next = false;
                    }
                    else next = false;
                }
                if (placesidehor == 2) {
                    if (y + 4 < 5) {
                        for (int i = y; i < y + 4; i++) {
                            if (functionships[x][i] == false) posplace++;
                        }
                        if (posplace == 4) next = true;
                        else next = false;
                    }
                    else next = false;
                }
            }
            if (placetype == 2) {
                if (placesidever == 1) {
                    if (x - 4 >= 0) {
                        for (int i = x; i > x - 4; i--) {
                            if (functionships[i][y] == false) posplace++;
                        }
                        if (posplace == 4) next = true;
                        else next = false;
                    }
                    else next = false;
                }
                if (placesidever == 2) {
                    if (x + 4 < 5) {
                        for (int i = x; i < x + 4; i++) {
                            if (functionships[i][y] == false) posplace++;
                        }
                        if (posplace == 4) next = true;
                        else next = false;
                    }
                    else next = false;
                }
            }
        }
        else if (shiptype == 2) {
            if (placetype == 1) {
                if (placesidehor == 1) {
                    if (y - 3 >= 0) {
                        for (int i = y; i > y - 3; i--) {
                            if (functionships[x][i] == false) posplace++;
                        }
                        if (posplace == 3) next = true;
                        else next = false;
                    }
                    else next = false;
                }
                if (placesidehor == 2) {
                    if (y + 3 < 5) {
                        for (int i = y; i < y + 3; i++) {
                            if (functionships[x][i] == false) posplace++;
                        }
                        if (posplace == 3) next = true;
                        else next = false;
                    }
                    else next = false;
                }
            }
            if (placetype == 2) {
                if (placesidever == 1) {
                    if (x - 3 >= 0) {
                        for (int i = x; i > x - 3; i--) {
                            if (functionships[i][y] == false) posplace++;
                        }
                        if (posplace == 3) next = true;
                        else next = false;
                    }
                    else next = false;
                }
                if (placesidever == 2) {
                    if (x + 3 < 5) {
                        for (int i = x; i < x + 3; i++) {
                            if (functionships[i][y] == false) posplace++;
                        }
                        if (posplace == 3) next = true;
                        else next = false;
                    }
                    else next = false;
                }
            }
        }
        else if (shiptype == 3) {
            if (placetype == 1) {
                if (placesidehor == 1) {
                    if (y - 2 >= 0) {
                        for (int i = y; i > y - 2; i--) {
                            if (functionships[x][i] == false) posplace++;
                        }
                        if (posplace == 2) next = true;
                        else next = false;
                    }
                    else next = false;
                }
                if (placesidehor == 2) {
                    if (y + 2 < 5) {
                        for (int i = y; i < y + 2; i++) {
                            if (functionships[x][i] == false) posplace++;
                        }
                        if (posplace == 2) next = true;
                        else next = false;
                    }
                    else next = false;
                }
            }
            if (placetype == 2) {
                if (placesidever == 1) {
                    if (x - 2 >= 0) {
                        for (int i = x; i > x - 2; i--) {
                            if (functionships[i][y] == false) posplace++;
                        }
                        if (posplace == 2) next = true;
                        else next = false;
                    }
                    else next = false;
                }
                if (placesidever == 2) {
                    if (x + 2 < 5) {
                        for (int i = x; i < x + 2; i++) {
                            if (functionships[i][y] == false) posplace++;
                        }
                        if (posplace == 2) next = true;
                        else next = false;
                    }
                    else next = false;
                }
            }
        }
        else if (shiptype == 4) {
            if (functionships[x][y] == false) next = true;
            if (functionships[x][y] == true) next = false;
        }
        posplace = 0;
    }
    void SetShipPlace() {
        int cruisers = 1;
        int destroyers = 1;
        int counter = 0;
        if (shiptype == 1) {
            if (placetype == 1) {
                if (placesidehor == 1) {
                    for (int i = y; i > y - 4; i--) {
                        functionfield[x][i] = 'Л';
                        functionships[x][i] = true;
                    }
                }
                if (placesidehor == 2) {
                    for (int i = y; i < y + 4; i++) {
                        functionfield[x][i] = 'Л';
                        functionships[x][i] = true;
                    }
                }
            }
            if (placetype == 2) {
                if (placesidever == 1) {
                    for (int i = x; i > x - 4; i--) {
                        functionfield[i][y] = 'Л';
                        functionships[i][y] = true;
                    }
                }
                if (placesidever == 2) {
                    for (int i = x; i < x + 4; i++) {
                        functionfield[i][y] = 'Л';
                        functionships[i][y] = true;
                    }
                }
            }
        }
        else if (shiptype == 2) {
            if (placetype == 1) {
                if (placesidehor == 1) {
                    for (int i = y; i > y - 3; i--) {
                        functionfield[x][i] = 'К';
                        functionships[x][i] = true;
                        if (player == true && cruisers==1) {
                            playercruisercoordinates1[counter] = i;
                            playercruiser1 = x;
                            counter++;
                        }
                        if (player = true && cruisers == 2) {
                            playercruisercoordinates2[counter] = i;
                            playercruiser2 = x;
                            counter++;
                        }
                        if (bot == true && cruisers == 3) {
                            botcruisercoordinates1[counter] = i;
                            botcruiser1 = x;
                            counter++;
                        }
                        if (bot == true && cruisers == 4) {
                            botcruisercoordinates2[counter] = i;
                            botcruiser2 = x;
                            counter++;
                        }
                    }
                    counter = 0;
                    cruisers++;
                }
                if (placesidehor == 2) {
                    for (int i = y; i < y + 3; i++) {
                        functionfield[x][i] = 'К';
                        functionships[x][i] = true;
                        if (player == true && cruisers == 1) {
                            playercruisercoordinates1[counter] = i;
                            playercruiser1 = x;
                            counter++;
                        }
                        if (player = true && cruisers == 2) {
                            playercruisercoordinates2[counter] = i;
                            playercruiser2 = x;
                            counter++;
                        }
                        if (bot == true && cruisers == 3) {
                            botcruisercoordinates1[counter] = i;
                            botcruiser1 = x;
                            counter++;
                        }
                        if (bot == true && cruisers == 4) {
                            botcruisercoordinates2[counter] = i;
                            botcruiser2 = x;
                            counter++;
                        }
                    }
                    counter = 0;
                    cruisers++;
                }
            }
            if (placetype == 2) {
                if (placesidever == 1) {
                    for (int i = x; i > x - 3; i--) {
                        functionfield[i][y] = 'К';
                        functionships[i][y] = true;
                        if (player == true && cruisers == 1) {
                            playercruisercoordinates1[counter] = i;
                            playercruiser1 = y;
                            counter++;
                        }
                        if (player = true && cruisers == 2) {
                            playercruisercoordinates2[counter] = i;
                            playercruiser2 = y;
                            counter++;
                        }
                        if (bot == true && cruisers == 3) {
                            botcruisercoordinates1[counter] = i;
                            botcruiser1 = y;
                            counter++;
                        }
                        if (bot == true && cruisers == 4) {
                            botcruisercoordinates2[counter] = i;
                            botcruiser2 = y;
                            counter++;
                        }
                    }
                    counter = 0;
                    cruisers++;
                }
                if (placesidever == 2) {
                    for (int i = x; i < x + 3; i++) {
                        functionfield[i][y] = 'К';
                        functionships[i][y] = true;
                        if (player == true && cruisers == 1) {
                            playercruisercoordinates1[counter] = i;
                            playercruiser1 = y;
                            counter++;
                        }
                        if (player = true && cruisers == 2) {
                            playercruisercoordinates2[counter] = i;
                            playercruiser2 = y;
                            counter++;
                        }
                        if (bot == true && cruisers == 3) {
                            botcruisercoordinates1[counter] = i;
                            botcruiser1 = y;
                            counter++;
                        }
                        if (bot == true && cruisers == 4) {
                            botcruisercoordinates2[counter] = i;
                            botcruiser2 = y;
                            counter++;
                        }
                    }
                    counter = 0;
                    cruisers++;
                }
            }
        }
        else if (shiptype == 3) {
            if (placetype == 1) {
                if (placesidehor == 1) {
                    for (int i = y; i > y - 2; i--) {
                        functionfield[x][i] = 'Э';
                        functionships[x][i] = true;
                        if (player == true && destroyers == 1) {
                            playerdestroyercoordinates1[counter] = i;
                            playerdestroyer1 = x;
                            counter++;
                        }
                        if (player = true && destroyers == 2) {
                            playerdestroyercoordinates2[counter] = i;
                            playerdestroyer2 = x;
                            counter++;
                        }
                        if (player == true && destroyers == 3) {
                            playerdestroyercoordinates3[counter] = i;
                            playerdestroyer3 = x;
                            counter++;
                        }
                        if (bot == true && destroyers == 4) {
                            botdestroyercoordinates1[counter] = i;
                            botdestroyer1 = x;
                            counter++;
                        }
                        if (bot == true && destroyers == 5) {
                            botdestroyercoordinates2[counter] = i;
                            botdestroyer2 = x;
                            counter++;
                        }
                        if (bot == true && destroyers == 6) {
                            botdestroyercoordinates3[counter] = i;
                            botdestroyer3 = x;
                            counter++;
                        }
                    }
                    counter = 0;
                    destroyers++;
                }
                if (placesidehor == 2) {
                    for (int i = y; i < y + 2; i++) {
                        functionfield[x][i] = 'Э';
                        functionships[x][i] = true;
                        if (player == true && destroyers == 1) {
                            playerdestroyercoordinates1[counter] = i;
                            playerdestroyer1 = x;
                            counter++;
                        }
                        if (player = true && destroyers == 2) {
                            playerdestroyercoordinates2[counter] = i;
                            playerdestroyer2 = x;
                            counter++;
                        }
                        if (player == true && destroyers == 3) {
                            playerdestroyercoordinates3[counter] = i;
                            playerdestroyer3 = x;
                            counter++;
                        }
                        if (bot == true && destroyers == 4) {
                            botdestroyercoordinates1[counter] = i;
                            botdestroyer1 = x;
                            counter++;
                        }
                        if (bot == true && destroyers == 5) {
                            botdestroyercoordinates2[counter] = i;
                            botdestroyer2 = x;
                            counter++;
                        }
                        if (bot == true && destroyers == 6) {
                            botdestroyercoordinates3[counter] = i;
                            botdestroyer3 = x;
                            counter++;
                        }
                    }
                    counter = 0;
                    destroyers++;
                }
            }
            if (placetype == 2) {
                if (placesidever == 1) {
                    for (int i = x; i > x - 2; i--) {
                        functionfield[i][y] = 'Э';
                        functionships[i][y] = true;
                        if (player == true && cruisers == 1) {
                            playerdestroyercoordinates1[counter] = i;
                            counter++;
                        }
                        if (player = true && cruisers == 2) {
                            playerdestroyercoordinates2[counter] = i;
                            counter++;
                        }
                        if (bot == true && cruisers == 3) {
                            botdestroyercoordinates1[counter] = i;
                            counter++;
                        }
                        if (bot == true && cruisers == 4) {
                            botdestroyercoordinates2[counter] = i;
                            counter++;
                        }
                    }
                    counter = 0;
                    destroyers++;
                }
                if (placesidever == 2) {
                    for (int i = x; i < x + 2; i++) {
                        functionfield[i][y] = 'Э';
                        functionships[i][y] = true;
                        if (player == true && destroyers == 1) {
                            playerdestroyercoordinates1[counter] = i;
                            playerdestroyer1 = y;
                            counter++;
                        }
                        if (player = true && destroyers == 2) {
                            playerdestroyercoordinates2[counter] = i;
                            playerdestroyer2 = y;
                            counter++;
                        }
                        if (player == true && destroyers == 3) {
                            playerdestroyercoordinates3[counter] = i;
                            playerdestroyer3 = y;
                            counter++;
                        }
                        if (bot == true && destroyers == 4) {
                            botdestroyercoordinates1[counter] = i;
                            botdestroyer1 = y;
                            counter++;
                        }
                        if (bot == true && destroyers == 5) {
                            botdestroyercoordinates2[counter] = i;
                            botdestroyer2 = y;
                            counter++;
                        }
                        if (bot == true && destroyers == 6) {
                            botdestroyercoordinates3[counter] = i;
                            botdestroyer3 = y;
                            counter++;
                        }
                    }
                    counter = 0;
                    destroyers++;
                }
            }
        }
        else if (shiptype == 4) {
            functionfield[x][y] = 'Т';
            functionships[x][y] = true;
        }
    }
    void PrintBotField() {
        cout << "\n\n";
        cout << "  ";
        for (int i = 0; i < 5; i++) {
            cout << letters[i] << " ";
        }
        cout << endl;
        for (int i = 0; i < 5; i++) {
            cout << i + 1 << " ";
            for (int j = 0; j < 5; j++) {
                cout << botfield[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
        cout << "\n\n";
    }
    void BotShipsPlace() {
        srand(time(0));
        int ships = 10;
        int battleship = 1, cruiser = 2, destroyer = 3, boats = 4;
        while (ships > 0) {
            next = false;
            if (battleship == 1) shiptype = 1;
            if (battleship == 0 && cruiser > 0) shiptype = 2;
            if (cruiser == 0 && destroyer > 0) shiptype = 3;
            if (destroyer == 0 && boats>0) {
                shiptype = 4;
                next = true;
            }
            while (next == false) {
                x = 0 + rand() % 4;
                y = 0 + rand() % 4;
                placetype = 1 + rand() % 2;
                if (placetype == 1) placesidehor = 1 + rand() % 2;
                if (placetype == 2) placesidever = 1 + rand() % 2;
                CheckPlacePossibility();
            }
            if (next == true) {
                SetShipPlace();
                ChangeBotField();
                PrintBotField();
                if (shiptype == 1) battleship--;
                if (shiptype == 2) cruiser--;
                if (shiptype == 3) destroyer--;
                if (shiptype == 4) boats--;
                ships--;
            }
        }
    }
};

int main()
{
    setlocale(LC_ALL, "rus");
    srand(time(0));
    bool firstview = false;
    SeaBattle* game = new SeaBattle();
    game->FirstFieldView();
    game->PlayerShipsPlace();
    return 0;
}

