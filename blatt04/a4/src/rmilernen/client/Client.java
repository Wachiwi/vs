package rmilernen.client;

import rmilernen.server.BasicPlusIf;

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


    private static void call_basicplus(String namespace, int port, int c) {
        Registry registry = null;
        BasicPlusIf basicplus = null;

        try {
            registry = LocateRegistry.getRegistry(port);
            basicplus = (BasicPlusIf) registry.lookup( "a4-" + namespace );
        } catch (RemoteException | NotBoundException e) {
            System.err.println("BasicPlus:[ERROR] " + e.getMessage());
        }

        if(registry == null || basicplus == null) {
            System.err.println("BasicPlus:Could not connect to registry or could not get lookup results!");
        }

        int a = new Random().nextInt(10);
        String  s1 = Client.gstr(3, false);

        try {
            System.out.println("BasicPlus:rmiQuad(" + a + ") = " + basicplus.rmiQuad(a));
            System.out.println("BasicPlus:rmiTwice(\"" + s1 + "\") = " + Arrays.toString(basicplus.rmiTwice(s1)));
            System.out.println("BasicPlus:rmiReaddir(\".\") = " + basicplus.rmiReaddir("."));

            if (c == 2) {
                System.out.println("BasicPlus:rmiShutdown()");
                basicplus.rmiShutdown();
            }

        } catch (RemoteException e) {
            System.err.println("BasicPlus:[ERROR] " + e.getMessage());
        }
    }



    public static void main(String[] args) {
        Client.call_basicplus("basic", 2500, 1);
        Client.call_basicplus("basicplus", 2501,1);
        Client.call_basicplus("extended", 2502, 1);
        Client.call_basicplus("basic", 2500, 1);
    }
}
