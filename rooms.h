#ifndef ROOMS_H
#define ROOMS_H

#include <vector> 
#include <fstream>
#include <iostream>
#include <string>

#include "areas.h"

using namespace std;

struct Room {
    string name;
    vector<Area> areas;
    
    Room(int room_number){
        string file_name;
        
        //open metadata file containing room name and areas in the room
        file_name = "metadata/room" + to_string(room_number) + ".txt";
        ifstream fin;
        fin.open(file_name);
        if (!fin.is_open()) {
            cout << "can't open file:" << file_name <<endl;
        }
        
        //Read from metadata
        string line;
        vector<string> temp;
        while (getline(fin, line)) {
            temp.push_back(line);
        }
        fin.close();
        name = temp[0];

        //open riddle files containing riddle, correct answer, and answer choices
        for (int i = 0; i < 4; i++) {
            file_name = "riddles/room" + to_string(room_number) + "_" + to_string(i) + ".txt";
            ifstream fin;
            fin.open(file_name);
            if (!fin) {
                cout << "can't open file:" << file_name << endl;
            }
            //read riddles 
            Area new_area;
            new_area.name = temp[i + 1];
            vector<string> temp2;
            while (getline(fin, line)) {
                temp2.push_back(line);
            }
            new_area.riddle = temp2[0];
            
            if (new_area.riddle != "no riddle") {
                new_area.answer = stoi(temp2[1]);
                for (int j = 2; j < 5; j++) {
                    new_area.choices.push_back(temp2[j]);
                }    
            }
            else {
                new_area.answered = true;
            }
            areas.push_back(new_area);
            fin.close();
        }
    }
    //check if room has been solved
    bool isComplete(){
        bool res = true;
        for (Area area : areas) {
            res = res && area.answered;
        }
        return res;
    }
};

#endif
