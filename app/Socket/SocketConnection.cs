using System.Net;
using System.Net.Sockets;

namespace AppSocket
{
    public class SocketConnection
    {
        public static Socket ConnectSocket(string ipAddressString, int port)
        {
            try
            {
                IPAddress ipAddress = IPAddress.Parse(ipAddressString);
                IPEndPoint remoteEP = new(ipAddress, port);

                Socket socket = new(ipAddress.AddressFamily, SocketType.Stream, ProtocolType.Tcp);

                try
                {
                    socket.Connect(remoteEP);

                    if(socket.RemoteEndPoint != null)
                        Console.WriteLine("Socket connected to {0}", socket.RemoteEndPoint.ToString());
                }
                catch (ArgumentNullException ane)
                {
                    Console.WriteLine("ArgumentNullException: {0}", ane.ToString());
                }
                catch (SocketException se)
                {
                    Console.WriteLine("SocketException: {0}", se.ToString());
                }
                catch (Exception e)
                {
                    Console.WriteLine("Unexpected exception: {0}", e.ToString());
                }

                return socket;
            }
            catch (Exception e)
            {
                Console.WriteLine(e.ToString());
            }

            return null!;
        }
    }
}
