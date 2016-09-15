import java.util.AbstractMap;
import java.rmi.server.UnicastRemoteObject;
import java.rmi.RemoteException;
import java.util.ArrayList;
 
public class Caminhante         extends UnicastRemoteObject 
        implements CaminhanteI
{
    int x = 0, 
	y = 0; //coordenadas.

    ArrayList<String> mensagemQueue;
    
    public Caminhante()
	throws RemoteException
    {
	mensagemQueue = new ArrayList<String>();
    }
    public void andar(int x, int y)
    {
	this.x += x;
	this.y += y;
    }
    
    public void enviarMensagem(String mensagem)
    {
	mensagemQueue.add(mensagem);
    }

    public String receberMensagem()
    {
	if(mensagemQueue.size() == 0)
	    return "Nao existem mensagens na fila";
	
	String msg = mensagemQueue.get(0);
	mensagemQueue.remove(0);

	return msg;
    }
			       
    public Pair<Integer,Integer> onde()
    {
	return new Pair<Integer,Integer>(x,y);
    }
}
