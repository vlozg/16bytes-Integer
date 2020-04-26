#include "Qfloat.h"

/*
Phương thức set bit tại vị trí bất kì
Parameter:
- pos: vị trí set
- bit: giá trị set
*/
void Qfloat::SetBit(int pos, bool bit){
    if (pos > 127) return;
    value[pos/8] |= bit << (pos%8);
}

/*
Phương thức lấy giá trị bit tại vị trí bất kì
Parameter:
- pos: vị trí bit cần lấy
*/
bool Qfloat::GetBit(int pos){
    if (pos > 127 || pos < 0) return 0;
    char mask = 1 << (pos%8);   //Mặt nạ đánh dấu bit cần lấy
    return (value[pos/8] & mask);
}

Qfloat BinToDec(bool* bit){
    Qfloat res;
    return res;
}

bool* DecToBin(Qfloat x){
    return 0;
}