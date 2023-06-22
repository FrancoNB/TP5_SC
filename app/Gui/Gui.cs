using System.Net.Sockets;
using Spectre.Console;
using AsciiChart.Sharp;
using AppSocket;
using AppUtils;

namespace AppGui
{
    class Gui
    {
        private static string? ipAddress, port;
        public static void Main()
        {            
            //(ipAddress, port) = Utils.GetServerConnectionInfo();
            ipAddress = "127.0.0.1";
            port = "8080";
            Socket socket = SocketConnection.ConnectSocket(ipAddress, int.Parse(port));
            
            if(socket == null)
                return;
            
            SocketCommunication.SendRequest(socket, ipAddress, "/sensors", "");

            //string data = SocketCommunication.ReceiveData(socket);
            string data = @"{
                            ""numSensors"": ""4"",
                            ""sensors"": ""temperature humidity heat_index altitude""
                            }";
            (string NumSensors, string[] Sensors) = Utils.JsonDecode(data);

            GuiInit(socket, ushort.Parse(NumSensors), Sensors);
        }
        
        private static void GuiInit(Socket socket, UInt16 numSensors, string[] sensors)
        {
            AnsiConsole.Clear();

            while(true)
            {
                AnsiConsole.Write(new FigletText("Sensor App").Centered().Color(Color.DarkCyan));

                var selection = AnsiConsole.Prompt(
                    new SelectionPrompt<string>()
                        .PageSize(numSensors)
                        .Title("What [green]signal[/] do you want to see?")
                        .AddChoices(sensors));

                ShowInterface(socket, selection);
            }
        }

        private static void ShowInterface(Socket socket, string signal)
        {
            List<double> dataArray = new();
            
            Random random = new();

            ConsoleKeyInfo keyInfo;

            while (true)
            {
                AnsiConsole.Clear();

                if (Console.KeyAvailable)
                {
                    keyInfo = Console.ReadKey(true);

                    if ((keyInfo.Modifiers & ConsoleModifiers.Control) != 0 && keyInfo.Key == ConsoleKey.A)
                        break;
                }
                /*
                SocketCommunication.SendRequest(socket, ipAddress);

                SocketCommunication.ReceiveData(socket);
                */
                double data = random.NextDouble() * 50;
                AppUtils.Utils.UpdateArray(data, dataArray);

                AnsiConsole.Write(new FigletText("Sensor App").Centered().Color(Color.DarkCyan));
                AnsiConsole.WriteLine();
                AnsiConsole.Write(new Rule(signal));
                AnsiConsole.WriteLine();

                string dataChart = AsciiChart.Sharp.AsciiChart.Plot(
                    dataArray.ToArray(), new Options 
                    {   Height = 20,
                        AxisLabelLeftMargin = 10,
                        AxisLabelRightMargin = 1, 
                        AxisLabelFormat = "0",
                    });

                AnsiConsole.Write(new Rule($"Hour: {DateTime.Now:HH:mm:ss}"));
                AnsiConsole.WriteLine();
                AnsiConsole.Write(dataChart);

                Thread.Sleep(1000);
            }
        }
    }
}