// Jacob Martin
// 9/23/2022
// Promotional.cpp
// Project 2 - create promotional class that lets user create a post with a valid link

#include "Promotional.hpp"

Promotional::Promotional(std::string p_name, std::string p_body, std::string p_acct, std::string link) : Post(p_name, p_body, p_acct) //passing constructor to the parent class constructor
{
	setLink(link); //passing url parameter to the setLink method to check if the parameter is valid
}

std::string Promotional::getLink() const
{
	return url; //returning data member
}

bool Promotional::setLink(const std::string& link)
{
	//const std::regex reg("^(http[s]?:\/\/www\.)[a-zA-Z0-9]+\.[a-z]{2,}$");
	const std::regex reg("((http|https)://)(www.)[a-zA-Z0-9@:%._\\+~#?&//=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%._\\+~#?&//=]*)");
    if (regex_match(link,reg) == true) //if it matches then assign parameter to url data member and return true
	{
        url = link;
        return true;
    }
	else //if it doesnt match then return false and set the link to a broken link
	{
    	url = "Broken link";
    	return false;
	}
}

/*
	Make the Post class abstract by making the displayPost function virtual, 
	where the implementation only lies within its children classes. 
	Make the necessary updates in the Poll, Promotional, and General classes.
*/
void Promotional::displayPost() const //printing Promotional class in the format that was assigned
{
	std::cout << std::endl << getTitle() << " at ";
	getTimeStamp();
	std::cout << getBody() << std::endl;
	std::cout << getLink() << std::endl;
}
