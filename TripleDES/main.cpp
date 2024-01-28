#include <fstream>
#include "TypeTransform.h"
#include "Des.h"
#include "TripleDes.h"

using namespace std;

/*
 * 可选的FileIn & FileOut有:
 * ../TextInput.txt   ../JpgInput.jpg       ../DocInput.doc     ../刘小慧 - 初恋情人.mp3
 * ../TextOutput.txt   ../JpgOutput.txt     ../DocOutput.txt    ../Mp3Output.txt
 */
//#define FileIN "../TextInput.txt"
//#define FileIN "../DocInput.doc"
#define FileIN "../JpgInput.jpg"
//#define FileIN "../刘小慧 - 初恋情人.mp3"


//#define FileOUT  "../TextOutput.txt"
//#define FileOUT  "../DocOutput.txt"
#define FileOUT  "../JpgOutput.txt"
//#define FileOUT  "../Mp3Output.txt"

//#define DecrypyFileOUT  "../TextOutput_Decrypy.txt"
//#define DecrypyFileOUT  "../DocOutput_Decrypy.txt"
#define DecrypyFileOUT  "../JpgOutput_Decrypy.txt"
//#define DecrypyFileOUT  "../Mp3Output_Decrypy.txt"


//#define DES
#define TriDES

std::ifstream file;
std::ofstream outfile,decrypt_outfile;



//返回文件类型
string getFileType(string &filepath)
{
    size_t lastDotPos = filepath.find_last_of('.');
    if (lastDotPos != std::string::npos && lastDotPos < filepath.length() - 1)
    {
        return filepath.substr(lastDotPos + 1);
    } else
    {
        return "";
    }
}


void LoadTxt(string &result)
{
    cout<<"-------   Loading .txt/.doc/.docx    -------"<<endl;
    string content;
    if(file)
    {
        char c;
        while (file.get(c))
        {
            content += c;
        }
    }
    cout<<content<<endl;
    cout<<"-------Finished Load .txt/.doc/.docx -------"<<endl<<endl;

    result = content;
}


void LoadJpg(string &result)
{
    cout<<"-------   Loading .jpg    -------"<<endl;
    // 读取文件到一个字符向量中
    std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    // 将字符向量转换为字符串
    std::string content(buffer.begin(), buffer.end());
    cout<<content<<endl;
    cout<<"-------Finished Load .jpg -------"<<endl<<endl;

    result = content;
}

void LoadMp3(string &result)
{
    cout<<"-------   Loading .mp3    -------"<<endl;
    // 读取文件到一个字符向量中
    std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    // 将字符向量转换为字符串
    std::string content(buffer.begin(), buffer.end());
    cout<<content<<endl;
    cout<<"-------Finished Load .mp3 -------"<<endl<<endl;

    result = content;
}


/*
 * 加载不同类型文件，全部转换成string后返回
 * filePath - 文件路径
 * type -   .txt .doc .docx(前3者读取方式一样）  .jpg .mp3
 */
string LoadFile(string &filePath)
{
    string result;
    string type;

    file.open(filePath, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Load file failed: " << filePath << std::endl;
        result="";
    } else
    {
        cout<<"Load file:   "<<filePath<<"  successfully!"<<endl;
        type = getFileType(filePath);
        cout<<"file type: "<<type<<endl<<endl;
    }

    if(type == "txt")
    {
        LoadTxt(result);
    }else if(type == "doc")
    {
        LoadTxt(result);
    } else if(type == "jpg")
    {
        LoadJpg(result);
    }  else if(type == "mp3")
    {
        LoadMp3(result);
    } else{;}

    return result;
}



/*
 * 注意：
 * x86为小端存储， 按位访问要从最后一位往前访问
 * 如：for i in 0 to 63 : result[i] = bits[63-i]
 */
int main() {

    outfile.open(FileOUT,ios::app);
    decrypt_outfile.open(DecrypyFileOUT,ios::app);

    string fileIn_path;
    vector<bitset<64>> M_v,deM_v,reM_v;
    fileIn_path = FileIN;
    string content = LoadFile(fileIn_path);
    StringToBit64Vec(content,M_v);

#ifdef DES
    //////////////         Test Des        //////////////
    bitset<64> key_des(0x6566696c2074654c);
    cout<<"---------  Des encrypt Ascii Cipher  ---------"<<endl;
//    cout<<"M-v size "<<M_v.size()<<endl;
    for(size_t i = 0 ; i < M_v.size(); i++)
    {
        bitset<64> cipher_des = encryptDES(M_v[i],key_des);
        deM_v.push_back(cipher_des);
        string res_ascii = show_Bit64ToCharAscii(cipher_des);
        string res = show_Char16(res_ascii);
//        cout<<endl;
        outfile<<res;
        outfile<<endl;
    }
    cout<<"---------  Des encrypt Ascii Cipher  ---------"<<endl<<endl;


    cout<<"---------  Des decrypt Ascii Plain  ---------"<<endl;
//    cout<<"deM-v size "<<deM_v.size()<<endl;
    for(size_t i = 0 ; i < deM_v.size(); i++)
    {
        bitset<64> plain_des = decryptDES(deM_v[i],key_des);
        reM_v.push_back(plain_des);
        show_Bit64ToCharAscii(plain_des);
        cout<<endl;
    }
    cout<<"---------  Des decrypt Ascii Plain  ---------"<<endl<<endl;
    //////////////         Test Des        //////////////

#elif defined TriDES
    //////////////         Test 3Des        //////////////
    string tmp = "0cf1cae4540a92ac0cf1cae4540a92ac";
    bitset<128> key_3des = Char16ToBitset128(tmp.c_str());
    cout<<"---------  3Des encrypt Ascii Cipher  ---------"<<endl;
    for(size_t i = 0 ; i < M_v.size(); i++)
    {
        bitset<64> cipher_des = encrypt3DES(M_v[i],key_3des);
        deM_v.push_back(cipher_des);
        string res_ascii = show_Bit64ToCharAscii(cipher_des);
        string res = show_Char16(res_ascii);

        outfile<<res;
//        outfile<<endl;
    }
    cout<<"---------  3Des encrypt Ascii Cipher  ---------"<<endl<<endl;


    cout<<"---------  3Des decrypt Ascii Plain  ---------"<<endl;
    //    cout<<"deM-v size "<<deM_v.size()<<endl;
    for(size_t i = 0 ; i < deM_v.size(); i++)
    {
        bitset<64> plain_des = decrypt3DES(deM_v[i],key_3des);
        reM_v.push_back(plain_des);
        show_Bit64ToCharAscii(plain_des);
        cout<<endl;
    }
    cout<<"---------  3Des decrypt Ascii Plain  ---------"<<endl<<endl;


    cout<<"---------  3Des decrypt Original Plain  ---------"<<endl;
    for(size_t i = 0 ; i < reM_v.size(); i++)
    {
        string res_ascii = show_Bit64ToCharAscii(reM_v[i], false);
        string res = show_Char16(res_ascii, false, false);
        cout<<res;
        decrypt_outfile<<res;
    }

    cout<<endl<<"---------  3Des decrypt Original Plain  ---------"<<endl;

    //////////////         Test 3Des        //////////////
#endif


    file.close();
    outfile.close();
    return 0;
}
