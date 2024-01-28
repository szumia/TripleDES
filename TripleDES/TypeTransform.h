#ifndef TRIPLEDES_TYPETRANSFORM_H
#define TRIPLEDES_TYPETRANSFORM_H

#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <sstream>
using namespace std;

bitset<64> Char8ToBitset64(char c[8])
{
    bitset<64> bits;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++) bits[i * 8 + j] = (c[i] >> j) & 1;
    return bits;
}

bitset<128> Char16ToBitset128(const char c[16])
{
    bitset<128> bits;
    for (int i = 0; i < 16; i++)
        for (int j = 0; j < 8; j++) bits[i * 8 + j] = (c[i] >> j) & 1;
    return bits;
}

//接收字符,1位ascil码扩展为64bit
bitset<64> CharToBit64(char c)
{
    int value = (int)c;
    bitset<64> bits(value);
    return bits;
}

char hexToChar(const std::string& hex) {
    int x;
    std::stringstream ss;
    ss << std::hex << hex;
    ss >> x;
    return static_cast<char>(x);
}

//接收代表ascii的字符串 输出对应的符号
string show_Char16(string ascii,bool is_print= false,bool is_ChangeLine=true)
{
    if(is_ChangeLine)
        cout<<endl;

    string tmp;
    string result;

    for(size_t i = 0 ;i < 8 ; i++)
    {
        int x;
        std::stringstream ss;
        for(int j = 1; j >= 0; j--)
        {
            tmp += ascii[15 - i*2 - j];
        }
        ss<<std::hex<<tmp;
        ss>>x;
        tmp.clear();
        if(is_print)
        {
            cout<<"ss: "<<ss.str()<<" x :"<<char(x)<<endl;
        }
        result += char(x);
    }
    return result;
}


//bitset<64> 输出 16进制ASCII   (1个char是无法接收64bit数据的)
string show_Bit64ToCharAscii(bitset<64> bits, bool is_print= true)
{
    string res_str;
    std::stringstream tmp_sstr;
    int result[64];
    int byte[16];
    for(size_t i = 0; i < 64 ; i++)
    {
        result[i] = bits[i];
//        res_str += to_string(result[i]);
    }
    for(size_t j = 0; j < 16; j++)
    {
        int tmp = result[j*4] + result[j*4 + 1]*2 + result[j*4 + 2]*4 + result[j*4 + 3]*8;
        byte[j] = tmp;
    }

//    cout<<"ascii :0x ";
    for(size_t i = 0; i < 16 ; i++)
    {
        if(is_print)
        {
            cout<<hex<<byte[15 - i];
        }

        tmp_sstr<< std::hex<< byte[15 - i];
//        res_str +=tmp_sstr.str();
//        cout<<"tmp: "<<tmp_sstr.str()<<endl;
    }
//    cout<<endl;
    return tmp_sstr.str();
}


void StringToBit64Vec(string &content, vector<bitset<64>> & m_vec)
{
/* ###8 char extend to 64 bit ### */
    //string补足8位char
    string tmp_content = content;
    int str_len = content.length();
    int rest_len = str_len % 8;
    for(size_t i = 0; i <rest_len; i++)
    {
        tmp_content += '0';
    }
//    cout<<tmp_content<<endl;

    cout<<"---------  Original Ascii Content  ---------"<<endl;
    //8位char 转 64bitset
    char tmp_c[8];
    int index = 0;
    for(char c: tmp_content)
    {
//        bitset<64> bits = CharToBit64(c);
        tmp_c[index] = (int)c;
        index++;
        if(index!=1 && (index)%8 ==0)
        {
            bitset<64> bits = Char8ToBitset64(tmp_c);
            m_vec.push_back(bits);
            //show bits
            show_Bit64ToCharAscii(bits);
            cout<<endl;
            index = 0;
        }
    }
    cout<<"---------  Original Ascii Content  ---------"<<endl<<endl;

/* ### 1 char extend to 64 bit ###  */
//    size_t str_len = content.length();
//    size_t numBitsets = str_len / 64 + (str_len % 64 !=0 ? 1:0);
//    cout<<"str_len: "<<str_len<<"  numBitsets: "<<numBitsets<<endl;
//
//    for(size_t i = 0; i < numBitsets; i++)
//    {
//        bitset<64> bits;
//        for(size_t j = 0; j < 64; j++)
//        {
//            size_t index = i * 64 + j;
//            if(index < str_len)
//            {
//                bits[j] = content[index] == '1';
//            } else
//            {
//                bits[j] = 0;
//            }
//        }
//        m_vec.push_back(bits);
//
//        //show bits
//        Bit64ToChar(bits);
//    }

}

#endif //TRIPLEDES_TYPETRANSFORM_H
