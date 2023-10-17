#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>


#define M 4
#define N 4

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        std::cerr << "No file path." << std::endl;
        exit(1);
    }

    char* file_path = argv[1];

    int fd = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    if(fd < 0)
    {
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    int fd_2 = dup(fd);
    if(fd_2 < 0)
    {
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    char** matrix = new char* [M];
    for(int i = 0; i < M; i++)
    {
        matrix[i] = new char[N];
    }

    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++) 
        {
            matrix[i][j] = char(i + j);
        }  
    }

    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++) 
        {
            int current_fd = (i + j) % 2 == 0 ? fd : fd_2;
            int write_result = write(current_fd, matrix[i] + j, 1);
            if(write_result < 0)
            {
                std::cerr << strerror(errno) << std::endl;
                exit(errno);
            }
        }

        int prabel_result = write(fd, "\n", 1);
        if(prabel_result < 0)
        {
            std::cerr << strerror(errno) << std::endl;
            exit(errno);
        }
    }

    for(int i = 0; i < N; i++)
    {
        delete [] matrix[i];
    }
    delete [] matrix;

    close(fd);
    close(fd_2);

    return 0;
}
