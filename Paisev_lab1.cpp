#include <iostream>
#include <string>
#include <limits>
#include <fstream>

using namespace std;

// ----------------------------------------------------STRUCTURS-------------------------------------------------------------------------

struct Pipe {
    std::string name;
    int length;
    int diametre;
    bool repair_status;
    bool created = false; 
};

struct Compressor_station {
    std::string name;
    int workshop;
    int workshop_active;
    int effective;
    bool created = false;
};


// ----------------------------------------------------FUNCTION_CHECK_INT--------------------------------------------------------------------

bool isValidNumber(const std::string& str) {
    for (char const &c : str) {
        if (std::isdigit(c) == 0) return false;
    }
    return true;
}

// ----------------------------------------------------FUNCTION_CREATE_PIPE-------------------------------------------------------------------

void CreatePipe(Pipe& own_pipe) {
    cout << "Please, enter name of your pipe >> ";
    std::getline(cin, own_pipe.name);
    
    cout << "Please, enter length of your pipe >> ";
    while (true) {
        std::string input;
        std::getline(cin, input);
        if (isValidNumber(input)) {
            own_pipe.length = std::stoi(input);
            if (own_pipe.length >= 1) break;
            else cout << "Length must be at least 1. Please enter a valid number for length >> ";
        } else {
            cout << "Invalid input. Please enter a valid number for length >> ";
        }
    }
    
    cout << "Please, enter diametre of your pipe >> ";
    while (true) {
        std::string input;
        std::getline(cin, input);
        if (isValidNumber(input)) {
            own_pipe.diametre = std::stoi(input);
            if (own_pipe.diametre >= 1) break;
            else cout << "Diametre must be at least 1. Please enter a valid number for diametre >> ";
        } else {
            cout << "Invalid input. Please enter a valid number for diametre >> ";
        }
    }
    
    cout << "Please, enter repair status of your pipe (0 for No, 1 for Yes) >> ";
    while (true) {
        std::string input;
        std::getline(cin, input);
        if (input == "0" || input == "1") {
            own_pipe.repair_status = std::stoi(input);
            own_pipe.created = true;
            break;
        } else {
            cout << "Invalid input. Please enter 0 or 1 for repair status >> ";
        }
    }
}

// ----------------------------------------------------FUNCTION_CREATE_CS-------------------------------------------------------------------

void CreateCS(Compressor_station& own_cs) {
    cout << "Please, enter name of your CS >> ";
    std::getline(cin, own_cs.name);

    cout << "Please, enter amount workshops of your CS >> ";    
    while (true){
        std::string input;
        std::getline(cin, input);
        if (isValidNumber(input)){
            own_cs.workshop = std::stoi(input);
            break;
        }
        else{
            cout << "Please, enter the valid number! >>";
        }
    }


    cout << "Please, enter amount workshops in active of your CS >> ";
    while (true)
    {
        std::string input;
        std::getline(cin, input);
        if (isValidNumber(input)){
            if (own_cs.workshop >= std::stoi(input)){
                own_cs.workshop_active = std::stoi(input);
                break;
            }
            else{
                cout << "Number of active workshops cannot be greater than total workshops. Please enter a valid number for active workshops >> ";
            }
        }
        else{
            cout << "Invalid input. Please enter a valid number for active workshops >> ";
        }
    }
    
    cout << "Please, enter effective of your cs (Its number equalse your own property) >> ";
    while (true){
        std::string input;
        getline(cin, input);
        if (isValidNumber(input)){
            own_cs.effective = std::stoi(input);
            own_cs.created = true;
            break;
        }
        else{
            cout << "Invalid input. Please enter a valid value >> ";
        }
    }
}

// ----------------------------------------------------FUNCTION_SHOW_PIPE_AND_CS-------------------------------------------------------------------

void Show_Pipe_and_CS(Pipe& own_pipe, Compressor_station& own_cs) {

    if (!own_pipe.created && !own_cs.created) {
        cout << "Nothing created." << endl;
        return;
    }
    
    if (own_pipe.created) {
        cout << "Pipe description:" << endl;
        cout << "    Name: " << own_pipe.name << endl;
        cout << "    Length: " << own_pipe.length << endl;
        cout << "    Diametre: " << own_pipe.diametre << endl;
        cout << "    Repair Status: " << (own_pipe.repair_status ? "Yes" : "No") << endl;
    } else {
        cout << "Pipe not created." << endl;
    }

    if (own_cs.created) {
        cout << "CS description:" << endl;
        cout << "    Name: " << own_cs.name << endl;
        cout << "    Workshops: " << own_cs.workshop << endl;
        cout << "    Workshops in active: " << own_cs.workshop_active << endl;
        cout << "    Effective: " << own_cs.effective << endl;
    } else {
        cout << "CS not created." << endl;
    }

}

// ----------------------------------------------------FUNCTION_EDIT_PIPE-------------------------------------------------------------------

void EditPipe(Pipe& own_pipe) {
    if (!own_pipe.created) {
        cout << "Pipe not created. Cannot edit." << endl;
        return;
    }
    else{
        cout << "Please, enter new repair status of your pipe (0 for No, 1 for Yes) >> ";
        while (true) {
            std::string input;
            std::getline(cin, input);
            if (input == "0" || input == "1") {
                own_pipe.repair_status = std::stoi(input);
                break;
            } else {
                cout << "Invalid input. Please enter 0 or 1 for repair status >> ";
            }
        }
    }
}

// ----------------------------------------------------FUNCTION_EDIT_CS-------------------------------------------------------------------

void EditCS(Compressor_station& own_cs) {
    if (!own_cs.created) {
        cout << "CS not created. Cannot edit." << endl;
        return;
    }
    else{
        cout << "Please, enter new amount of workshops in active >> ";
        while (true)
        {
            std::string input;
            std::getline(cin, input);
            if (isValidNumber(input)){
                if (own_cs.workshop >= std::stoi(input)){
                    own_cs.workshop_active = std::stoi(input);
                    break;
                }
                else{
                    cout << "Number of active workshops cannot be greater than total workshops. Please enter a valid number for active workshops >> ";
                }
            }
            else{
                cout << "Invalid input. Please enter a valid number for active workshops >> ";
            }
        }
    }
}

// ----------------------------------------------------FUNCTION_SAVE_CURRENT_PIPE_AND_CS-------------------------------------------------------------------

void Save(const Pipe& own_pipe, const Compressor_station& own_cs) {
    ofstream file("data_save.txt");
    if (file.is_open()) {
        file << "Pipe:\n";
        file << (own_pipe.created ? "1\n" : "0\n");
        if (own_pipe.created) {
            file << own_pipe.name << '\n';
            file << own_pipe.length << '\n';
            file << own_pipe.diametre << '\n';
            file << own_pipe.repair_status << '\n';
        }

        file << "CompressorStation: \n";
        file << (own_cs.created ? "1\n" : "0\n");
        if (own_cs.created) {
            file << own_cs.name << '\n';
            file << own_cs.workshop << '\n';
            file << own_cs.workshop_active << '\n';
            file << own_cs.effective << '\n';
        }
        file.close();
    } else {
        cout << "Unable to open file for saving." << endl;
    }
}

// ----------------------------------------------------FUNCTION_LOAD_PIPE_AND_CS_FROM_FILE-------------------------------------------------------------------

void Load(Pipe& own_pipe, Compressor_station& own_cs) {
    ifstream file("data.txt");
    if (file.is_open()) {
        string line;
        getline(file, line); // Read "Pipe"
        getline(file, line);
        own_pipe.created = (line == "1");
        if (own_pipe.created) {
            getline(file, own_pipe.name);
            file >> own_pipe.length;
            file >> own_pipe.diametre;
            file >> own_pipe.repair_status;
            file.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the line
        }
        
        getline(file, line); // Read "CompressorStation"
        getline(file, line);
        own_cs.created = (line == "1");
        if (own_cs.created) {
            getline(file, own_cs.name);
            file >> own_cs.workshop;
            file >> own_cs.workshop_active;
            if (own_cs.workshop_active > own_cs.workshop) {
                cout << "Error: Number of active workshops cannot be greater than total workshops." << endl;
                own_cs.created = false;
            } else {
                file >> own_cs.effective;
                file.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the line
            }
        }

        file.close();
    } else {
        cout << "Unable to open file for loading." << endl;
    }
}

// ----------------------------------------------------FUNCTION_CONFIRN_BETWEEN_MENU-------------------------------------------------------------------

void Pause() {
    cout << "Enter to continue...";
    cin.get(); // Ждем нажатия Enter
    system("cls");
}

// ----------------------------------------------------FUNCTION_LOOP_OF_MENU-------------------------------------------------------------------

int main() {
    int choice;
    std::string input;
    Pipe own_pipe;
    Compressor_station own_cs;

    while (true) {
        cout << "1. Create a pipe" << endl;
        cout << "2. Create a CS" << endl;
        cout << "3. Viewing all objects" << endl;
        cout << "4. Edit the pipe" << endl;
        cout << "5. Edit the CS" << endl;
        cout << "6. Save" << endl;
        cout << "7. Download" << endl;
        cout << "0. Exit" << endl;
        cout << "Choice item of menu: ";

        std::getline(std::cin, input);
        if (!isValidNumber(input)) {
            system("cls");
            cout << "Please input a valid number.\n";
            continue;
        }
        choice = std::stoi(input);

        switch (choice) {
            case 1:
                system("cls");
                CreatePipe(own_pipe);
                Pause();
                break;
            case 2:
                system("cls");
                CreateCS(own_cs);
                Pause();
                break;
            case 3:
                system("cls");
                Show_Pipe_and_CS(own_pipe, own_cs);
                Pause();
                break;
            case 4:
                system("cls");
                EditPipe(own_pipe);
                Pause();
                break;
            case 5:
                system("cls");
                EditCS(own_cs);
                Pause();
                break;
            case 6:
                system("cls");
                Save(own_pipe, own_cs);
                cout << "Data saved successfully.\n";
                Pause();
                break;
            case 7:
                system("cls");
                system("cls");
                Load(own_pipe, own_cs);
                cout << "Data loaded successfully.\n";
                Pause();
                break;
            case 0:
                Save(own_pipe, own_cs);
                return 0;
            default:
                system("cls");
                std::cout << "Incorrect choice.\n";
                Pause();
        }
    }
}