FROM ubuntu:latest

# Actualizar sistema e instalar dependencias básicas
RUN apt update && apt upgrade -y
RUN apt install -y software-properties-common

# Agregar repositorio de GNS3
RUN add-apt-repository ppa:gns3/ppa -y

# Actualizar después de agregar el repositorio
RUN apt update

# Instalar GNS3 y dependencias
RUN apt install -y gns3-gui gns3-server
RUN apt install -y ubridge wireshark qemu-kvm libvirt-clients libvirt-daemon-system bridge-utils virtinst libvirt-daemon virt-manager dynamips

# Crear usuario gns3 y agregarlo a los grupos necesarios
RUN useradd -m -s /bin/bash gns3_user
RUN groupadd -f wireshark || true
RUN usermod -aG ubridge gns3_user || true
RUN usermod -aG libvirt gns3_user || true  
RUN usermod -aG kvm gns3_user || true
RUN usermod -aG wireshark gns3_user || true

# Establecer el usuario de trabajo
USER gns3_user
WORKDIR /home/gns3_user

