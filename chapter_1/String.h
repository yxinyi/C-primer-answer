#pragma once
#include <memory>
#include <iostream>
extern int MoveCopyLoopTimes;
extern int CopyLoopTimes;
class String {
    friend std::ostream& operator<<(std::ostream& os, const String & s);
    friend bool operator==(const String & s_0, const String & s_1);
    friend bool operator!=(const String & s_0, const String & s_1);
    friend bool operator<(const String & s_0, const String & s_1);
public:
    String() {}
    String(char c[]):begin(nullptr),end(nullptr) {
        begin = end = alloc.allocate(strlen(c));
        alloc.construct(end++,c[end-begin]);
    }
    String(String &&s):begin(std::move(s.begin)),end(std::move(s.end)){
        //std::cout << "run String(String &&s)" << std::endl;
        MoveCopyLoopTimes++;
        begin = end = nullptr;
    }

    String(const String &s) :begin(nullptr), end(nullptr) {
        CopyLoopTimes++;
        //std::cout << "run String(const String &)" << std::endl;
        begin = end = alloc.allocate(s.end - s.begin);
        alloc.construct(end++, *(s.begin + (s.end - s.begin)));
    }
    String& operator=(String &&s) {
        //std::cout << "run operator=(String &&s)" << std::endl;
        if(this != &s){
            free();
            this->begin = std::move(s.begin);
            this->end = std::move(s.end);
            s.begin = s.end = nullptr;
        }
        return *this;
    }
    String& operator=(String& s) {
            //std::cout << "run operator=(String& s)" << std::endl;
        char* tmpBegin, *tmpEnd;
        free();
        tmpBegin = tmpEnd = alloc.allocate(s.end - s.begin);
        alloc.construct(tmpEnd++, *(s.begin + (s.end - s.begin)));
        begin = tmpBegin;
        end = tmpEnd;
    }
    char& operator[](size_t n) {
        return begin[n];
    }
    const char& operator[](size_t n) const {
        return begin[n];
    }
    ~String(){}
private:
    void free(){
        alloc.deallocate(begin,end-begin);
    }
    char* begin;
    char* end;
    std::allocator<char> alloc;
};

std::ostream& operator<<(std::ostream& os, const String & s) {
    size_t size = s.end -s.begin;
    for(size_t i = 0 ; i != size; i++){
        os << *(s.begin+i);
    }
    return os;
}
bool operator==(const String & s_0, const String & s_1){
    size_t size_0 = s_0.end - s_0.begin;
    size_t size_1 = s_1.end - s_1.begin;
    if(size_0!=size_1){
        return false;
    }
    for (size_t i = 0; i != size_0; i++) {
       if(*(s_0.begin + i) != *(s_1.begin+i)){
            return false;
       }
    }
    return true;
}
bool operator!=(const String & s_0, const String & s_1){
    return !(s_0 == s_1);
}
bool operator<(const String & s_0, const String & s_1) {
    size_t size_0 = s_0.end - s_0.begin;
    size_t size_1 = s_1.end - s_1.begin;
    if (size_0 != size_1) {
        return size_0 < size_1;
    }
    for (size_t i = 0; i != size_0; i++) {
        if (*(s_0.begin + i) != *(s_1.begin + i)) {
            return *(s_0.begin + i) < *(s_1.begin + i);
        }
    }
    return false;
}