using System.Net.Sockets;
using System.Text;

namespace AppSocket
{
    public class SocketCommunication
    {
        public static void SendRequest(Socket socket, string ipAddress, string endpoint, string requestData)
        {
            try
            {
                string request = $"GET {endpoint} HTTP/1.1\r\n" +
                                $"Host: {ipAddress}\r\n" +
                                $"Content-Length: {requestData.Length}\r\n" +
                                "\r\n" +
                                $"{requestData}";

                byte[] requestBytes = Encoding.ASCII.GetBytes(request);

                socket.Send(requestBytes);
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
        }

        public static string ReceiveData(Socket socket)
        {
            try
            {
                byte[] buffer = new byte[1024];

                int bytesRead = socket.Receive(buffer);

                string data = Encoding.ASCII.GetString(buffer, 0, bytesRead);

                return data;
            }
            catch (ArgumentNullException eArgNull)
            {
                Console.WriteLine("ArgumentNullException: {0}", eArgNull.ToString());
            }
            catch (ArgumentOutOfRangeException eArgOutOfRange)
            {
                Console.WriteLine("ArgumentOutOfRangeException: {0}", eArgOutOfRange.ToString());
            }
            catch (SocketException eSocket)
            {
                Console.WriteLine("SocketException: {0}", eSocket.ToString());
            }

            return "";
        }
    }
}