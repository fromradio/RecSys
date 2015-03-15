#include "MethodY.h"
#include "itemcf.h"
// #include <boost/iostreams/device/mapped_file.hpp>

int main(int argc,char *argv[])
{
	std::vector<std::vector<std::pair<int,double> > >score;
	std::vector<std::set<int> > trainuitems;
	// readTrainData("50_train.csv",score,trainuitems);
	// std::cout<<score.size()<<std::endl;
	// int ind = 0;
	// for (auto i = score.begin(); i != score.end() ; ++ i)
	// {
	// 	std::cout<<ind<<" user"<<std::endl;
	// 	for (auto k=i->begin();k!=i->end();++k)
	// 	{
	// 		std::cout<<k->first<<' '<<k->second<<std::endl;
	// 	}
	// 	++ind;
	// }
	readScore("50_new_score",score);
	// int ind = 0;
	// for (auto i = score.begin(); i != score.end() ; ++ i)
	// {
	// 	std::cout<<ind<<" user"<<std::endl;
	// 	for (auto k=i->begin();k!=i->end();++k)
	// 	{
	// 		std::cout<<k->first<<' '<<k->second<<std::endl;
	// 	}
	// 	++ind;
	// }

	std::vector<std::set<int> > testuitems;
	readTestData("50_test.csv",testuitems);
	readTestData("50_train.csv",trainuitems);
	std::cout<<"start recommendation"<<std::endl;
	testRecommendation(trainuitems,testuitems,score,20,20);
	// for (auto i = 0 ; i < testuitems.size() ; ++ i )
	// {
	// 	std::cout<<i<<" user "<<std::endl;
	// 	for (auto item = testuitems[i].begin(); item != testuitems[i].end() ; ++ item )
	// 	{
	// 		std::cout<<*item<<std::endl;
	// 	}
	// }
	// std::list<Action> acts;
	// firstRoundReadFile("u.data",4,acts);
	// std::cout<<acts.size()<<std::endl;
	// std::vector<User> users;
	// std::vector<Item> items;
	// std::map<int,int> useridmap,itemidmap;
	// constructUser(acts,users,useridmap);
	// constructItem(acts,items,itemidmap);
	// std::cout<<users.size()<<" users"<<std::endl;
	// std::cout<<items.size()<<" items"<<std::endl;
	// fixItems(users,items,itemidmap);
	// computeCoVisitation(users,items);

	// int count = 0;
	// for (int i = 0;i<items.size();++i)
	// {
	// 	count += items[i].counts();
	// 	std::cout<<i<<' '<<items[i].id()<<' '<<items[i].counts()<<std::endl;
	// }

	// std::cout<<"summation is "<<count<<std::endl;
	// boost::iostreams::mapped_file mmap("input.txt", boost::iostreams::mapped_file::readonly);
 //    auto f = mmap.const_data();
 //    auto l = f + mmap.size();

 //    uintmax_t m_numLines = 0;
 //    while (f && f!=l)
 //        if ((f = static_cast<const char*>(memchr(f, '\n', l-f))))
 //            m_numLines++, f++;

 //    std::cout << "m_numLines = " << m_numLines << "\n";
}