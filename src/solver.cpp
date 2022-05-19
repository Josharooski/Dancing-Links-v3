#include "DLX_Node.h"
#include "DLX_Header.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <memory>


void readFile();
void buildNetwork();
void buildHeaderList(std::vector<char>::iterator& it);

std::vector<char> inputVec;
std::shared_ptr<DLX_Header> headPtr = std::make_shared<DLX_Header>();



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

    //test
    // for(int print = 0; print < inputVec.size(); print++) {
    //     std::cout << "'" << inputVec[print] << "' ";
    //     if(inputVec[print] == ' ') {
    //         std::cout << '\n';
    //     }
    // }
}



void buildNetwork() {
    std::vector<char>::iterator iter = inputVec.begin();
    buildHeaderList(iter);

    std::shared_ptr<DLX_Header> runner = std::make_shared<DLX_Header>();
    runner = headPtr->getRight();
    while(runner != headPtr) {
        std::cout << runner->getName() << ' ';
        runner = runner->getRight();
    }
}



void buildHeaderList(std::vector<char>::iterator& it) {
    std::shared_ptr<DLX_Header> addMe;
    
    while(*it != ' ') {
        addMe = std::make_shared<DLX_Header>(*it);
        std::shared_ptr<DLX_Header> searcher = std::make_shared<DLX_Header>();
        searcher = headPtr;
        while(searcher->getRight() != headPtr) {
            searcher = searcher->getRight();
        }
        addMe->setLeft(searcher);
        addMe->setRight(headPtr);
        searcher->setRight(addMe);
        ++it;
    }
    headPtr->setLeft(addMe);
}