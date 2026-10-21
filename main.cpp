// program name: minereaper
// description: slime out da mines. why they tryna fake being cells fr?

#include <iostream>
#include <SDL3/SDL.h>   // for key input
#include <string>

using namespace std;

// CONSTANT VARIABLES
const int RANGE_X = 30; // max range
const int RANGE_Y = 30;

void rangeErr(int min, int max, int& input);
void mineInit(int wdth, int hght, bool a[RANGE_X][RANGE_Y], int b[1][1]);
void mapInit(int wdth, int hght, int a[RANGE_X][RANGE_Y], bool b[RANGE_X][RANGE_Y]);
void dispInit(int wdth, int hght, char a[RANGE_X][RANGE_Y], int startPos[RANGE_X][RANGE_Y]);

int main() {

    // init random seed
    srand(time(nullptr));

    // variables
    int mapX, mapY; // map dimensions
    int userX, userY;   // user position

    // title
    cout << "MINEREAPER: Kill the mines by exposing their facade!" << endl;

    // configure map
    cout << "What is the map width? (1-" << RANGE_X << " inclusive): ";
    cin >> mapX;
    rangeErr(1, RANGE_X, mapX);

    cout << "What is the map height? (1-" << RANGE_Y << " inclusive): ";
    cin >> mapY;
    rangeErr(1, RANGE_Y, mapY);

    bool mineMap[mapX][mapY] = {false, false};
    bool discMap[mapX][mapY] = {};
    int cellMap[mapX][mapY] = {0, 0};   // properties map
    char dispMap[mapX][mapY] = {"", ""};
    int choice[1][2] = {};

    int arr[mapX][mapY] = {};

    // 47 mins into the sesh:
    /*
    k so i am going to switch to one array of ints for storing properties:
    -1 = mine present
    0 = no adjacent mines 
    >0 = adjacent mine count

    maybe another for seeing if spot is undiscovered

    func structure for checking cell from now on:
    if cell is not discovered:
        write discovery of cell to bool array
        check if a mine is present
        kill if yes, otherwise write to a character array the current character (amount of adjacent mines or none at all)
    otherwise:
        do nothing
    if flagging:
        change current character to flag
        sub from remaining flags
    */

    mineInit(mapX, mapY, mineMap);
    mapInit(mapX, mapY, cellMap, mineMap);
    
    SDL_Event event;

    game loop
    while (true) {
        SDL_WaitEvent(&event);  // waits for event (key press)

        // key input
        if (event.type == SDL_EVENT_KEY_DOWN) {
            if (event.key.key == SDLK_DOWN && userY > 0) {           // movement
                userY++;
            } else if (event.key.key == SDLK_UP && userY < mapY) {      // ||
                userY--;
            } else if (event.key.key == SDLK_LEFT) {    // ||
                userX--;
            } else if (event.key.key == SDLK_RIGHT) {   // ||
                userX++;
            } else if (event.key.key == SDLK_RETURN) {  // clear cell
                choice[0][0] = {userX, userY};
            } else if (event.key.key == SDLK_BACKSPACE) {   // flag
                ;
            } else if (event.key.key == SDLK_ESCAPE) {  // quit
                break;
            }
        }

        // quit
        if (event.type == SDL_EVENT_QUIT) {
            break;
        }
    }
    for (int i = 0; i < mapY; i++) {
        for (int j = 0; j < mapX; j++) {
            if (mineMap[j][i] == true) {
                cout << '#';
            } else {
                cout << cellMap[j][i];
            }
            cout << ' ';
        }
        cout << endl;
    }

    return 0;

}

// deal with range error
void rangeErr(int min, int max, int& input) {
    while (input > max || input < min) {
        cout << "Range error! Enter a number between " << min << " and " << max << ": ";
        cin >> input;
    }
}

// init mine map
void mineInit(int wdth, int hght, bool a[RANGE_X][RANGE_Y], int b[1][2]) {
    for (int i = 0; i < (wdth * hght * 0.15); i++) {
        int rndX = rand() % wdth;  // random coordinates
        int rndY = rand() % hght;
        while (a[rndX][rndY] == true || b[0][1] == {{rndX, rndY}}) { // retry until mine is placeable
            rndX = rand() % wdth;
            rndY = rand() % hght;
        }
        // set cell to mine
        a[rndX][rndY] = true;
    }
}

// init adjacent mine counts
void mapInit(int wdth, int hght, int a[RANGE_X][RANGE_Y], bool b[RANGE_X][RANGE_Y]) {
    for (int i = 0; i < hght; i++) {
        for (int j = 0; j < wdth; j++) {
            if (b[j][i] == true) {  // init indicators
                for (int k = -1; k < 2; k++) {
                    for (int l = -1; l < 2; l++) {
                        int x = j + l;
                        int y = i + k;
                        // check for bad assignment
                        if (k != 0 || l != 0 && !(i + k < 0 || i + k > hght - 1 || j + l < 0 || j + l > wdth - 1)) {
                            a[j+l][i+k]++;
                        }
                    }
                }
            }
        }
    }
}

// init display of map
void dispInit(int wdth, int hght, char a[RANGE_X][RANGE_Y], bool b[RANGE_X][RANGE_Y], int startPos[1][1]) {
    a[startPos[0][0]][startPos[0][1]] = '\'';
    for (int i = 0; i < hght; i++) {
        for (int j = 0; j < wdth; j++) {
            if (b[j][i] == true) {
                a[j][i] = '';
            }
        }
    }
}

void checkCell(int wdth, int hght, bool a[RANGE_X][RANGE_Y], int b[RANGE_X][RANGE_Y], bool c[RANGE_X][RANGE_Y]) {
    if()
}