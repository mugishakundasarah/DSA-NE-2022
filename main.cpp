#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <string>

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
    cout << "list diseases                                              :List existing Diseases in locations" << endl;
    cout << "where <disease>                                            :Find where diease exists" << endl; 
    cout << "cases <location><disease>                                  :FInd cases of a disease in location" << endl;
    cout << "cases <disease>                                            :Find total cases of a given disease" << endl;
    cout << "help                                                       :Prints user manual" << endl;
    cout << "Exit                                                       :Exits the program" << endl;
    cout << endl;
}

string getUserInput(string input) {
    cout << "console > ";
    getline(cin, input);
    return input;
}

void addLocation(string data){
    ofstream outputFile("data.csv", ios::app);
    if(outputFile.is_open()){
        outputFile << data << "," << endl;
        outputFile.close();
    }else{
        cout << "unable to open file" << endl;
    }
    outputFile.close();
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
        if(line.find(location) != string::npos){
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

void listLocations() {
    ifstream file("data.csv");
    string line;
    string token;
    vector<string> splitLine;
    vector<string> locations;

    while (getline(file, line)){
        splitLine = split(line, ',');
        locations.push_back(splitLine[0]);
    }

    std::sort(locations.begin(), locations.end());

    for(const auto& location : locations){
        cout << location << endl;
    }

    file.close();
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
            tempFile << line << endl;
            continue;
        }
        found = true;
    }

    if(found == false){
        cout << "Location " << location << " not found " << endl;
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
                diseases.push_back(splitLine[0]);
            }
        }
    }

    if(found == false){
        cout << "Disease not found in any location" << endl;
    }
    for(const auto& disease : diseases){
        cout << disease << endl;
    }
    
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
    
    cout << "Total cases of " << disease << " = " << totalCases << endl;
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

    cout << "cases of " << disease << " at " << location << " are: " << totalCases << endl;
    file.close();
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
    cout<< endl;
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
    else if(command == "list"){
        if(featureRequestArray[1] == "diseases"){
            listDiseases();
        }else if(featureRequestArray[1] == "locations"){
            listLocations();
        }else{
            cout << "Please input a valid command " << endl;
        }
    }
    else if(command == "delete"){
        string location = featureRequestArray[1];
        deleteData(location);
    }
    else if(command == "where"){
        string disease = featureRequestArray[1];
        listLocationsWithDisease(disease);
    }
    else if(command == "cases"){
        if(featureRequestArray[2] == ""){
            totalDiseaseCases(featureRequestArray[1]);
        }else{
            string disease = featureRequestArray[2];
            string location = featureRequestArray[1];
            showDiseaseCasesInLocation(disease, location);
        }
    }
    else{
        cout << "Invalid command." << endl;
    }
    return 0;   
}
