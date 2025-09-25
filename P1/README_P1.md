# P1 – GNS3 + Docker images (host & router)

This folder provides two Docker images to be used as GNS3 nodes:
- Host: `alpine`-based, networking tools, no preconfigured IPs
- Router: `FRRouting`-based with zebra, bgpd, ospfd, isisd enabled

## Build

```bash
# From repo root
cd P1/host && docker build -t <login>_host:latest .
cd ../router && docker build -t <login>_router:latest .
```

## Import into GNS3
- Preferences > Docker > New template > From image
- Select `<login>_host` and `<login>_router`
- Create a small topology (include your login in node names)
- Export portable project including images, and commit zip + configs

## Notes
- Do not preconfigure interface IPs inside images; configure per lab.
- Router FRR config is minimal; adjust BGP/OSPF/ISIS as needed during labs.
