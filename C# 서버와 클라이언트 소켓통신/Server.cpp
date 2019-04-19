using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

public class SynchSocketServer
{
	public static int Main(String[] args)
	{
		StartListening();
		return 0;
	}
	
	//Incoming data from the client.
	public static string data = null;
	
	public static void StartListening()
	{
		//Data buffer for incoming data.
		byte[] bytes = new byte[1024];//Byte???
		
		//Establish the local endpoint for the socket.
		//Dns.GetHostName returns the name of the
		//host running the application.
		IPHostEntry ipHostInfo = Dns.Resolve(Dns.GetHostName());
		IPAddress ipAddress = ipHostInfo AddressList[0];
		IPEndPoint localEndPoint = new IPEndPoint(ipAddress, 11000);
		
		//Create a TCP/IP socket.
		Socket listener = new Socket(
			AddressFamily.InterNetwork,
			SocketType.Stream, ProtocolType.Tcp);
		
		try{
			listener.Bind(localEndPoint);
			listener.Listen(10);
			//Start listening for connections.
			
			while(true){
				Console.WriteLine("\nServer is waiting for a connection...");
				//Program is suspended while waiting for an incoming connection.
				Socket handler = listener.Accept();
				data = null;
				//An incoming connection needs to be processed.
				while(true){
					bytes = new byte[1024];
					int bytesRec = handler.Receive(bytes);
					data += Encoding.ASCII.GetString(bytes, 0, bytesRec);
					if(data.IndexOf("<EOF>") > -1)
					{
						break;
					}
				}
				//Show the data on the console.
				Console.WriteLine("Server received Text : {0}", data);
				//Echo the data back to the client.
				byte[] msg = Encoding.ASCII.GetBytes(data);
				handler.Send(msg);
				handler.Shutdown(SocketShutdown.Both);
				handler.Close();
			}
		}
		catch (Exception e){
			Console.Writeline(e.ToString)();
		}
		Console.WriteLine("\nPress ENTER to continue...");
		Console.Read();
	}
}
