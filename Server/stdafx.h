// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
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