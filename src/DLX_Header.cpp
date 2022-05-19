#include "DLX_Header.h"

DLX_Header::DLX_Header() {
    leftPtr = nullptr;
    rightPtr = nullptr;
    name = '\0';
    numNodes = 0;
}

DLX_Header::DLX_Header(char newName) {
    leftPtr = nullptr;
    rightPtr = nullptr;
    name = newName;
    numNodes = 0;
}

DLX_Header::DLX_Header(std::shared_ptr<DLX_Header> left, std::shared_ptr<DLX_Header> right) {
    leftPtr = left;
    rightPtr = right;
    name = '\0';
    numNodes = 0;
}

DLX_Header::DLX_Header(const DLX_Header& copyMe) {
    leftPtr = copyMe.leftPtr;
    rightPtr = copyMe.rightPtr;
    name = copyMe.name;
    numNodes = copyMe.name;
}

void DLX_Header::setLeft(std::shared_ptr<DLX_Header> ptr) {
    leftPtr = ptr;
}

void DLX_Header::setRight(std::shared_ptr<DLX_Header> ptr) {
    rightPtr = ptr;
}

void DLX_Header::setName(char newName) {
    name = newName;
}

std::shared_ptr<DLX_Header> DLX_Header::getLeft() const {
    return leftPtr;
}  

std::shared_ptr<DLX_Header> DLX_Header::getRight() const {
    return rightPtr;
}

char DLX_Header::getName() const {
    return name;
}

int DLX_Header::getNumNodes() const {
    return numNodes;
}