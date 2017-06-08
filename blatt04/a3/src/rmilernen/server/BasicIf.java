package rmilernen.server;

import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.List;

public interface BasicIf extends Remote {
    long rmiSquare(long l) throws RemoteException;
    long rmiAdd(long a, long b) throws RemoteException;
    String rmiConcat(String a, String b) throws RemoteException;
    List<String> rmiSplit(String a) throws RemoteException;
    void rmiIncrement() throws RemoteException;
    void rmiShutdown() throws RemoteException;
    char rmiServernameAtWithException(int i) throws RemoteException;
}
