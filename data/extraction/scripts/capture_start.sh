#!/usr/bin/env bash
OUTDIR=${OUTDIR:-/out}
PCAPFILE="$OUTDIR/capture.pcap"
echo "Starting tcpdump -> $PCAPFILE (capture loopback)"
# Capture loopback traffic (lo) and include full packet (-s 0)
# Write to file in pcap format
tcpdump -i lo -s 0 -w "$PCAPFILE" &
TC_PID=$!
echo "$TC_PID" > /tmp/tcpdump.pid
echo "tcpdump pid: $TC_PID"
