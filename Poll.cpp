// Jacob Martin
// 9/23/2022
// Poll.cpp
// Project 2 - create poll class that lets user interact with a poll post

#include "Poll.hpp"

Poll::Poll(std::string p_post, std::string p_quest, std::string p_acct, std::vector<std::string> opts) : Post(p_post, p_quest, p_acct) //constructor being passed to parent class constructor
{
	for (int i = 0; i < opts.size(); i++) //filling vector with the parameter that was given, and assigning the votes vector to 0, giving the vectors the same size
	{
		poll_opts.push_back(opts[i]);
		num_votes.push_back(0);
	}
}

bool Poll::votePoll(const int& num)
{
	bool final = false;
	if (num >= 0 && num < poll_opts.size()) //checking if parameter given was a valid input
	{
		num_votes[num] = num_votes[num]+1; //if valid then give the corresponding index a vote
		final = true;
	}
	return final;
}

void Poll::changePollOption(const std::string& opt, const int& index)
{
	if (index >= poll_opts.size()) //checking if parameter is within the vector and is a vote
	{
		poll_opts.push_back(opt); //if it is not in the vector, then adding parameter to the back of the vector
		num_votes.push_back(0); // and giving votes vector an addition index for the votes for the new poll option
	}
	else
	{
		poll_opts[index] = opt; //if it is in the vector then changing what is currently indexed to the new parameter
		num_votes[index] = 0; //resetting the votes at the index back to 0
	}
}

void Poll::getPollOptions() const
{
	for (int i = 0; i < poll_opts.size(); i++) //cycling through the vectors and printing the num of votes and what option it is
	{
		std::cout << num_votes[i] << " votes for: " << poll_opts[i] << std::endl;
	}
}

int Poll::getPollVotes(const int& num) //returning the num of votes for a certain poll option at the index given
{
	return num_votes[num];
}

/*
	Make the Post class abstract by making the displayPost function virtual, 
	where the implementation only lies within its children classes. 
	Make the necessary updates in the Poll, Promotional, and General classes.
*/
void Poll::displayPost() const //printing poll class in the format that was given
{
	std::cout << std::endl << getTitle() << " at ";
	getTimeStamp();
	std::cout << getBody() << std::endl;	
	getPollOptions();
	//std::cout << std::endl;
}
