using System.Diagnostics;
using System.Threading;
public class SynchronousSocketClient
{
	public static void Main(String[] args)
	{
		string server = @"D:\WEBSITES\www.wins.or.kr\lecture\OS\2011-2\Programs\socket\SynckSocketServer\bin\Debug\SynckSocketServer.exe";
		string client = @"D:\WEBSITES\www.wins.or.kr\lecture\OS\2011-2\Programs\socket\SocketClient\bin\Debug\SocketClient.exe";
		
		Process pClient;
		Process pServer;
		
		pServer = Process.Start(server);
		
		Thread.Sleep(2000);
		
		pClient = Process.Start(client);
		
		Thread.Sleep(2000);
		pClient.Kill();
		pClient = Process.Start(client);
		
		Console.ReadKey();
	}
}
