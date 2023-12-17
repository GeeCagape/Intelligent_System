#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <set>
#include <cctype>

using namespace std;

void mainMenu();
void addColor();
void displayColors();
void blendColor();
void generateColor();
void colorSheet();
void addColorToFile(const string& filename, const string& data);
void addCombiToFile(const string& filename, const string& color1, const string& color2, const string& color3);
void addColorsFromCombi (const string& filename, const string& color1, const string& color2, const string& color3);
bool colorChecker(const string& searchString);


struct ColorAttrib
{   string color1, color2;
    string result;
};

vector<ColorAttrib> colorCombo; // serves as dynamic array container
set<string> uniqueColors; // store only unique values

void addColorToFile(const string& filename, const string& data) {
    ofstream outputFile(filename, ios::app);
    if (!outputFile.is_open()) {
        cerr << "Could not open the file for writing." << endl;
        return;
    }

    outputFile << data << endl;
    outputFile.close();

    cout << "\nNew Color added to Color Sheet." << endl;
}

void addCombiToFile(const string& filename, const string& color1, const string& color2, const string& color3) {
    ofstream outputFile(filename, ios::app);
    if (!outputFile.is_open()) {
        cerr << "Could not open the file for writing." << endl;
        return;
    }

    outputFile << color1 << " + " << color2 << " = "<< color3 << endl;
    outputFile.close();

    cout << "\nCool!" << endl;

    addColorsFromCombi("colorSheet.txt",color1,color2,color3);
}

void addColorsFromCombi(const string& filename, const string& color1, const string& color2, const string& color3)
{
    ofstream outputFile(filename, ios::app);
    if (!outputFile.is_open()) {
        cerr << "Could not open the file for writing." << endl;
        return;
    }

    outputFile << color1 << "," << color2 << ","<< color3 << endl;
    outputFile.close();
}

void mainMenu()
{
    system("cls");
    cout << "===============================================\n";
    cout << "          COLOR BLEND WIZARD                   \n";
    cout << "===============================================\n";
    cout << "         [A] Add Color                         \n";
    cout << "         [B] New Blend                         \n";
    cout << "         [C] Generate Blend                    \n";
    cout << "         [1] Press 1 to Exit                   \n";
    cout << "===============================================\n";

    char letChoice;

    cout << "wizard: Choose a letter\nYou:";
    cin >> letChoice;

    if (letChoice == 'A' || letChoice == 'a'){
        addColor();
    }

    else if (letChoice == 'B' || letChoice == 'b'){
        blendColor();
    }
    else if (letChoice == 'C' || letChoice == 'c'){
        generateColor();
    }

    else system("exit");
}



void displayColors()
{
      // Read the data from file
    ifstream file("existingColors.txt");

    // Check if the file is open
    if (!file.is_open()) {
        // will display if there's an error when displaying the file
        cerr << "Error opening file." << endl;
    }

    string line;
    while (getline(file, line)) {
        cout << line << endl;
        uniqueColors.insert(line);
    }

    // Close the open file
    file.close();

}

void displayRules()
{
      // Read the data from file
    ifstream file("existingCombinations.txt");

    // Check if the file is open
    if (!file.is_open()) {
        // will display if there's an error when displaying the file
        cerr << "Error opening file." << endl;
    }

    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }

    // Close the open file
    file.close();

}

void addColor()
{
    // Clear the console
    system("cls");

    // Display ui
    cout << "======================================\n";
    cout << "*          COLOR BLEND WIZARD        *\n";
    cout << "======================================\n";
    cout << "*            NEW COLORS              *\n";
    cout << "======================================\n";

    //string color1,color2,result;

    // Function call to display the list of unique color names
    displayColors();

    cout << "\n\n         [1] Press 1 to Exit                   \n";
    cout << "\n======================================\n";
    string userInput;
    string letChoice;
    cout << "\nAdd new color: ";
    //getline(cin, userInput);
    cin >> userInput;

    if(userInput == "1"){
        mainMenu();
    }

    if(colorChecker(userInput)){
        cout << "\nwizard: Color already exist!\n";
    }else{
        addColorToFile("existingColors.txt", userInput);
    }

    cout << "\nwizard: Do you want to add more colors?[Y/N]\nYou:";
    cin >> letChoice;

    if (letChoice == "y" || letChoice == "Y"){
        addColor();
    }
    else mainMenu();


}

void blendColor()
{
    // Clear the console
    system("cls");

    // Display ui
    cout << "======================================\n";
    cout << "*          COLOR BLEND WIZARD        *\n";
    cout << "======================================\n";
    cout << "*            BLEND COLORS            *\n";
    cout << "======================================\n";

    string color1,color2,color3;
    string letChoice;

    // Function call to display the list of unique color names
    displayRules();
    cout << "\n\n         [1] Press 1 to Exit                   \n";
    cout << "\n======================================\n";
    cout << "\nAdd new color blend:\n";

    // Ask for first color for blending
    cout << endl << "Color 1: ";
    cin >> color1;

    if(color1 == "1"){
        mainMenu();
    } else {
        // Ask for second color for blending
        cout << "Color 2: ";
        cin >> color2;

        if(color2 == "1"){
            mainMenu();
        } else {
            // Ask for resulting color
            cout << "Makes: ";
            cin >> color3;
            if(color3 == "1"){
                mainMenu();

            } else {
                addCombiToFile("existingCombinations.txt", color1, color2, color3);
                cout << "\nwizard: Add another color blend?[Y/N]\nYou:";
                cin >> letChoice;
                if (letChoice == "y" || letChoice == "Y"){
                    blendColor();
                }
                else mainMenu();
            }
        }
    }
}

bool colorChecker(const string& searchString) {
    string filename = "existingColors.txt";
    ifstream file(filename);
    string line;


    if (!file.is_open()) {
        cerr << "Could not open the file." << endl;
        return false;
    }

    while (getline(file, line)) {
        if (line.find(searchString) != string::npos) {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

void colorSheet()
{
   // Read the data from file
    ifstream file("colorSheet.txt");

    // Check if the file is open
    if (!file.is_open()) {
        // will display if there's an error when displaying the file
        cerr << "Error opening file." << endl;
    }

    // Read each line in the file
    string line;
    while (getline(file, line))
    {
        // Initiallize color object
        ColorAttrib color;

        // Find the first comma in the line, serving as a delimiter
        // This serves as the first color in the combination
        size_t pos = line.find(',');

        // If no comma is found - will display erorr and will continue
        if (pos == string::npos)
        {
            cerr<<"Error"<<endl;
            continue;
        }

        // Get the substring in the line from the beginning until the index of the first comma found
        // Store the first substring in the color1 attribute
        color.color1 = line.substr(0, pos);

        // Erase the substring in the line including the comma
        line.erase(0, pos + 1);

        // // Find the second comma in the line
        // This serves as the second color in the combination
        pos = line.find(',');

        // If no comma found will display erorr and will continue
        if (pos == string::npos){
            cerr<<"Error"<<endl;
            continue;
        }

        // Get the substring in the line from the beginning until the index of the second comma found
        // Store the second substring in the color2 attribute
        color.color2 = line.substr(0, pos);

        // Erase the substring in the line including the comma
        line.erase(0, pos + 1);

        // The remaining substring will serve as the result attribute
        color.result = line;

        // Inserts the object into the vector
        colorCombo.push_back(color);
    }

    // Close the open file
    file.close();

}

void generateColor()
{
    // Clear the console
    system("cls");

    // Display ui
    cout << "======================================\n";
    cout << "*          COLOR BLEND WIZARD        *\n";
    cout << "======================================\n";
    cout << "*            Try and Combine         *\n";
    cout << "*                                    *\n";
    cout << "*     Combine any two (2) colors     *\n";
    cout << "*         and see its blend          *\n";
    cout << "======================================\n";

    string color1,color2,color3;



    // Ask for first color for blending
    cout << endl << "First Color: ";
    cin >> color1;

    // Ask for second color for blending
    cout << "Second Color: ";
    cin >> color2;


    colorSheet();
    bool combinationFound = false; // Flag to track if a matching combination is found

    if (colorChecker(color1) && colorChecker(color2))
    {
        // Find the combination in the vector and display the result
        // It loops through each element of the vector
        for (int i = 0; i < colorCombo.size(); i++)
        {
            // Compare the inputted colors to the attributes of the elements in the vector
            if ((colorCombo[i].color1 == color1 || colorCombo[i].color1 == color2) &&
                (colorCombo[i].color2 == color1 || colorCombo[i].color2 == color2))
            {
                // If it matches, it will display the resulting color and set the flag to true
                cout << "Makes: " << colorCombo[i].result << endl;
                cout << "\nwizard: That's nice!\n";
                combinationFound = true;
                break;
            }
        }
    }

    string input;
    // Check if a matching combination was not found
    if (!combinationFound)
    {
        cout << "\nwizard: I do not know the combination yet. Create that New Blend?[Y/N]\nYou:";
        cin >> input;

        if(input == "Y" || input == "y")
        {
            // Call the function blendColors to reset and blend colors again
            blendColor();
        }
    }

    // Ask the users if they want to blend colors again
    do{
        cout << "\nwizard: Would you like to try again?[Y/N]\nYou: ";
        cin >> input;

        // Checks the input of the user whether y or n
        if(input == "Y" || input == "y")
        {
            // Call the function generateColors to reset and blend colors again
            generateColor(); break;
        }
        else if (input == "N" || input == "n")
        {
            // Stops asking to blend again
            mainMenu(); break;
        }
        else cout << "wizard: I'm afraid those are not the choices.";

    } while (input != "Y" || input != "y"||input != "N" || input != "n");
}



int main() {

    //blendColors();
    mainMenu();

    return 0;
}
