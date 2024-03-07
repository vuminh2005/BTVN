#include <bits/stdc++.h>

using namespace std;

int first, last;
string response;
int guess;
string again;

void getRange() {
    cout << "Please enter the range (from ... to ...):" << endl;
    int a, b;
    cin >> a >> b;
    first = a;
    last = b;
}

int guessAnswer(int low, int high) {
    int answer = rand() %  (high - low + 1) + low;
    return answer;
}

string getHostAnswer(int random) {
    cout << "Is " << random << " the answer(=) or higher(>) / lower(<) than your number?" << endl;
    cin >> response;
    return response;
}

void guessIt() {
    getRange();
    do {
        guess = guessAnswer(first, last);
        response = getHostAnswer(guess);
        if (response == "=") {
            cout << "Great! Do you want to play again? (Y/N)" << endl;
            cin >> again;
            if (again == "N") cout << "OK! Goodbye <3";
        } else if (response == ">") {
            last = guess - 1;
        } else if (response == "<") {
            first = guess + 1;
        }
    } while (response != "=");
}

int main(){
    do {
        guessIt();
    } while (again == "Y");
}
