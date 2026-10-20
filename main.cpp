// program name: minereaper
// description: slime out da mines. why they tryna fake being cells fr?

#include <iostream>
#include <SDL3/SDL.h>   // for key input

using namespace std;

// CONSTANT VARIABLES
const int RANGE_X = 30; // max range
const int RANGE_Y = 30;

void rangeErr(int min, int max, int& input);
void mineInit(int wdth, int hght, bool b[RANGE_X][RANGE_Y]);
void mapInit(int wdth, int hght, int a[RANGE_X][RANGE_Y], bool b[RANGE_X][RANGE_Y]);

int main() {

    // init random seed
    srand(time(nullptr));

    // variables
    int mapX, mapY; // map dimensions
    int userX, userY;   // user position
    bool mineMap[RANGE_X][RANGE_Y] = {false, false};
    int cellMap[RANGE_X][RANGE_Y] = {0, 0};

    // title
    cout << "MINEREAPER: Kill the mines by exposing their facade!" << endl;

    // configure map
    cout << "What is the map width? (1-" << RANGE_X << " inclusive): ";
    cin >> mapX;
    rangeErr(1, RANGE_X, mapX);

    cout << "What is the map height? (1-" << RANGE_Y << " inclusive): ";
    cin >> mapY;
    rangeErr(1, RANGE_Y, mapY);

    mineInit(mapX, mapY, mineMap);
    mapInit(mapX, mapY, cellMap, mineMap);
    
    SDL_Event event;

    // game loop
    // while (true) {
    //     SDL_WaitEvent(&event);  // waits for event (key press)

    //     // key input
    //     if (event.type == SDL_EVENT_KEY_DOWN) {
    //         if (event.key.key == SDLK_DOWN && userY > 0) {           // movement
    //             userY++;
    //         } else if (event.key.key == SDLK_UP && userY < mapY) {      // ||
    //             userY--;
    //         } else if (event.key.key == SDLK_LEFT) {    // ||
    //             userX--;
    //         } else if (event.key.key == SDLK_RIGHT) {   // ||
    //             userX++;
    //         } else if (event.key.key == SDLK_RETURN) {  // clear cell
    //             ;
    //         } else if (event.key.key == SDLK_BACKSPACE) {   // flag
    //             ;
    //         } else if (event.key.key == SDLK_ESCAPE) {  // quit
    //             break;
    //         }
    //     }

    //     // quit
    //     if (event.type == SDL_EVENT_QUIT) {
    //         break;
    //     }
    // }
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
void mineInit(int wdth, int hght, bool a[RANGE_X][RANGE_Y]) {
    for (int i = 0; i < (wdth * hght * 0.15); i++) {
        int rndX = rand() % wdth;  // random coordinates
        int rndY = rand() % hght;
        while (a[rndX][rndY] == true) { // retry until mine is placeable
            rndX = rand() % wdth;
            rndY = rand() % hght;
        }
        // set cell to mine
        a[rndX][rndY] = true;
    }
}

void mapInit(int wdth, int hght, int a[RANGE_X][RANGE_Y], bool b[RANGE_X][RANGE_Y]) {
    for (int i = 0; i < hght; i++) {
        for (int j = 0; j < wdth; j++) {
            if (b[j][i] == true) {  // init indicators
                for (int k = -1; k < 2; k++) {
                    for (int l = -1; l < 2; l++) {
                        int x = j + l;
                        int y = i + k;
                        if (k != 0 || l != 0) {
                            if (!(i + k < 0 || i + k > hght - 1 || j + l < 0 || j + l > wdth - 1)) {
                                a[j+l][i+k]++;
                            }
                        }
                    }
                }
            }
        }
    }
}