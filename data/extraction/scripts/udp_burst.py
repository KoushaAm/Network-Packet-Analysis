#!/usr/bin/env python3 
"""
udp_burst.py
Send a burst of UDP packets to a destination (default loopback:127.0.0.1:9999)
"""

import socket
import argparse
import time
from multiprocessing import Process

def worker(host, port, count, size, delay):
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    payload = b"A" * size
    for i in range(count):
        try:
            sock.sendto(payload, (host, port))
        except Exception as e:
            # best effort
            print(f"send error: {e}")
        if delay:
            time.sleep(delay)
    sock.close()

def main():
    parser = argparse.ArgumentParser(description="UDP burst generator")
    parser.add_argument("--host", default="127.0.0.1", help="destination IP")
    parser.add_argument("--port", type=int, default=9999, help="destination port")
    parser.add_argument("--count", type=int, default=20000, help="packets per worker")
    parser.add_argument("--size", type=int, default=200, help="payload bytes per packet")
    parser.add_argument("--delay", type=float, default=0.0, help="seconds between packets (0 = max)")
    parser.add_argument("--workers", type=int, default=1, help="parallel workers")
    args = parser.parse_args()

    procs = []
    for _ in range(args.workers):
        p = Process(target=worker, args=(args.host, args.port, args.count, args.size, args.delay))
        p.start()
        procs.append(p)
    try:
        for p in procs:
            p.join()
    except KeyboardInterrupt:
        print("Interrupted, terminating workers...")
        for p in procs:
            p.terminate()

if __name__ == "__main__":
    main()