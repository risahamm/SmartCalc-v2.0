//
// Created by Risa Hammond on 8/11/24.
//

#ifndef CPP3_SMARTCALC_V2_0_1_REVERSE_POLISH_NOTATION_H
#define CPP3_SMARTCALC_V2_0_1_REVERSE_POLISH_NOTATION_H

#include <string>
#include <stack>
#include <list>
#include <iostream>

namespace s21 {

    enum Priority {
        kPriority_0,  // numbers, parenthesis
        kPriority_1,  // +, -
        kPriority_2,  // *, /, %
        kPriority_3,  // pow, sqrt
        kPriority_4,  // cos, sin, tan, acos, asin, atan
    };

    struct Lexeme {
        std::string value;
        Priority priority;
    };

    class ReversePolishNotation {
    public:
        ReversePolishNotation(std::string input_str) {
            rpn_list_ = Reverse(input_str);

        }

        std::list<Lexeme> get_rpn_list() { return rpn_list_; };

    private:
        std::list<Lexeme> rpn_list_;

        std::list<Lexeme> Reverse(std::string str);

        void AddNumber(std::string::iterator it);

    }; // class ReversePolishNotation

    std::list<Lexeme> ReversePolishNotation::Reverse(std::string str) {
        std::stack<std::string> operators;
        auto lexeme = str.begin();
        if (std::isdigit(*lexeme)) {
            AddNumber(lexeme);
        }
        return rpn_list_;
    }

    void ReversePolishNotation::AddNumber(std::string::iterator it) {
        Lexeme new_lexeme;
        while (std::isdigit(*it) || *it == '.' || *it == 'e' || (*it == '-' && *(it - 1) == 'e') ||
               (*it == '+' && *(it - 1) == 'e')) {
            new_lexeme.value.push_back(*it);
            ++it;
        }
        new_lexeme.priority = kPriority_0;
        rpn_list_.push_back(new_lexeme);
    }


} // s21


#endif //CPP3_SMARTCALC_V2_0_1_REVERSE_POLISH_NOTATION_H
