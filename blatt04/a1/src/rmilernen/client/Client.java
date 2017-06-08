package rmilernen.client;

import rmilernen.server.RMIMethods;

import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.Random;

public class Client {

    private static String gstr(int length, boolean space) {
        char[] s;

        if(!space) {
            s = new char[length];
            for(int i = 0; i < length; i++) s[i] =  (char) ('a' + new Random().nextInt(26));
        } else {
            int m = (int) Math.ceil(length / 2);
            s = new char[length + 1];
            for(int i = 0; i < length; i++) {
                if (i == m){
                    s[i] = ' ';
                } else {
                    s[i] =  (char) ('a' + new Random().nextInt(26));
                }
            }
        }

        return String.copyValueOf(s);
    }

    private static void callable(int c) {
        Registry registry = null;
        RMIMethods vs_rmi = null;

        try {
            registry = LocateRegistry.getRegistry();
            vs_rmi = (RMIMethods) registry.lookup( "RMIMethods" );
        } catch (RemoteException | NotBoundException e) {
            System.err.println("[ERROR] " + e.getMessage());
        }

        int a = new Random().nextInt(10),
            b = new Random().nextInt(10);
        String  s1 = Client.gstr(3, false),
                s2 = Client.gstr(3, false),
                s3 = Client.gstr(7, true);
        try {
            System.out.println("rmiSquare(" + a + ") = " + vs_rmi.rmiSquare(a));
            System.out.println("rmiAdd(" + a + ", " + b + ") = " + vs_rmi.rmiAdd(a, b));
            System.out.println("rmiConcat(\"" + s1 + "\", \"" + s2 + "\") = " + vs_rmi.rmiConcat(s1, s2));
            System.out.println("rmiSplit(\"" + s3 + "\") = " + vs_rmi.rmiSplit(s3));

            System.out.println("rmiIncrement()");
            vs_rmi.rmiIncrement();

            if (c == 2) {
                System.out.println("rmiShutdown()");
                vs_rmi.rmiShutdown();
            }

            System.out.println("rmiServernameAtWithException(" + a + ") = " + vs_rmi.rmiServernameAtWithException(a));
        } catch (RemoteException e) {
            System.err.println("[ERROR] " + e.getMessage());
        }
    }

    public static void main(String[] args) {
        System.out.println("Run 1:\n=================");
        Client.callable(1);
        System.out.println("Run 2:\n=================");
        Client.callable(2);
    }
}
