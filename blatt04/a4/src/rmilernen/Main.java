package rmilernen;

import rmilernen.server.Server;

public class Main {

    public static void main(String[] args) {
        Server s1 = new Server("basic", 10099);
        Server s2 = new Server("basicplus", 10100);
        Server s3 = new Server("extended", 10101);
    }
}
