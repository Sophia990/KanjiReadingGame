#ifndef CMAKESFMLPROJECT_WORDLIST_H
#define CMAKESFMLPROJECT_WORDLIST_H

#include "Word.h"

class WordList {
public:
    Word tempWordArray[10] = {
            Word(U"お菓子", U"おかし", U"okashi"),
            Word(U"お金", U"おかね", U"okane"),
            Word(U"お兄さん", U"おにいさん", U"oniisan"),
            Word(U"お皿", U"おさら", U"osara"),
            Word(U"お姉さん", U"おねえさん", U"oneesan"),
            Word(U"お手洗い", U"おてあらい", U"otearai"),
            Word(U"お酒", U"おさけ", U"osake"),
            Word(U"お茶", U"おちゃ", U"ocha"),
            Word(U"お父さん", U"おとうさん", U"otousan"),
            Word(U"お風呂", U"おふろ", U"ofuro")
    };
};


#endif //CMAKESFMLPROJECT_WORDLIST_H
