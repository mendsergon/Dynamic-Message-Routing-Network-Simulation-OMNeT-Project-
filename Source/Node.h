#ifndef _NODE_H_
#define _NODE_H_

#include <omnetpp.h>
#include "NodeMsg_m.h"

using namespace omnetpp;

class Node : public cSimpleModule
{
  private:
    // Counters for statistics
    int messagesGenerated;
    int messagesReceived;
    int messagesTransmitted;

    // Helper methods
    int getRandomDestination(int exclude);
    NodeMsg* generateMessage();

  protected:
    // OMNeT++ simulation methods
    virtual void initialize() override;
    virtual void handleMessage(cMessage* msg) override;
    virtual void finish() override;
};

#endif
