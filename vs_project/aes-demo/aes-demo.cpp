// aes-demo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "aes_encryptor.h"

void test()
{
    unsigned char key[256] = "hello";
    AesEncryptor * pAes = new AesEncryptor(key);
    std::string s_input = "11";
    //std::string s_input = "SIwPteE5zCgUW4eWcgpM2zzWmqwVrh219MiS8x8U2AkYJMhMctPPZT3Knpo47NtH";
    std::string s_encryp = pAes->EncryptString(s_input);
    printf("s_encryp=%s \n", s_encryp.c_str());

    std::string s_output = pAes->DecryptString(s_encryp);
    printf("s_output=%s \n", s_output.c_str());

    if (pAes)
    {
        delete pAes;
        pAes = NULL;
    }
}

int _tmain(int argc, _TCHAR* argv[])
{
    printf("Hello! \n");
    test();

	return 0;
}

