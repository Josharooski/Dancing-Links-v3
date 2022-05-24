#ifndef DLX_NODE_
#define DLX_NODE_

#include <memory>

class DLX_Node {
    private:
        std::shared_ptr<DLX_Node> leftPtr;
        std::shared_ptr<DLX_Node> rightPtr;
        std::shared_ptr<DLX_Node> upPtr;
        std::shared_ptr<DLX_Node> downPtr;
        std::shared_ptr<DLX_Node> listHeader;
        char name;
        int numNodes;

    public:
        DLX_Node();
        DLX_Node(char newName);
        DLX_Node(const DLX_Node& copyMe);
        ~DLX_Node();

        void setLeft(std::shared_ptr<DLX_Node> ptr);
        void setRight(std::shared_ptr<DLX_Node> ptr);
        void setUp(std::shared_ptr<DLX_Node> ptr);
        void setDown(std::shared_ptr<DLX_Node> ptr);
        void setHeader(std::shared_ptr<DLX_Node> ptr);
        void setName(char newName);
        void numNodesAdd();
        void numNodesSub();

        std::shared_ptr<DLX_Node> getLeft() const;
        std::shared_ptr<DLX_Node> getRight() const;
        std::shared_ptr<DLX_Node> getUp() const;
        std::shared_ptr<DLX_Node> getDown() const;
        std::shared_ptr<DLX_Node> getHeader() const;
        char getName() const;
        int getNumNodes() const;
};

#endif