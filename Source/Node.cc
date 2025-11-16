#include "Node.h"

Define_Module(Node);

void Node::initialize()
{
    // Initialize counters
    messagesGenerated = 0;
    messagesReceived = 0;
    messagesTransmitted = 0;

    // Schedule first message for ALL nodes
    NodeMsg* msg = generateMessage();
    scheduleAt(simTime() + uniform(0, 0.1), msg);
}

int Node::getRandomDestination(int exclude)
{
    int dest;
    int numNodes = 6;

    // Get random destination that's not self
    do {
        dest = intuniform(0, numNodes - 1);
    } while (dest == exclude);

    return dest;
}

NodeMsg* Node::generateMessage()
{
    char msgname[20];
    int src = getIndex();
    int dest = getRandomDestination(src);

    // Create message with source and destination
    sprintf(msgname, "msg-%d-to-%d", src, dest);
    NodeMsg* msg = new NodeMsg(msgname);

    msg->setSource(src);
    msg->setDestination(dest);
    msg->setHopCount(0);

    messagesGenerated++;
    EV << "Node " << src << " generated message to " << dest << endl;

    return msg;
}

void Node::forwardMessage(NodeMsg* msg)
{
    // Increment hop count befire sending as requested
    msg->setHopCount(msg->getHopCount() + 1);
    messagesTransmitted++;

    // Send through random gate
    int k = intuniform(0, gateSize("gate") - 1);
    send(msg, "gate$o", k);

    EV << "Node " << getIndex() << " forwarding to node " << msg->getDestination() << " via gate " << k << endl;
}

void Node::handleMessage(cMessage* rawMsg)
{
    NodeMsg* msg = check_and_cast<NodeMsg*>(rawMsg);

    // Check if message reached destination
    if (msg->getDestination() == getIndex()) {
        EV << "Message arrived at node " << getIndex() << " after " << msg->getHopCount() << " hops" << endl;
        messagesReceived++;
        delete msg;

        // Generate new message if under limit
        if (messagesGenerated < 3) {
            NodeMsg* newmsg = generateMessage();
            scheduleAt(simTime() + uniform(0.1, 0.5), newmsg);
        }
    }
    else {
        forwardMessage(msg);
    }

    // Generate additional message if under limit
    if (messagesGenerated < 3) {
        NodeMsg* newmsg = generateMessage();
        scheduleAt(simTime() + uniform(1.0, 2.0), newmsg);
    }
}

void Node::finish()
{
    // Print final statistics
    EV << "PC:" << getIndex() << " generated " << messagesGenerated << " received " << messagesReceived << " transmitted " << messagesTransmitted << endl;
}
