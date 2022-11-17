// Jacob Martin
// 9/23/2022
// Promotional.hpp
// Project 2 - create promotional class that lets user create a post with a valid link

#ifndef _PROMOTIONAL_
#define _PROMOTIONAL_

#include"Post.hpp"
#include<iostream>
#include<string>
#include<regex>

class Promotional : public Post
{
public:
	Promotional(std::string p_name, std::string p_body, std::string p_acct, std::string link);
	std::string getLink() const;
	bool setLink(const std::string& link);
	virtual void displayPost() const override; //overriding the pure virtual function
private:
	std::string url;
};
#endif
