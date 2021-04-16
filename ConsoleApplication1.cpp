#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>


using namespace std;

const string file_name_basket = "Text.txt";
void basket_via_stack();
void shop_via_queue();

struct stack
{
public:
    struct Node
    {
        string data;
        Node* prev;
    };
    Node* top = NULL;
    size_t count = 0;
    bool push(string);
    bool pop(string&);
    void info();
    size_t size();
};
size_t stack::size()
{
    return count;
}
bool stack::push(string data)
{
    if (!top)
    {
        top = new Node;
        top->prev = NULL;
        count = 1;
    }
    else
    {
        Node* temp;
        temp = new Node;
        temp->prev = top;
        top = temp;
        count++;
    }
    top->data = data;
    return true;
}
bool stack::pop(string& data)
{
    if (!top) return false;

    Node* temp = top->prev;
    data = top->data;
    delete top;
    top = temp;
    count--;
    return true;
}
void stack::info()
{
    if (!top) cout << "Stack is empty" << endl;
    else
    {
        cout << endl << "Stack info:" << endl;
        cout << "\tStack size = " << size() << endl;
        cout << "\tTop data = " << top->data << endl;
    }

    cout << endl;
}



struct queue_interface
{
    size_t item_count;
    size_t item_cost;
    double coef;
};
struct queue
{
public:
    bool push(size_t, size_t);
    bool pop();
    void info();
    size_t size();
    void buy(size_t);

    struct Node
    {
        size_t item_count;
        size_t item_cost;

        Node* next;
    };
    Node* first = NULL;
    size_t count = 0;
    size_t count_all = 0;
    size_t profit = 0;
};
size_t queue::size()
{
    return count;
}
bool queue::push(size_t count, size_t cost)
{
    if (!first)
    {
        first = new Node;
        first->next = NULL;
        first->item_count = count;
        first->item_cost = cost;
        count_all += first->item_count;
        this->count = 1;
    }
    else
    {
        Node* temp;
        temp = first;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = new Node;
        temp->next->item_count = count;
        count_all += temp->next->item_count;
        temp->next->item_cost = cost;
        temp->next->next = NULL;
        this->count++;
    }
    return true;
}
bool queue::pop()
{
    if (!first) return false;
    Node* temp = first->next;
    delete first;
    first = temp;
    count--;
    return true;
}
void queue::info()
{
    if (!first) cout << "Queue is empt\n\tProfit = " << profit << endl;
    else
    {
        cout << endl << "Queue info: " << endl;
        cout << "\tsize = " << size() << endl;
        cout << "\tfirst (count, cost) = " << first->item_count << " " << first->item_cost << " " << count_all << endl;
        cout << "\t\tProfit = " << profit << endl << endl;
    }
}
void queue::buy(size_t count)
{
    if (!first)
    {
        cout << "Товары закончились!" << endl << endl;
        return;
    }
    if (count > count_all)
    {
        cout << "Столько товаров нет!" << endl << endl;
        return;
    }

    const size_t cof = 2; // коофициент (закупочная цена) -> (цена продажи)

    if (count <= first->item_count)
    {
        first->item_count -= count;
        count_all -= count;
        profit += cof * count * first->item_cost;
        if (this->first->item_count == 0)
            pop();
        return;
    }
    else
    {
        count -= first->item_count;
        count_all -= first->item_count;

        profit += cof * first->item_cost * first->item_count;
        first->item_count = 0;
        pop();

    }


    if (count > 0)
        buy(count);
}
int main()
{

    setlocale(LC_ALL, "ru");
    int command = -1;


    while (true)
    {
        cout << "0:Выход\n1:Задание 1\n2:Задание 2\n";
        cout << "Введите номер команды: "; cin >> command; cout << endl << endl;

        if (command == 0)
            return 0;
        else if (command == 1)
            basket_via_stack();
        else if (command == 2)
            shop_via_queue();
    }

    return 0;
}


void basket_via_stack()
{
    stack basket;
    ifstream file(file_name_basket);

    string temp = "";
    while (!file.eof())
    {
        getline(file, temp);
        basket.push(temp);
    }
    file.close();

    while (true)
    {
        cout << endl;
        basket.info();


        cout << "0:Выход\n1:Добавить элемент\n2:Удалить элемент\n3:Очистить корзину\n";
        cout << "Введите номер команды и значение для неё: ";
        int command;
        cin >> command;


        if (command == 0)
            return;
        else if (command == 1)
        {
            getline(cin, temp);
            basket.push(temp);
        }
        else if (command == 2)
        {
            stack items;

            string item;
            getline(cin, item);

            temp = "";
            while ((basket.pop(temp)) && (temp != item))
                items.push(temp);
            while (items.pop(temp))
                basket.push(temp);
        }
        else if (command == 3)
        {
            while (basket.pop(temp))
                ;
        }
    }


}

void shop_via_queue()
{
    queue marge;

    int command;

    while (true)
    {
        cout << "0:Выход\n1:Поступление товара\n2:Продажа товара\n3:Отчёт\n";
        cout << "Введите номер команды: "; cin >> command; cout << endl << endl;

        if (command == 0)
            return;
        else if (command == 1)
        {
            size_t count, cost;
            cout << "Введите количество и стоимость товара за штуку: "; cin >> count >> cost;
            marge.push(count, cost);
        }
        else if (command == 2)
        {
            size_t count;
            cout << "Введите колличество товара для покупки: "; cin >> count;
            marge.buy(count);
        }
        else if (command == 3)
            marge.info();

    }

}