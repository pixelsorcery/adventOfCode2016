#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <Wincrypt.h>
#include <string>
#include <cassert>

using namespace std;

static constexpr int MD5LEN = 16;

int main()
{
    HCRYPTPROV hProv = 0;
    HCRYPTHASH hHash = 0;
    string base = "uqwqemis";
    char pass[] = "        ";
    int num = 0;
    BYTE rgbHash[MD5LEN];
    char hexHash[MD5LEN * 2 + 1];
    CHAR rgbDigits[] = "0123456789abcdef";
    int idx = 0;

    if (!CryptAcquireContext(&hProv,
        NULL,
        NULL,
        PROV_RSA_FULL,
        CRYPT_VERIFYCONTEXT))
    {
        assert(!"CryptAcquireContext failed!\n");
        return -1;
    }

    while(idx < 8)
    {
        string hash_string = base + to_string(num);

        if (!CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash))
        {
            assert(!"CryptCreateHash failed!\n");
            return -1;
        }

        if (!CryptHashData(hHash, (BYTE *)hash_string.c_str(), static_cast<DWORD>(hash_string.length()), 0))
        {
            assert(!"CryptHashData failed!\n");
            return -1;
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

        if (hexHash)

        CryptDestroyHash(hHash);
#if 0
        if (strncmp(hexHash, "00000", 5) == 0)
        {
            cout << hexHash << endl;
            pass[idx] = hexHash[5];
            idx++;
        }
#else
        if (strncmp(hexHash, "00000", 5) == 0)
        {
            // throw away hash < 8 and only use first result for each position
            if (hexHash[5] < '8' && pass[hexHash[5] - '0'] == ' ')
            {
                cout << hexHash << endl;
                pass[hexHash[5] - '0'] = hexHash[6];
                idx++;
            }
        }
#endif
        num++;
    }

    cout << "password: " << pass << endl;

    return 0;
}