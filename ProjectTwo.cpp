#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// ============================================================================
// Structure Definitions
// ============================================================================

// Structure to hold course information
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

// Internal structure for Binary Search Tree node
struct Node {
    Course course;
    Node* left;
    Node* right;

    // Constructor
    Node(Course aCourse) {
        course = aCourse;
        left = nullptr;
        right = nullptr;
    }
};

// ============================================================================
// Class Definition for Binary Search Tree
// ============================================================================

class BinarySearchTree {

private:
    Node* root;
    void destrHelper(Node* node);
    void inOrderHelper(Node* node);
    Node* insertHelper(Node* node, Course course);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void Insert(Course course);
    Course Search(string courseNumber);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}

/**
 * Destructor helper to delete nodes recursively
 */
void BinarySearchTree::destrHelper(Node* node) {
    if (node != nullptr) {
        destrHelper(node->left);
        destrHelper(node->right);
        delete node;
    }
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    destrHelper(root);
}

/**
 * Public InOrder traversal to print sorted list
 */
void BinarySearchTree::InOrder() {
    this->inOrderHelper(root);
}

/**
 * Private InOrder helper to recursively traverse and print
 */
void BinarySearchTree::inOrderHelper(Node* node) {
    if (node != nullptr) {
        inOrderHelper(node->left);

        // Matches format: CSCI100, Introduction to Computer Science
        cout << node->course.courseNumber << ", " << node->course.courseTitle << endl;

        inOrderHelper(node->right);
    }
}

/**
 * Public Insert function
 */
void BinarySearchTree::Insert(Course course) {
    if (root == nullptr) {
        root = new Node(course);
    }
    else {
        this->insertHelper(root, course);
    }
}

/**
 * Private Insert helper to place node alphabetically by courseNumber
 */
Node* BinarySearchTree::insertHelper(Node* node, Course course) {
    if (node == nullptr) {
        return new Node(course);
    }

    if (course.courseNumber.compare(node->course.courseNumber) < 0) {
        node->left = insertHelper(node->left, course);
    }
    else {
        node->right = insertHelper(node->right, course);
    }

    return node;
}

/**
 * Search for a specific course
 */
Course BinarySearchTree::Search(string courseNumber) {
    Node* current = root;

    while (current != nullptr) {
        if (current->course.courseNumber.compare(courseNumber) == 0) {
            return current->course;
        }
        if (courseNumber.compare(current->course.courseNumber) < 0) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }

    // Return empty course if not found
    Course emptyCourse;
    return emptyCourse;
}

// ============================================================================
// Helper Functions for Data Parsing & Validation
// ============================================================================

/**
 * Split a string by a delimiter
 */
vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        if (!token.empty() && token.back() == '\r') {
            token.pop_back();
        }
        tokens.push_back(token);
    }
    return tokens;
}

/**
 * Load courses from file and populate the BST
 */
bool loadCourses(string filename, BinarySearchTree* bst) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open file " << filename << endl;
        return false;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        vector<string> tokens = split(line, ',');

        if (tokens.size() < 2) {
            continue; // Skip malformed lines missing basic elements
        }

        Course course;
        course.courseNumber = tokens[0];
        course.courseTitle = tokens[1];

        for (size_t i = 2; i < tokens.size(); ++i) {
            if (!tokens[i].empty()) {
                course.prerequisites.push_back(tokens[i]);
            }
        }

        bst->Insert(course);
    }

    file.close();
    return true;
}

/**
 * Convert string to uppercase to ensure case-insensitive lookups
 */
string toUpperCase(string str) {
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

/**
 * Prints the core menu to clear clutter from main loop
 */
void displayMenu() {
    cout << "1. Load Data Structure." << endl;
    cout << "2. Print Course List." << endl;
    cout << "3. Print Course." << endl;
    cout << "9. Exit" << endl;
    cout << "What would you like to do? ";
}

// ============================================================================
// Main Interactive Application
// ============================================================================

int main() {
    BinarySearchTree* bst = new BinarySearchTree();
    // Default file name can be configured or prompted
    string filename = "ABCU_Advising_Program_Input.csv";
    string searchCourseNum = "";
    bool dataLoaded = false;
    int choice = 0;

    cout << "Welcome to the course planner." << endl;

    while (choice != 9) {
        displayMenu();

        // Ensure invalid characters don't break the scanner
        if (!(cin >> choice)) {
            cout << "Invalid selection." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            cout << endl;
            continue;
        }

        switch (choice) {
        case 1:
            // Guidelines indicate prompting for file name is required
            cout << "Enter the file name containing the course data: ";
            cin >> filename;
            dataLoaded = loadCourses(filename, bst);
            break;

        case 2:
            // Prompt states option 1 must run first, but sample execution 
            // shows it running seamlessly. We handle execution here.
            if (!dataLoaded) {
                // Fallback to load default file if user jumped straight to 2
                dataLoaded = loadCourses("ABCU_Advising_Program_Input.csv", bst);
            }
            cout << "Here is a sample schedule:" << endl;
            bst->InOrder();
            break;

        case 3:
            cout << "What course do you want to know about? ";
            cin >> searchCourseNum;

            searchCourseNum = toUpperCase(searchCourseNum);
            {
                Course foundCourse = bst->Search(searchCourseNum);

                if (!foundCourse.courseNumber.empty()) {
                    cout << foundCourse.courseNumber << ", " << foundCourse.courseTitle << endl;
                    cout << "Prerequisites: ";
                    if (foundCourse.prerequisites.empty()) {
                        cout << "None" << endl;
                    }
                    else {
                        for (size_t i = 0; i < foundCourse.prerequisites.size(); ++i) {
                            cout << foundCourse.prerequisites[i];
                            if (i < foundCourse.prerequisites.size() - 1) {
                                cout << ", ";
                            }
                        }
                        cout << endl;
                    }
                }
                else {
                    cout << "Course " << searchCourseNum << " not found." << endl;
                }
            }
            break;

        case 9:
            cout << "Thank you for using the course planner!" << endl;
            break;

        default:
            cout << choice << " is not a valid option." << endl;
            break;
        }
    }

    delete bst;
    return 0;
}