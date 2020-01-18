using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Knuckles
{
	class SerialCommunicator
	{
		static SerialPort serial;
		static void Main(string[] args)
		{
			serial = new SerialPort
			{
				BaudRate = 9600,
				DtrEnable = true
			};

			bool portOpen = false;

			while (!portOpen)
			{
				serial.PortName = "COM5";

				try
				{
					serial.Open();
					portOpen = true;
				}
				catch (System.IO.IOException)
				{
					Console.WriteLine("Port not found. Try again! :)");
				}
				catch (System.UnauthorizedAccessException)
				{
					Console.WriteLine("Port already open. Try again! :)");
				}
				catch (System.ArgumentException)
				{
					Console.WriteLine("Invalid port. Try again! :)");
				}

				Thread.Sleep(30);
			}

			Thread read = new Thread(() => ReadSerial(serial));
			Thread write = new Thread(() => WriteSerial(serial));

			read.Start();
			write.Start();

		}

		static void ReadSerial(SerialPort s)
		{
			while (true)
			{
				if(s.BytesToRead > 0)
				{
					Console.WriteLine(s.ReadLine().Trim());
					Thread.Sleep(100);
				}
			}

		}
		static void WriteSerial(SerialPort s)
		{
			ControllerInput controller = new ControllerInput();
			while (true)
			{
				String state = controller.Update();
				if (state.Length > 0)
					s.WriteLine("I," + state);
				Thread.Sleep(100);
			}
		}
	}
}
