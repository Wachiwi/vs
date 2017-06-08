package rmilernen.server;

import java.rmi.RemoteException;
import java.util.Arrays;
import java.util.List;

public class RMIMethodsImpl implements RMIMethods {

    private static int var = 0;

    RMIMethodsImpl() throws RemoteException {
        super();
    }

    @Override
    public long rmiSquare(long l) throws RemoteException {
        return l * l;
    }

    @Override
    public long rmiAdd(long a, long b) throws RemoteException {
        return a +b;
    }

    @Override
    public String rmiConcat(String a, String b) throws RemoteException {
        return a.concat(b);
    }

    @Override
    public List<String> rmiSplit(String a) throws RemoteException {
        return Arrays.asList(a.split("\\s", 2));
    }

    @Override
    public void rmiIncrement() throws RemoteException {
     RMIMethodsImpl.var++;
    }

    @Override
    public void rmiShutdown() throws RemoteException {

    }

    @Override
    public char rmiServernameAtWithException(int i) throws RemoteException {
        return 0;
    }
}
