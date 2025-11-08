#!/usr/bin/env python3
"""
malformed.py
Send IP packets containing unusual/rare IP protocol numbers and custom payload.

Use with care; default sends to 127.0.0.1 and small count.

Example:
  sudo python3 malformed.py --proto 250 --count 200 --size 128 --delay 0.01
"""
import argparse
import time
from scapy.all import IP, Raw, send

def send_malformed(dst, proto, count, size, delay):
    payload = b"X" * size
    print(f"Sending {count} packets to {dst} proto={proto} size={size} delay={delay}")
    for i in range(count):
        pkt = IP(dst=dst, proto=proto)/Raw(load=payload)
        send(pkt, verbose=False)
        if delay:
            time.sleep(delay)
    print("Done malformed packets.")

def main():
    parser = argparse.ArgumentParser(description="Send IP packets with unusual proto numbers (scapy)")
    parser.add_argument("--dst", default="127.0.0.1", help="target IP")
    parser.add_argument("--proto", type=int, default=250, help="IP protocol number to use")
    parser.add_argument("--count", type=int, default=200, help="number of packets")
    parser.add_argument("--size", type=int, default=120, help="payload size bytes")
    parser.add_argument("--delay", type=float, default=0.01, help="seconds between packets")
    args = parser.parse_args()

    send_malformed(args.dst, args.proto, args.count, args.size, args.delay)

if __name__ == "__main__":
    main()
