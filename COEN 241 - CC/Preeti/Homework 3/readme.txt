Task 1

1. What is the output of “nodes” and “net”

The output for the nodes is as follows: 
available nodes are: 
h1 h2 h3 h4 h5 h6 h7 h8 s1 s2 s3 s4 s5 s6 s7

The output for net is as follows: 
h1 h1-eth0:s3-eth2
h2 h2-eth0:s3-eth3
h3 h3-eth0:s4-eth2
h4 h4-eth0:s4-eth3
h5 h5-eth0:s6-eth2
h6 h6-eth0:s6-eth3
h7 h7-eth0:s7-eth2
h8 h8-eth0:s7-eth3
s1 lo:  s1-eth1:s2-eth1 s1-eth2:s5-eth1
s2 lo:  s2-eth1:s1-eth1 s2-eth2:s3-eth1 s2-eth3:s4-eth1
s3 lo:  s3-eth1:s2-eth2 s3-eth2:h1-eth0 s3-eth3:h2-eth0
s4 lo:  s4-eth1:s2-eth3 s4-eth2:h3-eth0 s4-eth3:h4-eth0
s5 lo:  s5-eth1:s1-eth2 s5-eth2:s6-eth1 s5-eth3:s7-eth1
s6 lo:  s6-eth1:s5-eth2 s6-eth2:h5-eth0 s6-eth3:h6-eth0
s7 lo:  s7-eth1:s5-eth3 s7-eth2:h7-eth0 s7-eth3:h8-eth0

2. What is the output of “h7 ifconfig”

The output for h7 ifconfig is: 
h7-eth0: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
        inet 10.0.0.7  netmask 255.0.0.0  broadcast 10.255.255.255
        ether 22:2d:04:61:ea:78  txqueuelen 1000  (Ethernet)
        RX packets 237  bytes 36730 (36.7 KB)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 11  bytes 886 (886.0 B)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0

lo: flags=73<UP,LOOPBACK,RUNNING>  mtu 65536
        inet 127.0.0.1  netmask 255.0.0.0
        loop  txqueuelen 1000  (Local Loopback)
        RX packets 0  bytes 0 (0.0 B)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 0  bytes 0 (0.0 B)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0

Tast - 2


1. Draw the function call graph of this controller. For example, once a packet comes to the
controller, which function is the first to be called, which one is the second, and so forth?

Function call graph:
We begin by turning on the POX listener, which then turns on the start switch.The _handle PacketIn() method is called by the start switch to handle the packet in messages from the switch.
The act like hub() function is then called by the _handle PacketIn() function.The act like hub() function generates a behavior that sends packets to all ports except the input port, simulating a hub environment.The resend packet() method is then called.The resend packet() function adds a packet to the message data and performs the action on it.The switch is then instructed to resend the packet to a specified port by this message. The graph is shown as below:
start switch : _handle_PacketIn() -> act_like_hub() -> resend_packet() -> send(msg)

2. Have h1 ping h2, and h1 ping h8 for 100 times (e.g., h1 ping -c100 p2).
a. How long does it take (on average) to ping for each case?
b. What is the minimum and maximum ping you have observed?
c. What is the difference, and why?

h1 ping -c100 h2
--- 10.0.0.2 ping statistics ---
100 packets transmitted, 100 received, 0% packet loss, time 98867ms
rtt min/avg/max/mdev = 1.011/1.654/3.516/0.745 ms

h1 ping -c100 h8
--- 10.0.0.8 ping statistics ---
100 packets transmitted, 100 received, 0% packet loss, time 97935ms
rtt min/avg/max/mdev = 4.904/5.586/12.736.0.256 ms


Ans 2.a. h1 ping h2 - Average ping is 1.535 ms
	 h1 ping h8 - Average ping is 4.983 ms


Ans 2.b. h1 ping h2 - Minimum ping observed is 1.865 ms
	 h1 ping h8 - Minimum ping observed is 4.238 ms
	 
	 h1 ping h2 - Maximum ping observed is 3.753 ms
	 h1 ping h8 - Maximum ping observed is 12.845 ms

Ans 2.c.
The ping times are much longer for h1 to h8 than h1 to h2, because h1 only has one switch in between itself and h2,i.e.s3, where as there are several hops between h1 and h8,i.e., s3,s2,s1,s5,s7.


3. Run “iperf h1 h2” and “iperf h1 h8”
a. What is “iperf” used for?
b. What is the throughput for each case?
c. What is the difference, and explain the reasons for the difference.

Ans 3.a. 
Iperf is an open source program that assists administrators in determining bandwidth for network performance and line quality.Two hosts running iperf are limiting the network link.It is used to determine the amount of data transferred between any two nodes on a network line. 
Ans 3.b. The throughput for each case is:
mininet> iperf h1 h2
*** Iperf: testing TCP bandwidth between h1 and h2
*** Results: ['11.4 Mbits/sec', '13.5 Mbits/sec']
mininet> iperf h1 h8
*** Iperf: testing TCP bandwidth between h1 and h8
*** Results: ['793 bits/sec','2.46 Mbits/sec']

Ans 3.c.
Because of network congestion and latency, throughput is higher between h1 and h2 than between h1 and h8 (same as ping time being slower).Because the number of hops between h1 and h2 is lower, more data can be sent in less time.Because the number of hops between h1 and h8 is higher, less data may be transferred in a given amount of time. 

4. Which of the switches observe traffic? Please describe your way for observing such traffic on switches (e.g., adding some functions in the “of_tutorial” controller).
Ans 4
We may inspect the information that lets us observe the traffic by adding log.info("Switch observing traffic: percent s" percent (self.connection) to the line number 107 "of tutorial" controller.As a result of this, we can deduce that all switches monitor traffic, particularly when they are overloaded with packets.The event listener function _handle PacketIn is invoked whenever a packet is received. 

Task 3.

1. Describe how the above code works, such as how the "MAC to Port" map is established. You could use a ‘ping’ example to describe the establishment process (e.g., h1 ping h2).
Ans 1. 
TThe functionality of the act like switch function in our code allows us to determine where MAC addresses are located.
As a result, when a MAC address is determined to be the address to which a sender wishes to send a message, the controller can map that MAC address to a port for convenience.This also aids the controller's speed when delivering packets to already known addresses, as the packet is simply directed to that known port.The function just floods the packet to all destinations if the destination is unknown.Because flooding occurs less frequently, the MAC Learning Controller helps to improve ping times and throughput. 
Establishment process could be well understood by seeing the output for a ping of 1 packet from h1 to h2:

root@bb0c39a1c37e:~/pox# ./pox.py log.level --DEBUG misc.of_tutorial
POX 0.7.0 (gar) / Copyright 2011-2020 James McCauley, et al.
DEBUG:core:POX 0.7.0 (gar) going up...
DEBUG:core:Running on CPython (3.6.9/Mar 15 2022 18:35:58)
DEBUG:core:Platform is Linux-5.4.0-110-generic-x86_64-with-Ubuntu-18.04-bionic
WARNING:version:Support for Python 3 is experimental.
INFO:core:POX 0.7.0 (gar) is up.
DEBUG:openflow.of_01:Listening on 0.0.0.0:6633
INFO:openflow.of_01:[00-00-00-00-00-07 2] connected
DEBUG:misc.of_tutorial:Controlling [00-00-00-00-00-07 2]
INFO:openflow.of_01:[00-00-00-00-00-06 3] connected
DEBUG:misc.of_tutorial:Controlling [00-00-00-00-00-06 3]
INFO:openflow.of_01:[00-00-00-00-00-01 4] connected
DEBUG:misc.of_tutorial:Controlling [00-00-00-00-00-01 4]
INFO:openflow.of_01:[00-00-00-00-00-04 5] connected
DEBUG:misc.of_tutorial:Controlling [00-00-00-00-00-04 5]
INFO:openflow.of_01:[00-00-00-00-00-03 6] connected
DEBUG:misc.of_tutorial:Controlling [00-00-00-00-00-03 6]
INFO:openflow.of_01:[00-00-00-00-00-02 7] connected
DEBUG:misc.of_tutorial:Controlling [00-00-00-00-00-02 7]
INFO:openflow.of_01:[00-00-00-00-00-05 8] connected
DEBUG:misc.of_tutorial:Controlling [00-00-00-00-00-05 8]
Learning that fe:c7:33:e2:a7:63 is attached at port 3
33:33:00:00:00:16 not known, resend to everybody
Learning that fe:c7:33:e2:a7:63 is attached at port 3
33:33:00:00:00:16 not known, resend to everybody
Learning that fe:c7:33:e2:a7:63 is attached at port 1
33:33:00:00:00:16 not known, resend to everybody
Learning that fe:c7:33:e2:a7:63 is attached at port 2
33:33:00:00:00:16 not known, resend to everybody
Learning that fe:c7:33:e2:a7:63 is attached at port 1
33:33:00:00:00:16 not known, resend to everybody
Learning that fe:c7:33:e2:a7:63 is attached at port 1
33:33:00:00:00:16 not known, resend to everybody
Learning that fe:c7:33:e2:a7:63 is attached at port 1
33:33:00:00:00:16 not known, resend to everybody
Learning that e6:8b:34:26:d2:f9 is attached at port 3
33:33:00:00:00:16 not known, resend to everybody
Learning that e6:8b:34:26:d2:f9 is attached at port 2
33:33:00:00:00:16 not known, resend to everybody
Learning that e6:8b:34:26:d2:f9 is attached at port 1
33:33:00:00:00:16 not known, resend to everybody
Learning that e6:8b:34:26:d2:f9 is attached at port 2
33:33:00:00:00:16 not known, resend to everybody
Learning that e6:8b:34:26:d2:f9 is attached at port 1
33:33:00:00:00:16 not known, resend to everybody
Learning that e6:8b:34:26:d2:f9 is attached at port 1
33:33:00:00:00:16 not known, resend to everybody
Learning that e6:8b:34:26:d2:f9 is attached at port 1
33:33:00:00:00:16 not known, resend to everybody
Learning that 12:3b:c3:3e:0b:62 is attached at port 2
33:33:00:00:00:16 not known, resend to everybody
Learning that 12:3b:c3:3e:0b:62 is attached at port 2
33:33:00:00:00:16 not known, resend to everybody
Learning that 12:3b:c3:3e:0b:62 is attached at port 1
33:33:00:00:00:16 not known, resend to everybody
Learning that 12:3b:c3:3e:0b:62 is attached at port 2
33:33:00:00:00:16 not known, resend to everybody
Learning that 12:3b:c3:3e:0b:62 is attached at port 1
33:33:00:00:00:16 not known, resend to everybody
Learning that 12:3b:c3:3e:0b:62 is attached at port 1
33:33:00:00:00:16 not known, resend to everybody
Learning that 12:3b:c3:3e:0b:62 is attached at port 1
33:33:00:00:00:16 not known, resend to everybody
33:33:ff:26:d2:f9 not known, resend to everybody
33:33:ff:26:d2:f9 not known, resend to everybody
33:33:ff:26:d2:f9 not known, resend to everybody
33:33:ff:26:d2:f9 not known, resend to everybody
33:33:ff:26:d2:f9 not known, resend to everybody
33:33:ff:26:d2:f9 not known, resend to everybody
33:33:ff:26:d2:f9 not known, resend to everybody
33:33:ff:3e:0b:62 not known, resend to everybody
33:33:ff:3e:0b:62 not known, resend to everybody
33:33:ff:3e:0b:62 not known, resend to everybody
33:33:ff:3e:0b:62 not known, resend to everybody
33:33:ff:3e:0b:62 not known, resend to everybody
33:33:ff:3e:0b:62 not known, resend to everybody
33:33:ff:3e:0b:62 not known, resend to everybody
Learning that 0a:fa:38:0c:09:dc is attached at port 2
33:33:00:00:00:16 not known, resend to everybody
Learning that 0a:fa:38:0c:09:dc is attached at port 3
33:33:00:00:00:16 not known, resend to everybody
Learning that 0a:fa:38:0c:09:dc is attached at port 1
33:33:00:00:00:16 not known, resend to everybody
Learning that 0a:fa:38:0c:09:dc is attached at port 1
33:33:00:00:00:16 not known, resend to everybody
Learning that 0a:fa:38:0c:09:dc is attached at port 1
33:33:00:00:00:16 not known, resend to everybody
Learning that 0a:fa:38:0c:09:dc is attached at port 1
33:33:00:00:00:16 not known, resend to everybody
Learning that 0a:fa:38:0c:09:dc is attached at port 1
33:33:00:00:00:16 not known, resend to everybody
Learning that fa:f1:d1:80:0c:b9 is attached at port 3
33:33:ff:80:0c:b9 not known, resend to everybody
Learning that fa:f1:d1:80:0c:b9 is attached at port 3
33:33:ff:80:0c:b9 not known, resend to everybody
Learning that fa:f1:d1:80:0c:b9 is attached at port 1
33:33:ff:80:0c:b9 not known, resend to everybody
Learning that fa:f1:d1:80:0c:b9 is attached at port 1
33:33:ff:80:0c:b9 not known, resend to everybody
Learning that fa:f1:d1:80:0c:b9 is attached at port 1
33:33:ff:80:0c:b9 not known, resend to everybody
Learning that fa:f1:d1:80:0c:b9 is attached at port 1
33:33:ff:80:0c:b9 not known, resend to everybody
Learning that fa:f1:d1:80:0c:b9 is attached at port 1
33:33:ff:80:0c:b9 not known, resend to everybody
Learning that a6:e8:e9:dd:39:24 is attached at port 2
33:33:00:00:00:16 not known, resend to everybody
Learning that a6:e8:e9:dd:39:24 is attached at port 2
33:33:00:00:00:16 not known, resend to everybody
Learning that a6:e8:e9:dd:39:24 is attached at port 1
33:33:00:00:00:16 not known, resend to everybody
Learning that a6:e8:e9:dd:39:24 is attached at port 1
33:33:00:00:00:16 not known, resend to everybody
Learning that a6:e8:e9:dd:39:24 is attached at port 1
33:33:00:00:00:16 not known, resend to everybody
Learning that a6:e8:e9:dd:39:24 is attached at port 1
33:33:00:00:00:16 not known, resend to everybody
Learning that a6:e8:e9:dd:39:24 is attached at port 1
33:33:00:00:00:16 not known, resend to everybody
33:33:ff:0c:09:dc not known, resend to everybody
33:33:ff:0c:09:dc not known, resend to everybody
33:33:ff:0c:09:dc not known, resend to everybody
33:33:ff:0c:09:dc not known, resend to everybody
33:33:ff:0c:09:dc not known, resend to everybody
33:33:ff:0c:09:dc not known, resend to everybody
33:33:ff:0c:09:dc not known, resend to everybody
Learning that 1a:d1:21:83:fe:bb is attached at port 3
33:33:00:00:00:16 not known, resend to everybody
Learning that 1a:d1:21:83:fe:bb is attached at port 2
33:33:00:00:00:16 not known, resend to everybody
Learning that 1a:d1:21:83:fe:bb is attached at port 1
33:33:00:00:00:16 not known, resend to everybody
Learning that 1a:d1:21:83:fe:bb is attached at port 1
33:33:00:00:00:16 not known, resend to everybody
Learning that 1a:d1:21:83:fe:bb is attached at port 1
33:33:00:00:00:16 not known, resend to everybody
Learning that 1a:d1:21:83:fe:bb is attached at port 1
33:33:00:00:00:16 not known, resend to everybody
Learning that 1a:d1:21:83:fe:bb is attached at port 1
33:33:00:00:00:16 not known, resend to everybody
33:33:ff:e2:a7:63 not known, resend to everybody
Learning that fa:94:b9:5b:2f:4d is attached at port 2
33:33:ff:5b:2f:4d not known, resend to everybody
33:33:ff:e2:a7:63 not known, resend to everybody
Learning that fa:94:b9:5b:2f:4d is attached at port 3
33:33:ff:5b:2f:4d not known, resend to everybody
33:33:ff:e2:a7:63 not known, resend to everybody
Learning that fa:94:b9:5b:2f:4d is attached at port 1
33:33:ff:5b:2f:4d not known, resend to everybody
33:33:ff:e2:a7:63 not known, resend to everybody
Learning that fa:94:b9:5b:2f:4d is attached at port 2
33:33:ff:5b:2f:4d not known, resend to everybody
33:33:ff:e2:a7:63 not known, resend to everybody
Learning that fa:94:b9:5b:2f:4d is attached at port 1
33:33:ff:5b:2f:4d not known, resend to everybody
33:33:ff:e2:a7:63 not known, resend to everybody
Learning that fa:94:b9:5b:2f:4d is attached at port 1
33:33:ff:5b:2f:4d not known, resend to everybody
33:33:ff:e2:a7:63 not known, resend to everybody
Learning that fa:94:b9:5b:2f:4d is attached at port 1
33:33:ff:5b:2f:4d not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:16 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
ff:ff:ff:ff:ff:ff not known, resend to everybody
a6:e8:e9:dd:39:24 destination known. only send message to it
ff:ff:ff:ff:ff:ff not known, resend to everybody
ff:ff:ff:ff:ff:ff not known, resend to everybody
ff:ff:ff:ff:ff:ff not known, resend to everybody
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
ff:ff:ff:ff:ff:ff not known, resend to everybody
ff:ff:ff:ff:ff:ff not known, resend to everybody
ff:ff:ff:ff:ff:ff not known, resend to everybody
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
33:33:00:00:00:02 not known, resend to everybody
1a:d1:21:83:fe:bb destination known. only send message to it
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
DEBUG:openflow.of_01:1 connection aborted
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
^[[1;2B1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
a6:e8:e9:dd:39:24 destination known. only send message to it
1a:d1:21:83:fe:bb destination known. only send message to it
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody
33:33:00:00:00:02 not known, resend to everybody


2. (Comment out all prints before doing this experiment) Have h1 ping h2, and h1 ping
h8 for 100 times (e.g., h1 ping -c100 p2).
a. How long did it take (on average) to ping for each case?
b. What is the minimum and maximum ping you have observed?
c. Any difference from Task 2 and why do you think there is a change if there is?

Ans 2
h1 ping -c100 h2
--- 10.0.0.2 ping statistics ---
100 packets transmitted, 100 received, 0% packet loss, time 93946ms
rtt min/avg/max/mdev = 1.835/1.376/2.423/0.246 ms

h1 ping -c100 h8
--- 10.0.0.8 ping statistics ---
100 packets transmitted, 100 received, 0% packet loss, time 93754ms
rtt min/avg/max/mdev = 4.247/4.853/13.321/1.742 ms

Ans 2.a. h1 ping h2 - Average ping is 1.614 ms
	 h1 ping h8 - Average ping is 4.374 ms


Ans 2.b. h1 ping h2 - Minimum ping observed is 1.766 ms
	 h1 ping h8 - Minimum ping observed is 3.256 ms
	 
	 h1 ping h2 - Maximum ping observed is 2.477 ms
	 h1 ping h8 - Maximum ping observed is 13.682 ms

Ans 2.c. 
Task 3 takes somewhat less time than task 2 for the value for h1 ping h2, while the difference is not substantial.In the instance of h1 and h8, the difference in ping time figures is large because it needs to go through a lot more changes.Because only the first few packets are flooded in job 3, it is clear that task 3 is considerably faster/ or has less ping time.The switches will only resend the packet to the corresponding port that is mapped to in the "mac to port" mapping after the destination MAC address is identified in the map.As a result, future pings are substantially faster due to the lack of network congestion. 

3. Q.3 Run “iperf h1 h2” and “iperf h1 h8”.
a. What is the throughput for each case?
b. What is the difference from Task 2 and why do you think there is a change if
there is?

Ans 3.a. 
mininet> iperf h1 h2
*** Iperf: testing TCP bandwidth between h1 and h2
*** Results: ['34.5 Mbits/sec', '38.2 Mbits/sec']

mininet> iperf h1 h8
*** Iperf: testing TCP bandwidth between h1 and h8
*** Results: ['4.24 Mbits/sec', '4.75 Mbits/sec']

b.
In both cases, the throughput for job 3 is higher than that of task 2.This is because, unlike job 3, there will be less network congestion since when mac to port map has learned all the ports, there will be no flooding of packets and the switches will be less burdened.Given that the routes are more pre-computed and learned with changes in controller, we can see in h1 and h2, task 1 and 2 had nearly 3 times the average improvement in throughputs.While there is no significant improvement in the case of h1 and h8, there is a modest improvement in the case of h1 and h8 due to the number of hops and packet dropping. 
