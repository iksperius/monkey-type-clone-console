//
// Created by kacper on 11/24/25.
//

#include "functions.h"

#include <chrono>
#include <ncurses.h>
#include <thread>
#include <vector>




void display_gen_words(std::vector<char> generated_words_list, int x , int y){
    move(x,y);
    attron(COLOR_PAIR(3));
    for (auto i : generated_words_list) {
        addch(i);
    }
    attroff(COLOR_PAIR(3));
    move(y,x);
}
void display_time(int x, int y) {

    time_t timestamp = time(&timestamp);
    struct tm datetime = *localtime(&timestamp);
    move(x,y);
    printf("%d", datetime.tm_sec);
    move(x,y);
}

void timer_thread_function() {
    while (running) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}