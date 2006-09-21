
#ifndef AT_MAP_HPP
#define AT_MAP_HPP

#include "atGlobals.h++"
#include "atList.h++"
#include "atItem.h++"
#include "atNotifier.h++"

enum atMapColor
{
    AT_MAP_BLACK,
    AT_MAP_RED
};

enum atMapChildType
{
    AT_MAP_LEFTCHILD,
    AT_MAP_RIGHTCHILD,
    AT_MAP_ROOTNODE
};

struct atMapNode
{
    atMapNode *   leftChild;
    atMapNode *   rightChild;
    atMapNode *   parent;
    int           color;
    
    atItem *      nodeKey;
    atItem *      nodeValue;
};

class atMap : public atNotifier
{
private:

    atMapNode *   treeRoot;
    int           treeSize;
    
    atMapNode *       findNode(atMapNode * node, atItem * key);
    void              rebalanceInsert(atMapNode * node);
    void              rebalanceDelete(atMapNode * parent,
                                      int deletedChildType);
    void              deleteNode(atMapNode * node);
    atMapNode *       getInorderSuccessor(atMapNode * node);
    void              rotateLeft(atMapNode * node);
    void              rotateRight(atMapNode * node);
    void              deleteTree(atMapNode * node);
    int               getChildType(atMapNode * node);
    void              fillLists(atMapNode * node, atList * keyList,
                                atList * valueList);

public:

                atMap();
    virtual     ~atMap();

    bool        addEntry(atItem * key, atItem * value);
    bool        deleteEntry(atItem * key);
    int         getEntryCount();
    
    bool        containsKey(atItem * key);
    atItem *    getValue(atItem * key);
    atItem *    changeValue(atItem * key, atItem * newValue);

    void        clear();

    void        getSortedList(atList * keyList,
                              atList * valueList);
};

#endif
