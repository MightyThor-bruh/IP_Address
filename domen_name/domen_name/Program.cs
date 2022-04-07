using System;
using System.Net;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace domen_name
{
    class Program
    {
        static void Main(string[] args)
        {
            string ip = System.Net.Dns.GetHostEntry("DESKTOP-PKU4T2M").AddressList[0].ToString();

            string host = Dns.GetHostEntry(ip).HostName;
            Console.WriteLine(ip + " " + host);
            Console.ReadLine();
        }
    }
}
