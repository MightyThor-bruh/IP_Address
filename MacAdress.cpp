// MacAdress.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <stdio.h>
#include <windows.h>
#include <Winsock2.h>
#include <Iphlpapi.h>
#include "tchar.h"
#pragma comment(lib, "WS2_32.lib")
#pragma comment(lib, "IPHlpApi.Lib")
using namespace std;

char ip[] = "10.7.12.161";

int _tmain(int argc, _TCHAR* argv[])
{
    WSADATA WsaData;
    DWORD _ip = inet_addr(ip);
    if (WSAStartup(0x0202, &WsaData) == NULL)
        printf("WSA Starup OK!\n");

    SOCKET udp_s;
    SOCKADDR_IN udp_sin;
    udp_s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (udp_s != SOCKET_ERROR)
    {
        udp_sin.sin_family = AF_INET;
        udp_sin.sin_port = htons(5232);     udp_sin.sin_addr.s_addr = _ip;
        if (sendto(udp_s, "TEST", 5, NULL, (SOCKADDR*)&udp_sin, sizeof(udp_sin)) > 0)
        {
            MIB_IPNETTABLE* pIpNetTable = (MIB_IPNETTABLE*) new char[0xFFFF];
            ULONG cbIpNetTable = 0xFFFF;
            if (NO_ERROR == GetIpNetTable(pIpNetTable, &cbIpNetTable, TRUE))
            {
                for (DWORD i = 0; i < pIpNetTable->dwNumEntries; i++)
                {
                    if (pIpNetTable->table[i].dwAddr == _ip && pIpNetTable->table[i].dwType != 2)
                    {
                        printf("IP:%s MAC:%X-%X-%X-%X-%X-%X\n", ip,
                            pIpNetTable->table[i].bPhysAddr[0],
                            pIpNetTable->table[i].bPhysAddr[1],
                            pIpNetTable->table[i].bPhysAddr[2],
                            pIpNetTable->table[i].bPhysAddr[3],
                            pIpNetTable->table[i].bPhysAddr[4],
                            pIpNetTable->table[i].bPhysAddr[5]);
                        delete[] pIpNetTable;
                        closesocket(udp_s);
                        WSACleanup();
                        return 0;
                    }
                }
                printf("MAC-address not found\n");
                delete[] pIpNetTable;
            }
            else printf("ERROR Open IPMAC table\n");
        }
        else printf("Send data ERROR!\n");
        closesocket(udp_s);
    }
    else printf("ERROR open socket\n");
    WSACleanup();
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
