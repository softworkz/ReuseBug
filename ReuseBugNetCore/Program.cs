using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

namespace ReuseBugNetCore
{
    class Program
    {
        private const int SERVICE_PORT = 2222;

        static void Main(string[] args)
        {
            Console.WriteLine("Initializing...");

            try
            {
                using (Socket udpSocket = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp))
                {
                    udpSocket.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.ReuseAddress, true);

                    udpSocket.Bind(new IPEndPoint(IPAddress.Any, SERVICE_PORT));

                    byte[] receiveBuffer = new byte[1024];
                    SocketFlags flags = SocketFlags.None;
                    EndPoint remoteEndPoint = new IPEndPoint(IPAddress.Any, 0);

                    Console.WriteLine("Start listening");
                    udpSocket.ReceiveMessageFrom(receiveBuffer, 0, receiveBuffer.Length, ref flags, ref remoteEndPoint, out IPPacketInformation packetInformation);
                }
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
            }
        }
    }
}
