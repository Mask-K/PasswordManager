#include "aesEncryption.h"

#include <iostream>
void AESEncryption::setKey(const std::string& key){
    key__ = key;
    std::cout << key.size() << '\n' << key << std::endl;
}
