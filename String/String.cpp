#include <stdexcept>
#include <cstring>
#include <algorithm>


class MyString{
    public:
        MyString();
        MyString(const MyString& other);
        MyString& operator=(const MyString& other);
        MyString(const size_t size);
        MyString(const char* s);
        ~MyString();

        size_t size() const;
        bool empty() const;

        char& operator[](size_t pos);
        const char& operator[](size_t pos) const;
        
        int compare(const MyString& other) const;
        MyString substr(size_t pos,size_t len) const;

    private:
        char *data;
        size_t length;
        size_t capacity; 
};

MyString::MyString(){
    capacity = 1;
    data = new char[capacity];
    data[0]='\0';
    length=0;
}

MyString::MyString(const size_t size){
    capacity = (size > 0 ? size + 1 : 1); //+1 for the space of terminator('\0')
    data = new char[capacity];
    data[0]='\0';
    length=0;
}

MyString::MyString(const char* s){ //create from a string constant
    if(!s){
        capacity = 1;
        data = new char[capacity];
        data[0] = '\0';
        length = 0;
    } 

    else {
        length = std::strlen(s);
        capacity = length + 1;
        data = new char[capacity];
        for(size_t i=0;i<length;i++){
            data[i]=s[i];
        }
        data[length] = '\0';
    }
}

MyString::MyString(const MyString& other){
    length = other.length;
    capacity = other.capacity;
    data = new char[capacity];
    for(size_t i=0;i<length;i++){
        data[i]=other.data[i];
    }
    data[length] = '\0';
}

MyString& MyString::operator=(const MyString& other){
    if(this == &other) {
        return *this;
    }
    char* newdata = new char[other.capacity];

    for(size_t i=0;i<other.length;i++){
        newdata[i]=other.data[i];
    }
    newdata[other.length] = '\0';

    delete[] data;  //Important! Don't forget!

    data = newdata;
    length = other.length;
    capacity = other.capacity;

    return * this;
}

MyString::~MyString(){
    delete[] data;
}

size_t MyString::size() const{
    return length;
}


bool MyString::empty() const{
    return length==0;
}

char& MyString::operator[](size_t pos){
    if(pos>=length){
        throw std::out_of_range("index out of range");
    }
    return data[pos];
}

const char& MyString::operator[](size_t pos) const{
    if(pos>=length){
        throw std::out_of_range("index out of range");
    }
    return data[pos];
}

int MyString::compare(const MyString& other) const{
    size_t min_len = std::min(size(), other.size());
    for(size_t i=0;i<min_len;i++){
        if(data[i]<other.data[i]){
            return -1;
        }
        if(data[i]>other.data[i]){
            return 1;
        }
    }
    if(size()>other.size()){
        return 1;
    }
    if(size()<other.size()){
        return -1;
    }
    return 0;
}

MyString MyString::substr(size_t pos,size_t len) const{
    if(pos>size()){
        throw std::out_of_range("substr pos out of range");
    }

    if(len==0){
        return MyString();  //return an empty string
    }

    if(len > size() - pos){
        throw std::out_of_range("substr length out of range");
    }

    MyString s(len);

    for(size_t i=0;i<len;i++){
        s.data[i]=data[pos+i];
    }

    s.data[len] = '\0';
    s.length = len;  //remember to update the length of new string

    return s;
}

int BF_Find(const MyString& str,const MyString& substr){  //Brute Find
    if(!str.size()||!substr.size()||str.size()<substr.size()){
        return -1;
    }

    for(size_t i=0;i<str.size()-substr.size()+1;i++){
        int ans=1;
        for(size_t j=0;j<substr.size();j++){
            if(substr[j]!=str[i+j]){
                ans=0;
                break;
            }
        }
        if(ans){
            return i;
        }
    }
    return -1;
}

