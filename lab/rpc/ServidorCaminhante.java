import java.rmi.Naming;
 
public class ServidorCaminhante
{
    public static void main(String[] args)        
    {
        try
        {
            CaminhanteI cam = new Caminhante();
            Naming.rebind(args[0],cam);
            System.out.println("registrado" + args[0]);
        }
        catch(Exception e)
        {
            System.err.println(e);
        }
    }
}

