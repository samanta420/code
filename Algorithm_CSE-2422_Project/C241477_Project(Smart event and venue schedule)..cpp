#include <bits/stdc++.h>
using namespace std;
int parseTimeToMinutes(const string &hhmm) {
    int hh, mm;
    char colon;
    stringstream ss(hhmm);
    ss >> hh >> colon >> mm;
    return hh * 60 + mm;
}

string minutesToHHMM(int minutes) {
    int hh = minutes / 60;
    int mm = minutes % 60;
    char buf[6];
    sprintf(buf, "%02d:%02d", hh, mm);
    return string(buf);
}

struct Event {
    int id;
    string name;
    int start;
    int end;
    int audience;
    int profit;
    string preferredVenue;
    bool assigned = false;
};

struct Venue {
    int id;
    string name;
    int capacity;
    int availableStart;
    int availableEnd;
};

struct Payment {
    int paymentId;
    int eventId;
    int people;
    int totalAmount;
};
vector<Event> events;
vector<Venue> venues;
int nextEventId = 1;
int nextVenueId = 1;
vector<Payment> payments;
int nextPaymentId = 1;

void mergeEventsByEnd(vector<int> &idx, int l, int m, int r) {
    vector<int> left(idx.begin() + l, idx.begin() + m + 1);
    vector<int> right(idx.begin() + m + 1, idx.begin() + r + 1);
    int i = 0, j = 0, k = l;
    while (i < (int)left.size() && j < (int)right.size()) {
        if (events[left[i]].end <= events[right[j]].end) {
            idx[k++] = left[i++];
        } else {
            idx[k++] = right[j++];
        }
    }
    while (i < (int)left.size()) idx[k++] = left[i++];
    while (j < (int)right.size()) idx[k++] = right[j++];
}

void mergeSortIdxByEnd(vector<int> &idx, int l, int r) {
    if (l >= r) return;
    int m = l + (r - l) / 2;
    mergeSortIdxByEnd(idx, l, m);
    mergeSortIdxByEnd(idx, m + 1, r);
    mergeEventsByEnd(idx, l, m, r);
}


int findPreviousCompatible(const vector<int> &sortedIdx, int j) {
    int low = 0, high = j - 1, ans = -1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (events[sortedIdx[mid]].end <= events[sortedIdx[j]].start) {
            ans = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return ans;
}


vector<int> weightedIntervalScheduling(const vector<int> &subsetIdx) {
    int n = subsetIdx.size();
    if (n == 0) return {};
    vector<int> sortedIdx = subsetIdx;
    mergeSortIdxByEnd(sortedIdx, 0, n - 1);

    vector<int> p(n, -1);
    for (int j = 0; j < n; ++j) {
        p[j] = findPreviousCompatible(sortedIdx, j);
    }

    vector<int> dp(n, 0);
    dp[0] = events[sortedIdx[0]].profit;
    for (int j = 1; j < n; ++j) {
        int includeProfit = events[sortedIdx[j]].profit + (p[j] != -1 ? dp[p[j]] : 0);
        int excludeProfit = dp[j - 1];
        dp[j] = max(includeProfit, excludeProfit);
    }


    vector<int> selected;
    int j = n - 1;
    while (j >= 0) {
        int includeProfit = events[sortedIdx[j]].profit + (p[j] != -1 ? dp[p[j]] : 0);
        int excludeProfit = (j - 1 >= 0 ? dp[j - 1] : 0);
        if (includeProfit >= excludeProfit) {
            selected.push_back(sortedIdx[j]);
            j = p[j];
        } else {
            j = j - 1;
        }
    }
    reverse(selected.begin(), selected.end());
    return selected;
}


vector<int> greedyMaxCount(const vector<int> &subsetIdx) {
    int n = subsetIdx.size();
    if (n == 0) return {};
    vector<int> sortedIdx = subsetIdx;
    mergeSortIdxByEnd(sortedIdx, 0, n - 1);

    vector<int> chosen;
    int lastEnd = -1;
    for (int idx : sortedIdx) {
        if (events[idx].start >= lastEnd) {
            chosen.push_back(idx);
            lastEnd = events[idx].end;
        }
    }
    return chosen;
}



map<int, vector<int>> assignEventsToVenues() {

    for (auto &e : events) e.assigned = false;

    vector<int> vIdx;
    for (int i = 0; i < (int)venues.size(); ++i) vIdx.push_back(i);
    sort(vIdx.begin(), vIdx.end(), [&](int a, int b) {
        return venues[a].capacity > venues[b].capacity;
    });

    map<int, vector<int>> schedule;

    for (int vidx : vIdx) {
        Venue &v = venues[vidx];

        vector<int> candidates;
        for (int i = 0; i < (int)events.size(); ++i) {
            if (events[i].assigned) continue;
            if (events[i].audience > v.capacity) continue;
            if (events[i].start < v.availableStart || events[i].end > v.availableEnd) continue;

            candidates.push_back(i);
        }

        if (candidates.empty()) continue;

        vector<int> chosen = weightedIntervalScheduling(candidates);

        for (int eidx : chosen) {
            events[eidx].assigned = true;
            schedule[v.id].push_back(eidx);
        }
    }

    return schedule;
}


void printAllEvents() {
    cout << "\n=== Events ===\n";
    for (const auto &e : events) {
        cout << "[" << e.id << "] " << e.name << " | "
             << minutesToHHMM(e.start) << "-" << minutesToHHMM(e.end)
             << " | audience: " << e.audience << " | profit: " << e.profit;
        if (!e.preferredVenue.empty()) cout << " | preferred: " << e.preferredVenue;
        if (e.assigned) cout << " | (assigned)";
        cout << "\n";
    }
}

void printAllVenues() {
    cout << "\n=== Venues ===\n";
    for (const auto &v : venues) {
        cout << "[" << v.id << "] " << v.name << " | capacity: " << v.capacity
             << " | available: " << minutesToHHMM(v.availableStart) << "-" << minutesToHHMM(v.availableEnd)
             << "\n";
    }
}

void printSchedule(const map<int, vector<int>> &schedule) {
    cout << "\n=== Final Schedule ===\n";
    for (const auto &entry : schedule) {
        int venueId = entry.first;
        const vector<int> &evlist = entry.second;
        // find venue
        auto itv = find_if(venues.begin(), venues.end(), [&](const Venue &vv){ return vv.id == venueId; });
        string vname = (itv != venues.end()) ? itv->name : to_string(venueId);
        cout << "\nVenue: " << vname << " (id=" << venueId << ")\n";
        for (int eidx : evlist) {
            const Event &e = events[eidx];
            cout << "  - [" << e.id << "] " << e.name << " | "
                 << minutesToHHMM(e.start) << "-" << minutesToHHMM(e.end)
                 << " | audience: " << e.audience << " | profit: " << e.profit << "\n";
        }
        if (evlist.empty()) cout << "  (no events assigned)\n";
    }
}


void seedSampleData() {

    events.push_back({nextEventId++, "Tech Talk A", parseTimeToMinutes("09:00"), parseTimeToMinutes("10:30"), 120, 50, "", false});
    events.push_back({nextEventId++, "Startup Pitch", parseTimeToMinutes("10:30"), parseTimeToMinutes("11:00"), 80, 120, "", false});
    events.push_back({nextEventId++, "Workshop ML", parseTimeToMinutes("11:00"), parseTimeToMinutes("13:00"), 60, 200, "Main Hall", false});
    events.push_back({nextEventId++, "Lunch Break", parseTimeToMinutes("13:00"), parseTimeToMinutes("14:00"), 200, 10, "", false});
    events.push_back({nextEventId++, "Panel Discussion", parseTimeToMinutes("14:00"), parseTimeToMinutes("15:30"), 150, 180, "Main Hall", false});
    events.push_back({nextEventId++, "Networking", parseTimeToMinutes("15:30"), parseTimeToMinutes("17:00"), 180, 60, "", false});
    events.push_back({nextEventId++, "Evening Keynote", parseTimeToMinutes("17:30"), parseTimeToMinutes("19:00"), 300, 250, "Main Hall", false});
    venues.push_back({nextVenueId++, "Main Hall", 350, parseTimeToMinutes("09:00"), parseTimeToMinutes("20:00")});
    venues.push_back({nextVenueId++, "Conference Room A", 100, parseTimeToMinutes("09:00"), parseTimeToMinutes("17:00")});
    venues.push_back({nextVenueId++, "Open Area", 250, parseTimeToMinutes("09:00"), parseTimeToMinutes("18:00")});
}

void addEventInteractive() {
    string name, startS, endS, pref;
    int audience, profit;
    cout << "Enter event name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, name);
    cout << "Start time (HH:MM): ";
    getline(cin, startS);
    cout << "End time (HH:MM): ";
    getline(cin, endS);
    cout << "Expected audience (number): ";
    cin >> audience;
    cout << "Profit/importance (integer): ";
    cin >> profit;
    cout << "Preferred Venue (leave empty if none): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, pref);

    int start = parseTimeToMinutes(startS);
    int end = parseTimeToMinutes(endS);
    if (end <= start) {
        cout << "Invalid times: end must be after start.\n";
        return;
    }
    events.push_back({nextEventId++, name, start, end, audience, profit, pref, false});
    cout << "Event added.\n";
}

void addVenueInteractive() {
    string name, startS, endS;
    int capacity;
    cout << "Enter venue name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, name);
    cout << "Capacity (number): ";
    cin >> capacity;
    cout << "Available start time (HH:MM): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, startS);
    cout << "Available end time (HH:MM): ";
    getline(cin, endS);

    int st = parseTimeToMinutes(startS);
    int ed = parseTimeToMinutes(endS);
    if (ed <= st) {
        cout << "Invalid availability times.\n";
        return;
    }
    venues.push_back({nextVenueId++, name, capacity, st, ed});
    cout << "Venue added.\n";
}

void runSchedulingInteractive() {
    if (venues.empty()) {
        cout << "No venues available. Add venues first.\n";
        return;
    }
    if (events.empty()) {
        cout << "No events available. Add events first.\n";
        return;
    }
    auto schedule = assignEventsToVenues();
    printSchedule(schedule);

    cout << "\nUnassigned Events (if any):\n";
    bool anyUnassigned = false;
    for (const auto &e : events) {
        if (!e.assigned) {
            anyUnassigned = true;
            cout << "  - [" << e.id << "] " << e.name << " | "
                 << minutesToHHMM(e.start) << "-" << minutesToHHMM(e.end)
                 << " | audience: " << e.audience << " | profit: " << e.profit << "\n";
        }
    }
    if (!anyUnassigned) cout << "  None\n";
}


void eventCancellationSurvival() {
    if (events.size() < 2) {
        cout << "Not enough events to check cancellation.\n";
        return;
    }

    cout << "\n--- Event Cancellation Survival Strategy ---\n";

    for (int i = 0; i < (int)events.size(); i++) {
        for (int j = i + 1; j < (int)events.size(); j++) {
            if (events[i].end > events[j].start && events[j].end > events[i].start) {
                int dur1 = events[i].end - events[i].start;
                int dur2 = events[j].end - events[j].start;

                double eff1 = (double)events[i].audience / dur1;
                double eff2 = (double)events[j].audience / dur2;

                if (eff1 >= eff2) {
                    cout << "Cancelled: " << events[j].name << "\n";
                    events.erase(events.begin() + j);
                    j--;
                } else {
                    cout << "Cancelled: " << events[i].name << "\n";
                    events.erase(events.begin() + i);
                    i--;
                    break;
                }
            }
        }
    }
}

void customerPayment() {
    int eid, people, price;
    cout << "Enter Event ID: ";
    cin >> eid;
    cout << "Number of people: ";
    cin >> people;
    cout << "Ticket price per person: ";
    cin >> price;

    Payment p;
    p.paymentId = nextPaymentId++;
    p.eventId = eid;
    p.people = people;
    p.totalAmount = people * price;

    payments.push_back(p);

    cout << "Payment successful! Total amount = " << p.totalAmount << "\n";
}


int main() {
    cout << "==== Smart Event & Venue Scheduling System ====\n\n";
    seedSampleData();

    while (true) {
        cout << "\nMenu:\n";
        cout << " 1. List all events\n";
        cout << " 2. List all venues\n";
        cout << " 3. Add event\n";
        cout << " 4. Add venue\n";
        cout << " 5. Run scheduling (assign events to venues maximizing profit per venue)\n";
        cout << " 6. Greedy schedule for a venue (max count)\n";
        cout << " 7. Event Cancellation Survival Strategy (Greedy)\n";
        cout << " 8. Customer Payment\n";
         cout << " 9. Exit\n";
        cout << "Choose option: ";
        int op;
        if (!(cin >> op)) {
            cout << "Invalid input. Exiting.\n";
            break;
        }
        if (op == 1) {
            printAllEvents();
        } else if (op == 2) {
            printAllVenues();
        } else if (op == 3) {
            addEventInteractive();
        } else if (op == 4) {
            addVenueInteractive();
        } else if (op == 5) {
            runSchedulingInteractive();
        } else if (op == 6) {

            if (venues.empty()) { cout << "No venues.\n"; continue; }
            printAllVenues();
            cout << "Enter venue id for greedy scheduling: ";
            int vid;
            cin >> vid;
            int vindex = -1;
            for (int i = 0; i < (int)venues.size(); ++i) if (venues[i].id == vid) vindex = i;
            if (vindex == -1) { cout << "Venue id not found.\n"; continue; }
            Venue &v = venues[vindex];
            vector<int> cand;
            for (int i = 0; i < (int)events.size(); ++i) {
                if (events[i].audience > v.capacity) continue;
                if (events[i].start < v.availableStart || events[i].end > v.availableEnd) continue;
                cand.push_back(i);
            }
            vector<int> chosen = greedyMaxCount(cand);
            cout << "\nGreedy chosen events for venue " << v.name << ":\n";
            for (int eidx : chosen) {
                const auto &e = events[eidx];
                cout << "  - [" << e.id << "] " << e.name << " | "
                     << minutesToHHMM(e.start) << "-" << minutesToHHMM(e.end)
                     << " | audience " << e.audience << "\n";
            }
        }
        else if (op == 7) {
    eventCancellationSurvival();
}
else if (op == 8) {
    customerPayment();
}
else if (op == 9) {
            cout << "Exiting. Goodbye!\n";
            break;
        }

        else {
            cout << "Invalid option.\n";
        }
    }

    return 0;
}
