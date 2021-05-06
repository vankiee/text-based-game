#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <chrono>
#include <thread>
#include "rooms.h" 

using namespace std;

const int NUMBER_OF_ROOMS = 3;
const int NUMBER_OF_AREAS = 4;

//display game title
void opening(){
    cout << " _____  " << " _____  " << " _____  " << "  ___   " << " _____  " << " _____  " << " " << " _   _  " << " _   __ " << " _   _  " << endl; //first layer
    cout << "|  ___| " << "/  ___| " << "/  __ \\ " << " / _ \\  " << "| ___ \\ " << "|  ___| " << " " << "| | | | " << "| | / / " << "| | | | " << endl; //second layer
    cout << "| |__   " << "\\ `--.  " << "| /  \\/ " << "/ /_\\ \\ " << "| |_/ / " << "| |__   " << " " << "| |_| | " << "| |/ /  " << "| | | | " << endl; //third layer
    cout << "|  __|  " << " `--. \\ " << "| |     " << "|  _  | " << "|  __/  " << "|  __|  " << " " << "|  _  | " << "|    \\  " << "| | | | " << endl; //fourth layer
    cout << "| |___  " << "/\\__/ / " << "| \\__/\\ " << "| | | | " << "| |     " << "| |___  " << " " << "| | | | " << "| |\\  \\ " << "| |_| | " << endl; //fifth layer
    cout << "\\____/  " << "\\____/  " << " \\____/ " << "\\_| |_/ " << "\\_|     " << "\\____/  " << " " << "\\_| |_/ " << "\\_| \\_/ " << " \\___/  " << endl; //sixth layer
    cout << endl;
}
//random comment generator when player fails to answer riddle
void randomComment_failed() {
    srand(time(NULL));
    vector<string> comments{
        "That is not the right answer, please try again.", 
        "A piece of paper flies into your face. It reads, 'LOSER'.", 
        "Don't get it? Check Wikipedia!", 
        "BRUH THAT AIN'T RIGHT...", 
        "What bad luck you have! The better to lose this game with."
    };
    int i = rand()%comments.size();
    cout << comments.at(i) << endl;
}
//random comment generator when player answers riddle correctly
void randomComment_succeed() {
    srand(time(NULL));
    vector<string> comments{
        "Good job! You solved it.",
        "YAY you got it!", 
        "You did great! Are you sure you didn't check Wikipedia?", 
        "Woohoo one step closer to escaping HKU!", 
        "That is correct. I wish you had this much enthusiasm in doing your assignments. :)"
    };
    int i = rand()%comments.size();
    cout << comments.at(i) << endl;
}
//random comment generator when no riddles are found in the riddle input file
void randomComment_nothing() {
    srand(time(NULL));
    vector<string> comments{
        "Nothing's here.",
        "Look in another area.", 
        "Only dust mites and cobwebs here.", 
        "You found....... nothing", 
        "You hear footsteps approaching...... LEAVE THIS AREA IMMEDIATELY."
    };
    int i = rand()%comments.size();
    cout << comments.at(i) << endl;
}

int main(){
    opening();
    
    //asks for player's name and input to start game
    string PlayerName;
    cout << "Please enter your name: ";
    cin >> PlayerName;
    cout << PlayerName << ", are you ready to escape HKU?\n" << "Please enter 'Y' to continue: ";
    string answer;
    cin >> answer;
    while (answer != "Y") {
        cout << "Not ready for this game? Type 'Y' to begin the game!: ";
        cin >> answer;
    }
    cout << endl;

    //initialize the seed
    srand(time(NULL)); 
    vector<Room> *rooms = new vector<Room>();
    
    //initialize rooms in the game
    for (int i = 0; i < NUMBER_OF_ROOMS; i++){
	    rooms->push_back(Room(i));
    }
    
    //keeps looping as long as the player has not escaped all 3 rooms
    while(!rooms->empty()){
        //randomize the starting room
        int RoomNumber = rand()%rooms->size();
        cout << "You're now in " << rooms->at(RoomNumber).name << ". Good luck!" << endl;
        cout << endl;
        
        //keeps looping as long as the player has not solved all riddles in the room
        while(!rooms->at(RoomNumber).isComplete()){
            int response;
            bool valid = false;
            
            while (!valid){
                cout << "Where do you want to explore?" << endl;
                
                //list the areas that the player can choose to explore
                for (int i = 0; i < NUMBER_OF_AREAS; i++){
                    cout << i + 1 << ". " << rooms->at(RoomNumber).areas[i].name << endl;
                }
                cin >> response;
                response--;
                
                //player input out of bounds
                if ((response < 0) || (response >= NUMBER_OF_AREAS)) {
                    cout << "There is no such area. Are you falling asleep?" << endl;
                }
                //if player input is valid and the area has yet to be explored
                else if (!rooms->at(RoomNumber).areas[response].explored){ 
                    valid = true;
                } 
                //if player input is valid, but the area has already been explored
                else {
                    cout << "You were already here. You don't remember?" << endl;
                    cout << endl;
                } 
                cout << endl;
            }
            while(!rooms->at(RoomNumber).areas[response].explored){
                int response2;
                
                //when no riddles are found in the area, three ellipses are printed one second after the other
                //and a random comment is displayed
                if (rooms->at(RoomNumber).areas[response].riddle == "no riddle") {
                    for (int j = 0; j < 3; ++j) {
                        cout << ".";
                        this_thread::sleep_for(chrono::seconds(1));
                    }
                    randomComment_nothing();
                    cout << endl;
                    rooms->at(RoomNumber).areas[response].explored = true;
                    break;
                }
                //display the riddle
                cout << "You found a riddle here. The " << rooms->at(RoomNumber).areas[response].name << " was a good choice." << endl;
                cout << "\"" << rooms->at(RoomNumber).areas[response].riddle << "\"" << endl;
                cout << endl;
                
                //display the choices of answers
                cout << "What am I?" << endl;
                for (int i = 0; i < rooms->at(RoomNumber).areas[response].choices.size(); i++){
                    cout << i + 1 << ". " << rooms->at(RoomNumber).areas[response].choices[i] << endl;
                }
                cout << endl;
                //ask for the correct answer
                cout << "Type 1/2/3 if you think it's the correct answer."<< endl;
                cin >> response2;
                cout << endl;
                
                //if player input is in bounds, and the answer is correct, the area is marked as explored
                if ((response2 > 0) && (response2 < 4)) {
                    if (rooms->at(RoomNumber).areas[response].isCorrectAnswer(response2)){
                        rooms->at(RoomNumber).areas[response].explored = true;
                        for (int j = 0; j < 3; ++j) {
                            cout << ".";
                            this_thread::sleep_for(chrono::seconds(1));
                        }
                        randomComment_succeed();
                        cout << endl;
                    }
                    else {
                        for (int j = 0; j < 3; ++j) {
                            cout << ".";
                            this_thread::sleep_for(chrono::seconds(1));
                        }
                        randomComment_failed();
                        cout << endl;
                    } 
                }
                else {
                    cout << "Your answer is invalid. (?_?)  Please try again." << endl;
                    cout << endl;
                }    
            }
        }
        //remove explored room
        rooms->erase(rooms->begin() + RoomNumber);
    }
    delete rooms;
    cout << "You have escaped HKU. Run and don't look back, " << PlayerName << "!" << endl;
    return 0;
}
