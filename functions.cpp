//
// Created by kacper on 11/24/25.
//

#include "functions.h"

#include <chrono>
#include <ncurses.h>
#include <thread>
#include <vector>


extern std::atomic<bool> running;
extern std::mutex mutex;

void display_gen_words(std::vector<char> generated_words_list, int x , int y){
    std::lock_guard<std::mutex> lock(mutex);
    move(x,y);
    attron(COLOR_PAIR(3));
    for (auto i : generated_words_list) {
        addch(i);
    }
    attroff(COLOR_PAIR(3));
    move(y,x);
    refresh();
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