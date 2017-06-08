package rmilernen.server;

import java.net.InetAddress;
import java.net.UnknownHostException;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.Arrays;
import java.util.List;

public class RMIMethodsImpl implements RMIMethods {

    private static int var = 0;

    RMIMethodsImpl() throws RemoteException {
        super();
    }

    @Override
    public long rmiSquare(long l) throws RemoteException {
        System.out.println("rmiSquare(" + l + ") called!");
        return l * l;
    }

    @Override
    public long rmiAdd(long a, long b) throws RemoteException {
        System.out.println("rmiAdd(" + a + ", " + b + ") called!");
        return a +b;
    }

    @Override
    public String rmiConcat(String a, String b) throws RemoteException {
        System.out.println("rmiConcat(\"" + a + "\", \"" + b + "\") called!");
        return a.concat(b);
    }

    @Override
    public List<String> rmiSplit(String a) throws RemoteException {
        System.out.println("rmiSplit(\"" + a + "\") called!");
        return Arrays.asList(a.split("\\s", 2));
    }

    @Override
    public void rmiIncrement() throws RemoteException {
        System.out.println("rmiIncrement() called!");
        RMIMethodsImpl.var++;
    }

    @Override
    public void rmiShutdown() throws RemoteException {
        System.out.println("rmiShutdown() called!");
        try {
            Registry r = LocateRegistry.getRegistry();
            r.unbind("RMIMethods");
            System.exit(0);
        } catch (NotBoundException e) {
            throw new RemoteException(e.getMessage());
        }
    }

    @Override
    public char rmiServernameAtWithException(int i) throws RemoteException {
        System.out.println("rmiServernameAtWithException() called!");
        try {
            return InetAddress.getLocalHost().getHostName().charAt(i);
        } catch (UnknownHostException e) {
            throw new RemoteException(e.getMessage());
        }

    }
}
