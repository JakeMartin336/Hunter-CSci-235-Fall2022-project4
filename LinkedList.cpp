// Jacob Martin
// 10/25/2022
// LinkedList.cpp
// Project 4

#include<iostream>

/* Default constructor*/
template<typename ItemType>
LinkedList<ItemType>::LinkedList() : head_(nullptr), size_(0) {}

/*
    A copy constructor
    @param            :   Another LinkedList passed by reference

    Initializes this LinkedList with the same items as the provided LinkedList
*/
template<typename ItemType>
LinkedList<ItemType>::LinkedList(const LinkedList<ItemType> &entry)
{
    size_ = entry.size_;
    Node<ItemType>* orig_ptr = entry.head_; //points to head node in linkedlist passed
    if(orig_ptr == nullptr) //if head node in linkedlist passed is null then set new list head node to null
        head_ = nullptr;
    else //if list is filled
    {
        head_ = new Node<ItemType>(); //create new head node in new linkedlist
        head_->setItem(orig_ptr->getItem()); //copy head node item from linked listed passed to new linked list
        
        Node<ItemType>* new_chain_ptr = head_; //create new temp node for traversing
        orig_ptr = orig_ptr->getNext(); //advance original chain node position
        while(orig_ptr != nullptr) //while there are still more nodes to copy
        {
            ItemType next_item = orig_ptr->getItem(); //get item from original chain
            Node<ItemType>* new_node_ptr = new Node<ItemType>(next_item); //create new node containing the next item
            new_chain_ptr->setNext(new_node_ptr); //link new node to the chain
            new_chain_ptr = new_chain_ptr->getNext(); //advance pointer to next node in chain
            orig_ptr = orig_ptr->getNext(); //advance original chain pointer
        }
        new_chain_ptr->setNext(nullptr); //when end of original chain, mark new last node setnext as null
    }
}

/* Destructor */
template<typename ItemType>
LinkedList<ItemType>::~LinkedList() {
    clear();
}

/* @return  : the head pointer
This function is for grading purposes*/
template<typename ItemType>
Node<ItemType>* LinkedList<ItemType>::getHeadPtr() const {
    return head_;
}

/*
    @post   : removes all items from the caller list
**/
template<typename ItemType>
void LinkedList<ItemType>::clear() {

    Node<ItemType>* curr_item = head_;
    while(curr_item != nullptr) {
        Node<ItemType>* temp = curr_item;
        curr_item = curr_item->getNext();
        // delete temp->getItem();
        // temp->setItem(NULL);
        // temp->setNext(nullptr);
        delete temp;
        temp = nullptr;
    }

}

/*
    @param  item: the item to insert in the list
    @param  position: the position where to inserted
    @pre position is a valid place within the list, otherwise false will be returned
    @return   :  true if the item has been inserted in the caller list,
                false otherwise
    @post     : Inserts item in  list at  position

**/
template<typename ItemType>
bool LinkedList<ItemType>::insert(const ItemType &item, const int &position)
{
    if((position < 0 || position > size_)){
        return false;
    }

    Node<ItemType> *node = new Node<ItemType>();
    node->setItem(item);

    if(size_ == 0){
        head_ = node;
    }
    else {
        Node<ItemType> *iterator;

        if(position == 0){
            node->setNext(head_);
            head_ = node;
        }

        else if (position == size_){
            iterator = getAtPos(size_-1);
            iterator->setNext(node);
        }
        else {
            iterator = getAtPos(position-1);
            node->setNext(iterator->getNext());
            iterator->setNext(node);
        }
    }
    size_++;
    return true;
}

/*
    @param  position:  the position where to remove
    @pre position is a valid place within the list, otherwise false will be returned
    @pre      : returns true if the item at position has been removed from the list,
                false otherwise
    @post     : removes node at  position
**/
template <typename ItemType>
bool LinkedList<ItemType>::remove(const int&position) {
    if (position < 0 || position >= size_) {
        return false;
    }

    Node<ItemType> *iterator;

    if (position == 0){
        iterator = head_;
        head_ = head_->getNext();
    }
    else {
        iterator = getAtPos(position-1);
        iterator->setNext(iterator->getNext()->getNext());
        iterator = iterator->getNext();
    }

    return true;

}

/*
    @param   item : the item to find in the list
    @pre      : takes item object and checks if exist in list and return
    @return   : returns the position (index) of object in the list

**/
template<typename ItemType>
int LinkedList<ItemType>::getIndexOf(const ItemType &item) const {
    Node<ItemType>* curr_item = head_;
    int counter = 0;
    while(curr_item != nullptr) {
        if(curr_item->getItem() == item) {
            return counter;
        }
        counter++;
        curr_item = curr_item->getNext();
    }
    return -1;
}

/* @return  : the size of the list */
template<typename ItemType>
int LinkedList<ItemType>::getSize() const {
    return size_;
}

  /* @return  : true if the list is empty, false otherwise */
template<typename ItemType>
bool LinkedList<ItemType>::isEmpty() const {
    return size_ == 0 ? true : false;
}

// PRIVATE METHODS

/*
    @param   pos : the position of the item
    @pre     : pos is a valid place in the list
    @return  : a pointer to the node at pos, if pos is invalid, returns nullptr
**/
template<typename ItemType>
Node<ItemType>* LinkedList<ItemType>::getAtPos(const int &pos) const {

    if(pos < 0 || pos >= size_) {
        return nullptr;
    }

    Node<ItemType>* curr_item = head_;
    int counter = 0;
    while(counter < pos && curr_item != nullptr) {
        counter++;
        curr_item = curr_item->getNext();
    }
    return curr_item;
}

/*
    A reversed copy function
    @param            :   Another LinkedList passed by reference

    Sets the current LinkedList with the same items as the provided LinkedList
    but in reverse order
*/
template<typename ItemType>
void LinkedList<ItemType>::reverseCopy(const LinkedList<ItemType> &entry)
{
    Node<ItemType>* curr_ptr = entry.head_; //takes the head pointer of the list being copied
    while(curr_ptr != nullptr)
    {
        this->insert(curr_ptr->getItem(), 0); //takes the list where its being copied to, and inserts the curr pointer in the list in the orig linked list
        curr_ptr = curr_ptr->getNext(); //gets next node of the list being copied
    }
}    

/*
    @param            :   A reference to an item
    @return           :   Return true if item was moved to top, false otherwise
    @post             :   Will move the item from its current position to the front
                          of the list.
                          For example, given the list 1 -> 3 -> 5 -> 6, moving 5 to the
                          top of the list would result in 5 -> 1 -> 3 -> 6
                          (recall that positions start at 0 and end at n-1).

    You are encouraged to create your own helper functions for this endeavour.
*/
template<typename ItemType>
bool LinkedList<ItemType>::moveItemToTop(const ItemType &entry)
{
    int index = getIndexOf(entry); //gets index of the post that is to be moved
    if(index == -1 || index == 0) //if its not in the linked list
        return false;
    else
    {
        this->remove(index); //remove where the post originally was
        this->insert(entry, 0); //then insert a new post at the start of the linked list
        return true;
    }
}
