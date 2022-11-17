// Jacob Martin
// 10/25/2022
// Network.cpp
// Project 4

#include "Network.hpp" //include needed headers and libraries

template<class ItemType>
Network<ItemType>::Network() : acct_count(0) {}

template<class ItemType>
int Network<ItemType>::getSizeOfNetwork() const //getting size of accounts in network
{
	return acct_count;
}

template<class ItemType>
bool Network<ItemType>::isEmpty() const //seeing if num of accounts in network is 0
{
	return acct_count == 0;
}

template<class ItemType>
bool Network<ItemType>::addAccount(ItemType* entry) //adding account to network
{
	bool space = (acct_count < DEFAULT_CAPACITY);
	if (space && !containsAccount(entry)) //if there is enough space in the network for another account and it isnt already within the network
	{
		//if item doesnt already exist..
		items[acct_count] = entry; //add new account to array
		acct_count++; //up the num of accounts in network
		entry->setNetwork(this); //set the network that the account is apart of
		return true;
	}
	else
		return false;
}

template<class ItemType>
bool Network<ItemType>::removeAccount(const ItemType* entry)
{
	int found_index = getIndexOf(entry->getUsername()); //finding where the account is in the array
	bool can_remove = !isEmpty() && (found_index > -1); //making sure the account isnt empty and is in valid index in array
	if (can_remove) // if previous statement is true
	{
		acct_count--; //making num of accounts in network smaller
		items[found_index] = items[acct_count]; //removing the account from the found index in array
	}
	return can_remove;
}

template<class ItemType>
void Network<ItemType>::clear()
{
	acct_count = 0; //setting num of accounts in the network to 0
}

template<class ItemType>
bool Network<ItemType>::containsAccount(const ItemType* entry) const
{
	return getIndexOf(entry->getUsername()) > -1; // if index is valid index in array then return true
}

template<class ItemType>
int Network<ItemType>::getIndexOf(const std::string& usr) const
{
	bool found = false; //to track progress of finding the account within the network
	int result = -1;
	int search_index = 0;

	while (!found && (search_index < acct_count)) //cycling through array index until the index of the account looking for is found
	{
		if (items[search_index]->getUsername() == usr) //if username of index matches the string given
		{
			found = true; // end search
			result = search_index; //send the index of the account to result
		}
		else
			search_index++; //keep searching index of array
	}
	return result;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class ItemType>
void Network<ItemType>::populateNetwork(const std::string file)
{
	std::ifstream myfile(file); //create fstream object
	if(!myfile.is_open()) //if fstream isnt open then give error
	{
		std::cout << "Error\n";
	}
	std::string line; //var to store lines from file
	while(std::getline(myfile, line)) //reading file line by line and storing it in line var
	{
		if(line[0] == ';') //if line is ; then terminate
		{
        	myfile.close();
			break;
		}
    	std::istringstream filter(line); //creating an input string stream object and having the line from the file pass through this object
		std::string user, pass; //var to store result of parsing each line
		filter >> user >> pass;
		if(user == "" || pass == "") //checking if user and pass are in the correct format
        {
            std::cout << "Improper Format\n"; //if not throw error and terminate
            myfile.close();
			break;
        }
        else //if user and pass are in correct format
        {
            ItemType *temp = new ItemType(user, pass); //create new Account and initialize it
            addAccount(temp); //add new account object to network
			user = "";
			pass = "";
        }
	}
	myfile.close();
}

template<class ItemType>
void Network<ItemType>::operator-=(Network<ItemType>& entry)
{
    for (int i=0; i< entry.acct_count; i++) //cycle through the amount of accounts in network
        if(containsAccount(entry.items[i])) //if an account is also within the network
            removeAccount(entry.items[i]); //remove the account
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class ItemType>
void Network<ItemType>::printFeedForAccount(ItemType& entry)
{
	std::vector<std::string> entry_following = entry.viewFollowing();
	for(int i = 0; i < entry_following.size(); i++) //look at account following vector and getting the size of the vector												//give the index of the vector of accounts being followed, find the if that username is in the network 
	{
		int account_index = getIndexOf(entry_following[i]);
		if(account_index > -1) //if it is in the network
			items[account_index]->viewPosts();
	}
}


template<class ItemType>
bool Network<ItemType>::authenticateFollow(ItemType& entry, const std::string& name)
{
	if (containsAccount(&entry) && getIndexOf(name) != -1) //if both accounts are within the network 
    {
        entry.followAccount(name); //then add the account to the vector of accounts the current account is following
        return true;
    }
    return false;
}

template<class ItemType>
bool Network<ItemType>::addToFeed(Post * const entry)
{
	if (getIndexOf(entry->getUsername()) != -1) //if the username of the post matches an index within the network
    {
		net_posts.insert(entry, 0); //insert the post into the linked list
		return true;
	}
	else
		return false;
}
/*
	can be called from account, and allows removing a post in the network linked list
*/
template<class ItemType>
void Network<ItemType>::removeHelper(Post* entry)
{
	int removed_ = net_posts.getIndexOf(entry); //gets index of the post
	if (removed_ != -1) //if its in the linked list
		net_posts.remove(removed_); //remove the post from the linked list
}

//////////////////////////////////////////////////////////////////////////////////////////////////
/*
    @param            :   A string (word or phrase, case-sensitive) passed by reference
    @return           :   The number of items removed from the list

    @post              :  Any Post that contains the provided word or phrase in it's title,
                          body or both is removed from the Network's `feed_` as well as
                          the Account's `posts_`.

    You are encouraged to create your own helper functions for this endeavour.
*/

template<class ItemType>
int Network<ItemType>::removeIfContains(std::string &entry)
{
	int removed_count = 0; //to return/keep track of removed posts
	Node<Post*> *curr_ptr = net_posts.getHeadPtr(); //gets the head pointer of the linked list
	while(curr_ptr != nullptr) //keeps looping til the end of the list
	{
		std::string temp_title = curr_ptr->getItem()->getTitle(); //gets the title of the curr post object that is being stored in the linked list
		std::string temp_body = curr_ptr->getItem()->getBody(); // gets the body of the curr post object that is being stored in the linked list
		if(temp_title.find(entry) != std::string::npos || temp_body.find(entry) != std::string::npos) //if the string that was passed was found in the curr post object
		{
			for(int i = 0; i < acct_count; i++) //find the account that made the post
			{
				if(items[i]->getUsername() == curr_ptr->getItem()->getUsername()) //if the username on the post object matches the username of the account
					items[i]->removePost(curr_ptr->getItem()); //then remove the post from the account post linked list
			}
			int index = net_posts.getIndexOf(curr_ptr->getItem()); //find the index of the post object within the linked list
			net_posts.remove(index); //remove the post object index from the linked list
			removed_count++; //add to the amount of posts removed
		}
		curr_ptr = curr_ptr->getNext(); //get the next node in the linked list
	}
	return removed_count;
}

template<class ItemType>
void Network<ItemType>:: moveHelper(Post* entry)
{
	net_posts.moveItemToTop(entry); //moves the post object that was passed to the top of the linked list
}
