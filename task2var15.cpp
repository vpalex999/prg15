
/*
Бубенщиков О,Ю.
Задание № 2
Вариант № 15.
Построить линейный список из входной последовательности чисел.
Удалить из него все числа, кратные 5.

тестовые случаи:
{}          = null
{5}         = null
{5,10}      = null
{5,1,10}    = {1}
{2, 5,10,3} = {2,3}
{4,10,6,5}  = {4,6}
{2,3,4}     = {2,3,4}

*/

#include <iostream>

using namespace std;

struct Element
{
    int data;
    Element* ptr_next;
};



Element* create_list(int* intarr, int size)
// создать односвязный список
{
    Element* base_el;
    base_el = NULL;

    for(int i=0; i<size; i++)
    {
        Element* el = new Element;
        el->data = intarr[i];
        el->ptr_next = base_el;
        base_el = el;
    }
    return base_el;
}


Element* delete_elelements_by_module(Element* base_el, int by_mod)
{

    Element* el = base_el;      // создать указатель для итерации
    Element* prev_el = base_el; // хранит адрес предыдущего элемента

    // итерируемся пока не дойдем до конца списка: (el != null)
    while (el)
    {
        // если удаляемый элемент - начало списка:
        if(el->data % by_mod == 0 and el == base_el)
        {
            // если элемент является единственным
            if(el->ptr_next == NULL)    
            {
                delete base_el;     // освобождаем память
                return NULL;        // списка нет, указателю не на что ссылаться
            }
            // если есть следующий элемент:
            else
            {   
                Element* tmp = base_el;         // копируем указатель удаляемого эл-та
                base_el = base_el->ptr_next;    // в базовый указатель копируемадрес следующего эл-та.
                delete tmp;                     // освобождаем память первого эл-та.
                el = base_el;                   // копируем в указатель итераций новый базовый адресс.
                prev_el = el;                   // обновляем указатель предыдужего эл-та.
                continue;                       // переход на начало цикла
            }
            
        }
        // если не первый эл-т списка и кандидат на удаление
        else if(el->data % by_mod == 0)
        {
            
            prev_el->ptr_next = el->ptr_next;   // обновить ссылку указателя предудущего эл-та на следующий эл-т.
            Element* tmp = el;                  // копируем указатель удаляемого эл-та
            delete tmp;                         // освобождаем память эл-та.
            el = prev_el->ptr_next;             // копируем в указатель итераций адрес следующего эл-та.
            continue;                           // переход на начало цикла
        }
        // текущий эл-т не кандидат на удаление
        prev_el = el;       // обновляем указатель предыдужего эл-та.      
        el = el->ptr_next; // копируем в указатель итераций адрес следующего эл-та.
    }
    return base_el; // возвращаем указатель на начало списка
}


void show_list(Element* base_el)
{
    // вывести значения эл-тов списка в консоль.
    Element* el = base_el;

    cout << "list data: ";
    
    // итерируемся пока не дойдем до конца списка: (el != null)
    while (el)
    {
        cout << el->data << " ";
        el = el->ptr_next;
    }
    cout << endl;
}


void delete_list(Element* base_el)
{
    // удаляет список, освобождает память
    Element* el = base_el;  // создать указатель для итерации

    // итерируемся пока не дойдем до конца списка: (el != null)
    while (el)
    {
        base_el = el->ptr_next;         // копируем в базовый указатель адрес след. эл-та.
        delete el;                      // удалить текущий элемент.
        el = base_el;                   // в указатель итерации скопировать адресс базового указателя (след. эл-та).
    }
    cout << "deleting elements is complete\n";
}

int main()
{

    const int SIZE = 3;

    int intarr[SIZE] = {2,3,4};

    

    Element* base_el = create_list(intarr, SIZE);

    show_list(base_el);

    base_el = delete_elelements_by_module(base_el, 5);

    show_list(base_el);

    delete_list(base_el);

    return 0;
}