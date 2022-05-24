#include "DLX_Node.h"

DLX_Node::DLX_Node() {
    leftPtr = nullptr;
    rightPtr = nullptr;
    upPtr = nullptr;
    downPtr = nullptr;
    listHeader = nullptr;
    name = '\0';
    numNodes = 0;
}

DLX_Node::DLX_Node(char newName) {
    leftPtr= nullptr;
    rightPtr = nullptr;
    upPtr = nullptr;
    downPtr = nullptr;
    listHeader = nullptr;
    name = newName;
    numNodes = 0;
}

DLX_Node::DLX_Node(const DLX_Node& copyMe) {
    leftPtr = copyMe.leftPtr;
    rightPtr = copyMe.rightPtr;
    upPtr = copyMe.upPtr;
    downPtr = copyMe.downPtr;
    listHeader = copyMe.listHeader;
    name = copyMe.name;
    numNodes = copyMe.numNodes;
}

DLX_Node::~DLX_Node() {}

void DLX_Node::setLeft(std::shared_ptr<DLX_Node> ptr) {
    leftPtr = ptr;
}

void DLX_Node::setRight(std::shared_ptr<DLX_Node> ptr) {
    rightPtr = ptr;
}

void DLX_Node::setUp(std::shared_ptr<DLX_Node> ptr) {
    upPtr = ptr;
}

void DLX_Node::setDown(std::shared_ptr<DLX_Node> ptr) {
    downPtr = ptr;
}

void DLX_Node::setHeader(std::shared_ptr<DLX_Node> ptr) {
    listHeader = ptr;
}

void DLX_Node::setName(char newName) {
    name = newName;
}

void DLX_Node::numNodesAdd() {
    ++numNodes;
}

void DLX_Node::numNodesSub() {
    --numNodes;
}

std::shared_ptr<DLX_Node> DLX_Node::getLeft() const {
    return leftPtr;
}

std::shared_ptr<DLX_Node> DLX_Node::getRight() const {
    return rightPtr;
}

std::shared_ptr<DLX_Node> DLX_Node::getUp() const {
    return upPtr;
}

std::shared_ptr<DLX_Node> DLX_Node::getDown() const {
    return downPtr;
}

std::shared_ptr<DLX_Node> DLX_Node::getHeader() const {
    return listHeader;
}

char DLX_Node::getName() const {
    return name;
}

int DLX_Node::getNumNodes() const {
    return numNodes;
}