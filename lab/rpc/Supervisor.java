import java.net.UnknownHostException;
import java.rmi.Naming;
import java.rmi.RemoteException;
import java.util.Scanner;
 
 public class Supervisor implements Runnable
{
    public static void main(String[] args)
    {
        CaminhanteI c = null;                
        try 
        {
            c  = (CaminhanteI) Naming.lookup(args[0]);
            Supervisor s = new Supervisor(c);
             (new Thread(s)).start();

            Thread.sleep(6000);
        }
        catch(Exception e)                
        {
            e.printStackTrace();
            System.exit(1);
        }
    } 
    CaminhanteI c;

    public Supervisor(CaminhanteI c)
    {                this.c = c;
    }

    public void run() 
    {                
        try
        {
            while(true)
            {
		System.out.println("1 - Enviar 2 - Receber");
		int opt;

		Scanner s = new Scanner(System.in);
		opt = s.nextInt();
		
		if(opt == 1)
		    {
			c.enviarMensagem("Hello World");
		    }
		else if (opt == 2)
		    System.out.println(c.receberMensagem());
	     
                c.andar(10,10);
		Thread.sleep(1000);
                //System.out.println(c.onde());
            }
        }
        catch(Exception e)                
        {
            e.printStackTrace();
        }
    }
}

