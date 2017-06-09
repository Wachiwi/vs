package rmilernen.server;

import java.io.File;
import java.net.InetAddress;
import java.net.UnknownHostException;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class ExtendedImpl implements ExtendedIf {

    private static int var = 0;

    @Override
    public long rmiSquare(long l) throws RemoteException {
        System.out.println("Extended:rmiSquare(" + l + ") called!");
        return l * l;
    }

    @Override
    public long rmiAdd(long a, long b) throws RemoteException {
        System.out.println("Extended:rmiAdd(" + a + ", " + b + ") called!");
        return a +b;
    }

    @Override
    public String rmiConcat(String a, String b) throws RemoteException {
        System.out.println("Extended:rmiConcat(\"" + a + "\", \"" + b + "\") called!");
        return a.concat(b);
    }

    @Override
    public List<String> rmiSplit(String a) throws RemoteException {
        System.out.println("Extended:rmiSplit(\"" + a + "\") called!");
        return Arrays.asList(a.split("\\s", 2));
    }

    @Override
    public void rmiIncrement() throws RemoteException {
        System.out.println("Extended:rmiIncrement() called!");
        ExtendedImpl.var++;
    }

    @Override
    public void rmiShutdown() throws RemoteException {
        System.out.println("Extended:rmiShutdown() called!");
        try {
            Registry r = LocateRegistry.getRegistry();
            r.unbind("Extended");
            System.exit(0);
        } catch (NotBoundException e) {
            throw new RemoteException(e.getMessage());
        }
    }

    @Override
    public char rmiServernameAtWithException(int i) throws RemoteException {
        System.out.println("Extended:rmiServernameAtWithException() called!");
        try {
            return InetAddress.getLocalHost().getHostName().charAt(i);
        } catch (UnknownHostException e) {
            throw new RemoteException(e.getMessage());
        }

    }

    @Override
    public List<Long> rmiQuad(long l) throws RemoteException {
        System.out.println("Extended:rmiQuad(" + l + ") called!");
        ArrayList<Long> ll = new ArrayList<>();
        for(long i = 1; i <= l; i++) ll.add(i*i);
        return ll;
    }

    @Override
    public String[] rmiTwice(String a) throws RemoteException {
        System.out.println("Extended:rmiTwice(\"" + a + "\") called!");
        String[] s = new String[2];
        s[0] = a;
        s[1] = a.concat(a);
        return s;
    }

    @Override
    public List<String> rmiReaddir(String p) throws RemoteException {
        System.out.println("Extended:rmiReaddir() called!");
        File f = new File(p);
        return Arrays.asList(f.list());
    }
}
