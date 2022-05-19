#ifndef DLX_NODE_
#define DLX_NODE_

#include <memory>

class DLX_Node {
    private:
        std::shared_ptr<DLX_Node> upPtr;
        std::shared_ptr<DLX_Node> downPtr;
        std::shared_ptr<DLX_Node> listHeader;

    public:
        DLX_Node();
        DLX_Node(const DLX_Node& copyMe);
        virtual ~DLX_Node();

        void setUp(std::shared_ptr<DLX_Node> ptr);
        void setDown(std::shared_ptr<DLX_Node> ptr);
        void setHeader(std::shared_ptr<DLX_Node> ptr);

        std::shared_ptr<DLX_Node> getUp() const;
        std::shared_ptr<DLX_Node> getDown() const;
        std::shared_ptr<DLX_Node> getHeader() const;
};

#endif