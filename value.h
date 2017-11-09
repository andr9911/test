#ifndef VALUE_H
#define VALUE_H
#include <string>
#include <vector>
class Value
{
public:
    Value();
    //std::string value_name; //значение value
    std::vector<std::pair<std::string, int>> def;  //массив пар имя файла, строка где стоит DEFINE
    std::vector<std::pair<std::string, int>> undef; //массив пар имя файла, строка где стоит UNDEF
    void add_def(std::string file_name, int number);
    void add_undef(std::string file_name, int number);
};

#endif // VALUE_H
