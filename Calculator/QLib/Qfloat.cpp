#include "Qfloat.h"

/*
Set bit tại vị trí bất kì
Parameter:
- pos: vị trí set
- bit: giá trị set
*/
void Qfloat::SetBit(int pos, bool bit){
    if (pos > 127) return;

    char mask = 1 << (pos%8);   //Mặt nạ đánh dấu bit cần sửa

    if (bit == 1){
        value[pos/8] |= mask;   //OR với mask để bật bit
    } else {
        value[pos/8] &= ~mask;  //Đảo mask và AND để tắt bit
    }
}

/*
Lấy giá trị bit tại vị trí bất kì
Parameter:
- pos: vị trí bit cần lấy
*/
bool Qfloat::GetBit(int pos){
    if (pos > 127 || pos < 0) return 0;
    char mask = 1 << (pos%8);   //Mặt nạ đánh dấu bit cần lấy
    return (value[pos/8] & mask);
}

/*
Đổi số thực từ dãy nhị phân sang thập phân lưu trữ trong Qfloat
Parameter:
- bit: dãy nhị phân 128bit 
*/
Qfloat BinToDecF(bool* bit){
    Qfloat res; //Lưu kết quả trả về

    for (int i = 0; i < 128; i++){
        res.SetBit(i, bit[127-i]);
    }
    return res;
}

/*
Đổi số thực từ dạng thập phân trong Qfloat sang dãy nhị phân 128bit
Parameter:
- x: số thực 128bit
*/
bool* DecToBin(Qfloat x){
    bool* res = new bool[128];  //Lưu kết quả trả về
    
    for (int i = 0; i < 128; i++){
        res[127-i] = x.GetBit(i);
    }

    return res;
}