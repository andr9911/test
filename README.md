# test

Дано N текстовых файлов (file1, file2, fileN), каждый из которых состоит из строк вида:

 

type value

type value

...

type value

 

где, type - это строка, имеющая значение "UNDEF" или "DEFINE"

value - строка произвольной длины, состоящая из ASCII символов.

 

type и value отделены одним или несколькими проблема или символами табуляции

 

* Необходимо: *

 

Проанализировать строки всех файлов и

- вывести те value, для которых одновременно выполняются условия:

  * есть хотя бы одно вхождение с type "UNDEF"

  * есть более одного вхождения с type "DEFINE"

 

В результате учитывать только вхождения с type "DEFINE".

Результат вывести в виде набора строк вида.

value: file:номер_строки, file:номер_строки

...

value: file:номер_строки, file:номер_строки

 

- вывести те value, для которых одновременно выполняются условия:

   * есть хотя бы одно вхождение с type "DEFINE"

   * нет ни одного вхождения с type "UNDEF"

 

Результат вывести в виде набора строк вида:

file: value:номер_строки, value:номер_строки

...

file: value:номер_строки, value:номер_строки

 

Пример: даны файлы

FILE1:

===

UNDEF sym1

UNDEF sym2

UNDEF sym3

UNDEF trololo

UNDEF sym5

UNDEF sym6

DEFINE sym7

UNDEF sym8

DEFINE sym9

 

FILE2:

===

DEFINE sym8

UNDEF rt4

UNDEF rt5

DEFINE rt6

DEFINE sym1

 

FILE3:

===

DEFINE sym1

DEFINE sym6

 

 

* Вывод *

 

sym1: FILE2:5, FILE3:1

 

sym7: FILE1:7

sym9: FILE1:9

rt6: FILE2:4
