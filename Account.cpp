/// Jacob Martin
// 10/25/2022
// Account.cpp
// Project 4

#include "Account.hpp" //include needed headers and libraries

Account::Account() : username(""), password(""), network_apartof(nullptr) {}

Account::Account(std::string name, std::string word) : username(name), password(word), network_apartof(nullptr) {}//param constructor

void Account::setUsername(const std::string& name) //setting username to value passed
{
	username = name;
}

std::string Account::getUsername() const //returning account username
{
	return username;
}

void Account::setPassword(const std::string& word) //setting password to value passed
{
	password = word;
}

std::string Account::getPassword() const //returning password
{
	return password;
}

bool Account::addPost(Post * const entry) //adding post to account post linked list
{
	if(act_posts.getIndexOf(entry) == -1 && entry->getBody() != "" && entry->getTitle() != "" && entry->getUsername() == username)
	{
		act_posts.insert(entry,0);
		if(network_apartof != nullptr)
			network_apartof->addToFeed(entry);
		return true;
	}
	else
		return false;
}

void Account::viewPosts() const//view all posts from account
{
	Node<Post*> *current_pointer = act_posts.getHeadPtr();
	while(current_pointer != nullptr) 
	{
		current_pointer->getItem()->displayPost();
		current_pointer = current_pointer->getNext();
	}
}

Network<Account>* Account::getNetwork() const //return the network the account is apart of
{
	return network_apartof;
}

void Account::setNetwork(Network<Account> *entry) //set the network the account is apart of from the value passed
{
	network_apartof = entry;
}

bool Account::followAccount(const std::string& name) //adding account to following vector
{
	bool final = true;
    for (int i = 0; i < following.size(); i++) //cycle through current following
        if (following[i] == name) //if account is already following then final = false, thus returning false
            final = false;
    if (network_apartof != nullptr && final == true && network_apartof ->containsAccount(this))//if this account is apart of the network that wants to follow, and not already following the account passed
    {
        following.push_back(name); //if passed then add account passed to the following vector
        return true;
    }
    return false;
}

std::vector<std::string> Account::viewFollowing() const
{
	return following;
}

void Account::updatePost(Post* entry, std::string newT, std::string newB)
{
	if(newT != "")
		entry->setTitle(newT);
	if(newB != "")
		entry->setBody(newB);
	entry->setNewTimeHelper();
	act_posts.moveItemToTop(entry);
	if(network_apartof != nullptr)
		network_apartof->moveHelper(entry);
}

bool Account::removePost(Post* entry)
{
	int index = act_posts.getIndexOf(entry);
	if(index != -1)
	{
		act_posts.remove(index);
		if(network_apartof != nullptr)
			network_apartof->removeHelper(entry);
		return true;
	}
	else
		return false;
}