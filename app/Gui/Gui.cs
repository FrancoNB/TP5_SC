using System.Net.Sockets;
using Spectre.Console;
using AsciiChart.Sharp;
using Utils;

namespace Gui
{
    class Gui
    {
        public static void Main()
        {
            Socket socket = SocketConfig.SocketConnection.ConnectSocket();

            GuiInit(socket);

            if(socket == null)
                return;

            socket.Close();
        }

        private static void GuiInit(Socket socket)
        {
            var console = AnsiConsole.Console;

            console.Clear();

            console.Write(new FigletText("Sensor App").Centered().Color(Color.DarkCyan));

            var selection = console.Prompt(
                new SelectionPrompt<string>()
                    .PageSize(4)
                    .Title("What signal do you want to see?")
                    .AddChoices(new[] { 
                        "Temperature", "Humidity", "Heat Index", "Distance",
                    }));

            ShowInterface(socket, selection);
        }

        private static void ShowInterface(Socket socket, string signal)
        {
            var console = AnsiConsole.Console;

            console.Clear();

            List<double> dataArray = new();
            
            Random random = new();

            while (true)
            {
                /*
                double temperature = SocketConfig.SocketReceiver.ReceiveData(socket, "temp");
                if (temperature == -1)
                    break;*/
                double data = random.NextDouble() * 50;
                Utils.Utils.UpdateArray(data, dataArray);

                console.Write(new FigletText("Sensor App").Centered().Color(Color.DarkCyan));
                console.Write(new Rule(signal));

                string dataChart = AsciiChart.Sharp.AsciiChart.Plot(
                dataArray.ToArray(), new Options 
                {   Height = 10,
                    AxisLabelLeftMargin = 10,
                    AxisLabelRightMargin = 0, 
                    AxisLabelFormat = "0",
                });

                console.Write(new Rule($"Hour: {DateTime.Now:HH:mm:ss}"));
                console.Write(dataChart);
                
                Thread.Sleep(1000);
                
                console.Clear();
            }
        }
    }
}