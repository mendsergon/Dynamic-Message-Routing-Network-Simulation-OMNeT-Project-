network Network
{
    parameters:
        @display("bgb=640,480");
    
    types:
        channel Channel extends ned.DelayChannel {
            delay = 100ms;
        }
    
    submodules:
        PC[6]: Node {
            @display("i=device/pc");
        }
    
    connections:
        PC[0].gate++ <--> Channel <--> PC[1].gate++;
        PC[0].gate++ <--> Channel <--> PC[3].gate++;
        PC[1].gate++ <--> Channel <--> PC[2].gate++;
        PC[1].gate++ <--> Channel <--> PC[4].gate++;
        PC[2].gate++ <--> Channel <--> PC[3].gate++;
        PC[2].gate++ <--> Channel <--> PC[5].gate++;
        PC[4].gate++ <--> Channel <--> PC[5].gate++;
}