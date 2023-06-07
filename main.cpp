#include <iostream>
#include <chrono>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

// open file for reading and writing
fstream file("data.csv");

vector<string> locations;
vector<string> cases;
vector<string> diseases;

void showHelpMenu(){
    cout << "========================================================================" << endl;
    cout << "                                   HELP MENU                               *" <<endl;
    cout << "========================================================================" << endl;
    cout << endl; 

    cout << "add <Location>                                             :Add a new location" << endl;
    cout << "delete <Location>                                          :Delete an existing location" << endl;
    cout << "record <Location> <disease> <cases>                        :Delete an existing location" << endl;
    cout << "list locations                                             :List all existing locations" << endl;
    cout << endl;
}

string getUserInput(string input) {
    cout << "console > ";
    getline(cin, input);
    return input;
}

void addLocation(string data){
    ofstream outputFile("data.csv");
    if(outputFile.is_open()){
        outputFile << data << "," << endl;
        outputFile.close();
    }else{
        cout << "unable to open file" << endl;
    }
}


void recordDisease(string location, string disease, string cases){
    ifstream inFile("data.csv");
    ofstream tempFile("temp.txt", ios::app);

    if(!inFile.is_open() || !tempFile.is_open()){
        cout << "Error opening file. " << endl;
    }
    
    string line;
    string token;
    bool lineFound = false;
    
    string newLine = location+","+disease+","+cases;
    while(getline(inFile, line)){
        if(line.find(location) == 0){
            lineFound = true;
            tempFile << newLine << endl;
        }
        else{
            tempFile << line << endl;
        }
    }    
    if(!lineFound){
        tempFile << newLine << endl;
    }
    inFile.close();
    tempFile.close();

    remove("data.csv");
    rename("temp.txt", "data.csv");

}

int main() {
    string initialRequest;
    string featureRequest;
    string featureRequestToken;
    vector<string> featureRequestArray; 


    cout << "=========================================================" << endl;
    cout << "*      Welcome to Disease Cases Reporting System!       *" << endl;
    cout << "*  ********************************************         *" << endl;
    cout << "*   *                          *                     *" << endl;
    cout << "It is developed by 'Kunda Mugisha Sarah' as practical *" <<endl;
    cout << "evaluation for the end of year 3." << endl;
    cout << "=========================================================" << endl;
    
    cout << "Need a help? Type 'help' then press Enter key." << endl;
    cout << endl;
    initialRequest = getUserInput(initialRequest);

    if(initialRequest != "help"){
        return 0;
    }

    showHelpMenu();

    featureRequest = getUserInput(featureRequest);

    // read featureRequest into an object to split it
    stringstream ss(featureRequest);
    while(ss >> featureRequestToken){
        featureRequestArray.push_back(featureRequestToken);
    }

    string command = featureRequestArray[0];
    
    if(command == "add"){
        string location = featureRequestArray[1];
        addLocation(location);
    }else if(command == "record"){
        string location = featureRequestArray[1];
        string disease = featureRequestArray[2];
        string cases = featureRequestArray[3];

        recordDisease(location, disease, cases);   
    }
    else{
        cout << "Invalid command." << endl;
    }
    return 0;   
}
