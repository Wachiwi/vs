package rmilernen.server;

import java.net.InetAddress;
import java.net.UnknownHostException;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.Arrays;
import java.util.List;

public class BasicImpl implements BasicIf {

    private static int var = 0;

    @Override
    public long rmiSquare(long l) throws RemoteException {
        System.out.println("Basic:rmiSquare(" + l + ") called!");
        return l * l;
    }

    @Override
    public long rmiAdd(long a, long b) throws RemoteException {
        System.out.println("Basic:rmiAdd(" + a + ", " + b + ") called!");
        return a +b;
    }

    @Override
    public String rmiConcat(String a, String b) throws RemoteException {
        System.out.println("Basic:rmiConcat(\"" + a + "\", \"" + b + "\") called!");
        return a.concat(b);
    }

    @Override
    public List<String> rmiSplit(String a) throws RemoteException {
        System.out.println("Basic:rmiSplit(\"" + a + "\") called!");
        return Arrays.asList(a.split("\\s", 2));
    }

    @Override
    public void rmiIncrement() throws RemoteException {
        System.out.println("Basic:rmiIncrement() called!");
        BasicImpl.var++;
    }

    @Override
    public void rmiShutdown() throws RemoteException {
        System.out.println("Basic:rmiShutdown() called!");
        try {
            Registry r = LocateRegistry.getRegistry();
            r.unbind("Basic");
            System.exit(0);
        } catch (NotBoundException e) {
            throw new RemoteException(e.getMessage());
        }
    }

    @Override
    public char rmiServernameAtWithException(int i) throws RemoteException {
        System.out.println("Basic:rmiServernameAtWithException() called!");
        try {
            return InetAddress.getLocalHost().getHostName().charAt(i);
        } catch (UnknownHostException e) {
            throw new RemoteException(e.getMessage());
        }

    }
}
