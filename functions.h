//
// Created by kacper on 11/24/25.
//


#include <iostream>
#include <vector>

#ifndef NCURSES_FUNCTIONS_H
#define NCURSES_FUNCTIONS_H

void display_gen_words(std::vector<char> &generated_words_list, std::vector<char> &user_typed_words, int x , int y);

void display_user_input(std::vector<char> &user_typed_words, std::vector<char> &generated_words_list, int x , int y);

void timer_thread_function();

std::vector<char> generate_random_words_array();

#endif //NCURSES_FUNCTIONS_H