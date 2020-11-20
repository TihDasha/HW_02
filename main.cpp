#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <bitset>
#include <cmath>

void encryption(std::vector<char> bytes, int shift, int key) {
    srand(key);
    std::ofstream ofs;
    ofs.open("2.0", std::ios::binary);
    std::cout << "Encryption" << std::endl;
    for (unsigned int i = 0; i < bytes.size(); i += 4) {
        unsigned int gamma = 0;
        char b1 = bytes[i];
        char b2 = i + 1 < bytes.size() ? bytes[i + 1] : 0u;
        char b3 = i + 2 < bytes.size() ? bytes[i + 2] : 0u;
        char b4 = i + 3 < bytes.size() ? bytes[i + 3] : 0u;
        unsigned int xored_message = (static_cast<unsigned int>(b1) << 24u | static_cast<unsigned int>(b2) << 16u
                         | static_cast<unsigned int>(b3) << 8u | static_cast<unsigned int>(b4)) xor gamma;
        std::cout << "Original word" << std::endl;
        std::cout << std::bitset<32>(xored_message) << std::endl;
        unsigned int shifted_message = (xored_message >> shift) | ((xored_message) << (32 - shift));
        std::cout << "Shifted word" << std::endl;
        std::cout << std::bitset<32>(shifted_message) << std::endl;
        b1 = shifted_message >> 24;
        ofs.write(&b1, sizeof(b1));
        b2 = shifted_message >> 16;
        ofs.write(&b2, sizeof(b2));
        b3 = shifted_message >> 8;
        ofs.write(&b3, sizeof(b3));
        b4 = shifted_message;
        ofs.write(&b4, sizeof(b4));
    }
    ofs.close();
}

void decryption(int shift, int key) {
    std::ifstream ifs;
    ifs.open("2.0", std::ios::binary);
    /*std::string text;
    ifs >> text;
    ifs.close();*/

    std::vector<char> bytes((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

    /*const char* input = text.data();
    std::vector <char> bytes;
    for(unsigned int i = 0; i < text.size(); i++){
        bytes.push_back(input[i]);
    }*/

    /*std::ofstream ofs;
    ofs.open("2.0", std::ios::binary);*/
    std::vector<char> result(bytes.size());

    srand(key);
    std::cout << "Decryption" << std::endl;
    for (int i = 0; i < bytes.size(); i += 4) {
        unsigned int gamma = 0;
        char b1 = bytes[i];
        char b2 = i + 1 < bytes.size() ? bytes[i + 1] : 0u;
        char b3 = i + 2 < bytes.size() ? bytes[i + 2] : 0u;
        char b4 = i + 3 < bytes.size() ? bytes[i + 3] : 0u;
        unsigned int w1 = static_cast<unsigned int>(b1) << 24u & 0xff000000;
        unsigned int w2 = static_cast<unsigned int>(b2) << 16u & 0x00ff0000;
        unsigned int w3 = static_cast<unsigned int>(b3) << 8u & 0x0000ff00;
        unsigned int w4 = static_cast<unsigned int>(b4) & 0x000000ff;
        unsigned int decrypted_message = (w1 | w2 | w3 | w4);
        std::cout << "Decrypted word" << std::endl;
        std::cout << std::bitset<32>(decrypted_message) << std::endl;
        unsigned int shifted_message = (decrypted_message << shift) | ((decrypted_message) >> (32 - shift));
        std::cout << "Shifted word" << std::endl;
        std::cout << std::bitset<32>(shifted_message) << std::endl;
        unsigned int result_message = shifted_message xor gamma;
        result[i] = result_message >> 24;
        result[i + 1] = result_message >> 16;
        result[i + 2] = result_message >> 8;
        result[i + 3] = result_message;
    }

    for (int i = 0; i < result.size(); i++) {
        std::cout << result[i];
    }
}

int main(int argc, const char *argv[]) {
    bool mode;
    try {
        if ((std::string) argv[1] == "encryption") mode = true;
        else {
            if ((std::string) argv[1] == "decryption") mode = false;
            else throw "The entered data is incorrect";
        }
    }
    catch (const char *exception) {
        std::cerr << "Error: " << exception << std::endl;
    }

    std::string text;
    std::cout << "Enter the text: ";
    std::cin >> text;
    const char *input = text.data();

    std::vector<char> bytes;
    for (unsigned int i = 0; i < text.size(); i++) {
        bytes.push_back(input[i]);
    }

    unsigned int key, shift = 3;
    std::cout << "Enter the key: ";
    std::cin >> key;

    encryption(bytes, 3, key);

    /*std::ofstream out;
    out.open("/Users/tihdarya/Documents/clion projects/2.0.txt");
    out << "test";
    out.close();*/
    decryption(3, key);
}