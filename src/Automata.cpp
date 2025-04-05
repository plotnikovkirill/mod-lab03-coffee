// Copyright 2022 UNN-IASR
#include "Automata.h"

#include <iostream>
#include <string>

void Automata::on() {
    if (state == OFF) {
        state = WAIT;
        getState();
    }
    else {
        std::cout << "Machine is already working\n";
    }
}
void Automata::off() {
    if (state == WAIT) {
        change();
        state = OFF;
        getState();
    }
    else {
        if (state != OFF) {
            std::cout << "wait\n";
        }
    }
}
void Automata::coin(int money) {
    if (state == WAIT || state == ACCEPT) {
        state = ACCEPT;
        cash += money;
        getState();
    }
    else {
        std::cout << "Unable to do this action now\n";
    }
}
void Automata::choice(std::string drink) {
    if (state == ACCEPT) {
        if (find(menu.begin(), menu.end(), drink) == menu.end()) {
            std::cout << "SORRYANCHIK UNABLE TO MAKE THIS ";
            cancel();
        }
        else {
            state = CHECK;
            getState();
            check(drink);
        }
    }
}
void Automata::cancel() {
    if (state != OFF) {
        state = WAIT;
    }
}
STATES Automata::getState() {
    std::cout << state;
    return state;
}
void Automata::getMenu() {
    for (int i = 0; i < menu.size(); i++) {
        std::cout << menu[i] << ' ' << prices[i] << '\n';
    }
}
void Automata::check(std::string drink) {
    if (state == CHECK) {
        auto it = find(menu.begin(), menu.end(), drink);
        int index = distance(menu.begin(), it);
        int price_of_coffee = prices[index];
        if (cash < price_of_coffee) {
            std::cout << "NO MONEY GO TO WORK\n";
            cancel();
        }
        else {
            cash -= price_of_coffee;
            cook();
        }
    }
    else {
        std::cout << "Ivalid state";
    }
}
void Automata::cook() {
    std::cout << "preparing wait\n";
    auto start = std::chrono::steady_clock::now();
    auto duration = std::chrono::seconds(5);
    auto printing_state = std::chrono::seconds(2);
    state = COOK;
    while (std::chrono::steady_clock::now() - start < duration) {
        if (std::chrono::steady_clock::now() - start == printing_state) getState();
    }
    std::cout << "Drink prepapred!\n";
    finish();
}
void Automata::finish() {
    state = WAIT;
    getState();
}
void Automata::change() {
    if (state == WAIT) {
        if (cash > 0) {
            std::cout << "TAKE YOUR CASH BACK" << cash;
            cash = 0;
        }
    }
}
int Automata::getCash() { return cash; }
