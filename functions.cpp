//
// Created by kacper on 11/24/25.
//

#include "functions.h"

#include <chrono>
#include <ncurses.h>
#include <thread>
#include <vector>
#include <random>
#include <fstream>


extern std::atomic<bool> running;
extern std::mutex mutex;

void display_gen_words(std::vector<char> &generated_words_list, std::vector<char> &user_typed_words, int x , int y){
    std::lock_guard<std::mutex> lock(mutex);
    move(x,y);
    attron(COLOR_PAIR(3));
    for (auto i : generated_words_list) {
        addch(i);
    }
    attroff(COLOR_PAIR(3));
    move(x,y);
    refresh();
    // move(x,user_typed_words.size());
    // attron(COLOR_PAIR(3));
    // for (int i = user_typed_words.size(); i < generated_words_list.size(); i++) {
    //     addch(i);
    // }
    // attroff(COLOR_PAIR(3));
    // move(x,y);
    // refresh();
}
void display_user_input(std::vector<char> &user_typed_words, std::vector<char> &generated_words_list , int x , int y) {
    std::lock_guard<std::mutex> lock(mutex);
    move(x, y);

    for (int i = 0; i < user_typed_words.size(); i++) {
        // if (generated_words_list[i] == ' ' && user_typed_words[i] != ' ') {
        //     attron(COLOR_PAIR(2));
        //     addch(user_typed_words[i]);
        //
        // }
        if (user_typed_words[i] == '0') {
            attron(COLOR_PAIR(3));
            addch(generated_words_list[i]);
            attroff(COLOR_PAIR(3));
        }
        else if (user_typed_words[i] == generated_words_list[i]) {
            attron(COLOR_PAIR(1));
            addch(user_typed_words[i]);
            attroff(COLOR_PAIR(1));
        }
        else {
            attron(COLOR_PAIR(2));
            addch(user_typed_words[i]);
            attroff(COLOR_PAIR(2));
        }
        // display_gen_words(generated_words_list,user_typed_words,10,10);
    }
}

void timer_thread_function() {
    int time_left = 5;
    while (running && time_left > 0) {
        {
            std::lock_guard<std::mutex> lock(mutex);
            move(5,10);
            printw("%i",time_left);
            move(10,10);
            refresh();
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
        time_left -= 1;
    }
    {
        std::lock_guard<std::mutex> lock(mutex);
        move(5,10);
        printw("%s","Finished");
        // move(6,10);
        // printw("%",);
        refresh();

    }

}

std::vector<char> generate_random_words_array() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> GEN_words_count(10,20);
    std::uniform_int_distribution<> GEN_words_top_1000(0,1000);

    std::ifstream file("wordsTop1000.txt");

    std::vector<char> generated_words_list;
    std::string word_string;

    int words_count = GEN_words_count(gen);
    for (int i = 0; i < words_count; i++) {
        for (int j = 0; j <= GEN_words_top_1000(gen); j++) {
            getline(file, word_string);
            word_string.append(" ");
        }
        for (char letter : word_string) {
            generated_words_list.push_back(letter);
        }
    }
    return generated_words_list;
}