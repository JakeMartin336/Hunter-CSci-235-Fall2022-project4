// Jacob Martin
// 9/23/2022
// Poll.hpp
// Project 2 - create poll class that lets user interact with a poll post

#ifndef _POLL_
#define _POLL_

#include "Post.hpp"
#include <iostream>
#include <vector>
#include<string>

class Poll : public Post
{
public:
	Poll(std::string p_post, std::string p_quest, std::string p_acct,std::vector<std::string> opts);
	bool votePoll(const int& num);
	void changePollOption(const std::string& opt, const int& index);
	void getPollOptions() const;
	int getPollVotes(const int& num);
	virtual void displayPost() const override; //overriding the pure virtual function
private:
	std::vector<std::string> poll_opts;
	std::vector<int> num_votes;
};

#endif
