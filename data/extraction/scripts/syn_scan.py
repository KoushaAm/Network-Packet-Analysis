#!/usr/bin/env python3
"""
syn_scan.py
Send TCP SYN packets to a range of ports on a destination.

Requires scapy and NET_RAW capability. Default target is 127.0.0.1.

Examples:
  sudo python3 syn_scan.py --dst 127.0.0.1 --start 1000 --end 1100
  sudo python3 syn_scan.py --dst 127.0.0.1 --start 1 --end 1000 --repeat 3
"""
import argparse
from scapy.all import IP, TCP, send
import time

def syn_scan(dst, start, end, repeat, gap):
    print(f"SYN scanning {dst} ports {start}-{end} (repeat={repeat}, gap={gap}s)")
    for r in range(repeat):
        for port in range(start, end + 1):
            pkt = IP(dst=dst)/TCP(dport=port, flags="S")
            send(pkt, verbose=False)
            if gap:
                time.sleep(gap)
    print("SYN scan done.")

def main():
    parser = argparse.ArgumentParser(description="SYN scan by sending TCP SYN packets (scapy)")
    parser.add_argument("--dst", default="127.0.0.1", help="target IP")
    parser.add_argument("--start", type=int, default=1000, help="start port")
    parser.add_argument("--end", type=int, default=1100, help="end port")
    parser.add_argument("--repeat", type=int, default=1, help="repeat scan N times")
    parser.add_argument("--gap", type=float, default=0.0, help="seconds between packets")
    args = parser.parse_args()

    syn_scan(args.dst, args.start, args.end, args.repeat, args.gap)

if __name__ == "__main__":
    main()
