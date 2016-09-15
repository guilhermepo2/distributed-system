import java.io.Serializable;
 
public class Pair<T1,T2> implements Serializable
{
    T1 first;
    T2 second;
    
    public Pair(T1 a, T2 b)
    {
      this.first = a;                
      this.second = b;
    }

    public String toString()
    { 
      return "f: " + first + " s:" + second;
    }
}
