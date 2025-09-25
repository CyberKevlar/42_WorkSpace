# Host image for GNS3 nodes (no preconfigured IPs)
FROM alpine:3.20

RUN apk add --no-cache \
    busybox-extras \
    iproute2 \
    iputils \
    tcpdump \
    ethtool \
    iperf3 \
    curl \
    bash

# Default shell; no IP configuration by default
ENTRYPOINT ["/bin/sh"]
