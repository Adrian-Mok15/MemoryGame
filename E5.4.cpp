#include <iostream>

std::string middle(std::string str){
	int a = str.length();
	std::string str2 = "";
	if (a%2 == 0){
		str2 = (str[a/2 -1]);
		str2 = str2 + str[a/2];
	}
	else if (a%2 != 0){
		str2 = str[a/2];
	}
	return str2;
}

int main(){

	std::string b = middle("What");
	std::cout << b << std::endl;
}