#!/usr/bin/env bash
set -e

# default output dir inside container (mounted from host)
OUTDIR=${OUTDIR:-/out}
mkdir -p "$OUTDIR"

echo "Anomaly generator container"
echo "Outputs will be written to: $OUTDIR"
echo
echo "Usage examples inside container:"
echo "  /app/scripts/capture_start.sh &    # start tcpdump writing to $OUTDIR/capture.pcap"
echo "  python3 /app/scripts/udp_burst.py  # run UDP flood (to 127.0.0.1:9999)"
echo "  python3 /app/scripts/syn_scan.py   # run SYN scan (127.0.0.1 ports 1000-1100)"
echo "  python3 /app/scripts/malformed.py  # send weird/proto packets"
echo "  python3 /app/scripts/udp_burst.py --count 10000 --delay 0.001"
echo
echo "Shortcuts:"
echo "  To start a capture in background and run a generator:"
echo "    /app/scripts/capture_start.sh & sleep 1; python3 /app/scripts/udp_burst.py; pkill tcpdump"
echo
# drop into a shell so user can run commands
exec /bin/bash -l
