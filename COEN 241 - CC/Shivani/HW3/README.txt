Task 1

Questions

1. What is the output of “nodes” and “net”

Ans:
output of "nodes":
h1 h2 h3 h4 h5 h6 h7 h8 s1 s2 s3 s4 s5 s6 s7

output of "net":
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

Ans:
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

Questions:

1. Draw the function call graph of this controller. For example, once a packet comes to the controller, which function is the first to be called, which one is the second, and so forth?

Ans:
packet enters -> _handle_PacketIn() -> act_like_hub() -> resend_packet() -> send message to port

2. Have h1 ping h2, and h1 ping h8 for 100 times (e.g., h1 ping -c100 p2).
a. How long does it take (on average) to ping for each case?
b. What is the minimum and maximum ping you have observed?
c. What is the difference, and why?

Ans:
h1 ping -c100 h2
--- 10.0.0.2 ping statistics ---
100 packets transmitted, 100 received, 0% packet loss, time 99867ms
rtt min/avg/max/mdev = 1.015/1.624/3.543/0.625 ms

h1 ping -c100 h8
--- 10.0.0.8 ping statistics ---
100 packets transmitted, 100 received, 0% packet loss, time 97935ms
rtt min/avg/max/mdev = 4.803/5.562/12.563.1.256 ms

a. h1 ping h2 - Average ping is 1.502 ms
	 h1 ping h8 - Average ping is 5.806 ms
   
b. h1 ping h2 - Minimum ping observed is 1.012 ms
	 h1 ping h8 - Minimum ping observed is 4.567 ms
	 
	 h1 ping h2 - Maximum ping observed is 3.517 ms
	 h1 ping h8 - Maximum ping observed is 10.122 ms
   
c. The ping times are much longer for h1 to h8 than h1 to h2, because h1 only has one switch in between itself and h2,i.e.s3, where as there are several hops between h1 and h8,i.e., s3,s2,s1,s5,s7.

3. Run “iperf h1 h2” and “iperf h1 h8”
a. What is “iperf” used for?
b. What is the throughput for each case?
c. What is the difference, and explain the reasons for the difference.

Ans:
a. Iperf is used to test network by creating TCP and UDP data streams and measures the throughput. It can be used to set parameters required for testing the network and optimizing it.

b. 
mininet> iperf h1 h2
*** Iperf: testing TCP bandwidth between h1 and h2
*** Results: ['11.4 Mbits/sec', '10.5 Mbits/sec']
mininet> iperf h1 h8
*** Iperf: testing TCP bandwidth between h1 and h8
*** Results: ['793 bits/sec','2.34 Mbits/sec']

c. 
The throughput for h1 and h2 is more than h1 and h8 due to network congestion and latency. For h1 and h2, number of hops are less therefore more data is transfered than h1 and h8.

4. Which of the switches observe traffic? Please describe your way for observing such traffic on switches (e.g., adding some functions in the “of_tutorial” controller).
For observing the traffic log.info is used. This helps to monitor traffic at each switch. When a packet is received, _handle PacketIn is invoked.

Task 3

Questions

1. Describe how the above code works, such as how the "MAC to Port" map is established. You could use a ‘ping’ example to describe the establishment process (e.g., h1 ping h2).

Ans:
"MAC to Port" mapping is done by act_like_switch(). Once MAC address is found, it can be mapped to a port that increases the performance as the addresses are known. But if the destination is not known, packet is flooded to all destinations. MAC learning controller improves ping times and throughput as flooding doesnt take place that often.

Establishment process:
root@bb0c39a1c37e:~/pox# ./pox.py log.level --DEBUG misc.of_tutorial
POX 0.7.0 (gar) / Copyright 2011-2020 James McCauley, et al.
DEBUG:core:POX 0.7.0 (gar) going up...
DEBUG:core:Running on CPython (3.6.9/Nov 16 2022 15:33:00)
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

Ans:
h1 ping -c100 h2
--- 10.0.0.2 ping statistics ---
100 packets transmitted, 100 received, 0% packet loss, time 94946ms
rtt min/avg/max/mdev = 1.823/1.276/2.363/0.256 ms

h1 ping -c100 h8
--- 10.0.0.8 ping statistics ---
100 packets transmitted, 100 received, 0% packet loss, time 92654ms
rtt min/avg/max/mdev = 4.228/4.865/13.311/1.322 ms

a. h1 ping h2 - Average ping is 1.524 ms
	 h1 ping h8 - Average ping is 4.332 ms


b. h1 ping h2 - Minimum ping observed is 1.425 ms
	 h1 ping h8 - Minimum ping observed is 3.233 ms
	 
	 h1 ping h2 - Maximum ping observed is 2.577 ms
	 h1 ping h8 - Maximum ping observed is 9.682 ms

c. For h1 ping h2, task 3 takes less time than task 2. While for h1 and h8 ping time difference is large as it requires to go through more changes. In task 3 only few packets are flooded therefore task 3 is faster or has less ping time. The switches will resend the packet once the destination MAC address is found in the map, only to the corresponding port that is mapped to in the  "mac_to_port" mapping. Therefore, the pings are much faster as there wont be many network congestions.

3. Q.3 Run “iperf h1 h2” and “iperf h1 h8”.
a. What is the throughput for each case?
b. What is the difference from Task 2 and why do you think there is a change if
there is?

Ans:

a. 
mininet> iperf h1 h2
*** Iperf: testing TCP bandwidth between h1 and h2
*** Results: ['35.3 Mbits/sec', '37.1 Mbits/sec']

mininet> iperf h1 h8
*** Iperf: testing TCP bandwidth between h1 and h8
*** Results: ['4.74 Mbits/sec', '4.37 Mbits/sec']

b.
Throughput for task 3 is more than task 2 because of less network congestion. This is becuase flooding did not take place as mac_to_port map has learnt all the ports. Average improvement of throughputs of h1 and h2 for task 1 and 2 is nearly 3 times. For h1 and h8, there is no significant improvement becaues of less packet hops.
