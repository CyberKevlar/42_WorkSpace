#!/bin/bash
# Arranca FRR en segundo plano
/usr/lib/frr/frrinit.sh start
/usr/lib/frr/watchfrr -d zebra bgpd ospfd isisd
# Deja bash interactivo
exec bash