# FRRouting-based router image for GNS3 (bgpd, ospfd, isisd)
FROM frrouting/frr:9.1.2

COPY frr/daemons /etc/frr/daemons
COPY frr/frr.conf /etc/frr/frr.conf

# Start FRR in container mode
CMD ["/usr/lib/frr/docker-start"]
