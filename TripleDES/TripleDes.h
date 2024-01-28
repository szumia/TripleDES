#ifndef TRIPLEDES_TRIPLEDES_H
#define TRIPLEDES_TRIPLEDES_H

#include "Des.h"
#include "TypeTransform.h"

bitset<64> encrypt3DES(bitset<64> plain, bitset<128> key)  // 3DES加密
{

    bitset<64>Lkey;
    bitset<64>Rkey;
    bitset<64>cipher;
    bitset<64>tmp;

    for (int i = 64; i < 128; i++) Lkey[i - 64] = key[i];
    for (int i = 0; i < 64; i++) Rkey[i] = key[i];

    tmp = encryptDES(plain, Lkey);
    tmp = decryptDES(tmp, Rkey);
    cipher = encryptDES(tmp, Lkey);
    return cipher;
}

bitset<64> decrypt3DES(bitset<64> cipher, bitset<128> key)  // 3DES解密
{

    bitset<64>Lkey;
    bitset<64>Rkey;
    bitset<64>plain;
    bitset<64>tmp;

    for (int i = 64; i < 128; i++) Lkey[i - 64] = key[i];
    for (int i = 0; i < 64; i++) Rkey[i] = key[i];

    tmp = decryptDES(cipher, Lkey);
    tmp = encryptDES(tmp, Rkey);
    plain = decryptDES(tmp, Lkey);
    return plain;
}

#endif //TRIPLEDES_TRIPLEDES_H
