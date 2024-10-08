#pragma once

#define true 1
#define false 0

#include <stdio.h>
void checkReturn(int returnVal,int expected,const char* error_ms);
void checkArgs(int getArgs,int expectedArgs,const char* error_ms);
void checkTrue(int evaluations,const char* error_ms);

int writeWithCheck(int fd,const char* data,int size,const char* error_ms);
int readWithCheck(int fd,char* data,int size,const char* error_ms);
