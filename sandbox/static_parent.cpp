
#include <iostream>
#include <string>
#include <map>

template<typename T>
class bass {
public:

bass(std::string name): _name(name) {}

std::string _name;

static std::map<std::string, T> stuff;
};

template<typename T>
class fam: public bass<T> {
public:

fam(std::string name): bass<T>(name) {}

void write_stuff() {
    bass<T>::stuff[bass<T>::_name] = _data;
}

    T _data;
};

template<typename T> 
std::map<std::string, T> bass<T>::stuff = std::map<std::string, T>();

template<typename T>
class tue: public bass<T> {
public:

tue(std::string name): bass<T>(name) {}

void get_stuff() { 
    _data = bass<T>::stuff[bass<T>::_name];
}

    T _data;
};

int main() {

    fam<std::string> huh("that");
    huh._data = " is cool";
    huh.write_stuff();

    fam<std::string> puh("other");
    puh._data = "that";
    puh.write_stuff();

    tue<std::string> neat("that");
    neat.get_stuff();

    tue<std::string> heat("other");
    heat.get_stuff();
    std::cout << heat._data << neat._data << std::endl;

    return 0;
}

