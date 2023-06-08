#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <string>
#include <cctype>

using namespace std;

// open file for reading and writing
fstream file("data.csv");

vector<string> locations;
vector<string> cases;
vector<string> diseases;

void showHelpMenu(){
    cout << "========================================================================" << endl;
    cout << endl;
    cout << "                                   HELP MENU                               *" <<endl;
    cout << endl;
    cout << "========================================================================" << endl;
    cout << endl; 

    cout << "add <Location>                                             :Add a new location" << endl;
    cout << endl;
    cout << "delete <Location>                                          :Delete an existing location" << endl;
    cout << endl;
    cout << "record <Location> <disease> <cases>                        :Delete an existing location" << endl;
    cout << endl;
    cout << "list locations                                             :List all existing locations" << endl;
    cout << endl;
    cout << "list diseases                                              :List existing Diseases in locations" << endl;
    cout << endl;
    cout << "where <disease>                                            :Find where diease exists" << endl; 
    cout << endl;
    cout << "cases <location> <disease>                                 :Find cases of a disease in location" << endl;
    cout << endl;
    cout << "cases <disease>                                            :Find total cases of a given disease" << endl;
    cout << endl;
    cout << "help                                                       :Prints user manual" << endl;
    cout << endl;
    cout << "Exit                                                       :Exits the program" << endl;
    cout << endl;
}

// util functions 

vector<string> split(string str, char delimeter){
    stringstream ss(str);
    string token;
    vector<string> tokens;
    while (getline(ss, token, delimeter))
    {   
        tokens.push_back(token);
    }
    return tokens;
}

string getUserInput(string input) {
    cout << "Console > ";
    getline(cin, input);
    return input;
}

int checkIfIncludes(vector<string> data, string searchValue){
    int found = 0;
    for(const auto& token : data){
        if(token == searchValue){
            found = 1;
        }
    }
    return found;
}


vector<string> toUpperCase(vector<string> data){
    for(auto& item : data){
        transform(item.begin(), item.end(), item.begin(), [](char c) {
            return toupper(c);
        });
    }

    return data;
}

void printOutput(string output){
    cout << "\t" << output << endl;
}

void printListOutput(vector<string> data){
    for(auto& item : data){
        cout << "\t" << item << endl;
    }
}

string getCurrentTime(){
    time_t currentTime = time(nullptr);

    // Format the time using std::strftime
    char formattedTime[50];
    strftime(formattedTime, sizeof(formattedTime), "%a %b %d %H:%M:%S CAT %Y", localtime(&currentTime));
    return formattedTime ;
}
// Features

void addLocation(string data){
    ofstream outputFile("data.csv", ios::app);
    ifstream file("data.csv");
    string line;
    vector<string> splitLine;
    vector<string> locations;

    while (getline(file, line)){
        splitLine = split(line, ',');
        if(!checkIfIncludes(locations, splitLine[0])){
            locations.push_back(splitLine[0]);
        }
    }

    if(outputFile.is_open()){
        if(!checkIfIncludes(locations, data)){
            outputFile << data << "," << endl;
            printOutput("Location " + data + " is successfully added!");
        }else{
            printOutput("Location " + data + "already added!");
        }
        outputFile.close();
    }else{
        printOutput("unable to open file");
    }
    outputFile.close();
}


void recordDisease(string location, string disease, string cases){
    ifstream inFile("data.csv");
    ofstream tempFile("temp.txt", ios::app);

    if(!inFile.is_open() || !tempFile.is_open()){
        printOutput("Error opening file. ");
    }
    
    string line;
    vector<string> splitLine;
    bool lineFound, lineFoundWithDisease = false;
    
    string newLine = location+","+disease+","+cases;
    while(getline(inFile, line)){
        if(line.find(location) != string::npos){
            lineFound = true;
            splitLine = split(line, ',');
            if(splitLine.size() == 1){
                tempFile << newLine << endl;
            }else{
                tempFile << line << endl;
                lineFoundWithDisease = true;
            }
        }
        else{
            tempFile << line << endl;
        }
    }    
    if(!lineFound || lineFoundWithDisease){
        tempFile << newLine << endl;
    }

    inFile.close();
    tempFile.close();

    remove("data.csv");
    rename("temp.txt", "data.csv");

}

void showWelcome(){
    cout << "=========================================================" << endl;
    cout << endl;
    cout << "*      Welcome to Disease Cases Reporting System!       *" << endl;
    cout << endl;
    cout << "*  *******************************************  *        " << endl;
    cout << endl;
    cout << "*                             *                          " << endl;
    cout << endl;
    cout << "* It is developed by 'Kunda Mugisha Sarah' as practical *" <<endl;
    cout << endl;
    cout << "* evaluation for the end of year 3." << endl;
    cout <<endl;
    cout << "=========================================================" << endl;
    cout<< endl;
    cout << "Starting Time: " << getCurrentTime() << endl;
    cout << endl;
    cout << "Need a help? Type 'help' then press Enter key." << endl;
    cout << endl;
}

void listLocations() {
    ifstream file("data.csv");
    string line;
    vector<string> splitLine;
    vector<string> locations;

    while (getline(file, line)){
        splitLine = split(line, ',');
        if(!checkIfIncludes(locations, splitLine[0])){
            locations.push_back(splitLine[0]);
        }
    }

    std::sort(locations.begin(), locations.end());

    printListOutput(locations);

    file.close();
}

void listDiseases() {
    ifstream file("data.csv");
    string line;
    string token;
    vector<string> splitLine;
    vector<string> diseases;

    while (getline(file, line)){
        splitLine = split(line, ',');
        if(!checkIfIncludes(diseases, splitLine[1])){
            diseases.push_back(splitLine[1]);
        }
    }

    std::sort(diseases.begin(), diseases.end());

    for(const auto& disease : diseases){
        cout << disease << endl;
    }
    
    file.close();
}

void deleteData(string location){
    ifstream file("data.csv");
    ofstream tempFile("newFile.csv");
    string line;
    bool found = false;

    while (getline(file, line)){
        if(line.find(location) != string::npos){
            found = true;
            continue;
        }
        tempFile << line << endl;
    }

    if(found == false){
        printOutput("Location " + location + " not found ");
    }

    tempFile.close();
    file.close();

    remove("data.csv");
    rename("newFile.csv", "data.csv");
}

void listLocationsWithDisease(string disease){
    ifstream file("data.csv");
    string line;
    string token;
    vector<string> splitLine;
    vector<string> locations;
    bool found = false;
    while (getline(file, line)){
        if(line.find(disease) != string::npos){
            found = true;
            splitLine = split(line, ',');
            if(!checkIfIncludes(locations, splitLine[0])){
                locations.push_back(splitLine[0]);
            }
        }
    }

    if(found == false){
        printOutput("No location with this disease");
    }
    printListOutput(locations);
    
    file.close();
}

void totalDiseaseCases(string disease){
    ifstream file("data.csv");
    string line;
    vector<string> splitData;
    int totalCases = 0;
    
    bool found = false;
    while (getline(file, line)){
        if(line.find(disease) != string::npos){
            splitData = split(line,',');
            totalCases += stoi(splitData[2]);
        }
    }    
    
    string output = "Total cases of '" + disease + "' = " + to_string(totalCases);
    printOutput(output);
    file.close();
}

void showDiseaseCasesInLocation(string disease, string location){
    ifstream file("data.csv");
    string line;
    vector<string> splitLine;
    int totalCases = 0;
    while (getline(file, line)){
        if(line.find(disease) != string::npos && line.find(location) != string::npos){
            splitLine = split(line, ',');
            totalCases += stoi(splitLine[2]);
        }
    }

    printOutput("Cases of " + disease + " at " + location + " are: " + to_string(totalCases));
    file.close();
}


int main() {
    string featureRequest;
    string featureRequestToken;
    vector<string> featureRequestArray; 
    bool exit = false;

    showWelcome();

    while(!exit){
        featureRequest = getUserInput(featureRequest);

        // read featureRequest into an object to split it
        stringstream ss(featureRequest);
        while(ss >> featureRequestToken){
            featureRequestArray.push_back(featureRequestToken);
        }

        // convert every user data to uppercase 
        featureRequestArray = toUpperCase(featureRequestArray);

        string command = featureRequestArray[0];
        if(command == "ADD"){
            string location = featureRequestArray[1];
            addLocation(location);
        }else if(command == "RECORD"){
            string location = featureRequestArray[1];
            string disease = featureRequestArray[2];
            string cases = featureRequestArray[3];

            recordDisease(location, disease, cases);   
        }
        else if(command == "LIST"){
            if(featureRequestArray.size() == 2){
                if(featureRequestArray[1] == "DISEASES"){
                    listDiseases();
                }else if(featureRequestArray[1] == "LOCATIONS"){
                    listLocations();
                }
            }else{
                cout << "Please input a valid command " << endl;
            }
        }
        else if(command == "DELETE"){
            string location = featureRequestArray[1];
            deleteData(location);
        }
        else if(command == "WHERE"){
            string disease = featureRequestArray[1];
            listLocationsWithDisease(disease);
        }
        else if(command == "CASES"){
            if(featureRequestArray.size() == 2){
                totalDiseaseCases(featureRequestArray[1]);
            }else{
                string disease = featureRequestArray[2];
                string location = featureRequestArray[1];
                showDiseaseCasesInLocation(disease, location);
            }
        }
        else if(command == "HELP"){
            showHelpMenu();
        }
        else if(command == "EXIT"){
            break;
        }
        else{
            cout << "Invalid command." << endl;
        }
        featureRequest = "" ;
        featureRequestArray.clear();
    }
    return 0;   
}
