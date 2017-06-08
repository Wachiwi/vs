package rmilernen.server;

import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.RemoteServer;
import java.rmi.server.UnicastRemoteObject;

public class Server {

    public static void main(String[] args) {
        try {
            LocateRegistry.createRegistry(Registry.REGISTRY_PORT);
            RemoteServer.setLog(System.out);

            // Basic
            BasicImpl basic = new BasicImpl();
            BasicIf basic_stub = (BasicIf) UnicastRemoteObject.exportObject(basic, 0);

            // BasicPlus
            BasicPlusImpl basicplus = new BasicPlusImpl();
            BasicPlusIf basicplus_stub = (BasicPlusIf) UnicastRemoteObject.exportObject(basicplus, 0);

            // BasicExtended
            ExtendedImpl extended = new ExtendedImpl();
            ExtendedIf extended_stub = (ExtendedIf) UnicastRemoteObject.exportObject(extended, 0);

            Registry registry = LocateRegistry.getRegistry();
            registry.rebind("Basic", basic_stub);
            registry.rebind("BasicPlus", basicplus_stub);
            registry.rebind("Extended", extended_stub);
            System.out.println("RMI-Methoden angemeldet!");
        } catch (RemoteException e) {
            System.out.println("ERROR: " + e.getMessage());
        }
    }
}
