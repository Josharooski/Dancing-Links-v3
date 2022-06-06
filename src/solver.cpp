#include "DLX_Node.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random> // for RNG matrices
#include <memory> // for smart pointers
#include <cctype> // for input reading


void readFile();
void buildNetwork();
void buildVector();
void connectHeaderList(int& index);
void connectNodeList(int index);
void insertSpacerNode(std::shared_ptr<DLX_Node> newSpacer, int index);
void insertNode(std::shared_ptr<DLX_Node> newNode, int index);
void cover(std::shared_ptr<DLX_Node> coverMe);
void uncover(std::shared_ptr<DLX_Node> uncoverMe);
void hide(std::shared_ptr<DLX_Node> hideMe);
void unhide(std::shared_ptr<DLX_Node> unhideMe);
void searchMain();
void search(int& level, bool& complete, std::vector<std::shared_ptr<DLX_Node>>& solution, std::shared_ptr<DLX_Node>& currentItem);
void searchRecur(int& level, bool& complete, std::vector<std::shared_ptr<DLX_Node>>& solution, std::shared_ptr<DLX_Node>& currentItem);
void searchSub(int& level, bool& complete, std::vector<std::shared_ptr<DLX_Node>>& solution, std::shared_ptr<DLX_Node>& currentItem);
void printSolution(std::vector<std::shared_ptr<DLX_Node>>& solution);
void coverSubItems(std::shared_ptr<DLX_Node> item);
void uncoverSubItems(std::shared_ptr<DLX_Node> item);
int lowestNumNodes();
bool inputHandler();
void displayHelp();

// Testing
void TEST_PrintNetworkVector();
void TEST_VerticalItemTraversal();
void TEST_HeadListHorizontalTraversal();
void TEST_PrintFileContents();
void TEST_PointersPrintout();
void TEST_PrintInputAsGraph();

// Testing - External Output
void outputPointers();
void outputGraph();

// Globals
std::vector<char> inputVec;
std::vector<std::shared_ptr<DLX_Node>> networkVec;
std::vector<std::shared_ptr<DLX_Node>> optionsVec;
std::shared_ptr<DLX_Node> headPtr = std::make_shared<DLX_Node>();
int numFiles = 0;
int numHeaders = 0;



int main() {
    headPtr->setRight(headPtr);
    headPtr->setName('H');
    readFile();
    // if(!inputHandler()) {
    //     exit(0);
    // }
    buildNetwork();
    std::cout << "File 0 - initial network";
    outputPointers();
    ++numFiles;
    searchMain();
    ++numFiles;
    std::cout << "File " << numFiles << " - on exit";
}



/**
 * @brief Opens file that holds the items and options
 * 
 * @pre The file path needs to hold the file. The program will exit otherwise
 * @post GLOBAL inputVec is filled with the exact cover problem
 */
void readFile() {
    std::ifstream XCfile;
    XCfile.open("C:/Users/jgils/git-repos/Dancing-Links-v3/TestCases/test-file2.txt");

    if(!XCfile.is_open()) {
        std::cout << "File opening failed.";
        exit(1);
    }

    while(!XCfile.eof()) {
        if(XCfile.peek() == '#' || XCfile.peek() == '\n') {
            XCfile.ignore(256, '\n');
        }
        else {
            std::string currentLine;
            while(std::getline(XCfile, currentLine, '\n')) {
                if(currentLine.size() > 0) {
                    for(int size = 0; size < currentLine.length(); size++) {
                        inputVec.push_back(currentLine[size]);
                    }
                    inputVec.push_back(' ');
                }
            }
        }
    }
    XCfile.close();
    //TEST_PrintFileContents();
}



/**
 * @brief 
 * 
 */
void buildNetwork() {
    int travelIndex = 0;
    buildVector();
    connectHeaderList(travelIndex);
    //TEST_HeadListHorizontalTraversal();
    connectNodeList(travelIndex);
    //std::cout << "\n\n";
    //TEST_VerticalItemTraversal();
}



void buildVector() {
    networkVec.push_back(headPtr);
    std::vector<char>::iterator iter = inputVec.begin();
    int count = 1;
    std::shared_ptr<DLX_Node> addMe;
    while(iter != inputVec.end()) {
        addMe = std::make_shared<DLX_Node>(*iter);
        addMe->setIndex(count);
        networkVec.push_back(addMe);
        ++iter;
        ++count;
    }
}



void connectHeaderList(int& index) {
    while(networkVec[index]->getName() != ' ') {
        ++numHeaders;
        networkVec[index]->setRight(networkVec[index + 1]);

        if(index != 0) {
            networkVec[index]->setLeft(networkVec[index - 1]);
        }

        networkVec[index]->setHeader(networkVec[index]);
        networkVec[index]->setUp(networkVec[index]);
        networkVec[index]->setDown(networkVec[index]);
        ++index;
    }
    networkVec[index - 1]->setRight(headPtr);
    headPtr->setLeft(networkVec[index - 1]);
}



void connectNodeList(int index) {
    while(index != networkVec.size()) {
        if(networkVec[index]->getName() == ' ') {
            insertSpacerNode(networkVec[index], index);
        }
        else {
            insertNode(networkVec[index], index);
        }
        ++index;
    }
}



void insertSpacerNode(std::shared_ptr<DLX_Node> newSpacer, int index) {
    int tempSearch = index + 1;
    if(tempSearch < networkVec.size()) {
        while(networkVec[tempSearch]->getName() != ' ') {
            ++tempSearch;
        }
        newSpacer->setDown(networkVec[tempSearch - 1]);
    }
    else {
        newSpacer->setDown(nullptr);
    }

    if(networkVec[index - 1]->getRight() != nullptr) {
        networkVec[index]->setUp(nullptr);
    }
    else {
        tempSearch = index - 1;
        while(networkVec[tempSearch]->getName() != ' ') {
            --tempSearch;
        }
        networkVec[index]->setUp(networkVec[tempSearch + 1]);
        optionsVec.push_back(networkVec[index]->getUp());
    }
}



void insertNode(std::shared_ptr<DLX_Node> newNode, int index) {
    std::shared_ptr<DLX_Node> runner = headPtr->getRight();

    while(runner->getName() != networkVec[index]->getName()) {
        runner = runner->getRight();
    }
    
    while(runner->getDown() != runner->getHeader()) {
        runner = runner->getDown();
    }

    newNode->setUp(runner);
    runner->setDown(newNode);
    newNode->setDown(runner->getHeader());
    newNode->setHeader(runner->getHeader());
    runner->getHeader()->setUp(newNode);
    runner->getHeader()->numNodesAdd();
    if(runner->getHeader()->getDown() == runner->getHeader()) {
        runner->getHeader()->setDown(newNode);
    }
}



void searchMain() {
    std::vector<std::shared_ptr<DLX_Node>> solution(numHeaders);
    std::shared_ptr<DLX_Node> currentItem;
    int level = 0;
    bool searchComplete = false;

    currentItem = networkVec[lowestNumNodes()];
    solution[level] = currentItem->getDown();
    
    search(level, searchComplete, solution, currentItem);
}



void search(int& level, bool& complete, std::vector<std::shared_ptr<DLX_Node>>& solution, std::shared_ptr<DLX_Node>& currentItem) {

    searchRecur(level, complete, solution, currentItem);
    //X8
    while(level != 0) {
        level -= 1;
        //X6
        uncoverSubItems(solution[level]);
        if(!complete) {
            currentItem = solution[level]->getHeader();
            solution[level] = solution[level]->getDown();
            
            searchSub(level, complete, solution, currentItem);
        }
    }
    printSolution(solution);
}



void searchRecur(int& level, bool& complete, std::vector<std::shared_ptr<DLX_Node>>& solution, std::shared_ptr<DLX_Node>& currentItem) {
    //X2
    if(headPtr->getRight() != headPtr) {
        //X3
        currentItem = networkVec[lowestNumNodes()];
        //X4
        cover(currentItem);
        solution[level] = currentItem->getDown();
        //X5&X7
        searchSub(level, complete, solution, currentItem);
    }
    else {
        complete = true;
    }
}



void searchSub(int& level, bool& complete, std::vector<std::shared_ptr<DLX_Node>>& solution, std::shared_ptr<DLX_Node>& currentItem) {
    if(solution[level] != currentItem) {
        coverSubItems(solution[level]);
        level += 1;
        searchRecur(level, complete, solution, currentItem);
    }
    else {
        uncover(currentItem);
    }
}



void printSolution(std::vector<std::shared_ptr<DLX_Node>>& solution) {
    TEST_PrintInputAsGraph();
    std::cout << '\n';

    std::cout << "Solution:" << '\n';
    std::shared_ptr<DLX_Node> printMe;
    for(int i = 0; i < numHeaders; ++i) {
        if(solution[i] != nullptr) {
            if(networkVec[solution[i]->getIndex() - 1]->getName() != ' ') {
                printMe = solution[i];
                while(printMe->getName() != ' ') {
                    printMe = networkVec[printMe->getIndex() + 1];
                }
                printMe = printMe->getUp();
            }
            else {
                printMe = solution[i];
            }
            int optionNum = 0;
            int itemNum = 0;
            while(itemNum != printMe->getIndex()) {
                ++itemNum;
                if(networkVec[itemNum]->getName() == ' ') {
                    ++optionNum;
                }
            }
            std::cout << "Option " << optionNum << ": ";

            while(printMe->getHeader() != nullptr) {
                std::cout << printMe->getName() << ' ';
                printMe = networkVec[printMe->getIndex() + 1];
            }
            std::cout << '\n';
        }
        else {
            i = numHeaders;
        }
    }
}



void cover(std::shared_ptr<DLX_Node> coverMe) {
    std::shared_ptr<DLX_Node> checker = coverMe->getDown();

    while(checker != coverMe) {
        hide(checker);
        checker = checker->getDown();
    }

    coverMe->getRight()->setLeft(coverMe->getLeft());
    coverMe->getLeft()->setRight(coverMe->getRight());

    // *TEST*
    // std::cout << "File " << numFiles << " is covering ";
    // std::cout << checker->getName() << '\n';
    // outputPointers();
    // ++numFiles;
}



void hide(std::shared_ptr<DLX_Node> hideMe) {
    int currentIndex = hideMe->getIndex() + 1;
    std::shared_ptr<DLX_Node> checker = networkVec[currentIndex];

    while(checker != hideMe) {
        if(checker->getHeader() == nullptr) {
            checker = checker->getUp();
            currentIndex = checker->getIndex();
        }
        else {
            checker->getDown()->setUp(checker->getUp());
            checker->getUp()->setDown(checker->getDown());
            checker->getHeader()->numNodesSub();
            ++currentIndex;
            checker = networkVec[currentIndex];
        }
    }
}



void coverSubItems(std::shared_ptr<DLX_Node> item) {
    std::shared_ptr<DLX_Node> checker = networkVec[item->getIndex() + 1];

    while(checker != item) {
        if(checker->getHeader() == nullptr) {
            checker = checker->getUp();
        }
        else{
            cover(checker->getHeader());
            checker = networkVec[checker->getIndex() + 1];
        }
    }

    // *TEST*
    // std::cout << "File " << numFiles << " is covering (sub) ";
    // std::cout << checker->getHeader()->getName() << '\n';
    // outputPointers();
    // ++numFiles;
}



void uncover(std::shared_ptr<DLX_Node> uncoverMe) {
    uncoverMe->getLeft()->setRight(uncoverMe);
    uncoverMe->getRight()->setLeft(uncoverMe);

    std::shared_ptr<DLX_Node> runner = uncoverMe->getUp();

    while(runner != uncoverMe) {
        unhide(runner);
        runner = runner->getUp();
    }

    // *TEST*
    // std::cout << "File " << numFiles << " is uncovering ";
    // std::cout << runner->getName() << '\n';
    // outputPointers();
    // ++numFiles;
}



void unhide(std::shared_ptr<DLX_Node> unhideMe) {
    int currentIndex = unhideMe->getIndex() - 1;
    std::shared_ptr<DLX_Node> runner = networkVec[currentIndex];

    while(runner != unhideMe) {
        if(runner->getHeader() == nullptr) {
            runner = runner->getDown();
            currentIndex = runner->getIndex();
        }
        else {
            runner->getUp()->setDown(runner);
            runner->getDown()->setUp(runner);
            runner->getHeader()->numNodesAdd();
            --currentIndex;
            runner = networkVec[currentIndex];
        }
    }
}



void uncoverSubItems(std::shared_ptr<DLX_Node> item) {
    if(item != nullptr) {
        std::shared_ptr<DLX_Node> checker = networkVec[item->getIndex() - 1];

        while(checker != item) {
            if(checker->getHeader() == nullptr) {
                checker = checker->getDown();
            }
            else {
                uncover(checker->getHeader());
                checker = networkVec[checker->getIndex() - 1];
            }
        }
        // *TEST*
        // std::cout << "File " << numFiles << " is uncovering (sub) ";
        // std::cout << checker->getHeader()->getName() << '\n';
        // outputPointers();
        // ++numFiles;
    }
}



int lowestNumNodes() {
    std::shared_ptr<DLX_Node> checker = headPtr->getRight();
    while(checker->getNumNodes() == 0 && checker != headPtr) {
        checker = checker->getRight();
    }
    int indexOfLowest = checker->getIndex();
    int lowestNumNdoes = checker->getNumNodes();
    checker = checker->getRight();

    while(checker != headPtr) {
        if(lowestNumNdoes > checker->getNumNodes()) {
            indexOfLowest = checker->getIndex();
        }
        checker = checker->getRight();
    }

    return indexOfLowest;
}



bool inputHandler() {
    std::string userInput;
    std::ifstream XCfile;
    bool proceed = true, open = false;
    do {    
        std::cout << "Enter the path to the exact cover problem text file" << '\n';
        std::cout << "(-1 to quit, 'help' for help)" << '\n';
        std::cout << "\t-> ";
        
        std::getline(std::cin, userInput);
        if(userInput == "-1") {
            proceed = false;
            continue;
        }
        else if(userInput == "help") {
            displayHelp();
            continue;
        }

        XCfile.open(userInput);
        if(!XCfile.is_open()) {
            std::cout << "File opening failed.\n";
            continue;
        }

        open = true;
        while(!XCfile.eof()) {
            if(XCfile.peek() == '#' || XCfile.peek() == '\n') {
                XCfile.ignore(256, '\n');
            }
            else {
                std::string currentLine;
                while(std::getline(XCfile, currentLine, '\n')) {
                    if(currentLine.size() > 0) {
                        for(int size = 0; size < currentLine.length(); size++) {
                            inputVec.push_back(currentLine[size]);
                        }
                        inputVec.push_back(' ');
                    }
                }
            }
        }
    } while(userInput != "-1" && !open);
    XCfile.close();
    return proceed;
}



void displayHelp() {
    std::cout << "\nTo open your file name, make sure it's located in the project directory\n";
    std::cout << "and use the format yourFile.txt.\n\n";
    std::cout << "Your file must follow the following format:\n";
    std::cout << "For an (MxN) matrix where M = num of columns, N = num of rows\n";
    std::cout << "Name each M uniquely and type them without spaces. If M = 7, 'abcdefg'\n";
    std::cout << "Each following N lines should be a set of those letters. 'cdg', 'adg', 'be'\n\n";
    std::cout << "EX: \n" << "\tabcdefg\n" << "\tce\n" << "\tadg\n" << "\tbcf\n" << "\tadf\n";
    std::cout << "\tbg\n" << "\tdeg\n\n";
    std::cout << "NOTE: All lines that start with a '#' or is empty will be ignored and skipped.\n";
    std::cout << "Don't use any spaces or characters outside of the item names.\n\n";
}



void TEST_PrintFileContents() {
    for(std::vector<char>::iterator it = inputVec.begin(); it != inputVec.end(); ++it) {
        std::cout << "'" << *it << "' ";
        if(*it == ' ') {
            std::cout << '\n';
        }
    }
}



void TEST_HeadListHorizontalTraversal() {
    std::shared_ptr<DLX_Node> runner = headPtr->getRight();

    while(runner != headPtr) {
        std::cout << runner->getName() << ' ';
        runner = runner->getRight();
    }
    std::cout << '\n';
    runner = runner->getLeft();
    while(runner != headPtr) {
        std::cout << runner->getName() << ' ';
        runner = runner->getLeft();
    }
}



void TEST_VerticalItemTraversal() {
    TEST_PrintNetworkVector();
    std::cout << '\n';
    std::shared_ptr<DLX_Node> runner = headPtr->getRight();

    int firstSpacer = 0;
    while(networkVec[firstSpacer]->getName() != ' ') {
        ++firstSpacer;
    }
    while(runner != headPtr) {
        runner = runner->getDown();
        int tempIndex = firstSpacer;
        std::cout << "Printing item " << runner->getName() << ": ";
        while(runner != runner->getHeader()) {
            while(networkVec[tempIndex] != runner) {
                ++tempIndex;
            }
            std::cout << tempIndex + 1 << ' ';
            runner = runner->getDown();
            ++tempIndex;
        }
        runner = runner->getUp();
        std::cout << "| ";
        while(runner != runner->getHeader()) {
            while(networkVec[tempIndex] != runner) {
                --tempIndex;
            }
            std::cout << tempIndex + 1 << ' ';
            runner = runner->getUp();
            ++tempIndex;
        }
        runner = runner->getHeader()->getRight();
        std::cout << '\n';
    }
}



void TEST_PrintNetworkVector() {
    std::cout << "Vector contents: " << '\n';

    for(int i = 0; i < networkVec.size() - 1; ++i) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
    int count = 1;
    for(std::vector<std::shared_ptr<DLX_Node>>::iterator it = networkVec.begin(); it != networkVec.end(); ++it) {
        if(*it == networkVec[0]) {
            std::cout << "H ";
        }
        else {
            std::cout << it->get()->getName() << ' ';
            if(count >= 10) {
                std::cout << ' ';
            }
        }
        ++count;
    }
    std::cout << '\n';
}



void TEST_PointersPrintout() {
    std::shared_ptr<DLX_Node> printMe = headPtr;
    std::cout << "Pointers" << std::endl;
    while(printMe->getIndex() != networkVec.size()) {
        std::cout << printMe->getIndex();
        if(printMe->getIndex() < 10) {
            std::cout << "  '";
        }
        else {
            std::cout << " '";
        }
        std::cout << printMe->getName() << "' -> ";

        if(printMe->getUp() != nullptr) {
            std::cout << "U: " << printMe->getUp()->getName() << ' ' << printMe->getUp()->getIndex() << " - ";
        }
        if(printMe->getDown() != nullptr) {
            std::cout << "D: " << printMe->getDown()->getName() << ' ' << printMe->getDown()->getIndex();
        }
        if(printMe->getRight() != nullptr) {
            std::cout << " - ";
            std::cout << "L: " << printMe->getLeft()->getName() << ' ' << printMe->getLeft()->getIndex() << " - ";
            std::cout << "R: " << printMe->getRight()->getName() << ' ' << printMe->getRight()->getIndex();
            std::cout << "# nodes: " << printMe->getNumNodes();
        }
        std::cout << std::endl;

        if(printMe->getIndex() != networkVec.size() - 1) {
            break;
        }
        printMe = networkVec[printMe->getIndex() + 1];
    }
}



void TEST_PrintInputAsGraph() {
    int index = 1;
    std::shared_ptr<DLX_Node> runner;

    std::cout << "Items:    ";
    for(index; index < numHeaders; ++index) {
        runner = networkVec[index];
        std::cout << runner->getName() << ' ';
    }
    std::cout << '\n';
    ++index;
    runner = networkVec[index];

    int vecSize = networkVec.size();
    int optionNum = 1;
    while(index < vecSize) {
        runner = networkVec[index];
        int headerIndex = 1;
        std::cout << "Option " << optionNum << ": ";
        while(runner->getName() != ' ') {
            while(runner->getHeader() != networkVec[headerIndex]) {
                std::cout << "  ";
                ++headerIndex;
            }
            std::cout << runner->getName() << ' ';
            ++headerIndex;
            ++index;
            runner = networkVec[index];
        }
        std::cout << '\n';
        ++index;
        ++optionNum;
    }
}



void outputPointers() {
    std::string fileName = "OutputFiles/testOutput";
    fileName += std::to_string(numFiles);
    fileName += ".txt";
    std::fstream outfile;
    outfile.open(fileName, std::fstream::out | std::fstream::trunc);
    std::shared_ptr<DLX_Node> printMe = headPtr;
    outfile << fileName << std::endl;
    outfile << "Pointers" << std::endl;
    while(printMe->getIndex() != networkVec.size()) {
        outfile << printMe->getIndex();
        if(printMe->getIndex() < 10) {
            outfile << "  '";
        }
        else {
            outfile << " '";
        }
        outfile << printMe->getName() << "' -> ";

        if(printMe->getUp() != nullptr) {
            outfile << "U: " << printMe->getUp()->getName() << ' ' << printMe->getUp()->getIndex() << " - ";
        }
        if(printMe->getDown() != nullptr) {
            outfile << "D: " << printMe->getDown()->getName() << ' ' << printMe->getDown()->getIndex();
        }
        if(printMe->getRight() != nullptr) {
            outfile << " - ";
            outfile << "L: " << printMe->getLeft()->getName() << ' ' << printMe->getLeft()->getIndex() << " - ";
            outfile << "R: " << printMe->getRight()->getName() << ' ' << printMe->getRight()->getIndex() << " - ";
            outfile << "# nodes: " << printMe->getNumNodes();
        }
        outfile << std::endl;

        if(printMe->getIndex() == networkVec.size() - 1) {
            break;
        }
        printMe = networkVec[printMe->getIndex() + 1];
    }
    outfile.close();
}



void outputGraph() {
    std::string fileName = "OutputFiles/graphOutput";
    fileName += std::to_string(numFiles);
    fileName += ".txt";
    std::fstream outfile;
    outfile.open(fileName, std::fstream::out | std::fstream::trunc);
    std::shared_ptr<DLX_Node> printMe = headPtr;
    outfile << fileName << std::endl;

    int index = 1;
    std::shared_ptr<DLX_Node> runner;

    outfile << "Items:    ";
    for(index; index < numHeaders; ++index) {
        runner = networkVec[index];
        outfile << runner->getName() << ' ';
    }
    outfile << std::endl;
    ++index;
    runner = networkVec[index];

    int vecSize = networkVec.size();
    int optionNum = 1;
    while(index < vecSize) {
        runner = networkVec[index];
        int headerIndex = 1;
        outfile << "Option " << optionNum << ": ";
        while(runner->getName() != ' ') {
            while(runner->getHeader() != networkVec[headerIndex]) {
                outfile << "  ";
                ++headerIndex;
            }
            outfile << runner->getName() << ' ';
            ++headerIndex;
            ++index;
            runner = networkVec[index];
        }
        outfile << std::endl;
        ++index;
        ++optionNum;
    }
    outfile.close();
}


