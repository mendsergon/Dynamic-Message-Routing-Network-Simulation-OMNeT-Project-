## Dynamic Message Routing Network Simulation (OMNeT++ Project)

### Project Summary

This OMNeT++ project implements a **dynamic message routing network** where nodes generate messages with randomly selected destinations and forward them through a connected network topology. The simulation features **bidirectional communication channels**, **dynamic destination selection**, and **comprehensive message tracking**. Each node maintains statistics on messages generated, received, and transmitted, with the simulation terminating when any node generates three messages. The project demonstrates **discrete event simulation**, **network protocol design**, and **dynamic routing algorithms** in a distributed system.

---

### Core Features

* **Dynamic Message Generation:** Nodes create messages with randomly assigned destinations (excluding self)
* **Bidirectional Communication:** Uses inout gates for two-way node connections
* **Hop Count Tracking:** Messages record the number of hops during routing via dedicated `forwardMessage()` method
* **Statistical Monitoring:** Real-time tracking of generated, received, and transmitted messages per node
* **Adaptive Termination:** Simulation ends when any node reaches the 3-message generation limit
* **Randomized Routing:** Messages are forwarded through randomly selected output gates

---

### Key Methods and Algorithms

#### 1. **Network Topology Design**

* Implements a **6-node network** with specific connectivity pattern:
  - PC[0] connected to PC[1] and PC[2]
  - PC[1] connected to PC[3]  
  - PC[2] connected to PC[3]
  - PC[3] connected to PC[4] and PC[5]
* Uses **bidirectional channels** with configurable delay parameters

#### 2. **Dynamic Message Creation**

* **Random Destination Selection:** Each node generates destinations using uniform random distribution excluding itself
* **Message Identification:** Messages are named using format `msg-<source>-to-<destination>`
* **Parameter Encapsulation:** Custom `NodeMsg` class extends `cMessage` with source, destination, and hopCount fields

#### 3. **Message Routing Algorithm**

* **Destination Checking:** Each node verifies if incoming message is destined for itself
* **Forward Message Method:** Dedicated `forwardMessage()` method handles hop counting and message transmission as required by exercise specifications
* **Hop Counting:** Increments hopCount in `forwardMessage()` before forwarding to track path length
* **Random Gate Selection:** Uses `intuniform(0, gateSize("gate") - 1)` for output gate selection
* **Safe Message Handling:** Employs `check_and_cast<NodeMsg*>()` for type-safe message processing

#### 4. **Statistical Tracking System**

* **Per-Node Counters:** Tracks messagesGenerated, messagesReceived, messagesTransmitted
* **Automatic Termination:** Simulation ends via natural event completion when generation limit reached
* **Final Reporting:** `finish()` method displays comprehensive statistics for each node

#### 5. **Event-Driven Simulation**

* **Self-Message Scheduling:** Uses `scheduleAt()` for timed message generation
* **Channel Communication:** Implements bidirectional message passing through OMNeT++ channels
* **Dynamic Behavior:** Network behavior evolves based on random destinations and routing decisions

---

### Skills Demonstrated

* **Discrete Event Simulation:** OMNeT++ framework mastery and event scheduling
* **Network Protocol Design:** Dynamic routing and message forwarding algorithms
* **Object-Oriented Programming:** Custom message classes and module inheritance
* **Statistical Analysis:** Comprehensive message tracking and performance metrics
* **Randomized Algorithms:** Destination selection and routing decisions
* **Bidirectional Communication:** Inout gate implementation and channel management
* **Memory Management:** Proper message deletion and resource handling
* **Simulation Configuration:** NED file topology definition and parameter setting
* **Methodology Compliance:** Strict adherence to exercise specifications including dedicated `forwardMessage()` method

---

### File Overview

| File Name | Description |
|-----------|-------------|
| **Network.ned** | Defines network topology with 6 nodes and bidirectional connections |
| **Node.ned** | Specifies node module with inout gates for bidirectional communication |
| **NodeMsg.msg** | Custom message definition with source, destination, and hopCount fields |
| **Node.h** | Node class declaration with message handling, statistics, and `forwardMessage()` method |
| **Node.cc** | Implementation of node behavior, routing logic with `forwardMessage()`, and statistics tracking |
| **omnetpp.ini** | Simulation configuration and network parameter settings |

---

### Simulation Output Example

```
PC:0 generated 3 received 3 transmitted 8
PC:1 generated 3 received 4 transmitted 12
PC:2 generated 3 received 1 transmitted 9
PC:3 generated 3 received 4 transmitted 22
PC:4 generated 3 received 3 transmitted 6
PC:5 generated 3 received 3 transmitted 4
```

**Output Analysis:**
- All nodes generated exactly 3 messages (meeting termination condition)
- PC[3] served as central hub with highest transmission count (22)
- Variable reception counts reflect random destination distribution
- Transmission counts indicate routing patterns and network utilization
- **Hop counting implemented via dedicated `forwardMessage()` method** as required

---

### How to Compile and Run

1. **Open in OMNeT++ IDE** and build the project to generate message headers
2. **Run simulation** using the OMNeT++ Qtenv environment
3. **Monitor real-time events** in simulation log
4. **View final statistics** in console output after simulation completion
