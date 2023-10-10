#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cerrno>
int main()
{
	close(1);
	int result = open("cout.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if(result < 0)
	{
		std::cerr<<"Error "<<errno<<std::endl;
		exit(errno);
	}
	std::cout<<"hola"<<std::endl;
	return 0;
}
