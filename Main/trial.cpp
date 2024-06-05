#include <iostream>
#include <queue>
#include <vector>
#include <thread>
#include <chrono>
#include <limits>

using namespace std;

struct Elevator {
    int id;
    int currentFloor;
    int direction; // 1 for up, -1 for down
    priority_queue<int, vector<int>, greater<int>> requestsUp;
    priority_queue<int> requestsDown;
};

void liveUpdate(vector<Elevator>& elevators) {
    while (true) {
        cout << "Live Update:" << endl;
        for (int i = 0; i < elevators.size(); ++i) {
            cout << "Elevator " << elevators[i].id << ": Floor " << elevators[i].currentFloor << ", Direction " << (elevators[i].direction == 1 ? "Up" : "Down") << endl;
        }
        cout << endl;
        this_thread::sleep_for(chrono::seconds(2));
    }
}

void processRequest(vector<Elevator>& elevators, int floor, int destination, int capacity) {
    int closest = -1;
    int minDistance = numeric_limits<int>::max(); // Using numeric_limits to get INT_MAX
    for (int i = 0; i < elevators.size(); ++i) {
        int distance = abs(elevators[i].currentFloor - floor);
        if (distance < minDistance && (elevators[i].direction == 0 || elevators[i].direction == (floor > elevators[i].currentFloor ? 1 : -1))) {
            closest = i;
            minDistance = distance;
        }
    }
    if (closest != -1) {
        if (elevators[closest].requestsUp.size() + elevators[closest].requestsDown.size() < capacity) {
            elevators[closest].direction = floor > elevators[closest].currentFloor ? 1 : -1;
            if (elevators[closest].direction == 1) {
                elevators[closest].requestsUp.push(floor);
            } else {
                elevators[closest].requestsDown.push(floor);
            }
        } else {
            cout << "Elevator " << elevators[closest].id << " is at full capacity." << endl;
        }
    } else {
        cout << "No available elevator to serve the request." << endl;
    }
}

void elevatorController(int floors, int elevators, int capacity) {
    vector<Elevator> elevatorList;
    for (int i = 0; i < elevators; ++i) {
        Elevator elevator;
        elevator.id = i + 1;
        elevator.currentFloor = 0;
        elevator.direction = 0;
        elevatorList.push_back(elevator);
    }

    thread liveUpdater(liveUpdate, ref(elevatorList));

    while (true) {
        int call_req_at, destination_req;
        cout << "Enter floor for elevator call request (-1 to exit): ";
        cin >> call_req_at;
        if (call_req_at == -1) break;
        cout << "Enter destination floor: ";
        cin >> destination_req;

        processRequest(elevatorList, call_req_at, destination_req, capacity);
    }

    liveUpdater.join();
}

int main() {
    int floors, elevators, capacity;
    cout << "Enter number of floors: ";
    cin >> floors;
    cout << "Enter number of elevators: ";
    cin >> elevators;
    cout << "Enter maximum capacity of one elevator: ";
    cin >> capacity;

    elevatorController(floors, elevators, capacity);

    return 0;
}
