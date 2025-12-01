#include <cstring>
#include <curses.h>
#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <ctime>

#include "functions.h"

int main() {

    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, true);

    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);

    int ch;
    int centerX = COLS/2;
    int centerY = LINES/2;
    std::vector<char> message;


    std::vector<char> generated_words_list;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> GEN_words_count(10,20);
    std::uniform_int_distribution<> GEN_words_top_1000(0,1000);


    std::ifstream file("wordsTop1000.txt");
    std::string word_string;

    int words_count = GEN_words_count(gen);

    move(centerY, centerX);
    for (int i = 0; i < words_count; i++) {
        for (int j = 0; j <= GEN_words_top_1000(gen); j++) {
            getline(file, word_string);
            word_string.append(" ");
        }
        for (char letter : word_string) {
            generated_words_list.push_back(letter);
        }
        addch(' ');

    }


    display_gen_words(generated_words_list,10,10);
    refresh();

    do {
        ch = getch();
        if ((ch == KEY_BACKSPACE) && !message.empty()) {
            message.pop_back();
            move(5,5);
            display_gen_words(generated_words_list,10,10);
            timer_thread_function();
            refresh();
        }
        else if (ch != KEY_BACKSPACE && ch) {
            message.push_back(ch);
        }
        else {
            continue;
        }

        //Displaying user input

        move(10, 10);

        for (int i = 0; i < message.size(); i++) {
            if (message[i] == generated_words_list[i]) {
                attron(COLOR_PAIR(1));
                addch(message[i]);
                attroff(COLOR_PAIR(1));
            }
            else {
                attron(COLOR_PAIR(2));
                addch(message[i]);
                attroff(COLOR_PAIR(2));
            }
        }
        refresh();
    }
    while (ch != KEY_F(10) && ch != '\n' && ch != KEY_ENTER);

    endwin();


}