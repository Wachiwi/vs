package rmilernen.server;

import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.List;

public interface VSMethodsIf extends Remote {
        List<Long> rmiQuad(long l) throws RemoteException;
        String[] rmiTwice(String a) throws RemoteException;
        List<String> rmiReaddir(String p) throws RemoteException;
        void rmiShutdown() throws RemoteException;
}
