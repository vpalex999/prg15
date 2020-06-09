
/*
Бубенщиков О,Ю.
Задание № 2
Вариант № 15.
Построить линейный список из входной последовательности чисел.
Удалить из него все числа, кратные 5.

*/


using namespace std;

struct Element
{
    int data;
    Element* ptr_prev;
};


int main(){

    int SIZE = 3;

    int intarr[SIZE] = {1, 5, 10};

    Element* base_el = nullptr;


    for(int i=0; i<SIZE; i++)
    {
        if(base_el == nullptr)
        {
            base_el = new Element;
            base_el->data = intarr[i];
            base_el-> ptr_prev = nullptr;
        }
        else
        {
            Element* el = new Element;
            el->data = base_el->data;
            el->ptr_prev = nullptr;
            base_el->data = intarr[i];
            base_el->ptr_prev = el;
        }
    }

    return 0;
}