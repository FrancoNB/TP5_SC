using System.Net.Sockets;
using System.Text;

namespace SocketConfig
{
    public class SocketReceiver
    {
        public static double ReceiveData(Socket socket, string signal)
        {
            try
            {
                byte[] bytes = new byte[8];

                socket.Send(Encoding.ASCII.GetBytes(signal));

                socket.Receive(bytes);

                return BitConverter.ToDouble(bytes, 0);
            }
            catch (ArgumentNullException ane)
            {
                Console.WriteLine("ArgumentNullException: {0}", ane.ToString());

                return -1;
            }
            catch (SocketException se)
            {
                Console.WriteLine("SocketException: {0}", se.ToString());

                return -1;
            }
            catch (Exception e)
            {
                Console.WriteLine("Unexpected exception: {0}", e.ToString());

                return -1;
            }
        }
    }
}