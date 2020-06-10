/*
Бубенщиков О,Ю.
Задание № 1
Вариант № 15.
Дан символьный файл.
Произвести «сжатие» этого файла, заменив каждую последовательность
из нескольких вхождений одного и того же символа записью вида x’k’,
где x – число вхождений символа k в исходную последовательность.
Сравнить размеры файлов.


З.Ы. Корретная обработка только для ASCII кодировки
З.Ы. Структура файла не меняется, переносы строк соблюдаются
З.Ы. При подсчёте размера файлов, служебные символы преноса строк не учитываются.
З.Ы. Работа выполненна и проверялась на ОС Linux(Ubuntu), поведение в Windows не проверялось.

*/

#include <fstream>
#include <ostream>
#include <iostream>
#include <string>

using namespace std;


int get_size(string filename)
{
    int size = 0; // элемент char имеет размер 1 байт


    ifstream infile(filename);

    char ch;

    while(infile)
    {
        ch = infile.get();
        if(int(ch) == -1)
            break;
        if(ch == '\r' or ch == '\n')
            continue;
        size++;
    }

    infile.close();

    return size;
}


void write_data(ofstream& outfile, char ch_saved, int count)
{
    if(count > 1)   // если счётчик хранит серию одного элемента
        outfile << count << '\'' << ch_saved << '\'';
    else if (count == 1)    // если счётчик хранит один элемент
        outfile << ch_saved;
}


int main()
{
    string src_file = "test_task1.txt";
    string dst_file = "archive_test_task1.txt";

    ifstream infile(src_file);
    ofstream outfile(dst_file);

    char ch;
    char ch_saved;
    int count = 0;

    while(infile)
    {
        ch = infile.get();
        
        // если получили символы перевода строки:
        if(ch == '\n' or ch == '\r')    
        {
            write_data(outfile, ch_saved, count);

            outfile << ch;  // записать перевод строки
            count = 0;      // обнулить счётчик
            continue;       // перейти на начало цикла
        }
        // если больше нет данных для чтения:
        if(int(ch) == -1)
        {
            write_data(outfile, ch_saved, count);
            break;  // выход из цикла
        }
        else
        {   
            // если это начало обработки файла или новой строки
            if(count == 0)  
            {
                ch_saved = ch;
                count++;
            }
            else if (ch == ch_saved)    // если символ повторяется
                count++;                // увеличиваем счётчик
            else    // если получили новый символ
            {
                // сохранить текущий счетчик и символ
                write_data(outfile, ch_saved, count);
                // записать новые значения
                ch_saved = ch;
                count = 1;
            }
        }
    }

    infile.close();
    outfile.close();

    cout << src_file << " has size: " << get_size(src_file) << " byte (s)\n";
    cout << dst_file << " has size: " << get_size(dst_file) << " byte (s)\n";

    return 0;
}

