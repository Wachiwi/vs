package rmilernen.client;

import rmilernen.server.VSMethodsIf;

import java.io.EOFException;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.Arrays;
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
        VSMethodsIf vs_rmi = null;

        try {
            registry = LocateRegistry.getRegistry();
            vs_rmi = (VSMethodsIf) registry.lookup( "VSMethods" );
        } catch (RemoteException | NotBoundException e) {
            System.err.println("[ERROR] " + e.getMessage());
        }

        if(registry == null || vs_rmi == null) {
            System.err.println("Could not connect to registry or could not get lookup results!");
        }

        int a = new Random().nextInt(10);
        String  s1 = Client.gstr(3, false);

        try {
            System.out.println("rmiQuad(" + a + ") = " + vs_rmi.rmiQuad(a));
            System.out.println("rmiTwice(\"" + s1 + "\") = " + Arrays.toString(vs_rmi.rmiTwice(s1)));
            System.out.println("rmiReaddir(\".\") = " + vs_rmi.rmiReaddir("."));

            if (c == 2) {
                System.out.println("rmiShutdown()");
                vs_rmi.rmiShutdown();
            }

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
