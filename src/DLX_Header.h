#ifndef DLX_HEADER_
#define DLX_HEADER_

#include "DLX_Node.h"

class DLX_Header : public DLX_Node {
    private:
        DLX_Header* leftPtr;
        DLX_Header* rightPtr;
        char name;
        int length;
    
    public:
        DLX_Header();
        DLX_Header(const DLX_Header& copyMe);

        void setLeft(DLX_Header* ptr);
        void setRight(DLX_Header* ptr);
        void setName(char newName);

        DLX_Header* getLeft() const;
        DLX_Header* getRight() const;
        char getName() const;
        int getLength() const;
};

#endif