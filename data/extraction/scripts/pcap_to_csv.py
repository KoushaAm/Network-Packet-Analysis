#!/usr/bin/env python3
from scapy.all import rdpcap
import csv
import argparse
from datetime import datetime

parser = argparse.ArgumentParser()
parser.add_argument("pcap", help="pcap file to parse")
parser.add_argument("out", help="csv output file")
args = parser.parse_args()

packets = rdpcap(args.pcap)
with open(args.out, "w", newline='') as f:
    writer = csv.writer(f)
    writer.writerow(["timestamp","protocol","src_ip","src_port","dst_ip","dst_port","length"])
    for pkt in packets:
        ts = datetime.fromtimestamp(float(pkt.time)).strftime("%Y-%m-%d %H:%M:%S.%f")
        proto = "OTHER"
        s_ip = ""
        d_ip = ""
        s_port = ""
        d_port = ""
        length = len(pkt)
        if pkt.haslayer("IP"):
            ip = pkt.getlayer("IP")
            s_ip = ip.src
            d_ip = ip.dst
            if pkt.haslayer("TCP"):
                t = pkt.getlayer("TCP")
                proto = "TCP"
                s_port = t.sport
                d_port = t.dport
            elif pkt.haslayer("UDP"):
                u = pkt.getlayer("UDP")
                proto = "UDP"
                s_port = u.sport
                d_port = u.dport
            else:
                proto = str(ip.proto)
        writer.writerow([ts,proto,s_ip,s_port,d_ip,d_port,length])
print("Wrote", args.out)
