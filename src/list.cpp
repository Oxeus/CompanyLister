/*****************************************************************************************
Program by: Adam LaFleur
Date: January 25, 2019
Class: CS163 - Data Structures
Program: #1
File: list.cpp
Purpose: The purpose of this program is to help the user create, organize, and search
for companies that are looking to hire entry level computer science positions
(or internships). list.cpp has the purpose of containing the algorithms that control the
adding to the list of jobs and to the list of locations, printing these lists, and deleting
a job from the jobLisg. Also there is an algorithm to delete a node from the job list, and 
another algorithm to edit the review at a specified job. Overall each functions returns a 1
for success and 0 for failure as error flags.
*****************************************************************************************/
#include "list.h"
#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>

//Only to be used for printing out data, no calling in
using namespace std;



//Initializes object, locHead is nullptr, also calls a function that adds from a file
list::list()
{
	locHead = nullptr;
	read();
}



//Function to read in data from a file and then sends the data in a struct object to addJob. Takes in input from data file, parses the like using | and '\n'
int list::read()
{
	info insert; //Defines struct data object
	ifstream inFile; //File variable
	char name[64], desc[64], qual[64], req[64], location[64], spec[64], pay[64], rating[64], review[64]; //Temp stores data from file
	
	inFile.open("data.txt");
	while(!inFile.eof() && inFile.getline(name, 64, '|')) //Runs until eof and stops running when a getline cant occur
	{
		inFile.getline(desc, 64, '|');
		inFile.getline(qual, 64, '|');
		inFile.getline(req, 64, '|');
		inFile.getline(location, 64, '|');
		inFile.getline(spec, 64, '|');
		inFile.getline(pay, 64, '|');
		inFile.getline(rating, 64, '|');
		inFile.getline(review, 64);
		insert.jobName = new char[strlen(name) + 1];
                strcpy(insert.jobName, name);
                insert.desc = new char[strlen(desc) + 1];
                strcpy(insert.desc, desc);
                insert.qual = new char[strlen(qual) + 1];
                strcpy(insert.qual, qual);
               	insert.req = new char[strlen(req) + 1];
             	strcpy(insert.req, req);
                insert.location = new char[strlen(location) + 1];
                strcpy(insert.location, location);
                insert.jobSpec = new char[strlen(spec) + 1];
                strcpy(insert.jobSpec, spec);
                insert.review = new char[strlen(review) + 1];
                strcpy(insert.review, review);
                insert.pay = atoi(pay);
                insert.rating = atoi(rating);
		addJob(insert);
	}
	inFile.close();
	return 1;
}



//deconstructs and deletes all data, makes a call to write which writes all the data to a file
list::~list(){
        write(); //call to write
        locNode * lCurr = locHead;
        locNode * lPtr = nullptr;
        jobNode * jCurr = nullptr;
        jobNode * jPtr = nullptr;
        
	while(lCurr)
        {
                jCurr = lCurr->jobHead;
                while(jCurr)
                {
                        delete [] jCurr->job.jobName;
                        delete [] jCurr->job.desc;
                        delete [] jCurr->job.qual;
                        delete [] jCurr->job.req;
                        delete [] jCurr->job.location;
                        delete [] jCurr->job.jobSpec;
                        delete [] jCurr->job.review;
                        jPtr = jCurr->next;
                        delete jCurr;
                        jCurr = jPtr;
                }
                lPtr = lCurr;
                lCurr = lCurr->next;
                delete [] lPtr->locName;
                delete lPtr;
        }
        lCurr = nullptr;
        locHead = nullptr;

}



//Writes out data to a data file seperating each field with a "|" to use for parsing during read
int list::write()
{
        int result = 0; //stores error info
        locNode * lCurr = locHead; //initialzie pointer for locNode
        jobNode * jCurr = nullptr; //initialize pointer for jobNode
        ofstream outFile; //initialize variable for file read
        
	outFile.open("data.txt");
        while(lCurr)
        {
                jCurr = lCurr->jobHead;
                while(jCurr)
                {
                        outFile << jCurr->job.jobName << "|" << jCurr->job.desc << "|" << jCurr->job.qual << "|" << jCurr->job.req << "|" << jCurr->job.location << "|" << jCurr->job.jobSpec << "|" << jCurr->job.pay << "|" <<  jCurr->job.rating << "|" << jCurr->job.review << endl;
                        jCurr = jCurr->next;
                }
                lCurr = lCurr->next;
                result = 1;
        }
        outFile.close();
        return result;
}



//Function for adding a location to the location list, and initializing jobHead and the new location. The functions
//are added to the list in alphabetic order. Takes in only one argument: location, which is used to create a new location
//node, also location is sent to the find function which checks if the location is in the list
int list::addLocation(const char * location)
{
	int result = 0; //Variable to control return value for success or failure
	locNode * curr = nullptr; //Initializes empty locNode pointer curr to null
	locNode * newNode = nullptr; //Initializes empty locNode pointer newNode to null
	locNode * prev = nullptr;
	
        if(findRec(locHead, location) == 0) //Checks if object is in list
	{
		//Create Node for location given by user or data file
		newNode = new locNode;
		newNode->locName = new char[strlen(location) + 1];
		strcpy(newNode->locName, location);
		newNode->jobHead = nullptr;
		newNode->next = nullptr;

		//If head is NULL, empty list, set newNode as head
		if(!locHead)
		{
			locHead = newNode;
		}
		//If node to insert has content that can go before head, special case for resetting head value
                else if(strcmp(locHead->locName, newNode->locName) > 0)
                {
			newNode->next = locHead;
			locHead = newNode;
		}
		else
		{
			curr = locHead;
			prev = nullptr;
			//Traverse through list until value in curr is greater than value in newNode
			while(curr && strcmp(curr->locName, newNode->locName) < 0)
			{
				prev = curr;
				curr = curr->next;
			}
			newNode->next = curr;
			prev->next = newNode;
		}
		result = 1;
	}
	return result;
}



//Recursive function that searches for a location, if found: then return 1, if not return 0. Takes in a locNode, and location
//then looks for the location by traversing through the list
int list::findRec(locNode * curr, const char * location)
{
	if(curr == nullptr)
	{
		return 0;
	}
	else if(strcmp(curr->locName, location) == 0)
	{
		return 1;
	}
	return findRec(curr->next, location);
}



//Function to add a job to the ADT. Calls a function to add the location to the list,
int list::addJob(info & insert)
{
	int result = 0; //Controls error flags
	locNode * ptr = nullptr; //Pointer to hold current pointer to locNode
	jobNode * newNode = nullptr; //Pointer to a newNode
	jobNode * curr = nullptr; //Pointer to hold current pointer to locNode
	jobNode * prev = nullptr;
	//Will add location to list, if location is not there nothing happens, otherwise the lcoation is added to the sorted list
	
	addLocation(insert.location);

	//Creation of jobNode
	newNode = new jobNode;
	//jobName
	newNode->job.jobName = new char[strlen(insert.jobName) + 1];
	strcpy(newNode->job.jobName, insert.jobName);
	delete [] insert.jobName;
	//desc
	newNode->job.desc = new char[strlen(insert.desc) + 1];
	strcpy(newNode->job.desc, insert.desc);
	delete [] insert.desc;
	//qual
	newNode->job.qual = new char[strlen(insert.qual) + 1];
        strcpy(newNode->job.qual, insert.qual);
        delete [] insert.qual;
	//req
	newNode->job.req = new char[strlen(insert.req) + 1];
        strcpy(newNode->job.req, insert.req);
        delete [] insert.req;
	//location
	newNode->job.location = new char[strlen(insert.location) + 1];
        strcpy(newNode->job.location, insert.location);
        delete [] insert.location;
	//jobSpec
	newNode->job.jobSpec = new char[strlen(insert.jobSpec) + 1];
        strcpy(newNode->job.jobSpec, insert.jobSpec);
        delete [] insert.jobSpec;
	//review
	newNode->job.review = new char[strlen(insert.review) + 1];
        strcpy(newNode->job.review, insert.review);
        delete [] insert.review;
	newNode->job.pay = insert.pay;
	newNode->job.rating = insert.rating;
	newNode->next = nullptr;
	
	ptr = locHead;
	while(ptr)
	{
		if(strcmp(ptr->locName, newNode->job.location) == 0)
		{;
			curr = nullptr;
			//Does same job as adding location to the list
			if(!ptr->jobHead)
			{
				ptr->jobHead = newNode;
			}
			else if(strcmp(ptr->jobHead->job.jobName, newNode->job.jobName) > 0)
			{
				newNode->next = ptr->jobHead;
				ptr->jobHead = newNode;
			}
			else
			{
				prev = nullptr;
				curr = ptr->jobHead;
				while(curr && strcmp(curr->job.jobName, newNode->job.jobName) <= 0)
				{
					prev = curr;
					curr = curr->next;
				}
				newNode->next = curr;
				prev->next = newNode;
			}
			result = 1;
		}
		ptr = ptr->next;
	}
	return result;
}



//Function that allows the editing of review data. Takes in a location, name, and review as an argument. Uses location to search the locList and name to search the jobList, if the job was found then the review field is deleted from the job and the new review is allocated and 
//copied over
int list::editJob(const char * location, const char * name, const char * review)
{
	int result = 0; //stores error state
	locNode * curr = locHead; //Initializes pointer to location head
	jobNode * jCurr = nullptr; //Initialize job pointer
	
	while(curr)
	{
		if(strcmp(curr->locName, location) == 0)
		{
			jCurr = curr->jobHead;
			while(jCurr)
			{
				if(strcmp(jCurr->job.jobName, name) == 0)
				{
					delete [] jCurr->job.review;
					jCurr->job.review = new char[strlen(review) + 1];
					strcpy(jCurr->job.review, review);
					result = 1;
				}
				jCurr = jCurr->next;
			}
		}
		curr = curr->next;
	}
	return result;
}



//Function to delete a node. Takes in a location and name as arguments, location is used to search the locList and name is used to search the jobList. Deletes the node if found.
int list::removeJob(const char * location, const char * name)
{
	int result = 0; //stores error state
	locNode * lCurr = locHead; //Initializes pointer to null
	jobNode * jPtr = nullptr; //Initializes pointer to null
	jobNode * jPrev = nullptr; //Initializes pointer to null
	jobNode * jCurr = nullptr; //Initializes pointer to null
	
	while(lCurr)
	{
		if(strcmp(lCurr->locName, location) == 0)
		{
			jCurr = lCurr->jobHead;
			while(jCurr)
			{
				if(strcmp(jCurr->job.jobName, name) == 0)
				{
					delete [] jCurr->job.jobName;
					delete [] jCurr->job.desc;
					delete [] jCurr->job.qual;
					delete [] jCurr->job.req;
					delete [] jCurr->job.location;
					delete [] jCurr->job.jobSpec;
					delete [] jCurr->job.review;
					//If jCurr is jobHead, then record address for head then next the next node as head, then delete head
					if(jCurr == lCurr->jobHead)
					{
						jPtr = lCurr->jobHead;
						lCurr->jobHead = lCurr->jobHead->next;
						delete jPtr;
					}
					//Otherwise record address for jCurr, then set previous next to the node after jCurr, then delete node
					else
					{
						jPtr = jCurr;
						jPrev->next = jCurr->next;
						delete jPtr;
					}
					result = 1;
				}
				jPrev = jCurr; //Record previous node info
				jCurr = jCurr->next;
			}
		}
		lCurr = lCurr->next;
	}
	return result;
}



//Prints only jobs at specified location, takes location in as an argument, and outputs the jobList.
int list::printLocation(const char * location)
{
	int result = 0; //stores error state
	locNode * lCurr = locHead; //Pointer used to hold current locList node
	jobNode * jCurr = nullptr; //Pointer used to hold current jobList node
	
	while(lCurr)
	{
		if(strcmp(lCurr->locName, location) == 0)
		{
			cout << "----------------------------------------------" << endl;
			cout << "Location: " << lCurr->locName << endl;
			cout << "----------------------------------------------" << endl;
			jCurr = lCurr->jobHead;
			while(jCurr)
			{
				cout << "Company Name: " << jCurr->job.jobName << endl;
                                cout << "Job Description: " << jCurr->job.desc << endl;
                                cout << "Job Qualifications: " << jCurr->job.qual << endl;
                                cout << "Job Requirements: " << jCurr->job.req << endl;
                                cout << "Job Location: " << jCurr->job.location << endl;
                                cout << "Job Specifications: " << jCurr->job.jobSpec << endl;
                                cout << "Pay: $" << fixed << setprecision(2) << jCurr->job.pay << endl;
                                cout << "Rating: " << jCurr->job.rating << endl;
                                cout << "Review: " << jCurr->job.review << endl;
				cout << "----------------------------------------------" << endl;
				jCurr = jCurr->next;
			}
			result = 1;
		}
		lCurr = lCurr->next;
	}
	return result;
}



//Function that prints out jobs at all locations, outputs jobs. 
int list::printAll()
{
	int result = 0; //stores error state
	jobNode * jCurr = nullptr; //initializes jobNode pointer
	locNode * lCurr = locHead; //Initializes locNode pointer
	
	while(lCurr != nullptr)
	{
		cout << "----------------------------------------------" << endl;
		cout << "Location: " << lCurr->locName << endl;
		cout << "----------------------------------------------" << endl;
		jCurr = lCurr->jobHead;
		while(jCurr)
		{
			cout << "Company Name: " << jCurr->job.jobName << endl;
			cout << "Job Description: " << jCurr->job.desc << endl;
			cout << "Job Qualifications: " << jCurr->job.qual << endl;
			cout << "Job Requirements: " << jCurr->job.req << endl;
			cout << "Job Location: " << jCurr->job.location << endl;
			cout << "Job Specifications: " << jCurr->job.jobSpec << endl;
			cout << "Pay: $" << jCurr->job.pay << endl;
			cout << "Rating: " << jCurr->job.rating << endl;
			cout << "Review: " << jCurr->job.review << endl;
			cout << "----------------------------------------------" << endl;
			jCurr = jCurr->next;
		}
		if(lCurr->next != nullptr)
		{
			cout << endl;
		}
		lCurr = lCurr->next;
		result = 1;
	}
	return result;
}
