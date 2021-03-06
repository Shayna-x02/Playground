// Windows libraries.
#include <windows.h>
#include <conio.h>
#include <cstdint>

// Standard libraries.
#include <algorithm>
#include <iostream>
#include <utility>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <random>
#include <ctime>

uint32_t Randint(const uint32_t& from, const uint32_t& to) {
    static std::random_device randomness_device;
    static std::mt19937 mersene_twister(randomness_device());
    
    std::uniform_int_distribution<uint32_t> uniform_distributer(from, to);
    
    return uniform_distributer(mersene_twister);
}

std::string MakeDisplayMessageString(const std::pair<std::string, std::string>& strings) {
    std::stringstream display_message_stream;
    display_message_stream << "\r" << strings.first << ": " << strings.second;
    std::string display_message = display_message_stream.str();
    display_message.resize(50, '-');
    return display_message;
}

inline std::clock_t CurrentTime() {
    return (std::clock() / CLOCKS_PER_SEC);
}

int main(int argc, char const* argv[]) {
    bool phrase_mode, error_tracking = false;
    std::vector<std::string> dictionary;

    /* 
    A pointer to the stream where the wordlist for the dictionary is located.
    This stream will be read line-by-line and each line will be added to
    the dictionary. */
    std::istream* input_data_stream = nullptr;
    bool memory_allocated = false;

    for(uint32_t i=0; i<argc; ++i) {
        char const* argument = argv[i];

        if(!strcmp(argument, "--stdin") || !strcmp(argument, "-s")) {
            freopen(NULL, "rb", stdin);
            input_data_stream = &(std::cin);
        } else if((!strcmp(argument, "--file") || !strcmp(argument, "-f")) && (i+1) < argc) {
            char const* file_path = argv[i+1];
            input_data_stream = new std::ifstream(file_path, std::ios::binary);
            memory_allocated = true;
        } else if(!strcmp(argument, "--phrases") || !strcmp(argument, "-p")) {
            phrase_mode = true;
        } else if(!strcmp(argument, "--error-tracking") || !strcmp(argument, "-t")) {
            error_tracking = true;
        }
    }

    for(std::string line; std::getline(*input_data_stream, line);) {
        if(line.size()) {
            line.pop_back(); // Removes the newline byte from the line.
            dictionary.push_back(line); // Adds the modified line to the dictionary.
        }
    }
    
    if(memory_allocated) delete input_data_stream;

    std::string target_word = dictionary.at(Randint(0, dictionary.size()-1));
    std::string word_buffer;
        
    double words_typed = 0;
    double delta_sum = 0;
    
    std::clock_t begin_time_total = CurrentTime();
    std::clock_t begin_time = CurrentTime();
        
    for(char last_character; last_character != 27;) {
        bool first_char_of_word = (last_character == 0x00);
        
        std::cout << MakeDisplayMessageString({target_word, word_buffer});
        
        last_character = _getch();
        
        if(first_char_of_word) begin_time = CurrentTime();
        
        if(last_character == 0x08) {
            if(word_buffer.size()) {
                word_buffer.pop_back();
            }
        } else {
            word_buffer.push_back(last_character);
        }
        
        std::cout << MakeDisplayMessageString({target_word, word_buffer});
                
        if(word_buffer == target_word) {
            target_word = dictionary.at(Randint(0, dictionary.size()-1));
            last_character = 0x00;
            word_buffer.clear();
            std::cout << std::endl;
            ++words_typed;
            delta_sum += (CurrentTime() - begin_time);
        }
    }
    
    begin_time_total = (CurrentTime() - begin_time_total);
    
    std::cout << std::endl << std::endl << words_typed << " Words typed in " << delta_sum << " seconds of typing, during " << begin_time_total << " total seconds." << std::endl;
    std::cout << (words_typed / delta_sum) << " Words per second." << std::endl;
    std::cout << (words_typed / delta_sum) * 60 << " Words per minutes spent typing." << std::endl;
    std::cout << (words_typed / begin_time_total) * 60 << " Words per minute." << std::endl;
        
    return 0;
}