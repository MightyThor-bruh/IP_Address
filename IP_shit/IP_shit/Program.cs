using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IP_shit
{
    class Program
    {
        private static string ToBinary(string input) //перевод в двоичную систему счисления
        {
            IEnumerable<string> parts = input.Split('.').Select(x => Convert.ToString(int.Parse(x), 2).PadLeft(8, '0'));
            return string.Join(".", parts);
        }

        private static string ToDecimal(string input) //перевод из двоичной системы счисления
        {
            IEnumerable<string> parts = input.Split('.').Select(x => Convert.ToInt32(x, 2).ToString());
            return string.Join(".", parts);
        }
        static void Main(string[] args)
        {
            string ip = "10.216.0.134";
            var ipAddress = IPAddress.Parse(ip);
            Console.WriteLine("ip-адрес: " + ip);
            Console.WriteLine(ToBinary(ip));
            Console.WriteLine();

            string mask = "255.255.255.0";
            var maskAddress = IPAddress.Parse(mask);
            Console.WriteLine("Маска: " + mask);
            Console.WriteLine(ToBinary(mask));
            Console.WriteLine();

            string host = GetHostIPAddress(ip, mask);
            Console.WriteLine($"ip-адрес узла: {host}");
            Console.WriteLine(ToBinary(host));
            Console.WriteLine();

            string maximum = GetNodesNetwork(ip, mask);
            Console.WriteLine($"максимальное количество узлов в сети: {maximum}");
            Console.WriteLine(ToBinary(maximum));
            Console.WriteLine();

            Console.ReadKey();
        }
        private static string GetHostIPAddress(string ip, string mask) // ip-адрес узла
        {
            IEnumerable<int> ipParts = ip.Split('.').Select(int.Parse);
            IEnumerable<int> maskParts = mask.Split('.').Select(int.Parse);
            int[] resultParts = ipParts.Zip(maskParts, (x, y) => x & y).ToArray();
            resultParts[resultParts.Length - 1]++;
            return string.Join(".", resultParts);
        }

        private static string GetNodesNetwork(string ip, string mask) // максимальное кол-во узлов в сети
        {
            IEnumerable<int> ipParts = ip.Split('.').Select(int.Parse);
            IEnumerable<int> maskParts = mask.Split('.').Select(int.Parse);


        }
    }
}