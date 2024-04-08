#pragma once
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<string.h>
void CreatePipe(char* pathname);
void DeletePipe(char* pathname);
void NoBlock(int fd);
