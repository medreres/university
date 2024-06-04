package main

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

type Bus struct {
	busNumber string
}

func NewBus(busNumber string) *Bus {
	return &Bus{busNumber}
}

type BusStop struct {
	name        string
	maxCapacity int
	semaphore   chan struct{}
}

func NewBusStop(name string, maxCapacity int) *BusStop {
	return &BusStop{
		name:        name,
		maxCapacity: maxCapacity,
		semaphore:   make(chan struct{}, maxCapacity),
	}
}

func (stop *BusStop) Arrive(bus *Bus) {
	stop.semaphore <- struct{}{}
	fmt.Printf("Bus %s arrived at %s\n", bus.busNumber, stop.name)
}

func (stop *BusStop) Depart(bus *Bus) {
	<-stop.semaphore
	fmt.Printf("Bus %s left %s\n", bus.busNumber, stop.name)
}

type BusRoute struct {
	routeName string
	stops     []*BusStop
	buses     []*Bus
}

func NewBusRoute(routeName string, stops []*BusStop, buses []*Bus) *BusRoute {
	return &BusRoute{
		routeName: routeName,
		stops:     stops,
		buses:     buses,
	}
}

func (route *BusRoute) Run() {
	fmt.Printf("Bus route %s is running.\n", route.routeName)

	var wg sync.WaitGroup
	for _, bus := range route.buses {
		wg.Add(1)
		go func(bus *Bus) {
			defer wg.Done()
			for _, stop := range route.stops {
				stop.Arrive(bus)
				passengerCount := rand.Intn(10) + 1
				fmt.Printf("%d passengers boarded bus %s\n", passengerCount, bus.busNumber)
				time.Sleep(100 * time.Millisecond)
				stop.Depart(bus)
			}
		}(bus)
	}

	wg.Wait()
	fmt.Printf("Bus route %s is completed.\n", route.routeName)
}

func main() {
	rand.Seed(time.Now().UnixNano())

	stop1 := NewBusStop("Stop 1", 3)
	stop2 := NewBusStop("Stop 2", 2)

	bus1 := NewBus("101")
	bus2 := NewBus("102")

	route := NewBusRoute("Route 1", []*BusStop{stop1, stop2}, []*Bus{bus1, bus2})
	route.Run()
}
