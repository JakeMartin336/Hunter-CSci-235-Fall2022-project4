// Jacob Martin
// 9/23/2022
// General.cpp
// Project 2 - create general class that lets user react to a post

#include "General.hpp"

General::General(std::string g_name, std::string g_body, std::string g_acct) : 	Post(g_name, g_body, g_acct) //constructor
{
	for (int i = 0; i < 6; i++) //assigning all values in array to 0
	{
		arr[i] = 0;
	}
}

bool General::reactToPost(const Reactions& react)
{
	if (react < 6) //test the input given and if its valid then add a vote to the array
	{
        arr[react] += 1;
        return true;
    }
    return false;
}

void General::getReactions() const
{
	//going through entire array and printing out the values stored
	std::vector<std::string> temp = {"Like", "Dislike", "Laugh", "Wow", "Sad", "Angry"};
    for(int i = 0; i < 5 ; i++) 
        std::cout << temp[i] << " : " << arr[i] << " | ";
    std::cout << temp[5] << " : " << arr[5] << std::endl;
}

/*
	Make the Post class abstract by making the displayPost function virtual, 
	where the implementation only lies within its children classes. 
	Make the necessary updates in the Poll, Promotional, and General classes.
*/
void General::displayPost() const //print display in format assigned
{
	std::cout << std::endl << getTitle() << " at ";
	getTimeStamp();
	std::cout << getBody() << std::endl;
	getReactions();
}
