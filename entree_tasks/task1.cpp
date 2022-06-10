#include <iostream>
#include <string>
#include <fstream>
#include <list>

#define ERROR "No string found\n"

std::string get_ip(std::string const& s)
{
	std::string::size_type pos = s.find('-');
	if (pos != std::string::npos)
	{
		return s.substr(0, pos-1);
	}
	else
	{
		return ERROR;
	}
}

std::string get_sid(std::string const& s)
{
	std::string::size_type pos_s = s.find("sid=");
	std::string::size_type pos_e = s.find('&', pos_s);
	if ((pos_e != std::string::npos)|| (pos_s != std::string::npos))
	{
		return s.substr(pos_s+5, pos_e-pos_s-6);
	}
	else
	{
		return ERROR;
	}
}

int main() {
	std::ifstream in("log.txt", std::ios_base::in);
	std::string line, ip,sid;
	std::list<std::string> sid_sorted;
	if (in.is_open()) {
		while (std::getline(in, line)) {
			if (get_ip(line) == "10.1.192.38") {
				sid = get_sid(line);
				if (sid != ERROR) {
					sid_sorted.push_back(sid);
				}
			}
		}
		sid_sorted.sort();
		for (std::string l : sid_sorted) std::cout << l << std::endl;
	}
	else std::cout << "Can't open file.\n";
	in.close();
	return 0;
}
