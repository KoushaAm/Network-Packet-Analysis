
A simple sandbox environment for simulating anamolous traffic

Guide: 
 - navigate ```cd extraction```
 - Build with ```docker build -t anomaly-generator .```
 - Run with ```docker run --rm -it \
  --network none \
  --cap-add=NET_RAW \
  -v "$(pwd)/out":/out \
  anomaly-generator```
