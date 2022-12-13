#include "cryptlib.h"

#include "rijndael.h"

#include "modes.h"

#include "files.h"

#include "osrng.h"

#include "hex.h"



#include <iostream>

#include <string>





std::string hextobin(const std::string &s){

    std::string out;

    for(auto i: s){

        uint8_t n;

        if(i <= '9' and i >= '0')

            n = i - '0';

        else

            n = 10 + i - 'A';

        for(int8_t j = 3; j >= 0; --j)

            out.push_back((n & (1<<j))? '1':'0');

    }



    return out;

}



int main(int argc, char* argv[])

{

    using namespace CryptoPP;



    AutoSeededRandomPool prng;

    std::string keyTxt;

    HexEncoder keyEnc(new StringSink(keyTxt));

    std::string ivTxt;

    HexEncoder ivEnc(new StringSink(ivTxt));

    std::string keyFragment[4]; 



    SecByteBlock key(AES::DEFAULT_KEYLENGTH);

    SecByteBlock iv(AES::BLOCKSIZE);



    prng.GenerateBlock(key, key.size());

    prng.GenerateBlock(iv, iv.size());



    std::string plain = "93";

    std::string cipher, recovered;



    std::cout << "plain text: " << plain << std::endl;



    /*********************************\

    \*********************************/



    try

    {

        CBC_Mode< AES >::Encryption e;

        e.SetKeyWithIV(key, key.size(), iv);



        StringSource s(plain, true, 

            new StreamTransformationFilter(e,

                new StringSink(cipher)

            ) // StreamTransformationFilter

        ); // StringSource

    }

    catch(const Exception& e)

    {

        std::cerr << e.what() << std::endl;

        exit(1);

    }



    /*********************************\

    \*********************************/



    keyEnc.Put(key, key.size());

    keyEnc.MessageEnd();

    

    ivEnc.Put(iv, iv.size());

    ivEnc.MessageEnd();

    

    std::cout << keyTxt << std::endl;

    

    for(int i = 0; i < 4; i++){

    	if(i == 3){

    		keyFragment[i] = hextobin(keyTxt.substr(i*keyTxt.length()/4, keyTxt.length()-1));	

    	}

    	else{

    		keyFragment[i] = hextobin(keyTxt.substr(i*keyTxt.length()/4, keyTxt.length()/4));

    	}

    	std::cout << keyFragment[i] << std::endl;

    }

    try{

    	StringSource a(keyFragment[0], true, 

                new FileSink("Input-P0-0")

        ); // StringSource

        StringSource b(keyFragment[1], true, 

                new FileSink("Input-P1-0")

        ); // StringSource

        StringSource c(keyFragment[2], true, 

                new FileSink("Input-P2-0")

        ); // StringSource

        StringSource d(keyFragment[3], true, 

                new FileSink("Input-P3-0")

        ); // StringSource

        /*

        StringSource e(keyFragment[4], true, 

                new FileSink("Input-P4-0")

        ); // StringSource

        StringSource f(keyFragment[5], true, 

                new FileSink("Input-P5-0")

        ); // StringSource*/

        StringSource g(ivTxt, true, 

                new FileSink("iv.txt")

        ); // StringSource

        StringSource h(cipher, true, 

                new FileSink("cipher.txt")

        ); // StringSource

    }

    catch(const Exception& e)

    {

        std::cerr << e.what() << std::endl;

        exit(1);

    }





    /*********************************\

    \*********************************/



    try

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

    }



    return 0;

}
