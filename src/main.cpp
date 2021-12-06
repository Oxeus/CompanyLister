/*****************************************************************************************
Program by: Adam LaFleur
Date: January 25, 2019
Class: CS163 - Data Structures
Program: #1
File: main.cpp
Purpose: The purpose of this program is to help the user create, organize, and search 
for companies that are looking to hire entry level computer science positions 
(or internships). main.cpp has the purpose of controlling the program and inputting data
to be sent to the ADT
*****************************************************************************************/
#include <iostream>
#include <cstring>
#include "list.h"

using namespace std;

void status(int num);



/*The purpose of main is the initialize and run the program, main has a menu that gives the user an
 * option of what they want to do, the menu repeats until the user specifices when to stop. The 
 * main program also creates a struct info, fills it, and then sends it to the adt, when addJob is
 * specified. The user is given the options of adding a job, adding a new location, editing a job 
 * review, displaying all jobs for an entered location, displaying all jobs for all locations, removing
 * a job, and finally quitting the program. */
int main()
{
	list jobs; //Initialize ADT
	info insert; //Initialize info data struct
	int choice = 0, num = 0; //choice used to control which menu option selected, num is used to record ADT return values
	bool control = true; //Controls whether the program loops or not
	char name[64], desc[64], qual[64], req[64], location[64],spec[64], review[64]; //Used to temporarily store user input until allocated and copied into the info struct
	double pay = 0.0, rating = 0.0; //Same as above

	cout << "----------------------------------------------" << endl;
        cout << "********** Program #1: Job Listings **********" << endl;
        cout << "----------------------------------------------" << endl;
	while(control)
	{
		cout << "Please choose an option: " << endl;
		cout << "01. Add a Job Entry." << endl;
		cout << "02. Add a new location." << endl;
		cout << "03. Edit a Job Review." << endl;
		cout << "04. Display all jobs for entered location." << endl;
		cout << "05. Display all jobs for all locations." << endl;
		cout << "06. Remove a job." << endl;
		cout << "07. Quit the client program." << endl;
		cout << "----------------------------------------------" << endl;
		cout << "Please enter a choice: ";
		cin >> choice;
		cin.ignore();
		cout << endl;
		switch(choice)
		{
			case 1:
				cout << "Please enter company name: ";
				cin.getline(name, sizeof(name));
				cout << "Please enter job description: ";
				cin.getline(desc, sizeof(desc));
				cout << "Please enter job qualifications: ";
				cin.getline(qual, sizeof(qual));
				cout << "Please enter job requirements: ";
				cin.getline(req, sizeof(req));
				cout << "Please enter job location: ";
				cin.getline(location, sizeof(location));
				cout << "Please enter job specifications: ";
				cin.getline(spec, sizeof(spec));
				cout << "Please enter job review: ";
				cin.getline(review, sizeof(review));
				cout << "Please enter pay: ";
				cin >> pay;
				cout << "Please enter job rating: ";
				cin >> rating;
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
				insert.pay = pay;
				insert.rating = rating;
				num = jobs.addJob(insert);
				status(num);
				break;
			case 2:
				cout << "Please enter a location: ";
				cin.getline(location, sizeof(location));
				num = jobs.addLocation(location);
				status(num);
				break;
			case 3:
				cout << "Where is the job located: ";
				cin.getline(location, sizeof(location));
				cout << "What is the name of the company: ";
				cin.getline(name, sizeof(name));
				cout << "What is the new review: ";
				cin.getline(review, sizeof(review));
				num = jobs.editJob(location, name, review);
				status(num);
				break;
			case 4:
				cout << "Please enter a location to find: ";
				cin.getline(location, sizeof(location));
				cout << endl;
				num = jobs.printLocation(location);
				status(num);
				break;
			case 5:
				num = jobs.printAll();
				status(num);
				break;
			case 6:
				cout << "Where is the job located (delete): ";
				cin.getline(location, sizeof(location));
				cout << "What is the name of the company (delete): ";
				cin.getline(name, sizeof(name));
				num = jobs.removeJob(location, name);
				status(num);
				break;
			case 7:
				control = false;
				break;
			default:
				cout << "Incorrect choice, please try again." << endl;
				break;
		}
	}
	return 0;
}



/* The prupose of status is to display whether the action succeded or not. Status takes in
 * an argument int num which is supplied from main, if the number supplied is 0 then
 * Failure will be printed out, if 1 is supplied then Success will be printed out.*/
void status(int num)
{
	cout << endl;
	cout << "Status: ";
	if(num == 0)
	{
		cout << "Failure" << endl;
	}
	else
	{
		cout << "Success" << endl;
	}
	cout << endl;
}
