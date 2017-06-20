package rmilernen.server;

import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.RemoteServer;
import java.rmi.server.UnicastRemoteObject;

public class Server {

    public Server(String namespace, int port) {
        try {
            Registry registry = LocateRegistry.getRegistry(port);
            if (registry != null) {
                LocateRegistry.createRegistry(port);
                registry = LocateRegistry.getRegistry(port);
            }
            RemoteServer.setLog(System.out);


            switch(namespace) {
                case "basic":
                    // Basic
                    BasicImpl basic = new BasicImpl();
                    BasicIf basic_stub = (BasicIf) UnicastRemoteObject.exportObject(basic, 0);
                    registry.rebind("a4-" + namespace, basic_stub);
                    break;
                case "basicplus":
                    // BasicPlus
                    BasicPlusImpl basicplus = new BasicPlusImpl();
                    BasicPlusIf basicplus_stub = (BasicPlusIf) UnicastRemoteObject.exportObject(basicplus, 0);
                    registry.rebind("a4-" + namespace, basicplus_stub);
                    break;
                case "extended":
                    // BasicExtended
                    ExtendedImpl extended = new ExtendedImpl();
                    ExtendedIf extended_stub = (ExtendedIf) UnicastRemoteObject.exportObject(extended, 0);
                    registry.rebind("a4-" + namespace, extended_stub);
                    break;
                default:
            }

            System.out.println("a4-" + namespace + ":RMI-Methoden für \"a4-" + namespace + "\" angemeldet!");
        } catch (RemoteException e) {
            System.out.println("a4-" + namespace + ":ERROR: " + e.getMessage());
        }
    }

}
