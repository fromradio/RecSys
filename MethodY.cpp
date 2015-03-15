#include "MethodY.h"

Action::Action(int ui,int ii,double s)
	:
	__user_id(ui),
	__item_id(ii),
	__score(s)
{

}

int Action::userID() const
{
	return __user_id;
}

int Action::itemID() const
{
	return __item_id;
}

double Action::score() const
{
	return __score;
}

Item::Item()
	:
	__id(-1),
	__id_set(false)
{
}

Item::Item(int id)
	:
	__id(id),
	__id_set(true)
{
}

void Item::setID(int id)
{
	if(__id_set)
	{
		std::cerr<<"Error, id has been set!"<<std::endl;
		return;
	}
	else
	{
		__id = id;
		__id_set = true;
	}
}

bool Item::idSet() const
{
	return __id_set;
}

User::User()
	:
	__id(-1),
	__id_set(false)
{

}

User::User(int id)
	:
	__id(id),
	__id_set(true)
{
}

void User::setID(int id)
{
	if(__id_set){
		std::cerr<<"Error, id has been set!"<<std::endl;
		return;
	}
	else
	{
		__id = id;
		__id_set = true;
	}
}

bool User::idSet() const
{
	return __id_set;
}

std::list<int>& User::items()
{
	return __items;
}


void firstRoundReadFile(const std::string& filename,int num,std::list<Action>& actions)
{
	actions.clear();
	std::ifstream fin(filename);
	std::set<int> item_ids;
	int i=0;
	while(fin)
	{
		int ui,// user id
		    ii;// item id
		double s; // score
		if(!(fin>>ui)) break;
		if(!(fin>>ii)) break;
		if(!(fin>>s)) break;
		for(int t= 3;t<num;++t)
		{
			int temp;
			if(!(fin>>temp)) break;
		}
		++i;
		actions.push_back(Action(ui,ii,s));
	}
}

void constructUser(const std::list<Action>& acts,std::vector<User>& users,std::map<int,int>& idmap)
{
	idmap.clear();
	int i = 0;
	for (auto a = acts.begin();a!=acts.end();++a)
	{
		if(idmap.find(a->userID())==idmap.end())
		{
			idmap[a->userID()]=i++;
		}
	}
	users.clear();
	users.resize(idmap.size());
	for(auto a=acts.begin();a!=acts.end();++a)
	{
		User& u=users[idmap[a->userID()]];
		if(!u.idSet())
			u.setID(a->userID());
		u.items().push_back(a->itemID());
	}
}


void constructItem(const std::list<Action>& acts,std::vector<Item>& items,std::map<int,int>& idmap)
{
	idmap.clear();
	int i = 0;
	for (auto a = acts.begin();a!=acts.end();++a)
	{
		if(idmap.find(a->itemID())==idmap.end())
		{
			idmap[a->itemID()]=i++;
		}
	}
	items.clear();
	items.resize(idmap.size());
	for(auto a=acts.begin();a!=acts.end();++a)
	{
		Item& item=items[idmap[a->itemID()]];
		if(!item.idSet())
			item.setID(a->userID());
	}
	// std::cout<<users.size()<<std::endl;
}

void fixItems( std::vector<User>& users,const std::vector<Item>& items,const std::map<int,int>& itemmap)
{
	for (auto user = users.begin();user!=users.end();++user)
	{
		for(auto i=user->items().begin();i!=user->items().end();++i)
		{
			(*i)=itemmap.at(*i);
		}
	}
	std::cout<<"here"<<std::endl;
}

void computeCoVisitation(const std::vector<User>& users, std::vector<Item>& items)
{
	for(auto user = users.begin(); user!= users.end() ; ++ user)
	{
		for(auto i=user->items().begin();i!=user->items().end();++i)
		{
			for(auto j=user->items().begin();j!=user->items().end();++j)
			{
				if((*i)==(*j))
				{
					items[*i].counts()++;
				}
				else
				{
					if(items[*i].coCounts().find(*j)!=items[*i].coCounts().end())
						items[*i].coCounts()[*j]++;
					else
						items[*i].coCounts()[*j]=1;
				}
			}
		}
	}
}