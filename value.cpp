#include "value.h"

Value::Value()
{
    def.clear();
    undef.clear();
}

void Value::add_def(std::string file_name, int number)
{
    def.push_back(std::make_pair(file_name, number));
}

void Value::add_undef(std::string file_name, int number)
{
    undef.push_back(std::make_pair(file_name, number));
}
