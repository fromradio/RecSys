#include "itemcf.h"

int main(int argc, char* argv[])
{
	if(argc != 4)
	{
		std::cerr<<"Usage: transform 'input file' 'output file' k"<<std::endl;
		exit(1);
	}
	else
	{
		std::vector<std::vector<std::pair<int,double> > >score;
		std::vector<std::set<int> > trainuitems;
		readTrainData(argv[1],score,trainuitems);
		writeScore(argv[2],score,std::stoi(std::string(argv[3]),nullptr,0));
	}
}