#!/bin/bash

echo "Configurando entorno para GNS3..."

# Limpiar sockets existentes
rm -f /var/run/libvirt/libvirt-sock* || true
rm -f /run/libvirt/libvirt-sock* || true

# Crear directorios necesarios
mkdir -p /var/run/libvirt
mkdir -p /var/lib/libvirt/images
mkdir -p /etc/libvirt/qemu/networks

# Configurar permisos
chmod 777 /var/run/libvirt
chmod 777 /var/lib/libvirt
chmod 777 /etc/libvirt/qemu/networks

# Crear interfaz bridge virbr0 para NAT (que espera GNS3)
echo "Creando interfaz virbr0 para NAT..."
ip link add name virbr0 type bridge || true
ip addr add 192.168.122.1/24 dev virbr0 || true
ip link set virbr0 up || true

# Configurar iptables para NAT
echo "Configurando NAT..."
iptables -t nat -A POSTROUTING -s 192.168.122.0/24 ! -d 192.168.122.0/24 -j MASQUERADE || true
iptables -A FORWARD -i virbr0 -o virbr0 -j ACCEPT || true
iptables -A FORWARD -s 192.168.122.0/24 -j ACCEPT || true
iptables -A FORWARD -d 192.168.122.0/24 -j ACCEPT || true

# Iniciar dnsmasq para DHCP en virbr0
echo "Iniciando DHCP en virbr0..."
dnsmasq --interface=virbr0 --bind-interfaces --dhcp-range=192.168.122.2,192.168.122.254 --pid-file=/var/run/dnsmasq-virbr0.pid || true

echo "Interfaz virbr0 creada y configurada para NAT"
echo "Iniciando GNS3..."
exec /usr/bin/gns3
