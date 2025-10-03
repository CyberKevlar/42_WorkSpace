#!/bin/bash
# Arranca FRR en segundo plano
/usr/lib/frr/frrinit.sh start
# Deja bash interactivo
exec bash