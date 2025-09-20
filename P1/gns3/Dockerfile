FROM ubuntu:24.04

# Actualizar sistema e instalar dependencias básicas.
RUN apt update && apt upgrade -y
RUN apt install -y software-properties-common

# Agregar repositorio de GNS3 y actualiza.
RUN add-apt-repository ppa:gns3/ppa -y
RUN apt update

# Instalar GNS3 y dependencias / librerias necesarias.
RUN apt install -y gns3-gui gns3-server
RUN apt install -y ubridge wireshark qemu-kvm libvirt-clients libvirt-daemon-system bridge-utils virtinst libvirt-daemon virt-manager dynamips

# Configurar herramientas de red básicas (libvirt simplificado)
RUN apt install -y python3-libvirt dnsmasq-base iproute2 iptables

# Habilitar reenvío de IP para NAT
RUN echo 'net.ipv4.ip_forward=1' >> /etc/sysctl.conf

# Crear directorios necesarios
RUN mkdir -p /etc/libvirt/qemu/networks/autostart
RUN mkdir -p /var/run/libvirt
RUN mkdir -p /var/lib/libvirt/images
COPY start_gns3.sh /usr/local/bin/start_gns3.sh
RUN chmod 777 /usr/local/bin/start_gns3.sh

# Crear usuario gns3 y agregarlo a los grupos necesarios.
RUN useradd -m -s /bin/bash gns3_user
RUN groupadd -f wireshark || true
RUN usermod -aG ubridge gns3_user || true
RUN usermod -aG libvirt gns3_user || true  
RUN usermod -aG kvm gns3_user || true
RUN usermod -aG wireshark gns3_user || true

# Configurar permisos especiales para uBridge y Dynamips
RUN chmod 777 /usr/bin/ubridge
RUN chmod 777 /usr/bin/dynamips

# Establecer el usuario de trabajo. Si no se usa entonces se ejecuta todo como root (que es el caso).
#USER gns3_user

WORKDIR /home/gns3_user

# Iniciar GNS3 en modo gráfico o desde el docker-compose.yml (que es este caso, porque usarlo qui no nos deja por permisos).
#CMD ["/usr/bin/gns3"]