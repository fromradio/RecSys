#ifndef ITEM_CF_HPP__
#define ITEM_CF_HPP__

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <sstream>
#include <cmath>
#include <set>
#include <list>

inline void readTrainData(const std::string& filename,std::vector<std::vector<std::pair<int,double> > >& sortedscore,std::vector<std::set<int> >& vitems)
{
	std::vector<std::map<int,double> > score;
	std::string line;
	std::fstream infile(filename);
	int curruser = -1;
	std::list<int> itemlist;
	// get the number of items
	int numitem = -1;
	int numuser = -1;
	int user,item;
	while(std::getline(infile,line))
	{
		std::istringstream iss(line);
		iss>>user>>item;
		if(item>numitem)
			numitem=item;
		if(user>numuser)
			numuser = user;
	}
	score.clear();
	score.resize(numitem+1);
	vitems.resize(numuser+1);
	infile.close();
	infile.open(filename);
	std::vector<double> itempop(numitem+1,0.0);
	while(std::getline(infile,line))
	{
		std::istringstream iss(line);
		
		iss>>user>>item;
		if(curruser!=user)
		{
			// handle current list
			for(auto i:itemlist)
			{
				for(auto j:itemlist)
				{
					if(i!=j)
					{
						if(score[i].find(j)==score[i].end())
						{
							// score[i][j]=1.0/(log(1.0+itemlist.size()));
							score[i][j]=1;
						}
						else{
							score[i][j]+=1;
							// score[i][j]+=1.0/(log(1.0+itemlist.size()));;
						}
					}
				}
				itempop[i]+=1.0;
			}
			// new user, clear former list
			itemlist.clear();
			itemlist.push_back(item);
			curruser = user;
		}
		else
		{
			itemlist.push_back(item);
			vitems[user].insert(item);
		}
	}
	for(auto i:itemlist)
	{
		for(auto j:itemlist)
		{
			if(i!=j)
			{
				if(score[i].find(j)==score[i].end())
				{
					score[i][j]=1;
				}
				else{
					score[i][j]+=1;
				}
			}
		}
	}
	int ind = 0;

	sortedscore.resize(numitem+1);

	auto cmp = [](std::pair<int,double> const & a, std::pair<int,double> const & b) 
	{ 
		return a.second>b.second;
	};
	for(auto im = score.begin() ; im != score.end() ; ++ im )
	{
		sortedscore[ind].reserve(im->size());
		for ( auto s = im->begin() ; s != im->end() ; ++ s )
		{
			// |N(i)&N(j)|/sqrt(|N(i)*N(j)|)
			s->second = s->second/std::sqrt(itempop[ind]*itempop[s->first]);

			sortedscore[ind].push_back(*s);
		}
		std::sort(sortedscore[ind].begin(),sortedscore[ind].end(),cmp);
		++ ind;
	}
}

void writeScore(const std::string& filename, const std::vector<std::vector<std::pair<int,double> > >& score,int cutoff = -1)
{
	std::ofstream fout(filename);
	int ind = 0;
	fout<<score.size()<<std::endl;
	for (auto item = score.begin(); item != score.end() ; ++ item)
	{
		fout<<"# "<<ind<<' '<<item->size()<<std::endl;
		if ( cutoff == -1 )
		{
			for (auto s = item->begin(); s != item->end() ; ++ s)
			{
				fout<<s->first<<" "<<s->second<<std::endl;
			}
		}
		else
		{
			int size = std::min(cutoff,static_cast<int>(item->size()));
			for ( int i = 0 ; i < size ; ++ i )
			{
				fout<<item->at(i).first<<' '<<item->at(i).second<<std::endl;
			}
		}
		++ ind;
	}
}

void readScore(const std::string& filename, std::vector<std::vector<std::pair<int,double> > >& score)
{
	std::ifstream fin(filename);
	int size;
	fin>>size;
	score.resize(size);
	std::string line;
	int curritem = 0;
	while(std::getline(fin,line))
	{
		if(line[0]=='#')
		{
			std::istringstream iss(line);
			char c;
			int item,isize;
			iss>>c>>item>>isize;
			score[item].reserve(isize);
			curritem = item;
		}
		else
		{
			std::istringstream iss(line);
			int ind;
			double s;
			iss>>ind>>s;
			score[curritem].push_back(std::pair<int,double>(ind,s));
		}
	}
}

void readTestData(const std::string& filename, std::vector<std::set<int> >& vitems )
{
	std::string line;
	std::fstream infile(filename);
	int numuser = -1;
	int user,item;
	while(std::getline(infile,line))
	{
		std::istringstream iss(line);
		iss>>user>>item;
		if(user>numuser)
			numuser = user;
	}
	infile.close();
	infile.open(filename);
	vitems.resize(numuser+1);
	while(std::getline(infile,line))
	{
		std::istringstream iss(line);
		iss>>user>>item;
		vitems[user].insert(item);
	}
}

void recommendation(
	const std::vector<std::set<int> >& vitems, 
	const std::vector<std::vector<std::pair<int,double> > >& score, 
	int user,
	int k, 
	int cutoff,
	std::set<int>& rec)
{
	std::map<int,double> rank;
	for(auto item = vitems[user].begin() ; item != vitems[user].end() ; ++ item)
	{
		for(int i = 0 ; i < k ; ++ i )
		{
			// get the neighborhood
			int ind = score[*item][i].first;
			if(vitems[user].find(ind)==vitems[user].end())
			{
				if(rank.find(ind)==rank.end())
					rank[ind]=score[*item][i].second;
				else
					rank[ind]+=score[*item][i].second;
			}
		}
	}
	std::vector<std::pair<int,double> > vrank;
	vrank.reserve(rank.size());
	for(auto r = rank.begin() ; r != rank.end() ; ++ r)
	{
		vrank.push_back(*r);
	}
	auto cmp = [](std::pair<int,double> const & a, std::pair<int,double> const & b) 
	{ 
		return a.second>b.second;
	};
	std::sort(vrank.begin(),vrank.end(),cmp);
	int s = std::min(static_cast<int>(vrank.size()),cutoff);
	for(int i=0; i<s; ++i)
	{
		rec.insert(vrank[i].first);
	}
}

double precision(const std::set<int>& rec,
	const std::set<int>& truth)
{
	std::vector<int> inter;
	std::set_intersection(rec.begin(),rec.end(),truth.begin(),truth.end(),std::back_inserter(inter));
	if (rec.size()==0)
		return 1.0;
	return static_cast<double>(inter.size())/rec.size();
}

double recall(const std::set<int>& rec,
	const std::set<int>& truth)
{
	std::vector<int> inter;
	std::set_intersection(rec.begin(),rec.end(),truth.begin(),truth.end(),std::back_inserter(inter));
	if(truth.size()==0)
		return 1.0;
	return static_cast<double>(inter.size())/truth.size();
}

void testRecommendation(const std::vector<std::set<int> >& vitems,
	const std::vector<std::set<int> >& testitems,
	const std::vector<std::vector<std::pair<int,double> > >& score,
	int k, 
	int cutoff
	)
{
	double mean_precision = 0.0;
	double mean_recall = 0.0;
	std::cout<<"there are "<<testitems.size()<<" test users"<<std::endl;
	for ( int i = 0 ; i < testitems.size() ; ++ i )
	{
		std::set<int> rec;
		recommendation(vitems,score,i,k,cutoff,rec);
		mean_precision += precision(rec,testitems[i]);
		mean_recall += recall(rec,testitems[i]);
		if(i%1000==0)
			std::cout<<i<<" users are done"<<std::endl;
	}
	mean_precision/=testitems.size();
	mean_recall/=testitems.size();
	std::cout<<"mean_precision is "<<mean_precision<<std::endl;
	std::cout<<"mean_recall is "<<mean_recall<<std::endl;
}


#endif