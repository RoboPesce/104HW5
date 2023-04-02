#include <stdexcept>
#include <cctype>
#include <iostream>
#include <fstream>
#include <set>
#include <string>
const std::set<std::string>& readDictWords(std::string filename)
{
	static std::set<std::string> dict;
	if(dict.size() == 0U)
	{
        size_t cnt = 0;
		std::ifstream ifile(filename.c_str());
		if(ifile.fail()){
			throw std::logic_error("Cannot open dictionary file.");
		}
		std::string instr;
		while(ifile >> instr)
		{
			if(isupper(instr[0])) continue;
			bool onlyLetters = true;
			for(char c : instr){
				if(!isalpha(c)) onlyLetters = false;
			}
			if(onlyLetters){
				dict.insert(instr);
				cnt++;
			}
		}
		ifile.close();
		std::cerr << "Read " << cnt << " words into dictionary." << std::endl;
	}
    return dict;
}