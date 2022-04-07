// examen_task.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <bitset>
using namespace std;

unsigned long ip, mask;

unsigned long CharToLong(char* ip_)
{
    unsigned long out = 0;
    char* buff;
    buff = new char[3];
    for (int i = 0, j = 0, k = 0; ip_[i] !='\0'; i++, j++) 
    {
        if (ip_[i] != '.')
            buff[j]=ip_[i];
        if (ip_[i] == '.' || ip_[i + 1] == '\0')
        {
            out <<= 8;
            if (atoi(buff) > 255)
                return NULL;
            out += unsigned long(atoi(buff));
            k++;
            j = -1;
            delete[]buff;
            buff = new char[3];
        }
    }
    return out;
}

bool CheckAddress(char* ip_) 
{
    int points = 0; 
    int numbers = 0;
    char* buff = new char[3];
    for (int i = 0; ip_[i] != '\0'; i++) 
    {
        if (ip_[i] <= '9' && ip_[i] >= '0')
        {
            if (numbers > 3) return false;
            buff[numbers++] = ip_[i];
        }
        else
            if (ip_[i] == '.')
            {
                if (atoi(buff) > 255)
                    return false;
                if (numbers == 0)
                    return false;
                numbers = 0;
                points++;
                delete[]buff;
                buff = new char[3];
            }
            else return false;
    }
    if (points != 3)
        return false;
    if (numbers == 0 || numbers > 3)
        return false;
    return true;
}

bool CheckMask(char* mask_)
{
    int points = 0;
    int numbers = 0;
    char* buff = new char[3];
    for (int i = 0; mask_[i] != '\0'; i++)
    {
        if (mask_[i] <= '9' && mask_[i] >= '0')
        {
            if (numbers > 3) return false;
            buff[numbers++] = mask_[i];
        }
        else
            if (mask_[i] == '.')
            {
                if (atoi(buff) > 255)
                    return false;
                if (numbers == 0)
                    return false;
                numbers = 0;
                points++;
                delete[]buff;
                buff = new char[3];
            }
            else return false;
    }
    unsigned long mask = CharToLong(mask_);
    bitset<32> bytemask = (bitset<32>(mask));

    if (points != 3)
        return false;
    if (numbers == 0 || numbers > 3)
        return false;
    for (size_t i = 31; i >= 1; i--)
    {
        if (bytemask[i] == 0 && bytemask[i - 1] == 1)
            return false;
    }
    return true;
}

int main()
{
    setlocale(0, "");
    unsigned long ip, mask;
    char* ip_ = new char[16], * mask_ = new char[16]; bool flag = true;

    do
    {
        if (!flag) cout << "Неверно введён IP-адрес!" << endl;
        cout << "Введите ваш IP-адрес: ";
        cin >> ip_;
    } while (!(flag = CheckAddress(ip_)));

    do
    {
        if (!flag) cout << "Неверно введена маска!" << endl;
        cout << "Введите маску в формате через точку: ";
        cin >> mask_;
    } while (!(flag = CheckMask(mask_)));



    mask = CharToLong(mask_); //Конвертация в unsigned long
    ip = CharToLong(ip_); //Конвертация в unsigned long

    bitset<32> byteip = (bitset<32>(ip));
    bitset<32> bytemask = (bitset<32>(mask));

    bitset<32>host = byteip & ~bytemask; //Расчет HOST ID

    bitset<8> byte1, byte2, byte3, byte4; //Для октетов HOST ID

    for (short i = 31, j = 7; i >= 24; i--, j--)
    {
       
        byte1[j] = host[i];
        byte2[j] = host[i - 8];
        byte3[j] = host[i - 16];
        byte4[j] = host[i - 24];
    }
    cout << "Ваш HOST ID: " << byte1.to_ulong() << "." << byte2.to_ulong() << "." << byte3.to_ulong() << "." << byte4.to_ulong() << endl;
    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
