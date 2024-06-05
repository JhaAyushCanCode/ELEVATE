#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// Struct to represent an elevator request
struct Request {
    int floor;
    int destination;

    Request(int f, int d) : floor(f), destination(d) {}
};

// Comparator for min heap
struct MinComparator {
    bool operator()(const Request& a, const Request& b) const {
        return a.destination > b.destination;
    }
};

// Comparator for max heap
struct MaxComparator {
    bool operator()(const Request& a, const Request& b) const {
        return a.destination < b.destination;
    }
};

class Elevator {
private:
    int capacity;
    priority_queue<Request, vector<Request>, MinComparator> upQueue;   // Min heap for upward direction
    priority_queue<Request, vector<Request>, MaxComparator> downQueue; // Max heap for downward direction

public:
    Elevator(int cap) : capacity(cap) {}

    // Function to handle call request
    void callRequest(int floor) {
        int destination;
        cout << "Enter destination floor for elevator: ";
        cin >> destination;
        Request req(floor, destination);
        upQueue.push(req); // For simplicity, all requests initially go up
    }

    // Function to serve requests
    void serveRequests() {
        while (!upQueue.empty() || !downQueue.empty()) {
            if (!upQueue.empty()) {
                serveUp();
            }
            if (!downQueue.empty()) {
                serveDown();
            }
        }
    }

    // Function to serve requests going upward
    void serveUp() {
        int count = 0;
        while (!upQueue.empty() && count < capacity) {
            Request req = upQueue.top();
            upQueue.pop();
            cout << "Elevator going to floor " << req.destination << " from floor " << req.floor << endl;
            cout << "Stoppage" << endl;
            count++;
        }
    }

    // Function to serve requests going downward
    void serveDown() {
        int count = 0;
        while (!downQueue.empty() && count < capacity) {
            Request req = downQueue.top();
            downQueue.pop();
            cout << "Elevator going to floor " << req.destination << " from floor " << req.floor << endl;
            cout << "Stoppage" << endl;
            count++;
        }
    }
};

int main() {
    int floors, elevators, capacity;
    cout << "Enter number of floors: ";
    cin >> floors;
    cout << "Enter number of elevators: ";
    cin >> elevators;
    cout << "Enter capacity of each elevator: ";
    cin >> capacity;

    // Create elevators
    vector<Elevator> elevatorList;
    for (int i = 0; i < elevators; ++i) {
        elevatorList.push_back(Elevator(capacity));
    }

    while (true) {
        int callFloor;
        cout << "Enter floor for elevator call request: ";
        cin >> callFloor;

        // Call request for elevator
        elevatorList[0].callRequest(callFloor);

        // Serve requests
        for (int i = 0; i < elevators; ++i) {
            elevatorList[i].serveRequests();
        }
    }

    return 0;
}
