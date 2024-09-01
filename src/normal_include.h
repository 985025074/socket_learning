#pragma once
#define true 1
#define false 0

#include <sys/socket.h>
#include <stdlib.h>
#include <bits/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include "check.h"
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/select.h>
typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr_in6 sockaddr_in6;
