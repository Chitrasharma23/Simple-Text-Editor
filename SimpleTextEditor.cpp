#include <iostream> // it allow you to perform input and output operations on various devices 
#include <fstream> //file stream used for both reading from and writing to files
#include <string> //to include the strings
#include <vector> //it is used to store elements of the same type in a contiguous memory block
#include <sstream> // For stringstream
#include <algorithm> // For remove_if

using namespace std; //avoid naming conflicts

class SimpleTextEditor {   // class name
public:
    void createFile(const string& filename) {
        ofstream file(filename);
        if (file.is_open()) {
            cout << "New file created: " << filename << endl;
            file.close();
        } else {
            cout << "Error creating file." << endl;
        }
    }

    void writeFile(const string& filename) {
        ofstream file(filename, ios::out | ios::trunc);
        if (file.is_open()) {
            cout << "Enter text (type 'exit' to save and close the file):" << endl;
            string line;
            while (getline(cin, line)) {
                if (line == "exit") break;
                file << line << endl;
            }
            file.close();
        } else {
            cout << "Error opening file." << endl;
        }
    }

    void appendFile(const string& filename) {
        ofstream file(filename, ios::out | ios::app);
        if (file.is_open()) {
            cout << "Enter text to append (type 'exit' to save and close the file):" << endl;
            string line;
            while (getline(cin, line)) {
                if (line == "exit") break;
                file << line << endl;
            }
            file.close();
        } else {
            cout << "Error opening file." << endl;
        }
    }

    void readFile(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                cout << line << endl;
            }
            file.close();
        } else {
            cout << "Error opening file." << endl;
        }
    }

    void deleteFile(const string& filename) {
        if (remove(filename.c_str()) == 0) {
            cout << "File deleted successfully." << endl;
        } else {
            cout << "Error deleting file." << endl;
        }
    }

    void insertInFile(const string& filename, int lineNumber, const string& text) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error opening file." << endl;
            return;
        }

        vector<string> lines;
        string line;
        while (getline(file, line)) {
            lines.push_back(line);
        }
        file.close();

        if (lineNumber < 0 || lineNumber > lines.size()) {
            cout << "Invalid line number." << endl;
            return;
        }

        lines.insert(lines.begin() + lineNumber, text);

        ofstream outFile(filename);
        if (!outFile.is_open()) {
            cout << "Error opening file." << endl;
            return;
        }

        for (const string& l : lines) {
            outFile << l << endl;
        }
        outFile.close();
    }

    void editLine(const string& filename, int lineNumber, const string& newText) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error opening file." << endl;
            return;
        }

        vector<string> lines;
        string line;
        while (getline(file, line)) {
            lines.push_back(line);
        }
        file.close();

        if (lineNumber < 0 || lineNumber >= lines.size()) {
            cout << "Invalid line number." << endl;
            return;
        }

        lines[lineNumber] = newText;

        ofstream outFile(filename);
        if (!outFile.is_open()) {
            cout << "Error opening file." << endl;
            return;
        }

        for (const string& l : lines) {
            outFile << l << endl;
        }
        outFile.close();
    }

    void deleteLine(const string& filename, int lineNumber) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error opening file." << endl;
            return;
        }

        vector<string> lines;
        string line;
        while (getline(file, line)) {
            lines.push_back(line);
        }
        file.close();

        if (lineNumber < 0 || lineNumber >= lines.size()) {
            cout << "Invalid line number." << endl;
            return;
        }

        lines.erase(lines.begin() + lineNumber);

        ofstream outFile(filename);
        if (!outFile.is_open()) {
            cout << "Error opening file." << endl;
            return;
        }

        for (const string& l : lines) {
            outFile << l << endl;
        }
        outFile.close();
    }

    void replaceWord(const string& filename, const string& oldWord, const string& newWord) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error opening file." << endl;
            return;
        }

        stringstream buffer;
        buffer << file.rdbuf(); // Read the entire file into a stringstream
        string fileContents = buffer.str();

        // Replace all occurrences of oldWord with newWord
        size_t pos = fileContents.find(oldWord);
        while (pos != string::npos) {
            fileContents.replace(pos, oldWord.length(), newWord);
            pos = fileContents.find(oldWord, pos + newWord.length());
        }

        file.close();

        ofstream outFile(filename);
        if (!outFile.is_open()) {
            cout << "Error opening file." << endl;
            return;
        }

        outFile << fileContents;
        outFile.close();
    }
};

int main() {
    SimpleTextEditor editor;
    int choice;
    string filename;
    string text; // Moved text variable here
    string oldWord; // Moved oldWord variable here
    string newWord; // Moved newWord variable here

    while (true) {
        cout << "\nSimple Text Editor\n";
        cout << "1. Create new file\n";
        cout << "2. Write to file\n";
        cout << "3. Append to file\n";
        cout << "4. Read file\n";
        cout << "5. Delete file\n";
        cout << "6. Insert text in the middle of file\n";
        cout << "7. Edit a line\n";
        cout << "8. Delete a line\n";
        cout << "9. Replace a word\n";
        cout << "10. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // to ignore the newline character left in the buffer

        switch (choice) {
            case 1:
                cout << "Enter filename: ";
                getline(cin, filename);
                editor.createFile(filename);
                break;
            case 2:
                cout << "Enter filename: ";
                getline(cin, filename);
                editor.writeFile(filename);
                break;
            case 3:
                cout << "Enter filename: ";
                getline(cin, filename);
                editor.appendFile(filename);
                break;
            case 4:
                cout << "Enter filename: ";
                getline(cin, filename);
                editor.readFile(filename);
                break;
            case 5:
                cout << "Enter filename: ";
                getline(cin, filename);
                editor.deleteFile(filename);
                break;
            case 6:
                cout << "Enter filename: ";
                getline(cin, filename);
                int lineNumber;
                cout << "Enter line number to insert text at: ";
                cin >> lineNumber;
                cin.ignore(); // to ignore the newline character left in the buffer
                cout << "Enter text to insert: ";
                getline(cin, text); // Initialize text inside case 6
                editor.insertInFile(filename, lineNumber, text);
                break;
            case 7:
                cout << "Enter filename: ";
                getline(cin, filename);
                int editLineNum;
                cout << "Enter line number to edit: ";
                cin >> editLineNum;
                cin.ignore(); // to ignore the newline character left in the buffer
                cout << "Enter new text: ";
                getline(cin, text); // Initialize text inside case 7
                editor.editLine(filename, editLineNum, text);
                break;
            case 8:
                cout << "Enter filename: ";
                getline(cin, filename);
                int deleteLineNum;
                cout << "Enter line number to delete: ";
                cin >> deleteLineNum;
                cin.ignore(); // to ignore the newline character left in the buffer
                editor.deleteLine(filename, deleteLineNum);
                break;
            case 9:
                cout << "Enter filename: ";
                getline(cin, filename);
                cout << "Enter word to replace: ";
                getline(cin, oldWord); // Initialize oldWord inside case 9
                cout << "Enter new word: ";
                getline(cin, newWord); // Initialize newWord inside case 9
                editor.replaceWord(filename, oldWord, newWord);
                break;
            case 10:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
