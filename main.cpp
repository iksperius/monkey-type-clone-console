#include <algorithm>
#include <atomic>
#include <cmath>
#include <cstring>
#include <curses.h>
#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <thread>

#include "functions.h"



//TODO:
// - kursor skacze jak powalony, trzeba bedzie zbierac aktualan wartosc x y i je przenosic pewnie
// - cala glowna funkcja do przebudowania

    std::atomic<bool> running(true);
    std::mutex mutex;


int main() {

    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, true);

    float start_time = 10;
    std::thread timer_thread(timer_thread_function,start_time);

    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);

    int ch;
    int centerX = COLS/2;
    int centerY = LINES/2;
    std::vector<char> user_typed_words;
    float correctly_typed_chars = 0;
    // int shift_index = 0;


    //Generate array of words

    std::vector<char> generated_words_list = generate_random_words_array();

    display_gen_words(generated_words_list,user_typed_words,10,10);


    do {

        ch = getch();
        if (ch == KEY_BACKSPACE && !user_typed_words.empty()) {
            user_typed_words.pop_back();
            move(5,5);
            display_gen_words(generated_words_list,user_typed_words,10,10);
        }
        // else if ((ch == ' ' && generated_words_list[user_typed_words.size()] == ' ') || ch != ' ')  {
        //     user_typed_words.push_back(ch);
        // }
        else if (ch == ' ') {
            if (generated_words_list[user_typed_words.size()] == ' ') {
                user_typed_words.push_back(ch);
            }
            else {
                int i = user_typed_words.size();
                while (true) {
                    if (generated_words_list[i] == ' ') {
                        user_typed_words.push_back(' ');
                        break;
                    }
                    user_typed_words.push_back('0');
                    i++;
                }
            }
        }
        else {
            user_typed_words.push_back(ch);
        }

        display_user_input(user_typed_words,generated_words_list,10,10);

    }
    while (ch != KEY_F(10) && ch != '\n' && ch != KEY_ENTER && running);

    move(6,10);
    int i = 0;
    for (char a : user_typed_words) {
        if (a == generated_words_list[i]) {
            correctly_typed_chars++;
        }
        i++;
    }

    for (char a : std::to_string(correctly_typed_chars)) {
        printw("%c",a);
    }
    move(5,20);
    float wpm = correctly_typed_chars/start_time/5*60;
    wpm = std::round(wpm);
    printw("%.0f", wpm);
    refresh();
    do {
        ch = getch();
    }
    while (ch != KEY_ENTER);

    if (timer_thread.joinable()) {
        timer_thread.join();
    }

    endwin();


}