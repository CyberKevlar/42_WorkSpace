#!/bin/bash

# Script para ejecutar GNS3 en Docker con soporte gráfico

IMAGE_NAME="gns3-docker"

echo "Ejecutando GNS3 en Docker..."
echo "Imagen: $IMAGE_NAME"
echo ""

# Verificar si la imagen existe
if ! docker image inspect $IMAGE_NAME >/dev/null 2>&1; then
    echo "La imagen $IMAGE_NAME no existe. Construyendo..."
    docker build -t $IMAGE_NAME .
    if [ $? -ne 0 ]; then
        echo "Error al construir la imagen"
        exit 1
    fi
fi

# Permitir conexiones X11 desde Docker
xhost +local:docker

# Ejecutar el contenedor con GNS3
docker run -it --rm \
  --name gns3-container \
  --privileged \
  --net=host \
  -e DISPLAY=$DISPLAY \
  -v /tmp/.X11-unix:/tmp/.X11-unix \
  -v /dev:/dev \
  -v $(pwd)/projects:/home/gns3_user/GNS3 \
  $IMAGE_NAME

# Restaurar permisos X11
xhost -local:docker

echo "GNS3 ha terminado de ejecutarse."
