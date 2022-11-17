// Jacob Martin
// 10/25/2022
// Network.hpp
// Project 4

#ifndef _NETWORK_ //defining Network
#define _NETWORK_

#include "Post.hpp" //include needed headers and libraries
#include "LinkedList.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

template<class ItemType> //defining Network as template
class Network
{
public:
	Network();
	int getSizeOfNetwork() const;
	bool isEmpty() const;
	bool addAccount(ItemType* entry); //add account to network
	bool removeAccount(const ItemType* entry); //remove account from network
	void clear();
	bool containsAccount(const ItemType* entry) const; //checks if network contains the account

	void populateNetwork(const std::string file); //taking in a file and crating accounts from the file
	void operator-=(Network<ItemType>& entry); //comparing networks

	void printFeedForAccount(ItemType& entry); //prints the following accounts posts
	bool authenticateFollow(ItemType& entry, const std::string& name); //allows an account to follow another
	bool addToFeed(Post * const entry); //add a post to the linked list

	int removeIfContains(std::string &entry); //remove a post in the linked list if it contains the string passed
	void removeHelper(Post* entry); //remove helper for removing posts from linked list
	void moveHelper(Post* entry); //move helper for moving posts in the linked list
private:
	static const int DEFAULT_CAPACITY = 200;
	ItemType* items[DEFAULT_CAPACITY];
	int acct_count;
	//std::vector<Post> net_posts;
	LinkedList<Post*> net_posts;
	int getIndexOf(const std::string& usr) const; //get index of the user within the account array
};
#include "Network.cpp"
#endif
