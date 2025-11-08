#!/usr/bin/env python3
"""
dns_spike.py
generate many UDP "DNS-like" queries to the target IP:port (default 127.0.0.1:53)

Examples:
  python3 dns_spike.py --count 1000
  python3 dns_spike.py --host 127.0.0.1 --port 53 --count 2000 --delay 0.001
"""
import socket
import argparse
import time

def dns_spike(host, port, count, delay):
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    for i in range(count):
        # craft a simple pseudo-DNS query as text (not real DNS wire format)
        # for real DNS format you could use dnspython; for traffic generation text is sufficient
        payload = f"q{i}.example".encode()
        try:
            s.sendto(payload, (host, port))
        except Exception as e:
            print(f"send error: {e}")
        if delay:
            time.sleep(delay)
    s.close()
    print("Done DNS-style UDP spike.")

def main():
    parser = argparse.ArgumentParser(description="Generate many small UDP packets to port 53 (DNS spike)")
    parser.add_argument("--host", default="127.0.0.1", help="target host")
    parser.add_argument("--port", type=int, default=53, help="target port")
    parser.add_argument("--count", type=int, default=500, help="number of requests to send")
    parser.add_argument("--delay", type=float, default=0.0, help="delay between sends (seconds)")
    args = parser.parse_args()

    dns_spike(args.host, args.port, args.count, args.delay)

if __name__ == "__main__":
    main()
