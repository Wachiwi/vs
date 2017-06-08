package rmilernen.server;

import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.RemoteServer;
import java.rmi.server.UnicastRemoteObject;

public class Server {

    public static void main(String[] args) {
        try {
            LocateRegistry.createRegistry( Registry.REGISTRY_PORT );
            RMIMethodsImpl vs_rmi = new RMIMethodsImpl();
            RMIMethods stub = (RMIMethods) UnicastRemoteObject.exportObject(vs_rmi, 0 );
            RemoteServer.setLog( System.out );

            Registry registry = LocateRegistry.getRegistry();
            registry.rebind( "vsRMI", stub );
            System.out.println( "RMIMethods angemeldet!" );
        }
        catch ( RemoteException e )  {
            System.out.println("ERROR: " + e.getMessage());
        }
    }
}
