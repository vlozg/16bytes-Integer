#include "Qfloat.h"
#include "FileHandling.h"
#include <string.h>

int main(int agrc, char* agrv[])
{
    int type = stoi(agrv[3]);
    if (agrc == 4)
    {
        if (type == 1)
            ReadFile(agrv[1], agrv[2]);
        else
            ReadFileF(agrv[1], agrv[2]);
    } 
    else
        cout << "Khong dung dinh dang. Dinh dang tham so: ten_file_input.txt ten_file_output.txt <type>";
    return 0;
}