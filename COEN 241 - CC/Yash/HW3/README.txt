Task 1

1. What is the output of “nodes” and “net”

The output of "nodes" is: 
available nodes are: 
h1 h2 h3 h4 h5 h6 h7 h8 s1 s2 s3 s4 s5 s6 s7

The output of "net" is: 
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

The output of "h7 ifconfig" is: 
h7-eth0: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
        inet 10.0.0.7  netmask 255.0.0.0  broadcast 10.255.255.255
        inet6 fe80::202d:4ff:fe61:ea78  prefixlen 64  scopeid 0x20<link>
        ether 22:2d:04:61:ea:78  txqueuelen 1000  (Ethernet)
        RX packets 237  bytes 36730 (36.7 KB)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 11  bytes 886 (886.0 B)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0

lo: flags=73<UP,LOOPBACK,RUNNING>  mtu 65536
        inet 127.0.0.1  netmask 255.0.0.0
        inet6 ::1  prefixlen 128  scopeid 0x10<host>
        loop  txqueuelen 1000  (Local Loopback)
        RX packets 0  bytes 0 (0.0 B)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 0  bytes 0 (0.0 B)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0

Tast - 2


1. Draw the function call graph of this controller. For example, once a packet comes to the
controller, which function is the first to be called, which one is the second, and so forth?

Function call graph:
start switch : _handle_PacketIn() -> act_like_hub() -> resend_packet() -> send(msg)

        packet comes in
	
        |
        V
	,__________________,
	|                  |
	| _handle_PacketIn |
	|__________________|
	
	    |
	    V
	,__________________,
	|                  |
	|   act_like_hub   |   (or act_like_switch, once we implement it)
	|__________________|
	
	    |
	    V
	,__________________,
	|                  |
	|  resend_packet   |
	|__________________|
		
	    |
	    V

     forward message to the port

2. Have h1 ping h2, and h1 ping h8 for 100 times (e.g., h1 ping -c100 p2).
a. How long does it take (on average) to ping for each case?
b. What is the minimum and maximum ping you have observed?
c. What is the difference, and why?

h1 ping -c100 h2
--- 10.0.0.2 ping statistics ---
100 packets transmitted, 100 received, 0% packet loss, time 99178ms
rtt min/avg/max/mdev = 1.014/1.552/3.417/0.499 ms

h1 ping -c100 h8
--- 10.0.0.8 ping statistics ---
100 packets transmitted, 100 received, 0% packet loss, time 99155ms
rtt min/avg/max/mdev = 4.507/5.966/12.122/1.603 ms

Ans 2.a. h1 ping h2 - Average ping is 1.552 ms
	 h1 ping h8 - Average ping is 5.966 ms


Ans 2.b. h1 ping h2 - Minimum ping observed is 1.014 ms
	 h1 ping h8 - Minimum ping observed is 4.507 ms
	 
	 h1 ping h2 - Maximum ping observed is 3.417 ms
	 h1 ping h8 - Maximum ping observed is 12.122 ms

Ans 2.c.
The ping times are much longer for h1 to h8 than h1 to h2, because h1 only has one switch in between itself and h2,i.e.s3, where as there are several hops between h1 and h8,i.e., s3,s2,s1,s5,s7.

3. Run “iperf h1 h2” and “iperf h1 h8”
a. What is “iperf” used for?
b. What is the throughput for each case?
c. What is the difference, and explain the reasons for the difference.

Ans 3.a. 
Iperf is an open source tool for helping the administrators measuring the bandwidth for the network performance and quality of a network line. The network link is restricted by two hosts running iperf. It is used to measure the throughput between any two nodes in a network line.

Ans 3.b.
mininet> iperf h1 h2
*** Iperf: testing TCP bandwidth between h1 and h2
*** Results: ['10.8 Mbits/sec', '12.9 Mbits/sec']
mininet> iperf h1 h8
*** Iperf: testing TCP bandwidth between h1 and h8
*** Results: ['3.15 Mbits/sec', '3.73 Mbits/sec'

Ans 3.c.
The throughput is higher between h1 and h2 than h1 and h8 because of network congestion and latency (same as ping time being slower). The number of hops between h1 and h2 are less and therefore more data can be transmitted in a shorter time. While the number of hops between h1 and h8 are more, and therefore less data can be transmitted in a given time.

4. Which of the switches observe traffic? Please describe your way for observing such traffic on switches (e.g., adding some functions in the “of_tutorial” controller).
Ans 4
By adding log.info("Switch observing traffic: %s" % (self.connection) in the line number 107 "of_tutorial" controller we can view the information which helps us to observe the traffic. After seeing that, we can conclude that all the switches view the traffic, specifically when all are flooded with packets. The _handle_PacketIn function is the event listener so its called everytime a packet is received.


Task 3.

1. Describe how the above code works, such as how the "MAC to Port" map is established. You could use a ‘ping’ example to describe the establishment process (e.g., h1 ping h2).
Ans 1. 
The act_like_switch function is able to map or “learn” which MAC addresses are located. So, if a MAC address is discovered to be a desired address that a sender sends to, the controller is able to map that MAC address to a port for simplicity. This also improves the performance of the controller when sending packets to already known addresses, as it just directs the packet to that known port. If the destination is not already known, the function simply floods the packet to all destinations. MAC Learning Controller also helps to improve the ping times and throughputs as flooding happens less often.

Establishment process could be well understood by seeing the output for a ping of 1 packet from h1 to h2:

root@bb0c39a1c37e:~/pox# ./pox.py log.level --DEBUG misc.of_tutorial
POX 0.7.0 (gar) / Copyright 2011-2020 James McCauley, et al.
DEBUG:core:POX 0.7.0 (gar) going up...
DEBUG:core:Running on CPython (3.6.9/Jan 26 2021 15:33:00)
DEBUG:core:Platform is Linux-5.11.0-41-generic-x86_64-with-Ubuntu-18.04-bionic
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
100 packets transmitted, 100 received, 0% packet loss, time 99169ms
rtt min/avg/max/mdev = 1.097/1.448/2.897/0.264 ms

h1 ping -c100 h8
--- 10.0.0.8 ping statistics ---
100 packets transmitted, 100 received, 0% packet loss, time 99158ms
rtt min/avg/max/mdev = 3.738/4.615/13.973/1.659 ms

Ans 2.a. h1 ping h2 - Average ping is 1.448 ms
	 h1 ping h8 - Average ping is 4.615 ms


Ans 2.b. h1 ping h2 - Minimum ping observed is 1.097 ms
	 h1 ping h8 - Minimum ping observed is 3.738 ms
	 
	 h1 ping h2 - Maximum ping observed is 2.897 ms
	 h1 ping h8 - Maximum ping observed is 13.973 ms

Ans 2.c. 
Compared to task 2 the value for h1 ping h2 takes sligtly less time in task 3, although the difference is not so significant. While in case of h1 and h8, the difference is significant for ping time values as it has to go through a lot more switches. Clearly task 3 is much quicker/ or has less ping time, because only initial few packets are flooded in task 3. Once the destincation MAC address is found in the map, the switches will resend the packet only to the corresponding port that is mapped to in the  "mac_to_port" mapping. And hence the subsequent pings are much faster as there wont be much network congestions.

3. Q.3 Run “iperf h1 h2” and “iperf h1 h8”.
a. What is the throughput for each case?
b. What is the difference from Task 2 and why do you think there is a change if
there is?

Ans 3.a.
mininet> iperf h1 h2
*** Iperf: testing TCP bandwidth between h1 and h2
*** Results: ['30.3 Mbits/sec', '36.2 Mbits/sec']
mininet> iperf h1 h8
*** Iperf: testing TCP bandwidth between h1 and h8
*** Results: ['3.74 Mbits/sec', '4.37 Mbits/sec']

b.
The throughput for task 3 is larger than that for task 2 in both the cases. This is due to lesser network congestion as in task 3, as there will not be flooding of packets after mac_to_port map has learnt all the ports and the switches will not be burdened much.
We can see in h1 and h2, task 1 and 2 the throughput had approximately 3 times the avg improvement in throughputs, given the routes are more pre-computed
and learnt with changes in controller. While in case of h1 and h8 there is not major improvement, but had slight improvement due to the number of hops
and dropping packet.