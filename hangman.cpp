#include <bits/stdc++.h>
#include <SDL.h>

using namespace std;

string guess;
string secretWord;
string guessWord;

string readGuess()
{
    cin >> guess;
    return guess;
}

const string WORD_LIST[] = {
	"angle", "ant", "apple", "arch", "arm", "army",
        "baby", "bag", "ball", "band", "basin", "basket", "bath", "bed", "bee", "bell", "berry",
        "bird", "blade", "board", "boat", "bone", "book", "boot", "bottle", "box", "boy",
        "brain", "brake", "branch", "brick", "bridge", "brush", "bucket", "bulb", "button",
        "cake", "camera", "card",  "cart", "carriage", "cat", "chain", "cheese", "chest",
        "chin", "church", "circle", "clock", "cloud", "coat", "collar", "comb", "cord",
        "cow", "cup", "curtain", "cushion",
        "dog", "door", "drain", "drawer", "dress", "drop", "ear", "egg", "engine", "eye",
        "face", "farm", "feather", "finger", "fish", "flag", "floor", "fly",
        "foot", "fork", "fowl", "frame",
        "garden", "girl", "glove", "goat", "gun",
        "hair", "hammer", "hand", "hat", "head", "heart", "hook", "horn", "horse",
        "hospital", "house",
        "island", "jewel",
        "kettle", "key", "knee", "knife", "knot",
        "leaf", "leg", "library", "line", "lip", "lock",
        "map", "match", "monkey", "moon", "mouth", "muscle",
        "nail", "neck", "needle", "nerve", "net", "nose", "nut",
        "office", "orange", "oven", "parcel", "pen", "pencil", "picture", "pig", "pin",
        "pipe", "plane", "plate", "plow", "pocket", "pot", "potato", "prison", "pump",
        "rail", "rat", "receipt", "ring", "rod", "roof", "root",
        "sail", "school", "scissors", "screw", "seed", "sheep", "shelf", "ship", "shirt",
        "shoe", "skin", "skirt", "snake", "sock", "spade", "sponge", "spoon", "spring",
        "square", "stamp", "star", "station", "stem", "stick", "stocking", "stomach",
        "store", "street", "sun",
        "table", "tail", "thread", "throat", "thumb", "ticket", "toe", "tongue", "tooth",
        "town", "train", "tray", "tree", "trousers",
        "umbrella",
        "wall", "watch", "wheel", "whip", "whistle", "window", "wire", "wing", "worm"};
const int WORD_COUNT = sizeof(WORD_LIST) / sizeof(string);

string chooseWord()
{
	int randomIndex = rand() % WORD_COUNT;
    return WORD_LIST[randomIndex];
}

const string FIGURE[] = {
        "   -------------    \n"
        "   |                \n"
        "   |                \n"
        "   |                \n"
        "   |                \n"
        "   |     \n"
        " -----   \n",
        "   -------------    \n"
        "   |           |    \n"
        "   |                \n"
        "   |                \n"
        "   |                \n"
        "   |     \n"
        " -----   \n",
        "   -------------    \n"
        "   |           |    \n"
        "   |           O    \n"
        "   |                \n"
        "   |                \n"
        "   |     \n"
        " -----   \n",
        "   -------------    \n"
        "   |           |    \n"
        "   |           O    \n"
        "   |           |    \n"
        "   |                \n"
        "   |     \n"
        " -----   \n",
        "   -------------    \n"
        "   |           |    \n"
        "   |           O    \n"
        "   |          /|    \n"
        "   |                \n"
        "   |     \n"
        " -----   \n",
        "   -------------    \n"
        "   |           |    \n"
        "   |           O    \n"
        "   |          /|\\  \n"
        "   |                \n"
        "   |     \n"
        " -----   \n",
        "   -------------    \n"
        "   |           |    \n"
        "   |           O    \n"
        "   |          /|\\  \n"
        "   |          /     \n"
        "   |     \n"
        " -----   \n",
        "   -------------    \n"
        "   |           |    \n"
        "   |           O    \n"
        "   |          /|\\  \n"
        "   |          / \\  \n"
        "   |     \n"
        " -----   \n"
    };

void renderGame(int attempt)
{
    cout << FIGURE[attempt] << endl;
    cout << guessWord << endl;
    cout << "Guess a character (" << 7 - attempt << " chance(s) left):" << endl;
}

bool readAndCheck()
{
    readGuess();
    if (guess.size() != 1) cout << "You can only choose 1 character at a time!" << endl;
    else {
        const char *check = guess.c_str();
        for (int i = 0; i < secretWord.size(); i++) {
            if (*check == secretWord[i]) {
                guessWord[i] = *check;
                return true;
            }
        }
    }
    return false;
}

void wordCheck()
{
    if (guessWord == secretWord) {
        cout << "Congratulations! You win!!!" << endl
            << "The word is: " << secretWord;
    }
}

void attemptCheck(int attempt)
{
    if (attempt == 7) {
        cout << "You lose!!! Better luck next time!" << endl
            << "The word is: " << secretWord;
    }
}

int main(int argc, char* argv[])
{
    srand(time(0));
    int attempt = 0;
    secretWord = chooseWord();
    guessWord = string(secretWord.length(), '-');

    while (attempt < 7 && guessWord != secretWord) {
        renderGame(attempt);

        if (readAndCheck()) {
            wordCheck();
            continue;
        } else attempt++;

        attemptCheck(attempt);
    }

    return 0;
}

//void drawHangman(SDL_Window* window, SDL_Renderer* renderer, int attempt)
//{
//    int centerX = 550;
//    int centerY = 350;
//    int radius = 50;
//
//    SDL_Rect bot, mid, top;
//    bot.x = 100;
//    bot.y = 650;
//    bot.w = 200;
//    bot.h = 50;
//    mid.x = 175;
//    mid.y = 150;
//    mid.w = 50;
//    mid.h = 500;
//    top.x = 175;
//    top.y = 100;
//    top.w = 400;
//    top.h = 50;
//    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
//    SDL_RenderFillRect(renderer, &bot);
//    SDL_RenderFillRect(renderer, &mid);
//    SDL_RenderFillRect(renderer, &top);
//
//    switch (attempt) {
//        case 7:
//            SDL_RenderDrawLine(renderer, 550, 500, 600, 600);
//        case 6:
//            SDL_RenderDrawLine(renderer, 550, 500, 500, 600);
//        case 5:
//            SDL_RenderDrawLine(renderer, 550, 425, 625, 450);
//        case 4:
//            SDL_RenderDrawLine(renderer, 550, 425, 475, 450);
//        case 3:
//            SDL_RenderDrawLine(renderer, 550, 400, 550, 500);
//        case 2:
//            for (int y = -radius; y <= radius; y++) {
//                for (int x = -radius; x <= radius; x++) {
//                    if (x * x + y * y <= radius * radius) {
//                        SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
//                    }
//                }
//            }
//        case 1:
//            SDL_RenderDrawLine(renderer, 550, 150, 550, 300);
//            break;
//    }
//}
