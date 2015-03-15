#ifndef METHODY_H
#define METHODY_H

#include <string>
#include <fstream>
#include <iostream>
#include <list>
#include <vector>
#include <set>
#include <map>

class Action
{
private:
	int 						__user_id;
	int 						__item_id;
	double 						__score;
public:
	Action(int ui,int ii,double s);
	int userID() const;
	int itemID() const;
	double score() const;
};

class Item
{
private:
	int 						__id; 			// the id of the item
	int 						__counts; 		// the number that the item is visited
	std::vector<int> 			__r_scores; 	// the co-visitation 
	bool 						__id_set;
	std::map<int,int> 			__co_counts;
public:
	Item();
	Item(int id);
	void setID(int id);
	bool idSet() const;
	int id() const{return __id;}
	int& counts(){return __counts;}
	std::map<int,int>& coCounts(){return __co_counts;}
};


// Item matrix stores the related information
class ItemMatrix
{
private:
	std::map<int,std::map<int,double> >			__mat;
};

class User
{
private:
	int 						__id;
	int 						__counts;
	std::list<int> 				__items;
	bool 						__id_set;
public:
	User();
	User(int id);
	std::list<int>& items();
	const std::list<int>& items() const{return __items;}
	void setID(int id);
	bool idSet() const;
};

void firstRoundReadFile(const std::string& filename,
	int num, // the number of elements in a row
	std::list<Action>& actions);

void constructUser(const std::list<Action>& acts, std::vector<User> &users, std::map<int,int>& idmap);
void constructItem(const std::list<Action>& acts, std::vector<Item> &items, std::map<int,int>& idmap);

void fixItems( std::vector<User>& users,const std::vector<Item>& items,const std::map<int,int>& itemmap);

void computeCoVisitation(const std::vector<User>& users, std::vector<Item>& items);



#endif