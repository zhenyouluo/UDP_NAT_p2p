// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>

using namespace std;

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "define.h"

const int LOGIN = 0x01;
const int LOGOUT = 0x02;
const int GET_ALL_USERS = 0x03;