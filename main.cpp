#include <iostream>
#include <stdio.h>
#include <fstream>
#include "value.h"
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>
#include<algorithm>
#include<iterator>
using namespace std;

/*typedef struct {
    std::vector<std::pair<std::string, int>> def;  //массив пар имя файла, строка где стоит DEFINE
    std::vector<std::pair<std::string, int>> undef; //массив пар имя файла, строка где стоит UNDEF
} Values_f;*/
typedef std::unordered_map<std::string, Value> values_map;
typedef std::unordered_map<std::string, Value>::iterator values_map_iter;

const std::string def_str = "DEFINE";
const std::string undef_str = "UNDEF";
int main(int argc, char * argv[])
{
    values_map values;

    for (int i = 1; i<argc; ++i) //нулевой аргумент это путь к данной проге
    {

        std::string filename(argv[i]);
        std::ifstream file;
        file.open(filename, std::ios::in);
        if(!file.is_open())
        {
            std::cout << "Не найден файл " << filename << endl;
            continue;
        }
        values_map_iter values_iter;
        //читаем каждую строку и заносим данные в массивы
        int count_str = 0; //номер строки, начинается с 1, но инкремент у нас вначале работы цикла
        for (std::string read_buf; std::getline(file, read_buf); )
        {
            bool def_b = false;
            string::size_type pos_def = read_buf.find(def_str);
            string::size_type pos_undef = read_buf.find(undef_str); //потранжирю немного память((
            if (pos_def != std::string::npos) //Если найдено DEFINE
            {
                read_buf.erase(pos_def, def_str.size());
                def_b = true;
                ++count_str;
            }
            else if(pos_undef != std::string::npos) //Если не надено, значит у нас там UNDEF, но все равно проверим
            {
                read_buf.erase(pos_undef, undef_str.size());
                ++count_str;
            }
            else continue; //неизвестная строка, даже как строку считать не будем, вот такой я злой бугага

            //отделяем от всяких пробелов value иии ищем в мапе
            std::string val_name;
            std::remove_copy(read_buf.begin(), read_buf.end(), std::back_inserter(val_name), ' ');
            read_buf = val_name;
            val_name = "";
            std::remove_copy(read_buf.begin(), read_buf.end(), std::back_inserter(val_name), '\t');
            read_buf = val_name;
            val_name = "";
            std::remove_copy(read_buf.begin(), read_buf.end(), std::back_inserter(val_name), '\r');
            values_iter = values.find(val_name);

            if (values_iter == values.end()) //не нашлось, придется добавлять(((
            {
                Value new_value;
                if (def_b) new_value.add_def(filename, count_str);
                else new_value.add_undef(filename, count_str);
                values.insert(std::make_pair(val_name, new_value));

            }
            else //нашлось, обновляем количество DEF-UNDEF
            {
                if(def_b) values_iter->second.add_def(filename, count_str);
                else values_iter->second.add_undef(filename, count_str);
            }
        }
    }
        //Отлично, прочли, теперь надо выводить value в соответствии с условиями
    for(auto value_to_out : values) //пробежимся по мапу в стиле C++11
    {
        /*  Проанализировать строки всех файлов и
        - вывести те value, для которых одновременно выполняются условия:

        * есть хотя бы одно вхождение с type "UNDEF"

        * есть более одного вхождения с type "DEFINE"*/

        if(value_to_out.second.def.size()>1 && value_to_out.second.undef.size()>0)
        {
           //В результате учитывать только вхождения с type "DEFINE".
           //value: file:номер_строки, file:номер_строки
           std::cout << value_to_out.first << ": ";
           for(auto def_to_out : value_to_out.second.def)
              std::cout << def_to_out.first << ":" << def_to_out.second << ", ";
           std::cout << endl;


        }

    }
        /*- вывести те value, для которых одновременно выполняются условия:

        * есть хотя бы одно вхождение с type "DEFINE"

        * нет ни одного вхождения с type "UNDEF"*/
    for(auto value_to_out : values) //из-за формата вывода придется второй раз бегать
    {
        if(value_to_out.second.def.size()>0 && value_to_out.second.undef.size()==0)
        {
            //file: value:номер_строки, value:номер_строки
            std::string file_name = ""; //для сохранения текущего имени файла.
            for(auto def_to_out : value_to_out.second.def)
            {
                if(def_to_out.first!=file_name)
                {
                    std::cout << endl;
                    std::cout << def_to_out.first << ": " << value_to_out.first << ":" << def_to_out.second;
                }
                else std::cout << value_to_out.first << ":" << def_to_out.second;
            }
        }
    }
    std::cout << endl;
    return 0;
}
