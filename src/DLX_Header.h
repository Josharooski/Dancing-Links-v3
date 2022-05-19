#ifndef DLX_HEADER_
#define DLX_HEADER_

#include "DLX_Node.h"

class DLX_Header : public DLX_Node {
    private:
        std::shared_ptr<DLX_Header> leftPtr;
        std::shared_ptr<DLX_Header> rightPtr;
        char name;
        int numNodes;
    
    public:
        DLX_Header();
        DLX_Header(char newName);
        DLX_Header(std::shared_ptr<DLX_Header> left, std::shared_ptr<DLX_Header> right);
        DLX_Header(const DLX_Header& copyMe);

        void setLeft(std::shared_ptr<DLX_Header> ptr);
        void setRight(std::shared_ptr<DLX_Header> ptr);
        void setName(char newName);

        std::shared_ptr<DLX_Header> getLeft() const;
        std::shared_ptr<DLX_Header> getRight() const;
        char getName() const;
        int getNumNodes() const;
};

#endif