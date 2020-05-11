/*

FileHandling.h là thư viện chưa các hàm 

hỗ trợ đọc file theo định dạng yêu cầu của đồ án

*/

#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include "QNum.h"

namespace qint{
void ReadFile(string input, string output);
}

namespace qfloat{
void ReadFile(string input, string output);
}