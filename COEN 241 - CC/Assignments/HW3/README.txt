COEN 241: HW - 3


Task 1:
1. What is the output of “nodes” and “ net”
The output of "nodes" is: available nodes are: h1 h2 h3 h4 h5 h6 h7 h8 s1 s2 s3 s4 s5 s6 s7 
		
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



Task 2:
1. Draw the function call graph of this controller. For example, once a packet comes to the controller, which function is the first to be called, which one is the second, and so forth?

switch start : _handle_PacketIn() -> act_like_hub() -> resend_packet() -> send(msg)

             Incoming packet
	
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
	   |   resend_packet  |
	   |__________________|
		
	             |
	             V

          send message to the port


2. Have h1 ping h2, and h1 ping h8 for 100 times (e.g., h1 ping -c100 p2).
h1 ping -c100 h2
--- 10.0.0.2 ping statistics ---
100 packets transmitted, 100 received, 0% packet loss, time 99466ms
rtt min/avg/max/mdev = 1.112/1.561/3.676/0.544 ms

h1 ping -c100 h8
--- 10.0.0.8 ping statistics ---
100 packets transmitted, 100 received, 0% packet loss, time 96231ms
rtt min/avg/max/mdev = 4.623/5.764/12.354/1.432 ms

	a) How long does it take (on average) to ping for each case?
	h1 ping h2: Average ping = 1.561 ms
	h1 ping h8: Average ping =  5.764 ms		

	b) What is the minimum and maximum ping you have observed?
	h1 ping h2: Observed Min. ping = 1.112 ms
	h1 ping h2: Observed Max. ping = 3.676 ms
	h1 ping h8: Observed Min. ping = 4.623 ms
	h1 ping h8: Observed Max. ping = 12.354 ms		

	c) What is the difference, and why?
	Since there are more hops between h1 and h8, especially in s3,s2,s1,s5,s7, than h1 and h2, the ping times for h1 to h8 are much prolonged than for h1 to h2.		


3. Run “iperf h1 h2” and “iperf h1 h8”
mininet> iperf h1 h2
*** Iperf: testing TCP bandwidth between h1 and h2
*** Results: ['11.1 Mbits/sec', '12.3 Mbits/sec']
mininet> iperf h1 h8
*** Iperf: testing TCP bandwidth between h1 and h8
*** Results: [‘3.25 Mbits/sec', ‘3.87 Mbits/sec’]

	a) What is “iperf” used for?
	Iperf are used to manage and measure the bandwidth needed for network speed and line quality. Two hosts that execute iperf are the ones limiting the network connection. The throughput between any two endpoints in a network connection is measured using it.		

	b) What is the throughput for each case?
	For “iperf h1 h2”: Results: ['11.1 Mbits/sec', '12.3 Mbits/sec']
	For “iperf h1 h8”: Results: [‘3.25 Mbits/sec', ‘3.87 Mbits/sec’]

	c) What is the difference, and explain the reasons for the difference.
	Due to network congestion and latency, the throughput between h1 and h2 is greater than h1 and h8. Since there are fewer steps between h1 and h2, more data can be transferred in less time. Since there are more hops between h1 and h8, less data can be transferred in a particular amount of time.		

4. Which of the switches observe traffic? Please describe your way for observing such traffic on switches (e.g., adding some functions in the “of_tutorial” controller).
log.info can be added in of_tutorial controller to observe such traffic on switches.This will aid in determining the flow of packets and when the _handle_PacketIn is invoked every time we receive a packet. 


Task 3:
1. Describe how the above code works, such as how the "MAC to Port" map is established. You could use a ‘ping’ example to describe the establishment process (e.g., h1 ping h2).
We can map “MAC to Port” using the act_like_switch function. It will increase the performance as the address is known (One we find the MAC address) which will further direct the packets to the destination ports. Further, as packed flooding happens less often (happens when the destination port is unknown), it enhances the ping times and throughputs.

Explaining the process with the pinging packet 1 from h1 to h2:
ubuntu@ubuntu:~/pox# ./pox.py log.level --DEBUG misc.of_tutorial
POX 0.7.0 (gar) / Copyright 2011-2020 James McCauley, et al.
DEBUG:core:POX 0.7.0 (gar) going up...
DEBUG:core:Running on CPython (3.7.2/Mar 4 2023 17:46:22)
DEBUG:core:Platform is Linux-5.7.0-11-generic-x86_64-with-Ubuntu-20.04.5-bionic
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


2. (Comment out all prints before doing this experiment). Have h1 ping h2, and h1 ping h8 for 100 times (e.g., h1 ping -c100 p2).
h1 ping -c100 h2
--- 10.0.0.2 ping statistics ---
100 packets transmitted, 100 received, 0% packet loss, time 96265ms
rtt min/avg/max/mdev = 1.236/1.657/2.544/0.275 ms

h1 ping -c100 h8
--- 10.0.0.8 ping statistics ---
100 packets transmitted, 100 received, 0% packet loss, time 95766ms
rtt min/avg/max/mdev = 3.995/4.721/13.586/1.543 ms

	a) How long did it take (on average) to ping for each case?
	h1 ping h2: Average ping = 1.657 ms
 	h1 ping h8: Average ping =  4.721 ms	

	b) What is the minimum and maximum ping you have observed?
	h1 ping h2: Observed Min. ping = 1.236 ms
	h1 ping h2: Observed Max. ping = 2.544 ms
 	h1 ping h8: Observed Min. ping =  3.995 ms
	h1 ping h8: Observed Max. ping =  13.586 ms

	c) Any difference from Task 2 and why do you think there is a change if there is?
	By observing the changes between the two tasks, task 3 requires less time than task 2 for h1 ping h2. The ping time difference between h1 and h8 is greater because more adjustments are necessary. Task 3 is quicker or has a shorter ping time because only a small number of messages are inundated in it. Once the target MAC address is located in the map, the switches will resend the message, but only to the port that corresponds to it in the “MAC to port" mapping. As a result, pings are much quicker because there won't be as much network congestion.


3. Run “iperf h1 h2” and “iperf h1 h8”.
mininet> iperf h1 h2
*** Iperf: testing TCP bandwidth between h1 and h2
*** Results: ['32.4 Mbits/sec', '36.7 Mbits/sec']
mininet> iperf h1 h8
*** Iperf: testing TCP bandwidth between h1 and h8
*** Results: [‘4.13 Mbits/sec', ‘4.62 Mbits/sec']

	a) What is the throughput for each case?
	For “iperf h1 h2”: Results: ['32.4 Mbits/sec', '36.7 Mbits/sec']
	For “iperf h1 h8”: Results: [‘4.13 Mbits/sec', ‘4.62 Mbits/sec']

	b) What is the difference from Task 2 and why do you think there is a change if there is?
	By observing the difference between the two tasks, task 3 has a higher throughput than task 2 due to less network latency. This is due to MAC to port map having learned all the ports, which prevents overflow from occurring. The average increase in h1 and h2 output for tasks 1 and 2 is close to three times. Because there are fewer packet steps, there is no noticeable increase for h1 and h8.