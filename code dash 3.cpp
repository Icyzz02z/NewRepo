#include <iostream>
#include <string>

using namespace std;

// Structure for player records
struct Player {
    int playerId;
    string playerName;
    int playerScore;
    string correctAnswers[10];
    string wrongAnswers[10];
    int wrongCount;
};

// Function to swap two elements
void swap(string& a, string& b) {
    string temp = a;
    a = b;
    b = temp;
}

// Function to manually shuffle answers (simple swap technique)
void shuffleAnswers(string options[], int size) {
    for (int i = 0; i < size; i++) {
        int swapIndex = (i + 2) % size;
        swap(options[i], options[swapIndex]);
    }
}

// Function to start the game
void startGame(Player*& players, int& playerCount) {
    Player newPlayer;
    newPlayer.playerId = playerCount + 1;
    newPlayer.playerScore = 0;
    newPlayer.wrongCount = 0;

    cout << "Enter your name (single word only): ";
    cin >> newPlayer.playerName;

    string questions[10] = {
        "What year did ENHYPEN debut?",
        "Which reality show formed ENHYPEN?",
        "Who is the leader of ENHYPEN?",
        "What is the fandom name of ENHYPEN?",
        "Which ENHYPEN member is Australian?",
        "Which album contains the song 'Drunk-Dazed'?",
        "Who is the maknae (youngest member) of ENHYPEN?",
        "What is the title track of their debut album?",
        "Which entertainment company manages ENHYPEN?",
        "Which member is known for his vampire-like visuals?"
    };

    string correctAnswers[10] = {
        "2020", "I-LAND", "Jungwon", "ENGENE", "Jake",
        "BORDER: CARNIVAL", "Ni-ki", "Given-Taken", "BELIFT LAB", "Sunghoon"
    };

    string options[10][4] = {
        {"2020", "2019", "2021", "2018"},
        {"I-LAND", "Produce X 101", "Kingdom", "MIXNINE"},
        {"Jungwon", "Heeseung", "Jake", "Sunoo"},
        {"ENGENE", "ENHYPENERS", "HYPENICS", "HEARTBEAT"},
        {"Jake", "Jay", "Sunghoon", "Jungwon"},
        {"BORDER: CARNIVAL", "BORDER: DAY ONE", "DIMENSION: ANSWER", "MANIFESTO: DAY 1"},
        {"Ni-ki", "Sunghoon", "Jay", "Jake"},
        {"Given-Taken", "Drunk-Dazed", "FEVER", "Blessed-Cursed"},
        {"BELIFT LAB", "HYBE", "JYP Entertainment", "SM Entertainment"},
        {"Sunghoon", "Heeseung", "Ni-ki", "Jay"}
    };

    for (int i = 0; i < 10; i++) {
        shuffleAnswers(options[i], 4);
    }

    int answerChoice;
    for (int i = 0; i < 10; i++) {
        cout << "\nQuestion " << (i + 1) << ": " << questions[i] << endl;

        int correctIndex = -1;
        for (int j = 0; j < 4; j++) {
            cout << j + 1 << ". " << options[i][j] << endl;
            if (options[i][j] == correctAnswers[i]) {
                correctIndex = j + 1;
            }
        }

        cout << "Enter the number of your choice: ";
        cin >> answerChoice;

        if (answerChoice < 1 || answerChoice > 4) {
            cout << "Invalid choice. Try again!" << endl;
            i--;
            continue;
        }

        if (answerChoice == correctIndex) {
            cout << "Correct!" << endl;
            newPlayer.playerScore++;
            newPlayer.correctAnswers[i] = questions[i] + " ✅ " + correctAnswers[i];
        }
        else {
            cout << "Incorrect! The correct answer was: " << correctAnswers[i] << endl;
            newPlayer.wrongAnswers[newPlayer.wrongCount++] =
                questions[i] + " ❌ " + options[i][answerChoice - 1] + " ➝ ✅ " + correctAnswers[i];
        }
    }

    cout << "\n" << newPlayer.playerName << "'s final score: " << newPlayer.playerScore << " out of 10\n";

    Player* temp = new Player[playerCount + 1];
    for (int i = 0; i < playerCount; i++) {
        temp[i] = players[i];
    }
    temp[playerCount] = newPlayer;

    delete[] players;
    players = temp;
    playerCount++;
}

// Function to view scores
void viewScores(Player* players, int playerCount) {
    if (playerCount == 0) {
        cout << "No scores recorded yet!" << endl;
        return;
    }

    for (int i = 0; i < playerCount; i++) {
        cout << "\nID: " << players[i].playerId << " | Name: " << players[i].playerName
            << " | Score: " << players[i].playerScore << "/10\n";
    }
}

// Function to delete player records
void deletePlayer(Player*& players, int& playerCount) {
    delete[] players;
    players = nullptr;
    playerCount = 0;
    cout << "All player records have been deleted!" << endl;
}

// Main menu function
void mainMenu() {
    Player* players = nullptr;
    int playerCount = 0;
    int choice;

    do {
        cout << "\n1. Start Game\n2. View Scores\n3. Delete All Records\n4. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            startGame(players, playerCount);
            break;
        case 2:
            viewScores(players, playerCount);
            break;
        case 3:
            deletePlayer(players, playerCount);
            break;
        case 4:
            cout << "Exiting...\n";
            delete[] players;
            return;
        default:
            cout << "Invalid choice, try again!\n";
        }
    } while (true);
}

// Main function
int main() {
    mainMenu();
    return 0;
}

