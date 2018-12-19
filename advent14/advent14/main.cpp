#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <Wincrypt.h>
#include <string>
#include <cassert>
#include <memory>
#include <vector>
#include <thread>
#include "md5.h"

#define _CRT_SECURE_NO_WARNINGS 1
using namespace std;

static constexpr int MD5LEN = 16;
static constexpr int RING_SIZE = 1000;

static bool created = 0; 

void genHash(const char* hash_string, char* hexHash)
{
    HCRYPTPROV hProv = 0;
    HCRYPTHASH hHash = 0;
    BYTE rgbHash[MD5LEN];
    CHAR rgbDigits[] = "0123456789abcdef";

    if (!created)
    {
        if (!CryptAcquireContext(&hProv,
            NULL,
            NULL,
            PROV_RSA_FULL,
            CRYPT_VERIFYCONTEXT))
        {
            assert(!"CryptAcquireContext failed!\n");
            return;
        }

        if (!CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash))
        {
            assert(!"CryptCreateHash failed!\n");
            return;
        }
    }


    if (!CryptHashData(hHash, (BYTE *)hash_string, static_cast<DWORD>(strlen(hash_string)), 0))
    {
        assert(!"CryptHashData failed!\n");
        return;
    }

    DWORD cbHash = MD5LEN;
    char tmp[5];
    if (CryptGetHashParam(hHash, HP_HASHVAL, rgbHash, &cbHash, 0))
    {
        // printf("MD5 hash of buffer %s is: ", hash_string.c_str());
        char *ptr = hexHash;
        for (DWORD i = 0; i < cbHash; i++)
        {
            sprintf_s(tmp, "%c%c", rgbDigits[rgbHash[i] >> 4],
                rgbDigits[rgbHash[i] & 0xf]);

            memcpy(ptr, tmp, 3);
            ptr += 2;
        }
    }

    //CryptDestroyHash(hHash);
}

//void genHashes(const vector<unique_ptr<char[]> >& hashes, const int start, const int end)
//{
//    long long hashSalt = 0;
//    char hexHash[MD5LEN * 2 + 1];
//    char hexHash2[MD5LEN * 2 + 1];
//    string base = "yjdafjpo";
//
//    hashSalt = start;
//    // generate 2000 hashes
//    for (int i = 0; i < end-start; i++)
//    {
//        string hash_string = base + to_string(hashSalt);
//        genHash(hash_string.c_str(), hexHash);
//        for (int j = 0; j < 2016; j++)
//        {
//            memcpy_s(hexHash2, 33, hexHash, 33);
//            genHash(hexHash2, hexHash);
//        }
//        unique_ptr<char[]> hash(new char[MD5LEN * 2 + 1]);
//        memcpy_s(hash.get(), MD5LEN * 2 + 1, hexHash, MD5LEN * 2 + 1);
//        vector<unique_ptr<char[]>>* pHashes = const_cast<vector<unique_ptr<char[]>>*>(&hashes);
//        hashes[hashSalt] = move(hash);
//        hashSalt++;
//    }
//}

int main()
{
    string base = "yjdafjpo";
    //string base = "abc";
    long long num = 0;
    char hexHash[MD5LEN * 2 + 1];
    char hexHash2[MD5LEN * 2 + 1];
    unique_ptr<char[]> hashRing(new char[RING_SIZE * (MD5LEN * 2 + 1)]);
    char* rHead = hashRing.get();
    char* rTail = hashRing.get();
    int idx = 0; 

    vector<unique_ptr<char[]>> hashes;
    hashes.reserve(21001);

    int hashIdx = 0;

    while (idx < 64)
    {
        if (num % 20000 == 0)
        {
            long long hashSalt = num;
            hashes.clear();
            hashes.reserve(21001);
            // generate 21000 hashes
            for (int i = 0; i < 21001; i++)
            {
                string hash_string = base + to_string(hashSalt);
                //genHash(hash_string.c_str(), hexHash);
                string result = md5(hash_string);
                for (int i = 0; i < 2016; i++)
                {
                    result = md5(result);
                    //genHash(hexHash2, hexHash);
                }
                unique_ptr<char[]> hash(new char[MD5LEN * 2 + 1]);
                //memcpy_s(hash.get(), MD5LEN * 2 + 1, hexHash, MD5LEN * 2 + 1);
                memcpy_s(hash.get(), MD5LEN * 2 + 1, result.c_str(), MD5LEN * 2 + 1);
                hashes.push_back(move(hash));
                hashSalt++;
                //if (hashSalt % 100 == 0)
                //    cout << hashSalt << endl;
            }

            //thread t1(genHashes, ref(hashes), 0, 5000);
            //thread t2(genHashes, ref(hashes), 5000, 10000);
            //thread t3(genHashes, ref(hashes), 10000, 15000);
            //thread t4(genHashes, ref(hashes), 15000, 20000);
            
            //genHashes(hashes, 20000, 21000);

            //t1.join();
            //t2.join();
            //t3.join();
            //t4.join();

        }

        //string hash_string = base + to_string(num);
        //genHash(hash_string, hexHash);
        char* ptr = (char *)hashes[num % 20000].get();
        for (size_t i = 0; i < (MD5LEN * 2) - 2; i++)
        {
            if (ptr[0] == ptr[1] &&
                ptr[0] == ptr[2])
            {
                for (int j = 0; j < RING_SIZE-1; j++)
                {
                    //genHash(hash_string, hexHash);
                    //assert(num + j < (num % 20000) + 1000);
                    char* ptr1 = (char *)hashes[((num % 20000) + j + 1)].get();
                    for (size_t k = 0; k < (MD5LEN * 2) - 2; k++)
                    {
                        if (ptr[0] == ptr1[0] &&
                            ptr1[0] == ptr1[1] &&
                            ptr1[0] == ptr1[2] &&
                            ptr1[0] == ptr1[3] &&
                            ptr1[0] == ptr1[4])
                        {
                            idx++;
                            cout << num << endl;
                            goto endloop;
                        }
                        ptr1++;
                    }
                }
                goto endloop;
            }
            ptr++;
        }
        //hashes.push_back(hexHash);
endloop:
        num++;
    }

    //cout << "password: " << pass << endl;
    cout << "num hashes: " << num-1;
    return 0;
}