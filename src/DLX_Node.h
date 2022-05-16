#ifndef DLX_NODE_
#define DLX_NODE_

class DLX_Node {
    private:
        DLX_Node* upPtr;
        DLX_Node* downPtr;
        DLX_Node* listHeader;

    public:
        DLX_Node();
        DLX_Node(const DLX_Node& copyMe);

        void setUp(DLX_Node* ptr);
        void setDown(DLX_Node* ptr);
        void setHeader(DLX_Node* ptr);

        DLX_Node* getUp() const;
        DLX_Node* getDown() const;
        DLX_Node* getHeader() const;
};

#endif