package rmilernen.server;

import java.io.File;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class VSMethodsImpl implements VSMethodsIf {
    @Override
    public List<Long> rmiQuad(long l) throws RemoteException {
        System.out.println("rmiQuad(" + l + ") called!");
        ArrayList<Long> ll = new ArrayList<>();
        for(long i = 1; i < l; i++) ll.add(i*i);
        return ll;
    }

    @Override
    public String[] rmiTwice(String a) throws RemoteException {
        System.out.println("rmiTwice(\"" + a + "\") called!");
        String[] s = new String[2];
        s[0] = a;
        s[1] = a.concat(a);
        return s;
    }

    @Override
    public List<String> rmiReaddir() throws RemoteException {
        System.out.println("rmiReaddir() called!");
        File f = new File(".");
        return Arrays.asList(f.list());
    }

    @Override
    public void rmiShutdown() throws RemoteException {
        System.out.println("rmiShutdown() called!");
        try {
            Registry r = LocateRegistry.getRegistry();
            r.unbind("VSMethods");
            System.exit(0);
        } catch (NotBoundException e) {
            throw new RemoteException(e.getMessage());
        }
    }
}
