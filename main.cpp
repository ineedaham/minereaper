// program name: minereaper
// description: slime out da mines. why they tryna fake being cells fr?

#include <iostream>
#include <SDL3/SDL.h>   // for key input

using namespace std;

void rangeErr(int min, int max, int& input);
void mineInit(int wdth, int hght, bool& a);

int main() {

    // init random seed
    srand(time(nullptr));

    // CONSTANT VARIABLES
    const int RANGE_X = 30;
    const int RANGE_Y = 30;

    // variables
    int mapX, mapY; // map dimensions
    int userX, userY;   // user position
    bool mineMap[RANGE_X][RANGE_Y] = {};
    int cellMap[RANGE_X][RANGE_Y] = {};

    // title
    cout << "MINEREAPER: Kill the mines by exposing their facade!" << endl;

    // configure map
    cout << "What is the map width? (1-30 inclusive): ";
    cin >> mapX;
    rangeErr(1, 30, mapX);

    cout << "What is the map height? (1-30 inclusive): ";
    cin >> mapY;
    rangeErr(1, 30, mapY);

    map = mapInit(RANGE_X, RANGE_Y, map);
    
    // game loop
    while (true) {
        SDL_WaitEvent(&event);  // waits for event (key press)

        // key input
        if (event.type == SDL_EVENT_KEY_DOWN) {
            if (event.key.key == SDLK_DOWN) {           // movement
                userY--;
            } else if (event.key.key == SDLK_UP) {      // ||
                userY++;
            } else if (event.key.key == SDLK_LEFT) {    // ||
                userX--;
            } else if (event.key.key == SDLK_RIGHT) {   // ||
                userX++;
            } else if (event.key.key == SDLK_RETURN) {  // check for cell
                
            } else if (event.key.key == SDLK_BACKSPACE) {   // flag
                
            } else if (event.key.key == SDLK_ESCAPE) {  // quit
                
            }
        }

        // quit
        if (event.type == SDL_EVENT_QUIT) {
            break;
        }
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
void mineInit(int wdth, int hght, bool& a) {
    for (int i = 0; i < (wdth * hght * 0.15); i++) {
        int rndX = rand() % (wdth * hght);  // random coordinates
        int rndY = rand() % (wdth * hght);
        while (a[rndX][rndY] == true) { // retry until mine is placeable
            rndX = rand() % (wdth * hght);
            rndY = rand() % (wdth * hght);
            a[rndX][rndY] = true;
        }
    }
}
