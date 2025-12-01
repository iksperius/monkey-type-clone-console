//
// Created by kacper on 11/24/25.
//


#include <iostream>
#include <vector>

#ifndef NCURSES_FUNCTIONS_H
#define NCURSES_FUNCTIONS_H

void display_gen_words(std::vector<char> generated_words_list, int x , int y);
void display_time(int x, int y);

void timer_thread_function();

#endif //NCURSES_FUNCTIONS_H