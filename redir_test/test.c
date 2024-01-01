#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	
	int fd = open("file2", O_WRONLY | O_TRUNC, 0644);
	//write(fd, "Hello World", 11);
	return(0);
}