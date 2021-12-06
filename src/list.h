/*****************************************************************************************
Program by: Adam LaFleur
Date: January 25, 2019
Class: CS163 - Data Structures
Program: #1
File: list.h
Purpose: The purpose of this program is to help the user create, organize, and search
for companies that are looking to hire entry level computer science positions
(or internships). list.h defines the ADT structure, also defines the struct info. 
*****************************************************************************************/



//Data struct that will hold all data, the declaration is outside the class so main can access and fill it to pass in through functions
struct info {
	char * jobName; //Holds title of company
	char * desc; //Holds description of job
	char * qual; //Holds qualifications needed
	char * req; //Holds job requirements
	char * location; //Holds job location
	char * jobSpec; //Holds job specifications
	double pay; //Holds pay amount
	double rating; //Holds job rating
	char * review; //Holds job review
};



class list
{
	public:
		list();
		~list();
		int addLocation(const char * location);
		int addJob(info & insert);
		int editJob(const char * location, const char * name, const char * review);
		int removeJob(const char * location, const char * name);;
		int printLocation(const char * location);
		int printAll();
	private:
		struct jobNode {
			info job;
			jobNode * next;
		}; //Defines job node, contains: info job data memeber, and next pointer the the next jobNode

		struct locNode {
			char * locName;
			locNode * next;
			jobNode * jobHead;
		}; //Defines locNode, contains: locaition name, next pointer to next locNode, and head node for Job List

		locNode * locHead; //Defines overall head of the ADT;

		int find(const char * location);
		int findRec(locNode * locHead, const char * location);
		int read();
		int write();
};
