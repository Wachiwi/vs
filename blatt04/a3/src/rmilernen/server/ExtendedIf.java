package rmilernen.server;

import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.List;

public interface ExtendedIf extends Remote {
    // Basic
    long rmiSquare(long l) throws RemoteException;
    long rmiAdd(long a, long b) throws RemoteException;
    String rmiConcat(String a, String b) throws RemoteException;
    List<String> rmiSplit(String a) throws RemoteException;
    void rmiIncrement() throws RemoteException;
    char rmiServernameAtWithException(int i) throws RemoteException;

    // Basic Plus
    List<Long> rmiQuad(long l) throws RemoteException;
    String[] rmiTwice(String a) throws RemoteException;
    List<String> rmiReaddir() throws RemoteException;

    // Duplicate
    void rmiShutdown() throws RemoteException;
}
