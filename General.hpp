// Jacob Martin
// 9/23/2022
// General.cpp
// Project 2 - create general class that lets user react to a post

#ifndef _GENERAL_
#define _GENERAL_

#include "Post.hpp"
#include<iostream>
#include<string>
#include<vector>

enum Reactions { LIKE, DISLIKE, LAUGH, WOW, SAD, ANGRY };

class General : public Post
{
public:
	General(std::string g_name, std::string g_body, std::string g_acct);
	bool reactToPost(const Reactions& react);
	void getReactions() const;
	virtual void displayPost() const override; //overriding the pure virtual function
private:
	int arr[6];
};
#endif
