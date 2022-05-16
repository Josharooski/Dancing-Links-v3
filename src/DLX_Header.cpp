#include "DLX_Header.h"

DLX_Header::DLX_Header() : leftPtr(nullptr), rightPtr(nullptr), name('\0'), length(0) {}

DLX_Header::DLX_Header(const DLX_Header& copyMe) {
    leftPtr = copyMe.leftPtr;
    rightPtr = copyMe.rightPtr;
    name = copyMe.name;
    length = copyMe.name;
}

void DLX_Header::setLeft(DLX_Header* ptr) {
    leftPtr = ptr;
}

void DLX_Header::setRight(DLX_Header* ptr) {
    rightPtr = ptr;
}

void DLX_Header::setName(char newName) {
    name = newName;
}

DLX_Header* DLX_Header::getLeft() const {
    return leftPtr;
}  

DLX_Header* DLX_Header::getRight() const {
    return rightPtr;
}

char DLX_Header::getName() const {
    return name;
}

int DLX_Header::getLength() const {
    return length;
}