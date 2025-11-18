#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

#define MAX 20

class Stack {
public:
    int arr[MAX];
    int top;

    Stack() { top = -1; }

    void push(int val) {
        arr[++top] = val;
    }

    int pop() {
        return arr[top--];
    }
};

void shuffleCards(vector<char> &a) {
    int n = a.size();
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(a[i], a[j]);
    }
}

int main() {
    int n;
    cout << "Enter number of pairs (max 10): ";
    cin >> n;

    int total = 2 * n;
    vector<char> cards(total);
    vector<int> shown(total, 0);

    srand(time(NULL));

    // Create pairs A, B, C...
    for (int i = 0; i < n; i++) {
        cards[2*i] = 'A' + i;
        cards[2*i + 1] = 'A' + i;
    }

    shuffleCards(cards);

    Stack s;
    int matched = 0, attempts = 0;

    cout << "\n--- MEMORY GAME STARTED ---\n";

    while (matched < n) {

        // Display board
        cout << "\nBoard:\n";
        for (int i = 0; i < total; i++) {
            if (shown[i])
                cout << "[" << cards[i] << "] ";
            else
                cout << "[*] ";
        }
        cout << "\n";

        int p1, p2;

        cout << "\nChoose first card (1-" << total << "): ";
        cin >> p1;
        cout << "Choose second card (1-" << total << "): ";
        cin >> p2;

        p1--; p2--; // convert to index

        if (p1 == p2 || p1 < 0 || p2 < 0 || p1 >= total || p2 >= total ||
            shown[p1] || shown[p2]) {
            cout << "Invalid positions! Try again.\n";
            continue;
        }

        attempts++;

        // Store in stack
        s.push(p1);
        s.push(p2);

        cout << "\nCard " << p1+1 << " = " << cards[p1];
        cout << "\nCard " << p2+1 << " = " << cards[p2] << "\n";

        if (cards[p1] == cards[p2]) {
            cout << "✔ Match Found!\n";
            shown[p1] = shown[p2] = 1;
            matched++;
        } else {
            cout << "✘ Not a match. Cards will be hidden again.\n";
        }
    }

    cout << "\n--- GAME OVER ---\n";
    cout << "Total Attempts = " << attempts << "\n";
    cout << "Stack Size (total selections stored) = " << (s.top + 1) << "\n";

    return 0;
}
