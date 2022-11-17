// Jacob Martin
// 10/25/2022
// Account.hpp
// Project 4

#ifndef _ACCOUNT_ //defining account
#define _ACCOUNT_

#include "Network.hpp" //include needed headers and libraries
#include "LinkedList.hpp"
#include "Post.hpp"
#include <vector>
#include <string>
#include <iostream>

class Account
{
public:
	Account();
	Account(std::string name, std::string word);
	void setUsername(const std::string& name);
	std::string getUsername() const;
	void setPassword(const std::string& word);
	std::string getPassword() const;
	bool addPost(Post * const entry); //taking a const POINTER to a Post in its addPost function
	void viewPosts() const;

	Network<Account> *getNetwork() const;
	void setNetwork(Network<Account> *entry);
	
	bool followAccount(const std::string& name);
	std::vector<std::string> viewFollowing() const;

	void updatePost(Post* entry, std::string newT, std::string newB);
	bool removePost(Post* entry);
private:
	std::string username;
	std::string password;
	//std::vector<Post> all_posts;
	std::vector<std::string> following;
	Network<Account>* network_apartof;
	
	LinkedList<Post*> act_posts;
};
#endif