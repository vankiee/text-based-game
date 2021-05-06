//areas in a room
#ifndef AREAS_H
#define AREAS_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Area {
    string name; //name of the area
    string riddle; 
    vector<string> choices; //answer choices
    int answer;
    bool answered; 
    bool explored;

    //initialize the area
    Area(){
        answered = false;
        explored = false;
    }
    //check if user inputs correct answer
    bool isCorrectAnswer(int response){
        answered = response == answer;
        return answered;
    }
};

#endif