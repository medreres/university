import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.CompletableFuture;

interface Foo {
    Double call(Double eps);
}

public class Server {

    private static final int ATTEMPTS_LIMIT = 4;
    private static final int PORT_NUMBER = 8080;
    private static final int SOCKET_TIMEOUT = 2000;
    private static String errorMessage = null;

    public static void main(String[] args) throws IOException {
        // * initialize socket
        try (ServerSocket serverSocket = new ServerSocket(PORT_NUMBER);
                Socket clientSocket = serverSocket.accept()) {

            // * take input
            BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
            String str = in.readLine();
            Double eps = Double.valueOf(str);
            long startTime = System.nanoTime();

            List<CompletableFuture<Double>> futures = new ArrayList<>();

            // * initialize promises
            // TODO add CompletableFuture factory here
            CompletableFuture<Double> future1 = CompletableFuture.supplyAsync(() -> {
                try {
                    return handleCrash((x) -> f(x), eps);
                } catch (Exception e) {
                    errorMessage = e.getMessage();
                    return 0.0;
                }
            });

            // CompletableFuture<Double> future1 = CompletableFuture.supplyAsync(() -> {
            // throw new RuntimeException("Always throwing exception for future1");
            // });

            futures.add(future1);

            CompletableFuture<Double> future2 = CompletableFuture.supplyAsync(() -> {
                try {

                    return handleCrash((x) -> g(x), eps);

                } catch (Exception e) {
                    errorMessage = e.getMessage();
                    return 0.0;
                }
            });

            // * uncomment this and demonstrate that calculations terminate
            // CompletableFuture<Double> future2 = CompletableFuture.supplyAsync(() -> {
            // throw new RuntimeException("Always throwing exception for future2");
            // });

            // TODO provide scalable way to terminate others futures
            future1.exceptionally(throwable -> {
                System.out.println("Future 1 cancel: " + throwable);
                future2.cancel(true);
                errorMessage = "Future 1 has failed";
                return null;
            });

            future2.exceptionally(throwable -> {
                future1.cancel(true);
                System.out.println("Future 2 cancel: " + throwable);
                errorMessage = "Future 2 has failed";
                return null;
            });

            PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);
            // If no exception occurred, proceed with the results
            try {
                double sum = future1.get() + future2.get();
                System.out.println("Result of execution: " + sum);
                out.println("Returned: " + sum);
            } catch (Exception e) {
                out.println(errorMessage);
            }

            long endTime = System.nanoTime();

            System.out.println("Execution took: " + (endTime - startTime) + "ns");

        }

    }

    private static Double f(Double eps) {
        Double x = 0.0;
        int n = 0;

        long start = System.currentTimeMillis();
        long end = start + SOCKET_TIMEOUT; // 2 seconds

        while (System.currentTimeMillis() < end) {
            System.out.println("Iteration: " + n);
            Double s = (Math.pow(-1, n)) / (2 * n + 1);

            if (Math.abs(s) < eps) {
                return 4 * x;
            }

            x += s;
            n++;
        }

        return 0.0;
    }

    private static Double g(Double eps) {
        Double x = 0.0;
        int n = 0;

        long start = System.currentTimeMillis();
        long end = start + SOCKET_TIMEOUT; // 2 seconds

        while (System.currentTimeMillis() < end) {
            Double s = 1 / ((2 * n + 1) * (2 * (double) n + 2));

            if (Math.abs(s) < eps) {
                return x;
            }

            x += s;
            n++;
        }

        return x;
    }

    private static Double handleCrash(Foo func, Double eps) throws Exception {
        if (eps >= 1 || eps <= 0)
            throw new Exception("Not an epsilon");

        if (eps <= Math.pow(10, -10))
            throw new Exception("Epsilon too low");

        Double res = 0.0;
        int iterationsCount = 0;

        while (iterationsCount < ATTEMPTS_LIMIT) {
            res = func.call(eps);

            if (res != 0.0) {
                return res;
            }

            System.out.println("Non-breaking error");
            iterationsCount++;
        }

        throw new Exception("Time limit exceeded");

    }
}