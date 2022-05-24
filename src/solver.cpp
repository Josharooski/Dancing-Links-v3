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

// Testing
void TEST_PrintNetworkVector();
void TEST_VerticalItemTraversal();
void TEST_HeadListHorizontalTraversal();
void TEST_PrintFileContents();

// Globals
std::vector<char> inputVec;
std::vector<std::shared_ptr<DLX_Node>> networkVec;
std::shared_ptr<DLX_Node> headPtr = std::make_shared<DLX_Node>();



int main() {
    headPtr->setRight(headPtr);
    readFile();
    buildNetwork();
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
            while(std::getline(XCfile, currentLine)) {
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
    TEST_PrintFileContents();
}



void buildNetwork() {
    int travelIndex = 0;
    buildVector();
    connectHeaderList(travelIndex);
    TEST_HeadListHorizontalTraversal();
    connectNodeList(travelIndex);
    std::cout << "\n\n";
    TEST_VerticalItemTraversal();
}



void buildVector() {
    networkVec.push_back(headPtr);
    std::vector<char>::iterator iter = inputVec.begin();
    std::shared_ptr<DLX_Node> addMe;
    while(iter != inputVec.end()) {
        addMe = std::make_shared<DLX_Node>(*iter);
        networkVec.push_back(addMe);
        ++iter;
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
        std::cout << i + 1 << ' ';
    }
    std::cout << '\n';
    int count = 1;
    for(std::vector<std::shared_ptr<DLX_Node>>::iterator it = networkVec.begin(); it != networkVec.end(); ++it) {
        if(*it == networkVec[0]) {
            std::cout << "h ";
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



