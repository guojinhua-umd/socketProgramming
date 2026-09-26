/* 
 * Client.java
 */

import java.io.*;
import java.net.*;

public class Client 
{
    public static final int SERVER_PORT = 5432;

    public static void main(String[] args) 
    {
	Socket clientSocket = null;  
	PrintStream os = null;
	String userInput = null;
	BufferedReader stdInput = null;

	//Check the number of command line parameters
	if (args.length < 1)
	{
	    System.out.println("Usage: client <Server IP Address>");
	    System.exit(1);
	}

	// Try to open a socket on SERVER_PORT
	// Try to open input and output streams
	try 
	{
	    clientSocket = new Socket(args[0], SERVER_PORT);
	    os = new PrintStream(clientSocket.getOutputStream());
	    stdInput = new BufferedReader(new InputStreamReader(System.in));
	} 
	catch (UnknownHostException e) 
	{
	    System.err.println("Don't know about host: hostname");
	} 
	catch (IOException e) 
	{
	    System.err.println("Couldn't get I/O for the connection to: hostname");
	}

	// If everything has been initialized then we want to write some data
	// to the socket we have opened a connection to on port 25

	if (clientSocket != null && os != null) 
	{
	    try 
	    {
		//Start a child thread to handle the server's messages
		SThread sThread = new SThread(clientSocket);
		sThread.start();

		//handle the user input
		while ((userInput = stdInput.readLine())!= null)
		{
		    os.println(userInput);
		}

		// close the input and output stream
		// close the socket
		os.close();
		clientSocket.close();   
		System.exit(0);
	    } 
	    catch (IOException e) 
	    {
	    }
	}
    }           
}

/*
 * SThread Class, which handle the server's messages
 */
class SThread extends Thread 
{
    Socket socket;
    BufferedReader is = null;
    String serverInput = null;

    /**
     * Constructor
     */
    SThread(Socket socket)
    {
	this.socket = socket;
    }

    /*
     * Child thread of execution, handle the server's messages
     */
    public void run()
    {
	try 
	{
	    is = new BufferedReader(new InputStreamReader(socket.getInputStream()));

	    while ((serverInput = is.readLine())!= null)
	    {
		System.out.println("s:" + serverInput);
	    }

	    is.close();
	    socket.close();   
	    System.exit(0);
	} 
	catch (IOException e) 
	{
	}
    }           
}
