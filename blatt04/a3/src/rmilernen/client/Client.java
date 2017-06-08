package rmilernen.client;

import rmilernen.server.BasicIf;
import rmilernen.server.BasicPlusIf;
import rmilernen.server.ExtendedIf;

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

    private static void call_basic(int c) {
        Registry registry = null;
        BasicIf basic = null;

        try {
            registry = LocateRegistry.getRegistry();
            basic = (BasicIf) registry.lookup( "Basic" );
        } catch (RemoteException | NotBoundException e) {
            System.err.println("Basic:[ERROR] " + e.getMessage());
        }

        if(registry == null || basic == null) {
            System.err.println("Basic:Could not connect to registry or could not get lookup results!");
        }

        int a = new Random().nextInt(10),
                b = new Random().nextInt(10);
        String  s1 = Client.gstr(3, false),
                s2 = Client.gstr(3, false),
                s3 = Client.gstr(7, true);
        try {
            System.out.println("Basic:rmiSquare(" + a + ") = " + basic.rmiSquare(a));
            System.out.println("Basic:rmiAdd(" + a + ", " + b + ") = " + basic.rmiAdd(a, b));
            System.out.println("Basic:rmiConcat(\"" + s1 + "\", \"" + s2 + "\") = " + basic.rmiConcat(s1, s2));
            System.out.println("Basic:rmiSplit(\"" + s3 + "\") = " + basic.rmiSplit(s3));

            System.out.println("Basic:rmiIncrement()");
            basic.rmiIncrement();

            if (c == 2) {
                System.out.println("Basic:rmiShutdown()");
                basic.rmiShutdown();
            }

            System.out.println("Basic:rmiServernameAtWithException(" + a + ") = " + basic.rmiServernameAtWithException(a));
        } catch (RemoteException e) {
            System.err.println("Basic:[ERROR] " + e.getMessage());
        }
    }

    private static void call_basicplus(int c) {
        Registry registry = null;
        BasicPlusIf basicplus = null;

        try {
            registry = LocateRegistry.getRegistry();
            basicplus = (BasicPlusIf) registry.lookup( "BasicPlus" );
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
            System.out.println("BasicPlus:rmiReaddir() = " + basicplus.rmiReaddir());

            if (c == 2) {
                System.out.println("BasicPlus:rmiShutdown()");
                basicplus.rmiShutdown();
            }

        } catch (RemoteException e) {
            System.err.println("BasicPlus:[ERROR] " + e.getMessage());
        }
    }

    private static void call_extended(int c) {
        Registry registry = null;
        ExtendedIf extended = null;

        try {
            registry = LocateRegistry.getRegistry();
            extended = (ExtendedIf) registry.lookup( "Extended" );
        } catch (RemoteException | NotBoundException e) {
            System.err.println("Extended:[ERROR] " + e.getMessage());
        }

        if(registry == null || extended == null) {
            System.err.println("Extended:Could not connect to registry or could not get lookup results!");
        }

        int a = new Random().nextInt(10),
                b = new Random().nextInt(10);
        String  s1 = Client.gstr(3, false),
                s2 = Client.gstr(3, false),
                s3 = Client.gstr(7, true);

        try {
            System.out.println("Extended:rmiSquare(" + a + ") = " + extended.rmiSquare(a));
            System.out.println("Extended:rmiAdd(" + a + ", " + b + ") = " + extended.rmiAdd(a, b));
            System.out.println("Extended:rmiConcat(\"" + s1 + "\", \"" + s2 + "\") = " + extended.rmiConcat(s1, s2));
            System.out.println("Extended:rmiSplit(\"" + s3 + "\") = " + extended.rmiSplit(s3));

            System.out.println("Extended:rmiIncrement()");
            extended.rmiIncrement();


            System.out.println("Extended:rmiQuad(" + a + ") = " + extended.rmiQuad(a));
            System.out.println("Extended:rmiTwice(\"" + s1 + "\") = " + Arrays.toString(extended.rmiTwice(s1)));
            System.out.println("Extended:rmiReaddir() = " + extended.rmiReaddir());

            if (c == 2) {
                System.out.println("Extended:rmiShutdown()");
                extended.rmiShutdown();
            }

            System.out.println("Extended:rmiServernameAtWithException(" + a + ") = " + extended.rmiServernameAtWithException(a));

        } catch (RemoteException e) {
            System.err.println("Extended:[ERROR] " + e.getMessage());
        }
    }

    public static void main(String[] args) {
        System.out.println("Basic Run 1:\n=================");
        Client.call_basic(1);
        System.out.println("BasicPlus Run 1:\n=================");
        Client.call_basicplus(1);
        System.out.println("Extended Run 1:\n=================");
        Client.call_extended(1);
        System.out.println("Extended Run 2:\n=================");
        Client.call_extended(2);
    }
}
