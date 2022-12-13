#include "cryptlib.h"

#include "rijndael.h"

#include "modes.h"

#include "files.h"

#include "osrng.h"

#include "hex.h"



#include <iostream>

#include <string>





std::string bintohex(const std::string &s){

    std::string out;

    for(uint i = 0; i < s.size(); i += 4){

        int8_t n = 0;

        for(uint j = i; j < i + 4; ++j){

            n <<= 1;

            if(s[j] == '1')

                n |= 1;

        }



        if(n<=9)

            out.push_back('0' + n);

        else

            out.push_back('A' + n - 10);

    }



    return out;

}



int main(int argc, char* argv[])

{

    using namespace CryptoPP;

    std::string key, iv;

    std::string cipher, recovered;



    /*********************************\

    \*********************************/

    try{

    	FileSource a("key.txt", true, 

                new StringSink(key)

        ); // StringSource

        FileSource b("iv.txt", true, 

                new StringSink(iv)

        ); // StringSource

        FileSource c("cipher.txt", true, 

                new StringSink(cipher)

        ); // StringSource

    }

    catch(const Exception& e)

    {

        std::cerr << e.what() << std::endl;

        exit(1);

    }

    

    key = bintohex(key);

    

    std::cout << key << std::endl;



    /*try

    {

        CBC_Mode< AES >::Decryption d;

        d.SetKeyWithIV(key, key.size(), iv);



        StringSource s(cipher, true, 

            new StreamTransformationFilter(d,

                new StringSink(recovered)

            ) // StreamTransformationFilter

        ); // StringSource



        std::cout << "recovered text: " << recovered << std::endl;

    }

    catch(const Exception& e)

    {

        std::cerr << e.what() << std::endl;

        exit(1);

    }*/



    return 0;

}
