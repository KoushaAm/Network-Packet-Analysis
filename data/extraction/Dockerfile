# Dockerfile - lightweight python + tools for generating/capturing traffic
# Use an image compatible with Apple M1 (arm64)
FROM python:3.11-slim

ENV DEBIAN_FRONTEND=noninteractive

# Install system dependencies
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        tcpdump \
        tshark \
        iproute2 \
        net-tools \
        iputils-ping \
        libpcap-dev \
        gcc \
        procps && \
    rm -rf /var/lib/apt/lists/*


# Python deps (scapy for crafting, pandas for later CSV helper)
RUN pip install --no-cache-dir \
    scapy \
    pandas \
    tqdm \
    requests

# Create working dir
WORKDIR /app

# Copy scripts
COPY scripts /app/scripts
RUN chmod +x /app/scripts/*.py /app/scripts/*.sh

# Default entrypoint runs a small menu script
ENTRYPOINT ["/app/scripts/entrypoint.sh"]
