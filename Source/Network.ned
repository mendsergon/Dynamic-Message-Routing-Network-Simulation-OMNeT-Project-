network Network
{
    parameters:
        @display("bgb=800,600");
    submodules:
        PC[6]: Node {
            @display("i=device/pc");
        }
    connections:
        PC[0].gate++ <--> { delay = 0.1s; } <--> PC[1].gate++;
        PC[0].gate++ <--> { delay = 0.1s; } <--> PC[2].gate++;
        PC[1].gate++ <--> { delay = 0.1s; } <--> PC[3].gate++;
        PC[2].gate++ <--> { delay = 0.1s; } <--> PC[3].gate++;
        PC[3].gate++ <--> { delay = 0.1s; } <--> PC[4].gate++;
        PC[3].gate++ <--> { delay = 0.1s; } <--> PC[5].gate++;
}