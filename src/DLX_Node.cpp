#include "DLX_Node.h"

DLX_Node::DLX_Node() : upPtr(nullptr), downPtr(nullptr), listHeader(nullptr){}

DLX_Node::DLX_Node(const DLX_Node& copyMe) {
    upPtr = copyMe.upPtr;
    downPtr = copyMe.downPtr;
    listHeader = copyMe.listHeader;
}

void DLX_Node::setUp(DLX_Node* ptr) {
    upPtr = ptr;
}

void DLX_Node::setDown(DLX_Node* ptr) {
    downPtr = ptr;
}

void DLX_Node::setHeader(DLX_Node* ptr) {
    listHeader = ptr;
}

DLX_Node* DLX_Node::getUp() const {
    return upPtr;
}

DLX_Node* DLX_Node::getDown() const {
    return downPtr;
}

DLX_Node* DLX_Node::getHeader() const {
    return listHeader;
}