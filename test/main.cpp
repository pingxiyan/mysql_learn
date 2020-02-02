#include <thread>
#include <chrono>
#include <iostream>
#include <call_mysql.hpp>

int main(int argc, char** argv) {
	std::string strip = "localhost";
	int port = 3306;
	std::string username = "root";
	std::string pw = "imim";
	if(argc == 2 && argv[1] == std::string("-h")) {
		std::cout << "Param guide:" << std::endl;
		std::cout << "Agrv[1]: ip [localhost]" << std::endl;
        std::cout << "Agrv[2]: port [3306] " << std::endl;
		std::cout << "Agrv[3]: username [root] " << std::endl;
		std::cout << "Agrv[4]: password [imim] " << std::endl;
        std::cout << "$ ./mysql_test localhost 3306 root imim" << std::endl;
		return EXIT_SUCCESS;
	}
    else  if(argc == 5) {
		strip = std::string(argv[1]);
		port = std::atoi(argv[2]);
		username = std::string(argv[3]);
		pw = std::string(argv[4]);
	}

	std::cout << "Current all parameter as follow: " << std::endl;
    std::cout << "strip = " << strip.c_str() << std::endl;
	std::cout << "port = " << port << std::endl;
	std::cout << "username = " << username.c_str() << std::endl;
	std::cout << "pw = " << pw.c_str() << std::endl;
	

	COUT_DEBUG("finish all");
	return EXIT_SUCCESS;
}
