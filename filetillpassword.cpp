#include <iostream>
#include <fstream>

using namespace std;




struct Question {
    string questionText;
    string options[4];
    int correctOption;
};

struct Student {
    string username;
    string password;
};
struct Teacher {
    string username;
    string password;
};




// Sample user account
Student sampleUser = { "user123", "password123" };


Student getUserInput(){
    Student newUser;
    fstream mypassword;
    mypassword.open("password.txt", ios::app); // Open the file in append mode to write into it

    if (mypassword.is_open()) {
        cout << "Please create a new user account:" << endl;
        cout << endl;

        cout << "Enter a username: ";
        
        cin >> newUser.username;
        cout << endl;

        cout << "Enter a password: ";
        cin >> newUser.password;
        cout << endl;

        // Write the new user information to the file
        mypassword << "Username: " << newUser.username << "\n";
        mypassword << "Password: " << newUser.password << "\n";
        mypassword << "\n"; // Add a newline for separation or formatting

        // Close the file after writing
        mypassword.close();
    } else {
        cout << "user not found ." << endl;
    }
    }

    



bool authenticateUser() {
    string username, password;
    cout << "Please log in to start the quiz:" << endl;
    cout << "Username: ";
    cin >> username;

    ifstream mypassword("password.txt"); // Open the file for reading

    if (mypassword.is_open()) {
        string line;
        bool userFound = false;

        while (getline(mypassword, line)) {
            if (line.find("Username: " + username) != string::npos) {
                userFound = true;
                cout << "Username found." << endl;
                cout << "Please enter the password:" << endl;
                cin >> password;

                getline(mypassword, line); // Read the password line

                if (line.find("Password: " + password) != string::npos) {
                    cout << "Authentication successful. Welcome, " << username << "!" << endl;
                    mypassword.close(); // Close the file
                    return true;
                } else {
                    cout << "Authentication failed. Incorrect password." << endl;
                    mypassword.close(); // Close the file
                    return false;
                }
            }
        }

        mypassword.close(); // Close the file

        if (!userFound) {
            cout << "Authentication failed. Username not found." << endl;
            getUserInput(); // Create a new user if the username is not found
            return authenticateUser();
        }
    } else {
        cout << "Failed to open the password file for reading." << endl;
        return false;
    }
}
Question quizQuestions[5]; 
void initializeQuestions() {
    quizQuestions[0] = { "Which operator is used to access the member functions and variables of a class in C++?", { "A. ::", "B. .", "C. ->", "D. /" }, 1 };

    quizQuestions[1] = { "What is the purpose of the 'break' statement in a loop in C++?", { "A. To exit the loop immediately", "B. To skip the next iteration of the loop", "C. To continue to the next iteration of the loop", "D.  To start the loop from the beginning" }, 1 };

    quizQuestions[2]=  {"Which C++ keyword is used to define a class?",{"A. struct","B. class","C. new","D. object"},2};

    quizQuestions[3]=  {"Which of the following is not a fundamental data type in C++?",{"A. int","B. double","C. boolean","D. string"},4};

    quizQuestions[4]=  {"In C++, what is the keyword used to declare a function that does not return any value?",{"A. void","B. int","C. double","D. none of the above"},1};
    
    // Add more questions here...
}

void takeQuiz() {
    int score = 0;
    for (int i = 0; i < 5; i++) {
        cout << "Question " << i + 1 << ": " << quizQuestions[i].questionText << endl;
        for (int j = 0; j < 4; j++) {
            cout << quizQuestions[i].options[j] << endl;
        }

        int userAnswer;
        cout << "Your answer (Enter 1, 2, 3, or 4): "<<endl;
        cin >> userAnswer;

        if (userAnswer >= 1 && userAnswer <= 4) {
            if (userAnswer == quizQuestions[i].correctOption) {
                cout << "Correct!" << endl;
                score++;
            } else {
                cout << "Incorrect. The correct answer is " << quizQuestions[i].options[quizQuestions[i].correctOption - 1] << endl;
            }
        } else {
            cout<<"PLEASE SELECT THE CORRECT OPTION NUMBER FROM 1 TO 4 CAREFULLY, AS YOU WONT BE PROVIDED ANOTHER CHANCE"<<endl;
            cout<<endl;

            bool answeredCorrectly = false;
            int attemptCount = 0;

            while (!answeredCorrectly && attemptCount < 1) {
            cout << "Your answer (Enter 1, 2, 3, or 4): ";
            cin >> userAnswer;

            if (userAnswer >= 1 && userAnswer <= 4) {
                if (userAnswer == quizQuestions[i].correctOption) {
                    cout << "Correct!" << endl;
                    score++;
                    answeredCorrectly = true;
                } else {
                    
                    if (attemptCount == 0) {
                        cout << "You have one more chance to answer this question." << endl;
                    }
                    cout << "Incorrect."<<endl;

                }
                
            } 

            attemptCount++;

            cout<<"The correct answer is " << quizQuestions[i].options[quizQuestions[i].correctOption - 1] << endl;
        }

        cout << endl;

        }
        cout << endl;
    }

    int totalQuestions = 5;
    double percentage = (static_cast<double>(score) / totalQuestions) * 100;

    cout << "Quiz completed! Your score: " << score << " out of " << totalQuestions << endl;
    cout << "Percentage score: " << percentage << "%" << endl;
    authenticateUser();
    takeQuiz();
}



Teacher teacherUser = { "teacher123", "password123" };
int totalQuestions = 0; // Total number of questions in the quiz

Teacher getTeacherInput() {
    Teacher newTeacher;
    fstream mypassword;
    mypassword.open("password.txt", ios::app); // Open the file in append mode to write into it

    if (mypassword.is_open()) {
        cout << "Please create a new teacher account:" << endl;
        cout << endl;

        cout << "Enter a username: ";
        cin >> newTeacher.username;
        cout << "Enter a password: ";
        cin >> newTeacher.password;

        // Write the new teacher information to the file
        mypassword << "Teacher Username: " << newTeacher.username << "\n";
        mypassword << "Teacher Password: " << newTeacher.password << "\n";
        mypassword << "\n"; // Add a newline for separation or formatting

        // Close the file after writing
        mypassword.close();
    } else {
        cout << "Failed to open the password file for writing." << endl;
    }

    return newTeacher;
}
void storedatainteacher(){
    Teacher newTeacher = getTeacherInput();
    teacherUser = newTeacher; // Store the input in sampleUser
    cout << "Account created successfully.  " << newTeacher.username << "!" << endl;
    cout << "Welcome, " << newTeacher.username << " ! You are logged in as a teacher." << endl;

}
bool authenticateTeacher() {
    string usernameteach, passwordteach;
    cout << "Please log in to add features :" << endl;
    cout << "Username: ";
    cin >> usernameteach;

    ifstream mypassword("password.txt"); // Open the file for reading

    if (mypassword.is_open()) {
        string line;
        bool userFound = false;

        while (getline(mypassword, line)) {
            if (line.find("Teacher Username: " + usernameteach) != string::npos) {
                userFound = true;
                cout << "Username found." << endl;
                cout << "Please enter the password:" << endl;
                cin >> passwordteach;

                getline(mypassword, line); // Read the password line

                if (line.find("Teacher Password: " + passwordteach) != string::npos) {
                    cout << "Authentication successful. Welcome, " << usernameteach << "!" << endl;
                    mypassword.close(); // Close the file
                    return true;
                } else {
                    cout << "Authentication failed. Incorrect password." << endl;
                    mypassword.close(); // Close the file
                    return false;
                }
            }
        }

        mypassword.close(); // Close the file

        if (!userFound) {
            cout << "Authentication failed. Username not found." << endl;
            getTeacherInput(); // Create a new teacher if the username is not found
            return authenticateTeacher();
        }
    } else {
        cout << "Failed to open the password file for reading." << endl;
        return false;
    }
}
void addQuestion() {
    if (totalQuestions < 100) {
        Question newQuestion;
        cout << "Enter the question: ";
        cin.ignore(); // Ignore the newline character left in the buffer
        getline(cin, newQuestion.questionText);
        cout << "Enter option A: ";
        getline(cin, newQuestion.options[0]);
        cout << "Enter option B: ";
        getline(cin, newQuestion.options[1]);
        cout << "Enter option C: ";
        getline(cin, newQuestion.options[2]);
        cout << "Enter option D: ";
        getline(cin, newQuestion.options[3]);
        cout << "Enter the correct option (1, 2, 3, or 4): ";
        cin >> newQuestion.correctOption;
        quizQuestions[totalQuestions] = newQuestion;
        totalQuestions++;
        cout << "Question added successfully!" << endl;
    } else {
        cout << "Cannot add more questions. Maximum limit reached." << endl;
    }
}

void displayQuestions() {
    cout << "Quiz Questions:" << endl;
    for (int i = 0; i < totalQuestions; i++) {
        cout << i + 1 << ". " << quizQuestions[i].questionText << endl;
        cout << "   A. " << quizQuestions[i].options[0] << endl;
        cout << "   B. " << quizQuestions[i].options[1] << endl;
        cout << "   C. " << quizQuestions[i].options[2] << endl;
        cout << "   D. " << quizQuestions[i].options[3] << endl;
        cout << "   Correct Option: " << quizQuestions[i].correctOption << endl;
    }
}

void deleteQuestion(int questionNumber) {
    if (questionNumber >= 1 && questionNumber <= totalQuestions) {
        for (int i = questionNumber - 1; i < totalQuestions - 1; i++) {
            quizQuestions[i] = quizQuestions[i + 1];
        }
        totalQuestions--;
        cout << "Question deleted successfully!" << endl;
    } else {
        cout << "Invalid question number. Deletion failed." << endl;
    }
}




void AfterExitingoingtorole(){
    int role;
    cout << "Select your role: \n1. Student\n2. Teacher" << endl;
    cin >> role;
    if (role == 1) {
        

        if (authenticateUser()) {
            cout << "You will be presented with 5 multiple-choice questions. Please select the correct answer." << endl;
            cout << "Let's get started!" << endl;
            takeQuiz();
        } else {
            cout << "Authentication failed. Exiting the program." << endl;
        }
    } else if (role == 2) {
        

        if (authenticateTeacher()) {
            cout << "Welcome, " << teacherUser.username << "! You are logged in as a teacher." << endl;
            cout << "Let's get started!" << endl;
            int choice;
            do {
                cout << "Teacher Menu:\n1. Add Question\n2. Display Questions\n3. Delete Question\n4. Exit" << endl;
                cin >> choice;
                switch (choice) {
                    case 1:
                        addQuestion();
                        break;
                    case 2:
                        displayQuestions();
                        break;
                    case 3: {
                        int questionNumber;
                        cout << "Enter the question number to delete: ";
                        cin >> questionNumber;
                        deleteQuestion(questionNumber);
                        break;
                    }
                    case 4:
                        cout << "Exiting teacher menu." << endl;
                        break;
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                }
            } while (choice != 4);
        } else {
            cout << "Authentication failed. Exiting program." << endl;
        }
    } else {
        cout << "Invalid role selection. Exiting program." << endl;
    }
}

int main() {
    initializeQuestions();
    

    cout << "\n\n\t\t***********************************" << endl;
    cout << "\t\t  Welcome to the Quiz Management System" << endl;
    cout << "\t\t***************************************" << endl;

    int role;
    cout << "Select your role: \n1. Student\n2. Teacher" << endl;
    cin >> role;

    if (role == 1) {
        

        if (authenticateUser()) {
            cout << "You will be presented with 5 multiple-choice questions. Please select the correct answer." << endl;
            cout << "Let's get started!" << endl;
            takeQuiz();
        } else {
            cout << "Authentication failed. Exiting the program." << endl;
        }
    } else if (role == 2) {
        

        if (authenticateTeacher()) {
            cout << "Welcome, " << teacherUser.username << "! You are logged in as a teacher." << endl;
            cout << "Let's get started!" << endl;
            int choice;
            do {
                cout << "Teacher Menu:\n1. Add Question\n2. Display Questions\n3. Delete Question\n4. Exit" << endl;
                cin >> choice;
                switch (choice) {
                    case 1:
                        addQuestion();
                        break;
                    case 2:
                        displayQuestions();
                        break;
                    case 3: {
                        int questionNumber;
                        cout << "Enter the question number to delete: ";
                        cin >> questionNumber;
                        deleteQuestion(questionNumber);
                        break;
                    }
                    case 4:
                        cout << "Exiting teacher menu." << endl;
                        AfterExitingoingtorole();
                        break;
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                }
            } while (choice != 4);
        } else {
            cout << "Authentication failed. Exiting program." << endl;
        }
    } else {
        cout << "Invalid role selection. Exiting program." << endl;
    }

    return 0;
}
