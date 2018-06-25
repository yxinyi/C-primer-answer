#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <forward_list>
#include <deque>
#include <sstream>
#include <string>
#include <stack>
#include <algorithm>
#include <numeric>
#include <memory>
#include <map>
#include <unordered_map>
#include <set>
#include <functional>
#include <iterator>
#include <bitset>
#include "String.h"
#include <type_traits>
#include <regex>
#include <iomanip> 
#include <random>
using namespace std;
using namespace std::placeholders;

struct Person {
    Person() {

    }
    Person(string name) :name(name) {

    }
    Person(string name, string address) :name(name), address(address) {

    }
private:
    string name;
    string address;
public:
    string getName() const { return name; }
    string getAddress() const { return address; }
};

struct Sales_data {
    friend std::hash<Sales_data>;

    Sales_data()=default;
    Sales_data(const string &s, unsigned n, double p) :bookNo(s), units_sold(n), revenue(p*n) {}
    explicit Sales_data(const string &s) :bookNo(s) {}
    operator string(){
        return this->bookNo;
    }
    Sales_data& operator+=(const Sales_data& sd);
    explicit Sales_data(istream&) {}
    string isBn()const { return bookNo; }
    Sales_data& combine(Sales_data& theData){
    
    }
    string bookNo;
    int units_sold = 0;
    double revenue = 0;
};

class out_of_stock : public std::runtime_error {
public:
    explicit out_of_stock(const std:: string&s ): std::runtime_error(s){}
};

class isbn_mismatch: public std::logic_error {
public:
    explicit isbn_mismatch(const std::string&s) : std::logic_error(s) {}
    isbn_mismatch(const std::string&s, const std::string& lhs, const std::string& rhs): std::logic_error(s),left(lhs),right(rhs){}
    const string left,right;
};



Sales_data&
Sales_data::operator+=(const Sales_data& sd){
    if(this->bookNo != sd.bookNo){
        throw isbn_mismatch("the isbns has wrong",isBn(),sd.isBn());
    }
    units_sold += sd.units_sold;
    revenue += sd.revenue;
    return *this;
}

struct NoDefault {
    NoDefault(int i):intValue(i){};
    int intValue;
};

//struct C {
//    C(NoDefault n = 5): no(n){};
//    NoDefault no ;
//};

class Debug {
public:
    constexpr Debug(bool b = true) :hw(b), io(b), other(b) {}
    constexpr Debug(bool h, bool i, bool o) : hw(h), io(i), other(o) {}
    bool any(){return hw||io||other;}
    void set_id(bool b)    { hw = b; }
    void set_hw(bool b)    { io = b; }
    void set_other(bool b) { other = b; }
private:
    bool hw;
    bool io;
    bool other;
};

class Account {
public:
    void calculate(){amount += amount * interestRate;}
    static double rate(){return interestRate;}
    static void rate(double);
    Account(string name);

private:
    string owner;
    double amount;
    static double interestRate ;
    static double initRate();
};
double Account::interestRate = 10;
Account::Account(string stringName){
    owner = stringName;
}

class Example {
public:
    static double rate ;
    static const int vecSize = 20;
    static vector<double > vec;
};

double Example::rate = 6.5;
vector<double > Example::vec(vecSize);


istringstream& read(istringstream& is){
    string i;
    while (is>> i)
    {
        cout << i ;
    }
    is.clear();
    return is;
}

struct PersonInfo {
    string name;
    vector<string> phones;
};


int findNumInVec(vector<int > vec, int theKeyNum){
    for (vector<int >::iterator it = vec.begin(); it != vec.end(); it++) {
        if (*it == theKeyNum)
            return *it;
    }
    return theKeyNum+1;
}

void insertForwardList(forward_list<string >& fstr, const string& str_0, const string& str_1){
    forward_list<string >::iterator it_after = fstr.before_begin();
    forward_list<string >::iterator it = fstr.begin();
    while (it != fstr.end())
    {
        if(*it == str_0){
            fstr.insert_after(it, str_1);
            return;
        }
        it++;
        it_after++;
    }
    fstr.insert_after(it_after, str_1);
}


void stringChangeIter(string& s, const string& oldVal, const string& newVal){
    for(string::iterator it = s.begin(); it != s.end(); ){
        string theCheckString(it, it+ oldVal.size());
        if(theCheckString == oldVal){
            it = s.erase(it,it+oldVal.size());
            it = s.insert(it,newVal.begin(),newVal.end());
            it += newVal.size();
        }else{
            it++;
        }
    }
}

void stringChangePos(string& s, const string& oldVal, const string& newVal) {
    for(size_t i = 0 ; i <s.size();){
        if((s.size() - i) < oldVal.size()){
            break;
        }
        string theCheckString(s,i,oldVal.size());
        if(theCheckString == oldVal){
            s.replace(i,oldVal.size(),newVal);
        }else{
            i++;
        }
    }
}

string& stringChangeAddPrefixAndSuffixIter(string& s, const string& prefix , const string& suffix){
    s.insert(s.begin(), prefix.begin(), prefix.end());
    s.append(suffix);
    return s;
}

string& stringChangeAddPrefixAndSuffixPos(string& s, const string& prefix, const string& suffix) {
    s.insert(0, prefix);
    s.insert(s.size(), suffix);
    return s;
}

string stringCheckForNotAscenderAndDescender(const string & str){
    string theStr(str);
    string ascender("df");
    string descender("pg");
    int pos = 0;
    while((pos = theStr.find_first_of(ascender)) != string::npos||
          (pos = theStr.find_first_of(descender)) != string::npos){
        theStr.erase(pos,1);
        ++pos;
    }
    return theStr;
}

class Date {
public:
    Date() = default;
    Date(const string&) ;
    int year;
    int month;
    int day;
};

Date::Date(const string& str) {
    const string numbers = "0123456789";
    int number_begin = 0;
    int number_end = 0;
    number_begin = str.find_first_of(numbers, number_begin);
    number_end =   str.find_first_not_of(numbers, number_end);
    string dayStr(str, number_begin, number_end - number_begin);
    day = stoi(dayStr);
    number_begin++;
    number_end++;
    number_begin = str.find_first_of(numbers, number_begin);
    number_end = str.find_first_not_of(numbers, number_end);
    string monthStr(str, number_begin, number_end - number_begin);
    month = stoi(monthStr);
    number_begin++;
    number_end++;
    number_begin = str.find_first_of(numbers, number_begin);
    number_end = str.find_first_not_of(numbers, number_end);
    if(number_end == string::npos){
        number_end = str.size();
    }
    string yearStr(str, number_begin, number_end - number_begin);
    year = stoi(yearStr);
}


int getSum (const string& left, const string& right){
    return stoi(left) + stoi(right);
}


void elimDups(vector<string >& vecInt){
    sort(vecInt.begin(), vecInt.end());
    vector<string >::iterator tmpIt = unique(vecInt.begin(), vecInt.end());
    vecInt.erase(tmpIt, vecInt.end());
}
int isShorter(const int& s1, const int&s2){
    return s1 < s2;
}
bool isCondition(const string& s1) {
    return s1.size() <= 5;
}
void checkStringSize(vector<string >& vecStr){
    vector<string >::iterator it = partition(vecStr.begin(), vecStr.end(), isCondition);
    for(auto vecIt = vecStr.begin(); vecIt!=it; vecIt++){
        cout << *vecIt<< endl;
    }
}


class BiggiesBoth{
public:
    bool operator()(const string& a, const string& b){
        return a.size() < b.size();
    }
};
class BiggiesSize{
public:
    BiggiesSize(size_t size):size(size){}
    bool operator()(const string& a) {
        return a.size() < size;
    }
private:
    size_t size;
};
class BiggiesPrint{
public:
    void operator()(const string& a) {
        cout << a << ends;
    }
};

void biggies(vector<string >& vecStr, const vector<string>::size_type& sz) {
    elimDups(vecStr);
    stable_sort(vecStr.begin(), vecStr.end(), BiggiesBoth());
    auto wc = find_if(vecStr.begin(),vecStr.end(), BiggiesSize(sz));
    auto count = vecStr.end() -wc;
    cout << count << " " << "of length" << sz << "or longer " << endl;
    for_each(vecStr.begin(),vecStr.end(),BiggiesPrint());
    cout << endl;
}
//void biggies(vector<string >& vecStr, const vector<string>::size_type& sz) {
//    elimDups(vecStr);
//    vector<string>::iterator it = partition(vecStr.begin(), vecStr.end(), [sz](const string& s1){return s1.size() >= sz;});
//    for_each(vecStr.begin(), it, [](const string& s1) { cout << s1 << endl; });
//}


bool isConditionWithSize(const string& s1, const vector<string >::size_type sz) {
    return s1.size() <= sz;
}


bool check_size(const string& s1, const int& val) {
    cout << "run check_size"<< endl;
    return s1.size() >= (size_t)val;
}
void biggiesWithBind(vector<string >& vecStr, const vector<string>::size_type& sz) {
    elimDups(vecStr);
    auto bindFunc = bind(check_size, _1, sz);
    vector<string>::iterator it = partition(vecStr.begin(), vecStr.end(), bindFunc);
    for_each(vecStr.begin(), it, [](const string& s1) { cout << s1 << endl; });
}

//vector<string > vec = { "123","1234","123","123456","123456789","123456798" };
//biggiesWithBind(vec,4);

void writeOddAndEven(ofstream& oddStream, ofstream& evenStream, ifstream& in){
    
    istream_iterator<string > isin(in),eof;
    ostream_iterator<string > oOs(oddStream, " ");
    ostream_iterator<string > eOs(evenStream, " ");
    while (isin != eof)
    {
        if(stoi(*isin) %2){
            *oOs++ = *isin++;
        }else{
            *eOs++ = *isin++;
        }
    }
    oddStream << flush;
    evenStream << flush;
}

void countMap(const set<string> setCondition, map<string, int > strCount, const string& str){
    if(setCondition.find(str) != setCondition.end()){
        pair<map<string,int>::iterator, bool> it = strCount.insert(make_pair(str,1));
        if(!it.second){
            ++it.first->second;
        }
    }
}
void countHashMap(const set<string> setCondition, unordered_map<string, int > strCount, const string& str) {
    if (setCondition.find(str) != setCondition.end()) {
        strCount[str] ++;
    }
}

void insertFamilyName(map<string, vector<pair<string, string>> > familyName, const string& firstName, const string& lastName,const string& birthday){
    familyName[firstName].push_back(pair<string,string>(lastName,birthday));
}
void insertFamilyName(multimap<string, vector<pair<string, string>> > familyName, const string& firstName, const string& lastName, const string& birthday) {
    vector<pair<string, string>> vec;
    vec.push_back(make_pair(lastName, birthday));
    familyName.insert(make_pair(firstName, vec));
}
void setWordLineMap(map<string, list<int > > wordLineMap, const string& word, const int& line) {
    wordLineMap[word].push_back(line);
}


bool compareIsBn(const int & i_0, const int & i_1){
    return i_0 < i_1;
}

void eraseForMultimap(multimap<string,string> mMap, const string& theKey){
    for(std::multimap<string, string>::iterator begin = mMap.lower_bound(theKey),
                                                end = mMap.upper_bound(theKey);
                                                begin != end;
                                                begin++
                                                ){
        mMap.erase(begin);
    }
}

map<string, string> saveRule(ifstream & rule){
    map<string, string> ruleMap;
    string key, value;
    while (rule >> key && getline(rule,value))
    {
        string::iterator strIt = value.begin();
        while (isspace(*strIt))
        {
            value.erase(strIt);
        }
        ruleMap.insert({key, value});
    }
    return ruleMap;
}

void word_transform(ifstream & rule, ifstream& changeTarger){
    map<string, string> ruleMap = saveRule(rule);
    string word;
    while (changeTarger >> word)
    {
        if(ruleMap.find(word) == ruleMap.end()){
            cout << word << ends;
        }else{
            cout << ruleMap[word] << ends;
        }
    }

}
class StrBlobPtr;
class StrBlob {
    friend bool operator==(const StrBlob& str_0, const StrBlob& str_1);
    friend bool operator!=(const StrBlob& str_0, const StrBlob& str_1);
    friend bool operator<(const StrBlob& str_0, const StrBlob& str_1);
public:
    StrBlob& operator=(StrBlob& str) {
            data = make_shared<vector<string>>(*str.data);
        return *this;
    }
    string& operator[](size_t t) {
        return data->at(t);
    }
    const string& operator[](size_t t) const {
        return data->at(t);
    }
    StrBlob(const StrBlob& str): data(make_shared<vector<string>>(*str.data)){}

    friend class ConstStrBlobPtr;
    friend class StrBlobPtr;
    StrBlobPtr begin();
    StrBlobPtr end()  ;
    typedef vector<string>::size_type size_type;
    StrBlob();
    StrBlob(initializer_list<string> il);
    size_type size()const {return data->size();}
    bool empty() const {return data->empty();}
    void push_back(const string& t){data->push_back(t);}
    void push_back(string&& t) { data->push_back(std::move(t)); }
    void pop_back() const;
    const string& front() const;
    const string& back()const;
private:
    std::shared_ptr<vector<string>> data;
    void check(const size_type count, const string& msg) const;

};
bool operator==(const StrBlob& str_0, const StrBlob& str_1){
    return (*str_0.data) == (*str_1.data);
}
bool operator!=(const StrBlob& str_0, const StrBlob& str_1) {
    return !(str_0 == str_1);
}
bool operator<(const StrBlob& str_0, const StrBlob& str_1) {
    return (*str_0.data) < (*str_1.data);
}

StrBlob::StrBlob() :data(make_shared<vector<string>>()) {}
StrBlob::StrBlob(initializer_list<string> il) : data(make_shared<vector<string>>(il)) {}

void StrBlob::check(const size_type count, const string& msg)const {
    if(count > data->size()){
        throw out_of_range(msg);
    }
}
void StrBlob::pop_back()const {
    check(0, "pop back size short");
    data->pop_back();
}

const string& StrBlob::front()const {
    check(0, "front size short");
    return data->front();
}

const string& StrBlob::back()const {
    check(0, "back size short");
    return data->back();
}

shared_ptr<vector<int >> createVec(){
    return make_shared<vector<int >>();
}


void getCinToVectore(istream& in, vector<int >& vec){
    int i = 0;
    while (in >> i)
    {
        vec.push_back(i);
    }
}


void printElements(const vector<int >& vec) {
    for(auto vecE : vec){
        cout << vecE << endl;
    }
}

void process(shared_ptr<int> ptr){

}

//struct destination;
//struct connection;
//connection connect(destination*);
//void disconnect(connection);
//void end_connection(connection* p){
//    disconnect(*p);
//}
//void f(destination& d){
//    connection c = connect(&d);
//    shared_ptr<connection >(&c, [](connection* c_p){disconnect(*c_p);});
//}

class StrBlobPtr {
    friend bool operator==(const StrBlobPtr& str_0, const StrBlobPtr& str_1);
    friend bool operator!=(const StrBlobPtr& str_0, const StrBlobPtr& str_1);
    friend bool operator<(const StrBlobPtr& str_0, const StrBlobPtr& str_1);
public:
    string& operator[](size_t n){
        return wptr.lock()->at(n);
    }
    StrBlobPtr& operator++() {
        check(curr, "out size come on");
        ++curr;
        return *this;
    }
    StrBlobPtr& operator--() {
        --curr;
        check(curr, "less zero come on");
        return *this;
    }
    StrBlobPtr operator++(int) {
        StrBlobPtr ret = *this;
        ++*this;
        return ret;
    }
    StrBlobPtr operator--(int) {
        StrBlobPtr ret = *this;
        --*this;
        return ret;
    }
    StrBlobPtr& operator+(size_t n) {
        check(curr+n,"out size come on");
        curr+=n;
        return *this;
    }
    StrBlobPtr& operator-(size_t n) {
        check(curr - n, "out size come on");
        curr -= n;
        return *this;
    }
    string& operator*() const {
        auto p = check(curr, "out size come on");
        return (*p)[curr];
    }
    string* operator->() const {
        return &this->operator*();
    }
    const string& operator[](size_t n)const {
        return wptr.lock()->at(n);
    }
    StrBlobPtr():curr(0){}
    StrBlobPtr(StrBlob& a, size_t sz = 0):wptr(a.data),curr(sz){}
    string& deref() const;
    StrBlobPtr& incr();

private:
    std::shared_ptr<vector<string >> check(size_t,const string&) const;
    weak_ptr<vector<string>> wptr;
    size_t curr;
};
shared_ptr<vector<string >>
StrBlobPtr::check(size_t sz, const string& msg) const {
    shared_ptr<vector<string >> spv = wptr.lock();
    if(!spv){
        throw runtime_error(" unbound StrBlobPtr");
    }
    if(sz > spv->size()){
        throw range_error(msg);
    }
    return spv;
}
string& StrBlobPtr::deref()const{
    auto p = check(curr,"dereference past end");
    return (*p)[curr];
}
StrBlobPtr& StrBlobPtr::incr()  {
    check(curr,"increment past end of StrBlobPtr");
    ++curr;
    return *this;
}
bool operator==(const StrBlobPtr& str_0, const StrBlobPtr& str_1){
    shared_ptr<vector<string >> sp_0 = str_0.wptr.lock();
    shared_ptr<vector<string >> sp_1 = str_1.wptr.lock();
    return *sp_0 == *sp_1;
}
bool operator!=(const StrBlobPtr& str_0, const StrBlobPtr& str_1){
    return !(str_0 ==str_1);
}
bool operator<(const StrBlobPtr& str_0, const StrBlobPtr& str_1) {
    shared_ptr<vector<string >> sp_0 = str_0.wptr.lock();
    shared_ptr<vector<string >> sp_1 = str_1.wptr.lock();
    return *sp_0 < *sp_1;
}
StrBlobPtr StrBlob::begin() { return StrBlobPtr(*this); }
StrBlobPtr StrBlob::end() { return StrBlobPtr(*this, data->size()); }

class StrBlobPtrControl {
public:
    StrBlobPtr& operator*(){
        return *sbp;
    }
    StrBlobPtr* operator->() {
        return &this->operator*();
    }
private:
    StrBlobPtr* sbp;
};

class ConstStrBlobPtr {
public:
    ConstStrBlobPtr() :curr(0) {}
    ConstStrBlobPtr(const StrBlob& a, size_t sz = 0) :wptr(a.data), curr(sz) {}
    string& deref() const;
    ConstStrBlobPtr& incr();
    const string& operator*()const{
        auto p = check(curr,"out side");
        return (*p)[curr];
    }
    const string* operator->()const {
        return &this->operator*();
    }
private:
    std::shared_ptr<vector<string >> check(size_t, const string&) const;
    weak_ptr<vector<string>> wptr;
    size_t curr;
};

shared_ptr<vector<string >>
ConstStrBlobPtr::check(size_t sz, const string& msg) const {
    shared_ptr<vector<string >> spv = wptr.lock();
    if (!spv) {
        throw runtime_error(" unbound StrBlobPtr");
    }
    if (sz > spv->size()) {
        throw range_error(msg);
    }
    return spv;
}

string& ConstStrBlobPtr::deref()const {
    auto p = check(curr, "dereference past end");
    return (*p)[curr];
}
ConstStrBlobPtr& ConstStrBlobPtr::incr() {
    check(curr, "increment past end of StrBlobPtr");
    ++curr;
    return *this;
}


char* sumForString(const string a, const string b) {
    allocator<char> charAllocator;
    char * charArray = charAllocator.allocate(a.size() + b.size());
    
    for(size_t i = 0 ; i < a.size(); i++){
        charArray[i] = a[i];
    }
    for (size_t i = a.size(), j =0; i < a.size() + b.size(); i++, j++) {
        charArray[i] = b[j];
    }
    *(charArray + a.size() + b.size()) = '\0';
    return charArray;
}


class MyTextQuery {
public:
    MyTextQuery() = default;
    MyTextQuery(ifstream& );

private:
    vector<string > vec;
    map<string, set<int>> wordMap;
};

MyTextQuery::MyTextQuery(ifstream& ifs){
    string lineStr, word;
    int lineCount = 0;
    while (getline(ifs, lineStr))
    {
        vec.push_back(lineStr);
        istringstream ist(lineStr);
        while (ist >> word && ist.eof())
        {
            wordMap[word].insert(lineCount);
        }
        lineCount++;
    }
    
}

//void* operator new(size_t s) {
//    cout << "runing operator new" << endl;
//    if (void * mem = std::malloc(s)) {
//        return mem;
//    }
//    else {
//        throw bad_alloc();
//    }
//}
//void operator delete(void* v) {
//    cout << "runing operator delete" << endl;
//    std::free(v);
//}

class StrVec {
    friend bool operator==(const StrVec& sv_0, const StrVec& sv_1);
    friend bool operator!=(const StrVec& sv_0, const StrVec& sv_1);
    friend bool operator<(const StrVec& sv_0, const StrVec& sv_1);
public:
    void* operator new(size_t s){
        cout<< "StrVec::new" << endl;
        return std::malloc(s);
    }
    StrVec() :emlemnts(nullptr), first_free(nullptr), cap(nullptr) {}
    StrVec(const StrVec&);
    StrVec(StrVec&& s):emlemnts(std::move(s.emlemnts)), first_free(std::move(s.first_free)), cap(std::move(s.cap)){
        s.emlemnts = s.first_free = s.cap = nullptr;
    };
    StrVec(initializer_list<string>);
    const string& operator[](size_t n)const{
        return emlemnts[n];
    };
    string& operator[](size_t n) {
        return emlemnts[n];
    };
    StrVec& operator=(StrVec&);
    StrVec& operator=(initializer_list<string>);
    StrVec& operator=(StrVec&&s){
        if(this != &s){
            free();
            this->emlemnts = s.emlemnts;
            this->first_free = s.first_free;
            this->cap = s.cap;
            s.emlemnts = s.first_free = s.cap = nullptr;
        }
        return *this;
    };
    ~StrVec();
    void push_back(const string&);
    string* begin()const { return emlemnts; }
    string* end()const { return first_free; }
    size_t size() { return first_free - emlemnts; };
    size_t capacity() { return cap - emlemnts; };
    void reserve(const size_t& n);
    void resize(const size_t& n);
    template <typename...Args>
    void emplace_back(Args...args){
        chk_n_alloc();
        alloc.construct(first_free++,std::forward(args)..);
    }

private:
    string * emlemnts;
    string* first_free;
    string* cap;
    allocator<std::string> alloc;
    pair<string*, string* > alloc_n_copy(const string *, const string *);
    void chk_n_alloc() { if (size() == capacity()) { reallocate(); } }
    void reallocate();
    void free();

};

bool operator==(const StrVec& sv_0, const StrVec& sv_1){
    return (sv_0.emlemnts == sv_1.emlemnts) &&(sv_0.first_free == sv_1.first_free) && (sv_0.cap == sv_1.cap);
}
bool operator!=(const StrVec& sv_0, const StrVec& sv_1){
    return !(sv_0 ==sv_1);
}
bool operator<(const StrVec& sv_0, const StrVec& sv_1) {
    size_t size_0 = sv_0.first_free - sv_0.emlemnts;
    size_t size_1 = sv_1.first_free - sv_1.emlemnts;
    if(size_0 != size_1){
        return size_0 < size_1;
    }
    for(size_t i = 0 ; i < size_0; i++){
        if((*sv_0.emlemnts)!=(*sv_1.emlemnts)){
            return (*sv_0.emlemnts) < (*sv_1.emlemnts);
        }
    }
    return false;
}

pair<string*, string* > StrVec::alloc_n_copy(const string * b, const string *e){
    auto data = alloc.allocate(e-b);
    return {data, uninitialized_copy(b,e,data)};
}
StrVec::~StrVec() {
    free();
}
void StrVec::push_back(const string& s) {
    chk_n_alloc();
    alloc.construct(first_free++, s);
}
StrVec::StrVec(const StrVec& s) {
    auto tmpAlloc = alloc_n_copy(s.begin(), s.end());
    emlemnts = tmpAlloc.first;
    emlemnts = tmpAlloc.second;
}

StrVec::StrVec(initializer_list<string> list) {
    for (initializer_list<string>::iterator it = list.begin(); it != list.end(); it++) {
        push_back(*it);
    }
}
StrVec& StrVec::operator=(initializer_list<string> list) {
    for (initializer_list<string>::iterator it = list.begin(); it != list.end(); it++) {
        push_back(*it);
    }
    return *this;
}

StrVec& StrVec::operator=(StrVec& s) {
    auto tmpAlloc = alloc_n_copy(s.begin(), s.end());
    free();
    emlemnts = tmpAlloc.first;
    first_free = tmpAlloc.second;
    return *this;
}
void StrVec::free() {
    //for (auto p = first_free; p != emlemnts;) {
    //    alloc.destroy(--p);
    //}
    for_each(emlemnts, first_free, [](string& a){a.~basic_string();});
    alloc.deallocate(emlemnts, capacity());
}
void StrVec::reallocate() {
    auto newcapacity = size() ? 2 * size() : 1;
    auto newdata = alloc.allocate(newcapacity);
    auto dest = newdata;
    auto elem = emlemnts;
    for (size_t i = 0; i != size(); i++)
        alloc.construct(dest++, move(*elem++));
    free();
    emlemnts = newdata;
    first_free = dest;
    cap = emlemnts + newcapacity;
}

void StrVec::reserve(const size_t& n) {
    if (n < size()) {
        return;
    }
    auto newdata = alloc.allocate(n);
    auto dest = newdata;
    auto elem = emlemnts;
    for (size_t i = 0; i != size(); i++)
        alloc.construct(dest++, move(*elem++));
    free();
    emlemnts = newdata;
    first_free = dest;
    cap = emlemnts + n;
}
void StrVec::resize(const size_t& n) {
    auto newdata = alloc.allocate(n);
    auto dest = newdata;
    auto elem = emlemnts;
    for (size_t i = 0; i != size() && i < n; i++)
        alloc.construct(dest++, move(*elem++));
    free();
    emlemnts = newdata;
    first_free = dest;
    cap = emlemnts + n;
}

class Point {
public:
    int x;
    int y;
};
Point global;
Point foo_bar(Point arg){
    Point local = arg, *heap = new Point(global);
    *heap = local;
    Point pa[4] = {local, *heap};
    return *heap;
}
class HasPtr {
friend void swap(HasPtr& h1, HasPtr& h2);
public:
    bool  operator < (HasPtr& has) const {
        return this->i < has.i;
    }
    //HasPtr& operator = (HasPtr& has){
    //    cout << "operator = (HasPtr &has)" << endl;
    //    if (this != &has) {
    //        auto newps = new string(*has.ps);
    //        delete ps;
    //        ps = newps;
    //        i = has.i;
    //    }
    //    return *this;
    //}
    HasPtr& operator = (HasPtr has) {
        //auto newps = new string(*has.ps);
        cout << "operator = (HasPtr has)" << endl;
        if (this != &has) {
            swap(*this, has);
        }
        return *this;
    }
    HasPtr& operator = (HasPtr&& has) {
        cout << "operator = (HasPtr &&has)" << endl;
        //auto newps = new string(*has.ps);
        if (this != &has) {
            delete ps;
            ps = std::move(has.ps);
            i = std::move(has.i);
            use_count = std::move(has.use_count);
        }
        return *this;
    }
    HasPtr(const HasPtr& has) : ps(new string(*has.ps)), i(has.i), use_count(has.use_count) { }
    HasPtr(const std::string &s = std::string()):
        ps(new std::string(s)),i(0){}
    ~HasPtr(){
        delete ps;
    }
    //HasPtr(const HasPtr& has) : ps(has.ps), i(has.i), use_count(has.use_count) { ++*use_count; }
    //~HasPtr() {
    //    if(--*use_count == 0){
    //        delete ps;
    //        delete use_count;
    //    }
    //}
    int getI() const { return i; }
    void setI(int value ) { i = value; }
    string getS()const { return *ps; }
private:
    std::string *ps;
    std::size_t *use_count;
    int i;
};
void swap(HasPtr& h1, HasPtr& h2){
    //cout << "function HasPtr swap running" << endl;
    std::swap(h1.i, h2.i);
    std::swap(h1.ps, h2.ps);
}
//struct X {
//    X() { cout << "X() " << endl; };
//    X(const X&) { cout << "const X&" << endl; }
//    ~X(){cout << "~X()" << endl;}
//    X& operator = (X& x){cout << "operator = " << endl; return *this;}
//};
static int number = 0;
class Numbered {
public:
    Numbered():i (number){ number++;}
    Numbered(const Numbered&):i(number) { number++; }
    int i ;

};
void f(const Numbered& s ) {cout << s.i << endl;}
class Employee{
public:
    Employee():no(number){ number ++;};
    Employee(string name) :name(name), no(number) { number++; }
    Employee(const Employee& emp) :name(emp.name), no(number) { number++; }
private:
    string name;
    int no;
};
class TreeNode {
    TreeNode() :left(0), right(0) {}
    TreeNode(const TreeNode& tn) :value(tn.value), count(tn.count),left(tn.left), right(tn.right) {}
    TreeNode& operator=(TreeNode& tn){
        value = tn.value;
        count = tn.count;
        left = tn.left;
        right= tn.right;
        return *this;
    }

private:
    string value;
    int count;
    TreeNode *left;
    TreeNode *right;

};
class BinStrTree {
public:
    BinStrTree():root(0){}
    BinStrTree(const BinStrTree& bst):root(bst.root){}
    BinStrTree& operator=(BinStrTree& bst){
        root = bst.root;
        return *this;
    }
private:
    TreeNode * root;
};
static int MoveCopyLoopTimes = 0;
static int CopyLoopTimes = 0;
void pushBackByLoopTimes(std::vector<String>& vecS, const int times){
    MoveCopyLoopTimes = 0;
    CopyLoopTimes = 0;
    vecS.clear();
    for(int i = 0 ; i != times; i++){
        vecS.push_back("a");
    }
    cout << "push_back times:" << times << endl;
    cout << "MoveCopyLoopTimes times:" << MoveCopyLoopTimes << endl;
    cout << "CopyLoopTimes times:" << CopyLoopTimes << endl;
}
class Foo{
public:
    Foo(initializer_list<int > init_data) :data(vector<int >(init_data.begin(), init_data.end())) {}
    Foo(const Foo & f) :data(f.data) {}
    Foo(Foo && f) :data(std::move(f.data)) {}
    Foo sorted() && ;
    Foo sorted() const & ;
private:
    vector<int > data;
};
Foo Foo::sorted() && {
    cout << "Foo::sorted() &&" << endl;
    sort(data.begin(), data.end());
    return *this;
}
Foo Foo::sorted() const & {
    cout << "Foo::sorted() const &" << endl;
    return Foo(*this).sorted();
}
class IfThenElse {
public:
    int& operator()(const int& i_0, int& i_1, int& i_2){
        if(i_0){
            return i_1;
        }
        return i_2;
    }
};
class CinString {
public:
    CinString(istream& is = std::cin):is(is){}
    string operator()()const{
        string tmp;
        if(is >> tmp){
            if(!tmp.empty()){
                return tmp;
            }
        }
        return "";
    }
private:
    istream & is;
};
class EqualJudgment {
public:
    EqualJudgment(const int & i):theVal(i){}
    bool operator()(const int & i){
        return i == theVal;
    }
private:
    int theVal;

};
class WordSizeJudgment {
public:
    WordSizeJudgment(){}
    bool operator()(const string & str, const int theJudgmentSize){
        return str.size() == theJudgmentSize;
    }
};
typedef map<string, function<int (int , int)>> computer;
void initFunc(computer& com){
    com["+"] = std::plus<int>();
    com["-"] = std::minus<int>();
    com["*"] = std::multiplies<int>();
    com["/"] = std::divides<int>();
    com["%"] = std::modulus<int>();
}
struct LongDouble {
    LongDouble(double = 0.0);
    operator double();
    operator int();
};
class Quote {
public:
    Quote() = default;
    Quote(const Quote& q) = default;
    Quote& operator=(const Quote& dq) = default;
    Quote(const string& book,  const double& sales_price):bookNo(book), price(sales_price){
        //cout << this->bookNo << ends;
        //cout << "Quote" << endl;
    }
    virtual Quote* clone()const & { return new Quote(*this); }
    virtual Quote* clone()&& { return new Quote(std::move(*this)); }
    string isbn() const{return bookNo;}
    virtual double net_price(size_t n) const {
        //cout << "Quote net_price n : " << n << "price" << price << endl;
        return n * price;
    }
    virtual ~Quote(){
        //cout << "~Quote" << endl;
    };
    virtual void debug()const {
        //cout << "book No" << bookNo << "price " << price << endl;
    }
private:
    std::string bookNo;
protected:
    double price =0.0;
};
class Disc_quote : public Quote {
public:
    Disc_quote():Quote(){};
    Disc_quote(const Disc_quote& dq) :Quote(dq) { 
        //cout << " const Disc_quote& bq " << endl; 
    };
    Disc_quote& operator=(const Disc_quote& dq)
    {
        Quote::operator=(dq);
        return *this;
    };
    Disc_quote(const string& book, double price, size_t qty, double disc): Quote(book,price), quantity(qty),discount(disc){
        //cout << "Disc_quote" << endl;
    }
    ~Disc_quote() {
    };
    virtual double net_price(size_t n )const = 0;
protected:
    size_t quantity = 0;
    double discount = 0.0;
};
class Bulk_quote : public Disc_quote {
public:
    Bulk_quote():Disc_quote(){ }
    Bulk_quote& operator=(const Bulk_quote& dq)
    {
        Disc_quote::operator=(dq);
        //cout << " operator= const Bulk_quote& bq " << endl;
        return *this;
    };
    virtual Bulk_quote* clone()const & { return new Bulk_quote(*this); }
    virtual Bulk_quote* clone() && { return new Bulk_quote(std::move(*this)); }
    ~Bulk_quote() {
        //cout << "~Bulk_quote" << endl;
    };
    Bulk_quote(const Bulk_quote& bq):Disc_quote(bq){};
    Bulk_quote(const string& book, double price, size_t qty, double disc):Disc_quote(book,price,qty,disc){
        //cout << "Bulk_quote" << endl;
    }
    virtual double net_price(size_t n)const override {
        //cout << "Bulk_quote net_price" << endl;
        double sum = 0.0;
        if(n <= quantity){
            sum = n * this->price * discount;
        }else{
            sum = n * this->price;
        }
        return sum;
    }
};
class Disc_do : public Bulk_quote {
public: 
    Disc_do() = default;
    Disc_do(const string& book, double price, size_t qty, double disc) : Bulk_quote(book, price, qty,disc) {

    }
    double net_price(size_t n) {
        //cout << "Disc_do net_price" << endl;
        if(n <= quantity){
            return price * discount * n;
        }else{
            return price *n ;
        }
    }
};
double print_total(ostream& os, const Quote & item, size_t n){
    double ret = item.net_price(n);
    os << "ISBN: " << item.isbn() << "#sold:" << n << "total due"<<ret << endl;
    return ret;
}
class Basket {
public:
    void addItems(const Quote& qt){
        items.insert(shared_ptr<Quote>(qt.clone()));
    }
    void addItems(Quote&& qt) {
        items.insert(shared_ptr<Quote>(std::move(qt).clone()));
    }
    void total_receipt(ostream& os){
        double sum = 0.0;
        for(auto it = items.cbegin();it != items.cend();it = items.upper_bound(*it)){
            sum += print_total(os,**it,items.count(*it));
        }
        cout << "sum:" << sum << endl;
    }
    static bool compare(const std::shared_ptr<Quote> & lhs, const std::shared_ptr<Quote> & rhs){
        return lhs->isbn() < rhs->isbn();
    }
private:
    std::multiset<shared_ptr<Quote>,  bool(*)(const std::shared_ptr<Quote> &, const std::shared_ptr<Quote> &)> items{compare};
};
class base {
public:
    string name() {cout << "base :: name" << endl; return basename;}
    virtual void print(ostream & os) { cout << "base :: print" << endl;os << basename;}
private:
    string basename;
};
class derived : public base {
public:
    void print(ostream& os) { cout << "derived :: print" << endl; }
private:
    int i;
};
class Base0 {
public:
    void pub_mem();
protected:
    int prot_mem;
private:
    char priv_mem;
};
struct  Pub_Derv:public Base0
{
    void memfcn(Base0& b) {b = *this;}
};
struct Priv_Derv: private Base0
{
    void memfcn(Base0& b) { b = *this; }
};
struct Prot_Derv : protected Base0
{
    void memfcn(Base0& b) { b = *this; }
};
struct  Derived_from_public: public Pub_Derv
{
    void memfcn(Base0& b) { b = *this; }
};
struct  Derived_from_private : public Priv_Derv
{
    //void memfcn(Base0& b) { b = *this; }
};
struct  Derived_from_protected : public Prot_Derv
{
    void memfcn(Base0& b) { b = *this; }
};
class Checker {
};
class Round: public  Checker {
protected:
    double radius;
};
class Cone: public Round {
private:
    double height;
};
class Ball : public Round {
};




class DebugDelete {
public:
    DebugDelete(ostream& os = std::cerr) :os(os) {}
    template<typename T>
    void operator()(T * p) {
        os << "delete p " << endl;
        delete p;
    }
private:
    ostream & os;
};

using line_no = vector<string >::size_type;
class TextQuery {
public:
    class QueryResult;
    TextQuery(ifstream&);
    TextQuery(const TextQuery& tq) :file(new StrVec(*tq.file), DebugDelete()) {
        for (auto it : tq.wm) {
            wm[it.first].reset(new set<line_no>(it.second->begin(), it.second->end()), DebugDelete());
        }
    };
    TextQuery(ifstream& ifs, const set<int > setInt) :file(new StrVec()) {
        string lineStr, word;
        while (getline(ifs, lineStr))
        {
            file->push_back(lineStr);
            int lineCount = file->size();
            if(setInt.find(lineCount) == setInt.end()){
                continue;
            }
            istringstream ist(lineStr);
            while (ist >> word)
            {
                shared_ptr<set<line_no>>& line = wm[word];
                
                if (!line) {
                    line.reset(new set<line_no>, DebugDelete());
                }
                line->insert(lineCount);
            }
        }
    };
    //int getSize()const { return file->size(); };
    //void clear()const {  file->clear(); };
    QueryResult query(const string &)const;
private:
    shared_ptr<StrVec> file;
    map<string, shared_ptr<set<line_no>>> wm;
};

TextQuery::TextQuery(ifstream & ifs) :file(new StrVec(), DebugDelete()) {
    string lineStr, word;
    while (getline(ifs, lineStr))
    {
        file->push_back(lineStr);
        int lineCount = file->size();
        istringstream ist(lineStr);
        while (ist >> word)
        {
            shared_ptr<set<line_no>>& line = wm[word];
            if (!line) {
                line.reset(new set<line_no>, DebugDelete());
            }
            line->insert(lineCount);
        }
    }
}


class QueryResultTuple {
    friend ostream& print(ostream&, const QueryResultTuple&);
public:
    QueryResultTuple(string s, shared_ptr<set<line_no>> ss, shared_ptr<StrVec> sp) :spss(s,ss, sp){};
    QueryResultTuple(const TextQuery::QueryResult& qr) :spss(spss){}
    set<line_no>::iterator begin() { return get<1>(spss)->begin(); }
    set<line_no>::iterator end() { return get<1>(spss)->end(); }
    shared_ptr<StrVec>& get_file() { return get<2>(spss); }
private:
    tuple<string, shared_ptr<set<line_no>>, shared_ptr<StrVec>> spss;
};

class TextQuery::QueryResult {
    friend ostream& print(ostream&, const QueryResult&);
public:
    QueryResult(string s, shared_ptr<set<line_no>> ss, shared_ptr<StrVec> sp) :s(s), ss(ss), sp(sp) {};
    QueryResult(const QueryResult& qr) :s(qr.s), ss(new set<line_no>(qr.ss->cbegin(), qr.ss->cend())), sp(new StrVec(*qr.sp)) {}
    set<line_no>::iterator begin() { return ss->begin(); }
    set<line_no>::iterator end() { return ss->end(); }
    shared_ptr<StrVec>& get_file() { return sp; }
private:
    string s;
    shared_ptr<StrVec> sp;
    shared_ptr<set<line_no>> ss;
};

TextQuery::QueryResult TextQuery::query(const string & word)const {
    static shared_ptr<set<line_no>> noData(new set<line_no>);
    auto result = wm.find(word);
    if (result == wm.end()) {
        return QueryResult(word, noData, file);
    }
    else {
        //cout << wm.find(word)->second->size() << endl;
        return QueryResult(word, wm.find(word)->second, file);
    }
}

ostream& print(ostream& os, const TextQuery::QueryResult & ptr) {
    cout << "you find " << ptr.ss->size() << " in file" << endl;
    //for(auto begin = ptr.sp->begin(); begin!= ptr.sp->end();begin++){
    //    cout << "(line: " << it << " ) " << *begin << endl;
    //}

    for (auto it : *ptr.ss) {
        cout << "(line: " << it << " ) " << *(ptr.sp->begin() + it-1) << endl;
    }
    //for (set<line_no>::iterator it = *ptr.ss->begin(); it != *ptr.ss->end(); it++) {
    //    
    //}
    //for(auto it : *ptr.ss){
    //    cout << "(line: " << it << " ) " << ptr.sp << endl;
    //}
    return os;
}
class Query_base {
    friend class Query;
protected:
    virtual ~Query_base() = default;
private:
    virtual TextQuery::QueryResult eval(const TextQuery&) const = 0;
    virtual string rep() const = 0;
};
class Query {
    friend Query operator~(const Query&);
    friend Query operator|(const Query& lq, const Query& rq);
    friend Query operator&(const Query& lq, const Query& rq);
public:
    Query(const string&);
    TextQuery::QueryResult eval(const TextQuery & t)const { return q->eval(t); }
    string rep()const { return q->rep(); }
private:
    Query(shared_ptr<Query_base> theQ) : q(theQ) { cout << "Query(shared_ptr<Query_base> theQ" << endl; }
    shared_ptr<Query_base> q;
};
ostream& operator<<(ostream& os, const Query& q) {
    os << q.rep();
    return os;
}

class WordQuery : public Query_base {
    friend class Query;
    WordQuery(const string & s):query_word(s){ cout << "WordQuery(const string & s)" << endl; }
    TextQuery::QueryResult eval(const TextQuery & t)const {return t.query(query_word);}
    string rep()const{
        //cout << "WordQuery::rep()" << endl;
        return query_word;
    }
    string query_word;
};

inline Query::Query(const string& s): q(new WordQuery(s)){ cout << "Query(const string &)" << endl; }
class NotQuery : public Query_base {
    friend Query operator~(const Query& q);
    NotQuery(const Query& q):query(q){ cout << "NotQuery()" << endl; }
    TextQuery::QueryResult eval(const TextQuery & t)const;
    string rep()const { 
        //cout << "NotQuery::rep()" << endl;
        return "~(" + query.rep() +")" ;
    }
    Query query;
};

TextQuery::QueryResult NotQuery::eval(const TextQuery& t)const {
    auto queryResult = query.eval(t);
    auto finalResult = make_shared<set<line_no>>();
    size_t sz = queryResult.get_file()->size();
    auto beg = queryResult.begin(), end = queryResult.end();
    for(size_t i = 0 ; i != sz; i++){
        if(beg == end || *beg != i){
            finalResult->insert(i);
        }else if(beg != end){
            beg++;
        }
    }
    return TextQuery::QueryResult(rep(), finalResult, queryResult.get_file());
}
Query operator~(const Query& q){
    return shared_ptr<Query_base>(new NotQuery(q));
}


class BinaryQuery :public Query_base {
protected:
    BinaryQuery(const Query& l , const Query& r, const string& s):lhs(l),rhs(r),opSym(s){ cout << "BinaryQuery(const Query& l , const Query& r, const string& s)" << endl; }
    string rep()const {
        //cout<< "BinaryQuery::rep()" << endl;
        return "("+lhs.rep()+ " "+ opSym + " " + rhs.rep()+ ")";
    }

protected:
    Query lhs, rhs;
    string opSym;
};

class AndQuery : public BinaryQuery {
public:
    friend Query operator&(const Query& lq, const Query& rq);
    AndQuery(const Query & lq, const Query & rq): BinaryQuery(lq,rq,"&"){ cout << "AndQuery(const Query & lq, const Query & rq)" << endl; }
    TextQuery::QueryResult eval(const TextQuery& t)const;
};
Query operator&(const Query& lq, const Query& rq){
    cout << "operator&(const Query& lq, const Query& rq)" << endl;
    return shared_ptr<Query_base>(new AndQuery(lq,rq));
}


TextQuery::QueryResult AndQuery::eval(const TextQuery& t)const {
    auto lQueryResult = lhs.eval(t);
    auto rQueryResult = rhs.eval(t);
    auto finalResult = make_shared<set<line_no>>();
    set_intersection(lQueryResult.begin(), lQueryResult.end(), rQueryResult.begin(), rQueryResult.end(), inserter(*finalResult, finalResult->begin()));
    return TextQuery::QueryResult(rep(), finalResult, lQueryResult.get_file());
}


class OrQuery : public BinaryQuery {
    friend Query operator|(const Query& lq, const Query& rq);
    OrQuery(const Query & lq, const Query & rq) : BinaryQuery(lq, rq, "|") {cout << "OrQuery(const Query & lq, const Query & rq)"<< endl;}
    TextQuery::QueryResult eval(const TextQuery& t)const;
};
Query operator|(const Query& lq, const Query& rq) {
    cout << "operator|(const Query& lq, const Query& rq)" << endl;
    return shared_ptr<Query_base>(new OrQuery(lq, rq));
}
TextQuery::QueryResult OrQuery::eval(const TextQuery& t)const {
    auto lQueryResult = lhs.eval(t);
    auto rQueryResult = rhs.eval(t);
    shared_ptr<set<line_no>>& finalResult = make_shared<set<line_no>>(lQueryResult.begin(), lQueryResult.end());
    finalResult->insert(rQueryResult.begin(), rQueryResult.end());
    return TextQuery::QueryResult(rep(), finalResult, lQueryResult.get_file());
}
//c:

//class Query_base {
//    friend class Query;
//protected:
//    virtual ~Query_base() = default;
//private:
//    virtual QueryResult eval(const TextQuery&) const = 0;
//    virtual string rep() const = 0;
//};
//
//class Query {
//    friend Query operator~(const Query&);
//    friend Query operator|(const Query& lq, const Query& rq);
//    friend Query operator&(const Query& lq, const Query& rq);
//public:
//    Query(const string&);
//    Query(const Query& q):q(q.q),use_count(q.use_count){++*use_count;}
//
//    Query(Query& q) :q(q.q), use_count(q.use_count) { ++*use_count; }
//
//    Query& operator= (const Query & q);
//    QueryResult eval(const TextQuery & t)const { return q->eval(t); }
//    string rep()const { return q->rep(); }
//    ~Query(){
//        if(--*use_count == 0){
//            delete q;
//            delete use_count;
//        }
//    }
//private:
//    Query(Query_base* theQ) : q(theQ), use_count(new size_t(1)) { cout << "Query(shared_ptr<Query_base> theQ" << endl; }
//    Query_base* q;
//    size_t* use_count;
//};
//Query& Query::operator= (const Query & q) {
//    if (this != &q) {
//        if (--*this->use_count == 0) {
//            delete this->q;
//            delete use_count;
//        }
//        this->q = q.q;
//        this->use_count = q.use_count;
//        ++*this->use_count;
//    }
//    return *this;
//}
//ostream& operator<<(ostream& os, const Query& q) {
//    os << q.rep();
//    return os;
//}
//
//class WordQuery : public Query_base {
//    friend class Query;
//    WordQuery(const string & s) :query_word(s) { cout << "WordQuery(const string & s)" << endl; }
//    QueryResult eval(const TextQuery & t)const { return t.query(query_word); }
//    string rep()const {
//        //cout << "WordQuery::rep()" << endl;
//        return query_word;
//    }
//    string query_word;
//};
//
//inline Query::Query(const string& s) : q(new WordQuery(s)),use_count(new size_t(1)) { cout << "Query(const string &)" << endl; }
//
//class NotQuery : public Query_base {
//    friend Query operator~(const Query& q);
//    NotQuery(const Query& q) :query(q) { cout << "NotQuery()" << endl; }
//    QueryResult eval(const TextQuery & t)const;
//    string rep()const {
//        //cout << "NotQuery::rep()" << endl;
//        return "~(" + query.rep() + ")";
//    }
//    Query query;
//};
//
//QueryResult NotQuery::eval(const TextQuery& t)const {
//    auto queryResult = query.eval(t);
//    auto finalResult = make_shared<set<line_no>>();
//    size_t sz = queryResult.get_file()->size();
//    auto beg = queryResult.begin(), end = queryResult.end();
//    for (size_t i = 0; i != sz; i++) {
//        if (beg == end || *beg != i) {
//            finalResult->insert(i);
//        }
//        else if (beg != end) {
//            beg++;
//        }
//    }
//    return QueryResult(rep(), finalResult, queryResult.get_file());
//}
//Query operator~(const Query& q) {
//    return new NotQuery(q);
//}
//
//
//class BinaryQuery :public Query_base {
//protected:
//    BinaryQuery(const Query& l, const Query& r, const string& s) :lhs(l), rhs(r), opSym(s) { cout << "BinaryQuery(const Query& l , const Query& r, const string& s)" << endl; }
//    string rep()const {
//        //cout<< "BinaryQuery::rep()" << endl;
//        return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")";
//    }
//
//protected:
//    Query lhs, rhs;
//    string opSym;
//};
//
//class AndQuery : public BinaryQuery {
//    friend Query operator&(const Query& lq, const Query& rq);
//    AndQuery(const Query & lq, const Query & rq) : BinaryQuery(lq, rq, "&") { cout << "AndQuery(const Query & lq, const Query & rq)" << endl; }
//    QueryResult eval(const TextQuery& t)const;
//};
//Query operator&(const Query& lq, const Query& rq) {
//    cout << "operator&(const Query& lq, const Query& rq)" << endl;
//    return new AndQuery(lq, rq);
//}
//
//
//QueryResult AndQuery::eval(const TextQuery& t)const {
//    auto lQueryResult = lhs.eval(t);
//    auto rQueryResult = rhs.eval(t);
//    auto finalResult = make_shared<set<line_no>>();
//    set_intersection(lQueryResult.begin(), lQueryResult.end(), rQueryResult.begin(), rQueryResult.end(), inserter(*finalResult, finalResult->begin()));
//    return QueryResult(rep(), finalResult, lQueryResult.get_file());
//}
//
//
//class OrQuery : public BinaryQuery {
//    friend Query operator|(const Query& lq, const Query& rq);
//    OrQuery(const Query & lq, const Query & rq) : BinaryQuery(lq, rq, "|") { cout << "OrQuery(const Query & lq, const Query & rq)" << endl; }
//    QueryResult eval(const TextQuery& t)const;
//};
//Query operator|(const Query& lq, const Query& rq) {
//    cout << "operator|(const Query& lq, const Query& rq)" << endl;
//    return new OrQuery(lq, rq);
//}
//QueryResult OrQuery::eval(const TextQuery& t)const {
//    auto lQueryResult = lhs.eval(t);
//    auto rQueryResult = rhs.eval(t);
//    shared_ptr<set<line_no>>& finalResult = make_shared<set<line_no>>(lQueryResult.begin(), lQueryResult.end());
//    finalResult->insert(rQueryResult.begin(), rQueryResult.end());
//    return QueryResult(rep(), finalResult, lQueryResult.get_file());
//}

template <typename T>
int compare(const T &l, const T &r){
    if(l < r){
        return -1;
    }
    if(r < l){
        return 1;
    }
    return 0;
}

template <typename T, typename U>
T myFind(T &l, const U& val) {
    while (*l != val)
    {
        ++l;
    }
    return l;
}

template <typename T, unsigned U>
void myPrint(const T (&l)[U]) {
    for(auto tmp : l){
        cout << tmp << ends;
    }
    cout <<endl;
}

template<typename T, unsigned U>
T* myBegin(T (&val)[U]){
    return &val[0];
}
template<typename T, unsigned U>
T* myEnd(T(&val)[U]) {
    return &val[U-1];
}
template<typename T, unsigned U>
constexpr
int getArrLength(T(&val)[U]){
    return U;
}

template <typename elemType> class ListItem;
template <typename elemType> class List {
public:
    List<elemType>() = default;
    List<elemType>(const List<elemType>& );
    List<elemType>& operator=(const List<elemType>&);
    ~List<elemType>() = default;
    void insert(ListItem<elemType>*ptr, elemType value);
private:
    ListItem<elemType> * front, * end;
};


template <typename> class BlobPtr;
template <typename> class Blob;
template <typename T>
bool operator==(const Blob<T>&, const Blob<T>&){
    return true;
}

template <typename T>
class Blob{
    friend class BlobPtr<T>;
    friend bool operator==(const Blob<T>&, const Blob<T>&);
public:
    typedef T value_type;
    typedef typename vector<T>::size_type size_type;
    Blob();
    Blob(initializer_list<T> il)try{
    
    }catch(const std::bad_alloc& e){
    
    };
    template <typename BT>
    Blob(BT  begin, BT end);
    size_type size() const {return data->size();}
    bool empty() const {return data->empty();}
    void push_back(const T& t){data->push_back(t);}
    void push_back(const T && t){data->push_back(std::move(t));}
    T& back();
    T& operator[](size_type t);
    void pop_back();
private:
    shared_ptr<vector<T>> data;
    void check(size_type i, const string & msg)const;
};

template <typename T>
void Blob<T>::check(size_type i, const string & msg) const{
    if(i >= data->size()){
        throw out_of_range(msg);
    }
}
template <typename T>
T& Blob<T>::back(){
    return data->back();
}
template <typename T>
Blob<T>::Blob():data(make_shared(vector<T>)){

}
//template <typename T>
//Blob<T>::Blob(initializer_list<T> il) : data(make_shared(vector<T>(il))) {
//
//}
template <typename T>
template <typename BT>
Blob<T>::Blob(BT  begin, BT end) :data(make_shared<vector<T>>(begin, end)) {

}

template <typename T>
T& Blob<T>::operator[](size_type t){
    check(t, "out of range");
    return ( *data)[t];
}

template <typename T>
void Blob<T>::pop_back() {
    data->pop_back();
}

template <typename T>
class BlobPtr {
public:
    BlobPtr()try:curr(0){
    
    }catch(const std::bad_alloc & e ){
        
    }
    BlobPtr(Blob<T>&a, size_t sz = 0): wptr(a.data),curr(sz){}
    T& operator*()const{
        auto p = check(curr, "dereference past end");
        return (*p)[curr];
    }
    BlobPtr& operator++(T);
    BlobPtr& operator--(T);
private:
    shared_ptr<vector<T>> check(size_t, const string& )const;
    weak_ptr<vector<T>> wptr;
    size_t curr;

};
template <typename T>
BlobPtr<T>& BlobPtr<T>::operator++(T){
    BlobPtr ret = *this;
    ++*this;
    return ret;
}




template <typename T>
class Screen {
    friend istream& operator>>(istream& is, Screen<T> s);
    friend ostream& operator<<(ostream& is, Screen<T> s);
public:
    typedef T pos;
    friend class Window_mgr;
    Screen() = default;
    Screen(pos wightVal, pos heightVal) :wight(wightVal), height(heightVal), contents(wightVal*heightVal, ' ') {
    }
    Screen(pos wightVal, pos heightVal, char contents) :wight(wightVal), height(heightVal), contents(wightVal*heightVal, contents) {
    }
    Screen& set(char);
    Screen& move(pos r, pos col);
    Screen& display(ostream& os);
    int getWight()const { return wight; }
    string& getContents() { return contents; }
    int getHeight()const { return height; }
    pos size()const;
//private:
    pos cursor;
    pos wight, height;
    string contents;
    void do_displayer(ostream& os) {
        os << contents;
    }
};


template <typename T>
istream& operator>>(istream& is, Screen<T> s){
    T tmpH, tmpW;
    if(is>> tmpH >> tmpW){
        s = Sreen(tmpH, tmpW);
    }
    return is;
}
template <typename T>
ostream& operator<<(ostream& os, Screen<T> s){
    os << s.getWight() << " " << s.getHeight() << endl;
    return os;
}


template <typename T>
typename Screen<T>::pos Screen<T>::size()const {
    return height * wight;
}

class Window_mgr {
public:
    typedef  string::size_type ScreenIndex;
    void clear(ScreenIndex index);
private:
    vector<Screen<int>> screens{ Screen<int>(24, 80, ' ') };
};

void Window_mgr::clear(ScreenIndex index) {
    Screen<int> & s = screens[index];
    s.getContents() = string(s.getWight()*s.getHeight(), ' ');
}
template <typename T>
Screen<T>& Screen<T>::set(char c) {
    contents[cursor] = c;
    return *this;
}
template <typename T>
Screen<T>& Screen<T>::move(pos r, pos col) {
    cursor = wight * r + col;
    return *this;
}
template <typename T>
Screen<T>& Screen<T>::display(ostream& os) {
    cout << "Screen<T> display" << endl;
    do_displayer(os);
    return *this;
}




template <typename T>
class Vec {
    friend bool operator==(const Vec& sv_0, const Vec& sv_1);
    friend bool operator!=(const Vec& sv_0, const Vec& sv_1);
    friend bool operator<(const Vec& sv_0, const Vec& sv_1);
public:
    Vec() :emlemnts(nullptr), first_free(nullptr), cap(nullptr) {}
    Vec(const Vec&);
    Vec(Vec&& s) :emlemnts(std::move(s.emlemnts)), first_free(std::move(s.first_free)), cap(std::move(s.cap)) {
        s.emlemnts = s.first_free = s.cap = nullptr;
    };
    Vec(initializer_list<T>);
    const T& operator[](size_t n)const {
        return emlemnts[n];
    };
    T& operator[](size_t n) {
        return emlemnts[n];
    };
    Vec& operator=(Vec&);
    Vec& operator=(initializer_list<T>);
    Vec& operator=(Vec&&s) {
        if (this != &s) {
            free();
            this->emlemnts = s.emlemnts;
            this->first_free = s.first_free;
            this->cap = s.cap;
            s.emlemnts = s.first_free = s.cap = nullptr;
        }
        return *this;
    };
    ~Vec();
    void push_back(const T&);
    T* begin()const { return emlemnts; }
    T* end()const { return first_free; }
    size_t size() { return first_free - emlemnts; };
    size_t capacity() { return cap - emlemnts; };
    void reserve(const size_t& n);
    void resize(const size_t& n);
    template <typename...Args>
    void emplace_back(Args...args){
        alloc.construct(first_free++,std::forward(args)...);
    }
private:
    T * emlemnts;
    T* first_free;
    T* cap;
    allocator<T> alloc;
    pair<T*, T* > alloc_n_copy(const T *, const T *);
    void chk_n_alloc() { if (size() == capacity()) { reallocate(); } }
    void reallocate();
    void free();

};

template <typename T>
bool operator==(const Vec<T>& sv_0, const Vec<T>& sv_1) {
    return (sv_0.emlemnts == sv_1.emlemnts) && (sv_0.first_free == sv_1.first_free) && (sv_0.cap == sv_1.cap);
}
template <typename T>
bool operator!=(const Vec<T>& sv_0, const Vec<T>& sv_1) {
    return !(sv_0 == sv_1);
}
template <typename T>
bool operator<(const Vec<T>& sv_0, const Vec<T>& sv_1) {
    size_t size_0 = sv_0.first_free - sv_0.emlemnts;
    size_t size_1 = sv_1.first_free - sv_1.emlemnts;
    if (size_0 != size_1) {
        return size_0 < size_1;
    }
    for (size_t i = 0; i < size_0; i++) {
        if ((*sv_0.emlemnts) != (*sv_1.emlemnts)) {
            return (*sv_0.emlemnts) < (*sv_1.emlemnts);
        }
    }
    return false;
}

template <typename T>
pair<T*, T* > Vec<T>::alloc_n_copy(const T * b, const T *e) {
    auto data = alloc.allocate(e - b);
    return { data, uninitialized_copy(b,e,data) };
}
template <typename T>
Vec<T>::~Vec() {
    free();
}
template <typename T>
void Vec<T>::push_back(const T& s) {
    chk_n_alloc();
    alloc.construct(first_free++, s);
}
template <typename T>
Vec<T>::Vec(const Vec<T>& s) {
    auto tmpAlloc = alloc_n_copy(s.begin(), s.end());
    emlemnts = tmpAlloc.first;
    emlemnts = tmpAlloc.second;
}

template <typename T>
Vec<T>::Vec(initializer_list<T> list) {
    for (initializer_list<T>::iterator it = list.begin(); it != list.end(); it++) {
        push_back(*it);
    }
}
template <typename T>
Vec<T>& Vec<T>::operator=(initializer_list<T> list) {
    for (initializer_list<T>::iterator it = list.begin(); it != list.end(); it++) {
        push_back(*it);
    }
    return *this;
}
template <typename T>
Vec<T>& Vec<T>::operator=(Vec& s) {
    auto tmpAlloc = alloc_n_copy(s.begin(), s.end());
    free();
    emlemnts = tmpAlloc.first;
    first_free = tmpAlloc.second;
    return *this;
}
template <typename T>
void Vec<T>::free() {
    //for (auto p = first_free; p != emlemnts;) {
    //    alloc.destroy(--p);
    //}
    for_each(emlemnts, first_free, [](T& a) {a.~T(); });
    alloc.deallocate(emlemnts, capacity());
}
template <typename T>
void Vec<T>::reallocate() {
    auto newcapacity = size() ? 2 * size() : 1;
    auto newdata = alloc.allocate(newcapacity);
    auto dest = newdata;
    auto elem = emlemnts;
    for (size_t i = 0; i != size(); i++)
        alloc.construct(dest++, move(*elem++));
    free();
    emlemnts = newdata;
    first_free = dest;
    cap = emlemnts + newcapacity;
}

template <typename T>
void Vec<T>::reserve(const size_t& n) {
    if (n < size()) {
        return;
    }
    auto newdata = alloc.allocate(n);
    auto dest = newdata;
    auto elem = emlemnts;
    for (size_t i = 0; i != size(); i++)
        alloc.construct(dest++, move(*elem++));
    free();
    emlemnts = newdata;
    first_free = dest;
    cap = emlemnts + n;
}
template <typename T>
void Vec<T>::resize(const size_t& n) {
    auto newdata = alloc.allocate(n);
    auto dest = newdata;
    auto elem = emlemnts;
    for (size_t i = 0; i != size() && i < n; i++)
        alloc.construct(dest++, move(*elem++));
    free();
    emlemnts = newdata;
    first_free = dest;
    cap = emlemnts + n;
}



template <typename T, typename U, typename V>
void f1(T,U,V);

template <typename T>
T f2(T& i){

}

 
template <typename T> inline T foo(T,unsigned int*);
template <typename T> void f4(T,T){
}

typedef char Chartype;
template <typename Ctype> Ctype f5(Ctype a){
    return a;
}


template <typename T>
void printContainer(T & con){
    for(typename T::size_type i = 0 ; i != con.size(); i++){
        cout << con[i] << ends;
    }
    cout <<endl;
}
template <typename T>
void printContainerIterator(T & con) {
    for (typename T::iterator it = con.begin(); it != con.end(); it++) {
        cout << *it << ends;
    }
    cout << endl;
}


//class Nodefault {
//public:
//    Nodefault() = delete;
//};
//template class vector<Nodefault>;



template <typename T, typename Func = default_delete<T>*>
class my_shared_ptr {
public:
    my_shared_ptr(Func func = 0) :data(nullptr), useCount(new int(1)),del(a) {

    }
    my_shared_ptr(T* value, Func func = 0):data(value), useCount(new int(1)), del(func) {
        
    }
    my_shared_ptr(const my_shared_ptr& msp, Func func = 0):data(msp.data),use_count(msp.useCount), del(func) {
        if(*useCount){
            ++*useCount;
        }
    }
    my_shared_ptr& operator=(const my_shared_ptr& msp){
        if(--*useCount == 0){
            delete data;
            delete useCount;
        }
        data = msp.data;
        useCount = msp.useCount;
        ++*useCount;
        return *this;
    }
    size_t use_count(){
        return use_count;
    }
    T* get() {
        return data;
    }
    void swap(my_shared_ptr& msp){
        std::swap(this->data, msp.data);
    }
    void reset(my_shared_ptr& data){
        free();
        this->data = data.data;
        this->useCount = data.useCount;
        ++*data.use_count;
    }
    bool unique(){
        if(*useCount == 1){
            return true;
        }
        return false;
    }
    T& operator*() { return *p; }
    T& operator*() const { return *p; }
    ~my_shared_ptr(){
        free();
    }
private:
    void free(){
        if (--*useCount == 0) {
            cout << del << endl;
            del ? (*del)(data) : delete data;
        }
    }
    T* data;
    int* useCount;
    Func del = 0;
};
template <typename T, typename Func = default_delete<T>*>
class my_unique_ptr {
public:
    my_unique_ptr(T* data, Func func = 0): data(data), del(func){}
    T* release(){
        T* tmpData = data;
        data = 0;
        return tmpData;
    }
    void reset(){
        data = 0;
    }
    void reset(T* p){
        delete data;
        data = p;
    }
    ~my_unique_ptr(){
        del ? (*del)(data) : delete data;
    }
private:
    T*  data;
    Func del = 0;
};

void delelteData(int* a){
    cout << "run deleteData()" << endl;
}

template <typename T> int compare_1634(const T& , const T&){
    return 1;
}

template <typename T>
T calc(T ,int){

}

template <typename T>
T fcn(T, T) {

}

template <typename T>
void f1(T, T) {

}
template <typename T1, typename T2>
void f2(T1, T2) {

}

template<typename T1, typename T2>
auto sum(T1 t1, T2 t2)-> decltype(t1+t2){
    return t1+t2;
}

//template <typename T>
//void g(T&& val){
//    vector<T> v;
//    typename remove_reference<decltype(val)>::type;
//}

template <typename F, typename T1, typename T2>
void filp(F f, T1&& t1, T2&& t2){
    f(std::forward<T1>(t1),std::forward<T2>(t2));
}

void func_f(int& i, int&& j){
}
void func_g(int i, int j) {
}



template <typename T>
void func_g_1649(T) {
    cout << "func_g_1649(T)" << endl;
}
template <typename T>
void func_g_1649(T *) {
    cout << "func_g_1649(T *)" << endl;
}

template <typename T>
void func_1649(T){
    cout << "func_1649(T)" << endl;
}
template <typename T>
void func_1649(const T *) {
    cout << "func_1649(const T *)" << endl;
}

template <typename T, typename...Args>
void foo_1651(T& t1, Args... args){
    cout << "Args size: " << sizeof...(Args) << " args size: " << sizeof...(args) << endl;
}
template <typename T, typename...Args>
ostream& print_args(ostream& os, const T& t, Args...args){
    os << t << ",";
    return print_args(os, args...);
}
template <typename T>
ostream& print_args(ostream& os, const T& t) {
    return os << t << endl;
}

template <typename T>
string debug_rep(const T&t) {
}

template <typename T>
string debug_rep(T*t) {
}

string debug_rep(const string& p){
    return debug_rep(string(p));

}

string debug_rep(char * p) {
    return debug_rep(string(p));
}
string debug_rep(const char * p) {
    return debug_rep(string(p));
}

template<>
string debug_rep(char * const& p){
    return debug_rep(string(p));
}
template<>
string debug_rep(const char*const& p) {
    return debug_rep(string(p));
}


template <typename...Args>
ostream& errorMsg(ostream& os, Args...args){
    return print_args(os,debug_rep(args)...);
}

template<typename T1, typename...Args>
shared_ptr<T1> my_make_shared(Args...args){
    return shared_ptr<T1>(new T1(std::forward(args)...));
}

namespace std{
    template<>
    class hash<Sales_data>{
        typedef size_t result_type;
        typedef Sales_data argument_type;
        size_t operator()(const Sales_data & )const;
    };
    size_t hash<Sales_data>::operator()(const Sales_data & s)const{
        return hash<string>()(s.bookNo)^hash<int>()(s.units_sold)^hash<double>()(s.revenue);
    }
}

template<typename T>
size_t countInVec(vector<T> vec, const T & key){
    return count(vec.cbegin(), vec.cend(), key);
}
template<>
size_t countInVec(vector<const char *> vec, const char* const & key){
    size_t count = 0;
    for(vector<const char *>::const_iterator it = vec.cbegin(); it != vec.cend(); ++it){
        if(strcmp((*it),key) == 0){
            count++;
        }
    }
    return count;
}


bool compareIsBnSales_data(const Sales_data & i_0, const Sales_data & i_1) {
    return i_0.bookNo < i_1.bookNo;
}

//typedef tuple<vector<Sales_data>::size_type, vector<Sales_data>::iterator, vector<Sales_data>::iterator> matches;
//vector<matches> findBook(vector<vector<Sales_data>> & files, const string& s){
//    vector<matches > ret;
//    for(auto it = files.begin(); it != files.end();it++){
//        auto range = equal_range(it->begin(),it->end(), s,compareIsBnSales_data);
//        if(range.first!=range.second){
//            ret.push_back(make_tuple(it- files.begin(), range.first, range.second));
//        }
//    }
//    return ret;
//}
//typedef pair<int, pair<vector<Sales_data>::iterator, vector<Sales_data>::iterator>> matches_pair;
//vector<matches_pair> findBook(vector<vector<Sales_data>> & files, const string& s) {
//    vector<matches_pair> ret;
//    for(auto it = files.begin(); it != files.end();it++){
//        auto range = equal_range(it->begin(),it->end(), s,compareIsBnSales_data);
//        if(range.first!=range.second){
//            ret.push_back({ it - files.begin(),{range.first, range.second}});
//        }
//    }
//    return ret;
//}

struct matches_struct
{
    int slot;
    vector<Sales_data>::iterator begin;
    vector<Sales_data>::iterator end;
};


vector<matches_struct> findBook(vector<vector<Sales_data>> & files, const string& s) {
    vector<matches_struct> ret;
    for (auto it = files.begin(); it != files.end(); it++) {
        auto range = equal_range(it->begin(), it->end(), Sales_data(s), compareIsBnSales_data);
        if (range.first != range.second) {
            ret.push_back(matches_struct{it - files.begin(), range.first, range.second});
        }
    }
    return ret;
}

template <size_t N >
bool theAnswerSet(bitset<N>& b, size_t topic_slot, bool answer){
    return b[topic_slot] == answer;
}

unsigned int returnNumber(const size_t& seed){
    static uniform_int_distribution<unsigned int > u(0, 9);
    static default_random_engine e;
    return u(e);
}

void printHexfloat(float f){
    cout << uppercase << hexfloat << f << nouppercase << dec << endl;
}

namespace Exercise{
    int ivar = 0;
    double dvar =0;
    const int limit = 1000;
}

int ivar = 0;
void manip(){
    using namespace Exercise;
    double dvar = 3.1416;
    int iobj = limit +1;
    ++Exercise::ivar;
    ++::ivar;
    cout << left << "Exercise::ivar:  " << setw(14) << Exercise::ivar << right << " \n";
    cout << left << "Exercise::dvar:  " << setw(14) << Exercise::dvar << right << " \n";
    cout << left << "Exercise::limit: " << setw(14) << Exercise::limit << right << " \n";
    cout << left << "::ivar:          " << setw(14) << ::ivar << right << " \n";
    cout << left << "dvar:            " << setw(14) << dvar << right << " \n";
    cout << left << "iobj:            " << setw(14) << iobj << right;
}

namespace primerLib{
    void compute() { cout << "primerLib::compute()" << endl; };
    //void compute(const void * ) { cout << "primerLibcompute(const void *)" << endl; };
}
void compute(int){cout << "compute(int)" << endl;};
void compute(double, double = 3.4) { cout << "compute(double, double = 3.4)" << endl; };
void compute(char*, char* = 0){ cout << "compute(char*, char* = 0)" << endl; };
void f(){
    using primerLib::compute;
}

class iostream : public istream, public ostream {


};


//static size_t constructor_slot = 1;
//class A {
//public:
//    A(){cout << constructor_slot << ". A()" << endl; constructor_slot++;}
//};
//class B: public A {
//public:
//    B() { cout << constructor_slot << ". B()" << endl; constructor_slot++;    }
//};
//class C : public B {
//public:
//    C() { cout << constructor_slot << ". C()" << endl; constructor_slot++;    }
//};
//class X {
//public:
//    X() { cout << constructor_slot << ". X()" << endl; constructor_slot++;    }
//};
//class Y {
//public:
//    Y() { cout << constructor_slot << ". Y()" << endl; constructor_slot++;    }
//};
//class Z : public X, public Y{
//public:
//    Z() { cout << constructor_slot << ". Z()" << endl; constructor_slot++;    }
//};
//class MI : public C, public Z {
//public:
//    MI() { cout << constructor_slot << ". MI()" << endl; constructor_slot++;    }
//
//};
//
//class D : public X, public C {
//
//
//};

//class Base1 {
//public:
//    virtual void print() = 0;
//    virtual ~Base1() {
//        //cout << "Base1::~Base1" << endl;
//    };
//};
//class Base2 {
//public:
//    virtual void print() = 0;
//    virtual ~Base2() {
//        //cout << "Base2::~Base2" << endl;
//    };
//};
//
//class D1 : public Base1 {
//public:
//    void print(){
//        cout << "D1::print"<<endl;
//    }
//    ~D1() {
//        cout << "D1::~D1" << endl;
//    }
//};
//
//class D2 : public Base2 {
//public:
//    void print() {
//        cout << "D2::print" << endl;
//    }
//    ~D2() {
//        cout << "D2::~D2" << endl;
//    }
//};
//class MI : public D1, public D2 {
//public:
//    void print() {
//        cout << "MI::print" << endl;
//    }
//    ~MI() {
//        cout << "MI::~MI" << endl;
//    }
//};
//
//

class Class {
public:
    virtual void func() { cout << "Class::func()" << endl; };
    Class(){
    }
    int miInt;
};
class Base:public Class {
public:
    Base() = default;
    Base(const Base& b){
    }
    Base(const int & i) {
    }
    virtual void func() { cout << "Base::func()" << endl; };
};
class D1: virtual public Base {
public:
    D1()=default;
    D1(const D1& d) :Base(d) {
    }
    D1(const int & i) :Base(i) {
    }

};
class D2 : virtual public Base {
public:
    D2() = default;
    D2(const D2& d) :Base(d) {
    }
    D2(const int & i) :Base(i) {
    }
};
class MI: virtual public D1, virtual public D2 {
public:
    MI() = default;
    MI(const MI& d) :Base(d) {
    }
    MI(const int & i) :Base(i) {
    }
    virtual void func() { cout << "MI::func()" << endl; };
};
class Final : public MI, public Class {
public:
    Final() = default;
    Final(const Final& d) :Base(d) {
    }
    Final(const int & i) :Base(i) {
    }
};

class A {};
class B :public A {};
class C :public B {};

enum {
    

};

class Token{
public:
    Token():tok(INT),ival(10){}
    Token(const Token& t ):tok(t.tok){copyUniom(t);}
    Token(const Token&& t) :tok(t.tok) { copyUniom(std::move(t)); }
    Token& operator=(const Token&);
    Token& operator=(const Token&&);
    Token& operator=(Token);
    ~Token(){
        if(tok == STR)
            sval.~string();
    }
    Token& operator=(const string&);
    Token& operator=(char);
    Token& operator=(int);
    Token& operator=(double);
private:
    enum{INT,CHAR,DBL,STR} tok;
    union {
        char cval;
        int ival;
        double dval;
        std::string sval;
    };
    void copyUniom(const Token&);
};

Token& Token::operator=(int i){
    if(tok==STR){
        sval.~string();
    }
    tok= INT;
    ival = i;
    return *this;
}
Token& Token::operator=(char c) {
    if (tok == STR) {
        sval.~string();
    }
    tok = CHAR;
    cval = c;
    return *this;
}
Token& Token::operator=(double d) {
    if (tok == STR) {
        sval.~string();
    }
    tok = DBL;
    dval = d;
    return *this;
}
Token& Token::operator=(const string& s) {
    if (tok == STR) {
        sval = s;
    }else{
        new (&sval)string(s);
    }
    tok = STR;
    return *this;
}
void Token::copyUniom(const Token& t){
    switch (t.tok)
    {
    case Token::INT:{
        ival = t.ival;
        break;
    }
    case Token::CHAR: {
        cval = t.cval;
        break;
    }
    case Token::DBL: {
        dval = t.dval;
        break;
    }
    case Token::STR: {
        new(&sval)string(sval);
        break;
    }
    default:
        break;
    }
}
Token& Token::operator=(const Token& t){
    if(t.tok == STR && tok !=STR){
        t.sval.~string();
    }
    if(t.tok == STR && tok == STR){
        sval = t.sval ; 
    }else{
        copyUniom(t);
    }
    tok = t.tok;
    return *this;
}
Token& Token::operator=(const Token&& t) {
    if (t.tok == STR && tok != STR) {
        t.sval.~string();
    }
    if (t.tok == STR && tok == STR) {
        sval = std::move(t.sval);
    }
    else {
        copyUniom(t);
    }
    tok = t.tok;
    return *this;
}


int main(int argc, char *argv[]) {
    ifstream ifs(argv[1]);
    TextQuery tq(ifs);
    print(cout, tq.query("happy"));
    for (;;);
    return 0;
}
