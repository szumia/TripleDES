#ifndef TRIPLEDES_DES_H
#define TRIPLEDES_DES_H

#include "TypeTransform.h"

using namespace std;

int Intial_P[] = {  // 初始置换PI
        58, 50, 42, 34, 26, 18, 10, 2,
        60, 52, 44, 36, 28, 20, 12, 4,
        62, 54, 46, 38, 30, 22, 14, 6,
        64, 56, 48, 40, 32, 24, 16, 8,
        57, 49, 41, 33, 25, 17, 9, 1,
        59, 51, 43, 35, 27, 19, 11, 3,
        61, 53, 45, 37, 29, 21, 13, 5,
        63, 55, 47, 39, 31, 23, 15, 7 };

int Inverse_P[] = {  // 逆初始置换FP
        40, 8, 48, 16, 56, 24, 64, 32,
        39, 7, 47, 15, 55, 23, 63, 31,
        38, 6, 46, 14, 54, 22, 62, 30,
        37, 5, 45, 13, 53, 21, 61, 29,
        36, 4, 44, 12, 52, 20, 60, 28,
        35, 3, 43, 11, 51, 19, 59, 27,
        34, 2, 42, 10, 50, 18, 58, 26,
        33, 1, 41, 9, 49, 17, 57, 25 };

int PC64To56[] = {  // 密钥置换IP1 64->56
        57, 49, 41, 33, 25, 17, 9,
        1, 58, 50, 42, 34, 26, 18,
        10, 2, 59, 51, 43, 35, 27,
        19, 11, 3, 60, 52, 44, 36,
        63, 55, 47, 39, 31, 23, 15,
        7, 62, 54, 46, 38, 30, 22,
        14, 6, 61, 53, 45, 37, 29,
        21, 13, 5, 28, 20, 12, 4 };

int PC56To48[] = {  // 密钥置换IP2 56->48
        14, 17, 11, 24, 1, 5,
        3, 28, 15, 6, 21, 10,
        23, 19, 12, 4, 26, 8,
        16, 7, 27, 20, 13, 2,
        41, 52, 31, 37, 47, 55,
        30, 40, 51, 45, 33, 48,
        44, 49, 39, 56, 34, 53,
        46, 42, 50, 36, 29, 32 };


int shiftbit[] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };  // 左循环移位

int E[] = {  // 扩展置换E 32->48
        32, 1, 2, 3, 4, 5,
        4, 5, 6, 7, 8, 9,
        8, 9, 10, 11, 12, 13,
        12, 13, 14, 15, 16, 17,
        16, 17, 18, 19, 20, 21,
        20, 21, 22, 23, 24, 25,
        24, 25, 26, 27, 28, 29,
        28, 29, 30, 31, 32, 1 };


int S[8][4][16] ={  // S盒
        {  // S1
                {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
                {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
                {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
                {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
        },
        {  //S2
                {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
                {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
                {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
                {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
        },
        {  // S3
                {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
                {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
                {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
                {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
        },
        {  // S4
                {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
                {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
                {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
                {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
        },
        {  // S5
                {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
                {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
                {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
                {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
        },
        {  // S6
                {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
                {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
                {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
                {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
        },
        {  // S7
                {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
                {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
                {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
                {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
        },
        {   // S8
                {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
                {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
                {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
                {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
        }
};

int P[] = {  // 置换运算P
        16, 7, 20, 21,
        29, 12, 28, 17,
        1, 15, 23, 26,
        5, 18, 31, 10,
        2, 8, 24, 14,
        32, 27, 3, 9,
        19, 13, 30, 6,
        22, 11, 4, 25 };


// 轮函数f
// 接受32位数据和48位子密钥,返回32位数据
bitset<32> f(bitset<32> R, bitset<48> K)
{
    bitset<48> expandR;

    for (int i = 0; i < 48; i++) expandR[47 - i] = R[32 - E[i]];  // 扩展置换32->48

    expandR = expandR ^ K;  // 异或

    // S盒运算
    bitset<32> R_1;
    int x = 0;
    for (int i = 0; i < 48; i += 6) {
        int row = expandR[47 - i] * 2 + expandR[47 - i - 5];
        int col = expandR[47 - i - 1] * 8 + expandR[47 - i - 2] * 4 + expandR[47 - i - 3] * 2 + expandR[47 - i - 4];
        int num = S[i / 6][row][col];
        bitset<4> binary(num);
        R_1[31 - x] = binary[3], R_1[31 - x - 1] = binary[2];
        R_1[31 - x - 2] = binary[1], R_1[31 - x - 3] = binary[0];
        x += 4;
    }

    // P置换
    bitset<32>tmp = R_1;
    for (int i = 0; i < 32; i++) R_1[31 - i] = tmp[32 - P[i]];
    return R_1;
}

bitset<28> CShift(bitset<28> k, int shift) {  // // 28位密钥左移
    bitset<28> tmp = k;

    for (int i = 27; i >= 0; i--) {
        if (i - shift < 0) k[i] = tmp[i - shift + 28];
        else k[i] = tmp[i - shift];
    }
    return k;
}

void generateKeys(bitset<64>Key, bitset<48>subKey[]) {  // 生成子密钥
    bitset<56> realKey;
    bitset<28> C;
    bitset<28> D;
    bitset<48> tmpkey;

    for (int i = 0; i < 56; ++i) realKey[55 - i] = Key[64 - PC64To56[i]];  // 去除校验位

    for (int round = 0; round < 16; round++) {
        for (int i = 28; i < 56; i++) C[i - 28] = realKey[i];
        for (int i = 0; i < 28; i++) D[i] = realKey[i];

        // 左移
        C = CShift(C, shiftbit[round]), D = CShift(D, shiftbit[round]);

        // 生成48位子密钥
        for (int i = 28; i < 56; i++) realKey[i] = C[i - 28];
        for (int i = 0; i < 28; i++) realKey[i] = D[i];

        for (int i = 0; i < 48; i++) tmpkey[47 - i] = realKey[56 - PC56To48[i]];

        subKey[round] = tmpkey;
    }
}

bitset<64> encryptDES(bitset<64> plain, bitset<64> key) {  // DES加密
    bitset<64> cipher;
    bitset<64> currentBits;
    bitset<32> L;
    bitset<32> R;
    bitset<32> tmpL;
    bitset<48> subKey[16];

    generateKeys(key, subKey);

    // 初始置换IP
    for (int i = 0; i < 64; i++) currentBits[63 - i] = plain[64 - Intial_P[i]];
    for (int i = 32; i < 64; i++) L[i - 32] = currentBits[i];
    for (int i = 0; i < 32; i++) R[i] = currentBits[i];

    for (int round = 0; round < 16; round++) {  // 十六轮加密
        tmpL = R;
        R = L ^ f(R, subKey[round]);
        L = tmpL;
    }

    for (int i = 0; i < 32; i++) cipher[i] = L[i];
    for (int i = 32; i < 64; i++) cipher[i] = R[i - 32];

    // 结尾置换FP
    currentBits = cipher;
    for (int i = 0; i < 64; i++) cipher[63 - i] = currentBits[64 - Inverse_P[i]];
    return cipher;
}

bitset<64> decryptDES(bitset<64> cipher, bitset<64> key) {  // DES解密
    bitset<64> plain;
    bitset<64> currentBits;
    bitset<32> L;
    bitset<32> R;
    bitset<32> tmpL;
    bitset<48> subKey[16];

    generateKeys(key, subKey);

    for (int i = 0; i < 64; i++) currentBits[63 - i] = cipher[64 - Intial_P[i]];  // 初始置换IP

    for (int i = 32; i < 64; i++) L[i - 32] = currentBits[i];
    for (int i = 0; i < 32; i++) R[i] = currentBits[i];

    for (int round = 0; round < 16; round++) {  // 十六轮加密
        tmpL = R;
        R = L ^ f(R, subKey[15 - round]);
        L = tmpL;
    }

    for (int i = 0; i < 32; i++) plain[i] = L[i];
    for (int i = 32; i < 64; i++) plain[i] = R[i - 32];

    // 结尾置换IP
    currentBits = plain;
    for (int i = 0; i < 64; ++i) plain[63 - i] = currentBits[64 - Inverse_P[i]];
    return plain;
}

#endif //TRIPLEDES_DES_H
