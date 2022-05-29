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
void search(int level);
void coverSubItems(std::shared_ptr<DLX_Node> item);
void uncoverSubItems(std::shared_ptr<DLX_Node> item);
int lowestNumNodes();

// Testing
void TEST_PrintNetworkVector();
void TEST_VerticalItemTraversal();
void TEST_HeadListHorizontalTraversal();
void TEST_PrintFileContents();
void TEST_PointersPrintout();

// Testing - External Output
void outputPointers();

// Globals
std::vector<char> inputVec;
std::vector<std::shared_ptr<DLX_Node>> networkVec;
std::shared_ptr<DLX_Node> headPtr = std::make_shared<DLX_Node>();
int numFiles = 1;



int main() {
    headPtr->setRight(headPtr);
    headPtr->setName('H');
    readFile();
    buildNetwork();
    outputPointers();
    search(0);
    outputPointers();
    return 0;
}



void readFile() {
    std::ifstream XCfile;
    XCfile.open("C:/users/jgils/git-repos/dancing-links-v3/test-file.txt");

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



void cover(std::shared_ptr<DLX_Node> coverMe) {
    std::shared_ptr<DLX_Node> checker = coverMe->getDown();

    while(checker != coverMe) {
        hide(checker);
        checker = checker->getDown();
    }

    coverMe->getRight()->setLeft(coverMe->getLeft());
    coverMe->getLeft()->setRight(coverMe->getRight());
}



void uncover(std::shared_ptr<DLX_Node> uncoverMe) {
    uncoverMe->getLeft()->setRight(uncoverMe);
    uncoverMe->getRight()->setLeft(uncoverMe);

    std::shared_ptr<DLX_Node> runner = uncoverMe->getUp();

    while(runner != uncoverMe) {
        unhide(runner);
        runner = runner->getUp();
    }
}



void hide(std::shared_ptr<DLX_Node> hideMe) {
    int currentIndex = hideMe->getIndex() + 1;
    std::shared_ptr<DLX_Node> checker = networkVec[currentIndex];

    while(checker != hideMe) {
        if(checker->getHeader() == nullptr) {
            checker = checker->getUp();
            currentIndex = hideMe->getIndex();
        }
        else {
            checker->getDown()->setUp(checker->getUp());
            checker->getUp()->setDown(checker->getDown());
            checker->getHeader()->numNodesSub();
            ++currentIndex;
        }
        checker = networkVec[currentIndex];
    }
}



void unhide(std::shared_ptr<DLX_Node> unhideMe) {
    int currentIndex = unhideMe->getIndex() - 1;
    std::shared_ptr<DLX_Node> runner = networkVec[currentIndex];

    while(runner != unhideMe) {
        if(runner->getHeader() == nullptr) {
            runner = runner->getDown();
            currentIndex = unhideMe->getIndex();
        }
        else {
            runner->getUp()->setDown(runner);
            runner->getDown()->setUp(runner);
            runner->getHeader()->numNodesAdd();
            --currentIndex;
        }
        runner = networkVec[currentIndex];
    }
}



void search(int level) {
    std::shared_ptr<DLX_Node> solution[networkVec.size()];
    std::shared_ptr<DLX_Node> currentItem;

    //X2
    if(headPtr->getRight() != headPtr) {
        //X3
        currentItem = networkVec[lowestNumNodes()];
        //X4
        cover(currentItem);

        // *TEST*
        outputPointers();

        solution[level] = currentItem->getDown();
        //X5
        if(solution[level] != currentItem) {
            coverSubItems(solution[level]);
            
            // *TEST*
            outputPointers();

            level += 1;
            search(level);
        }
        //X7
        else{
            uncover(currentItem);

            // *TEST*
            outputPointers();
        }
    }
    //X8
    else{
        if(level != 0) {
            level -= 1;
            //X6
            uncoverSubItems(solution[level]);

            // *TEST*
            outputPointers();

            currentItem = solution[level]->getHeader();
            solution[level] = solution[level]->getDown();
            //X5
            if(solution[level] != currentItem) {
                coverSubItems(solution[level]);

                // *TEST*
                outputPointers();

                level += 1;
                search(level);
            }
        }
        else {
            std::cout << "Solution:" << '\n';
            std::shared_ptr<DLX_Node> printMe;
            for(int i = 0; i < networkVec.size(); ++i) {
                printMe = solution[i];
                if(printMe != nullptr) {
                    while(printMe->getHeader() != nullptr) {
                        std::cout << printMe->getName() << ' ';
                        printMe = networkVec[printMe->getIndex() + 1];
                    }
                }
            }
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
}



void uncoverSubItems(std::shared_ptr<DLX_Node> item) {
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
}



int lowestNumNodes() {
    std::shared_ptr<DLX_Node> checker = headPtr->getRight();
    int indexOfLowest = checker->getIndex();
    int lowestNumNdoes = checker->getNumNodes();

    while(checker != headPtr) {
        if(lowestNumNdoes > checker->getNumNodes()) {
            indexOfLowest = checker->getIndex();
        }
        checker = checker->getRight();
    }

    return indexOfLowest;
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
        }
        std::cout << std::endl;

        if(printMe->getIndex() == networkVec.size() - 1) {
            break;
        }
        printMe = networkVec[printMe->getIndex() + 1];
    }
}



void outputPointers() {
    std::string fileName = "OutputFiles/testOutput";
    fileName += std::to_string(numFiles);
    fileName += ".txt";
    ++numFiles;
    std::fstream outfile;
    outfile.open(fileName, std::fstream::out | std::fstream::trunc);
    std::shared_ptr<DLX_Node> printMe = headPtr;
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
            outfile << "R: " << printMe->getRight()->getName() << ' ' << printMe->getRight()->getIndex();
        }
        outfile << std::endl;

        if(printMe->getIndex() == networkVec.size() - 1) {
            break;
        }
        printMe = networkVec[printMe->getIndex() + 1];
    }
    outfile.close();
}


