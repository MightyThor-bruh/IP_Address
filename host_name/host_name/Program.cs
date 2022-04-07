using System;
using System.Net;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace host_name
{
    class Program
    {
        static void Main(string[] args)
        {
            string ip = "192.168.56.1";
            IPAddress addr = IPAddress.Parse(ip);
            IPHostEntry entry = Dns.GetHostEntry(addr);
            Console.WriteLine(entry.HostName);
            Console.ReadLine();
        }
    }
}
