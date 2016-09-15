import java.rmi.Remote;
import java.rmi.RemoteException;
 
public interface CaminhanteI extends Remote{
    //andar x passos no eixo x e y passos no eixo y.
    void andar(int x, int y) throws RemoteException;

    void enviarMensagem (String mensagem) throws RemoteException;
    String receberMensagem() throws RemoteException;

    //retorna a posicao atual.
    Pair<Integer,Integer> onde() throws RemoteException; 
}
