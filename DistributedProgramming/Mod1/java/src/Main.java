import java.util.ArrayList;
import java.util.List;

class Bus {
    private String number;
    private BusRoute route;

    public Bus(String number, BusRoute route) {
        this.number = number;
        this.route = route;
    }

    public void followRoute() {
        for (BusStop stop : route.getStops()) {
            stop.arrive(this);
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            stop.depart(this);
        }
        System.out.println("Bus " + number + " returned to park.");
    }

    @Override
    public String toString() {
        return number;
    }
}

class BusRoute {
    private List<BusStop> stops;

    public BusRoute(List<BusStop> stops) {
        this.stops = stops;
    }

    public List<BusStop> getStops() {
        return stops;
    }
}

class BusStop {
    private String name;
    private int maxBuses;
    private List<Bus> busesAtStop;

    public BusStop(String name, int maxBuses) {
        this.name = name;
        this.maxBuses = maxBuses;
        this.busesAtStop = new ArrayList<>();
    }

    public synchronized void arrive(Bus bus) {
        if (busesAtStop.size() < maxBuses) {
            busesAtStop.add(bus);
            System.out.println("Bus " + bus + " stopped at the bus stop " + name);
        } else {
            System.out.println("At the bus stop " + name + " is no space for Bus " + bus);
        }
    }

    public synchronized void depart(Bus bus) {
        busesAtStop.remove(bus);
        System.out.println("Bus " + bus + " left the stop " + name);
    }
}

public class Main {
    public static void main(String[] args) {
        BusStop stop1 = new BusStop("Stop 1", 2);
        BusStop stop2 = new BusStop("Stop 2", 3);
        BusStop stop3 = new BusStop("Stop 3", 1);
        BusStop stop4 = new BusStop("Stop 4", 4);
        BusStop stop5 = new BusStop("Stop 5", 2);

        List<BusStop> routeStops = new ArrayList<>();
        routeStops.add(stop1);
        routeStops.add(stop2);
        routeStops.add(stop3);
        routeStops.add(stop4);
        routeStops.add(stop5);

        BusRoute route = new BusRoute(routeStops);

        Bus bus1 = new Bus("1", route);
        Bus bus2 = new Bus("2", route);
        Bus bus3 = new Bus("3", route);
        Bus bus4 = new Bus("4", route);

        new Thread(() -> bus1.followRoute()).start();
        new Thread(() -> bus2.followRoute()).start();
        new Thread(() -> bus3.followRoute()).start();
        new Thread(() -> bus4.followRoute()).start();
    }
}
