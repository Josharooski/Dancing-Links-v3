#include "DLX_Node.h"

DLX_Node::DLX_Node() {
    upPtr = nullptr;
    downPtr = nullptr;
    upPtr = nullptr;
}

DLX_Node::DLX_Node(const DLX_Node& copyMe) {
    upPtr = copyMe.upPtr;
    downPtr = copyMe.downPtr;
    listHeader = copyMe.listHeader;
}

DLX_Node::~DLX_Node() {}

void DLX_Node::setUp(std::shared_ptr<DLX_Node> ptr) {
    upPtr = ptr;
}

void DLX_Node::setDown(std::shared_ptr<DLX_Node> ptr) {
    downPtr = ptr;
}

void DLX_Node::setHeader(std::shared_ptr<DLX_Node> ptr) {
    listHeader = ptr;
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