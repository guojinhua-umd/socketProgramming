/* 
 * ChildThread.java
 */


import java.io.*;
import java.net.Socket;
import java.util.Vector;

public class ChildThread extends Thread 
{
    static  Vector<ChildThread> handlers = new Vector<ChildThread>(20);
    private Socket socket;
    private BufferedReader in;
    private PrintWriter out;

    public ChildThread(Socket socket) throws IOException 
    {
	this.socket = socket;
	in = new BufferedReader(
	    new InputStreamReader(socket.getInputStream()));
	out = new PrintWriter(
	    new OutputStreamWriter(socket.getOutputStream()));
    }

    public void run() 
    {
	String line;
	synchronized(handlers) 
	{
	    // add the new client in Vector class
	    handlers.addElement(this);
	}

	try 
	{
	    while ((line = in.readLine()) != null) 
	    {
		System.out.println(line);
	
		// Broadcast it to everyone!  You will change this.  
		// Most commands do not need to broadcast
		for(int i = 0; i < handlers.size(); i++) 
		{	
		    synchronized(handlers) 
		    {
			ChildThread handler =
			    (ChildThread)handlers.elementAt(i);
			if (handler != this) 
			{
			    handler.out.println(line);
			    handler.out.flush();
			}
		    }
		}
	    }
	} 
	catch(IOException ioe) 
	{
	    ioe.printStackTrace();
	} 
	finally 
	{
	    try 
	    {
		in.close();
		out.close();
		socket.close();
	    } 
	    catch(IOException ioe) 
	    {
	    } 
	    finally 
	    {
		synchronized(handlers) 
		{
		    handlers.removeElement(this);
		}
	    }
	}
    }
}

