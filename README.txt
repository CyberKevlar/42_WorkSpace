<< DOCUMENTACION RESUMIDA DEL PROYECTO 42_BADASS >>

Parte 1: creacion de imagenes Docker

El objetivo es crear las imagenes base que se utilizaran en el programa GNS3 para simular los distintos dispositivos de red.

+ Imagen host (Dockerfile_host):

    - Usamos 'Alpine' como base por ser un sistema ligero y estable, perfecto para emular el equipo de un usuario final.
    - Instalamos los paquetes que creemos comenientes para usarlos durante las pruebas:
    
        * bash (shell).
        * iputils (ping).
        * tcpdump (análisis de tráfico).
        * iproute2 (para gestión de IP's).
        * vim.

+ Imagen router (Dockerfile_router):
    
    - Usamos una imagen oficial de 'FRRouting', o FRR. Se trata de un sistema operativo que emula
    sobre una base de linux un router con todas sus caracterirsticas.
    - Instalamos y habilitamos los demons de enrutamiento necesarios en la ruta '/etc/frr/daemons':
    
        * `zebra` (núcleo)
        * `bgpd` (BGP)
        * `ospfd` (OSPF)
        * `isisd`.
    
    - Se ha configurado un script de entrada (`start.sh`) que inicia los servicios de FRR y mantiene el contenedor en ejecución.

## Parte 2: VXLAN y Bridging (P2)

En esta fase se implementa una red superpuesta (Overlay) utilizando VXLAN para conectar hosts en diferentes segmentos de red a través de un túnel L2 sobre L3.

**Topología**: Host1 <-> Router1 <-> Switch <-> Router2 <-> Host2

Se han configurado dos modos de funcionamiento:

1.  **Modo Multicast (Dinámico - `_g`)**:
    *   Se configuran las interfaces VXLAN asociándolas a un grupo Multicast (ej. `239.1.1.1`).
    *   Esto permite que los VTEPs (Virtual Tunnel End Points) descubran automáticamente a otros miembros del grupo sin configuración explícita de IPs remotas.

2.  **Modo Estático (`_s`)**:
    *   Se configuran las interfaces VXLAN definiendo explícitamente la IP remota (`remote <IP>`) del otro router.
    *   No requiere mensajería multicast en la red física, pero es menos escalable.

**Configuración común**:
*   Creación de un **Bridge** (`br0`) en los routers para unir la interfaz física conectada al host y la interfaz VXLAN, permitiendo que el tráfico del host viaje encapsulado por el túnel.

## Parte 3: BGP EVPN con Arquitectura Spine-Leaf (P3)

Esta es la fase final y más compleja, donde se utiliza BGP EVPN para gestionar el plano de control de la red VXLAN, eliminando la necesidad de multicast o configuración estática manual punto a punto.

**Topología**: Arquitectura Spine-Leaf
*   **1 Spine** (Router 1): Actúa como el núcleo de la red.
*   **3 Leaves** (Router 2, 3, 4): Actúan como bordes donde se conectan los hosts.

**Pasos de la configuración**:

1.  **Configuración del Underlay (OSPF)**:
    *   Se configuran direcciones IP en las interfaces físicas que conectan el Spine con los Leaves.
    *   Se configuran interfaces **Loopback** (`lo`) en cada router para tener una IP estable (Router-ID).
    *   Se utiliza **OSPF** (Area 0) para anunciar las rutas de las Loopbacks y asegurar que todos los routers tengan conectividad IP básica entre sí.

2.  **Configuración del Overlay (BGP EVPN)**:
    *   Todos los routers forman parte del mismo Sistema Autónomo (AS 1), utilizando **iBGP**.
    *   **Spine**: Se configura como **Route Reflector**. Esto evita tener que hacer una malla completa (Full Mesh) de conexiones BGP entre todos los Leaves.
    *   **Leaves**: Se configuran como clientes del Route Reflector.
    *   Se activa la familia de direcciones `l2vpn evpn` para intercambiar información sobre las direcciones MAC y los VNI (VXLAN Network Identifiers).

3.  **Configuración de VXLAN**:
    *   En los Leaves, se crean interfaces VXLAN utilizando la IP de la Loopback como origen del túnel.
    *   Gracias a BGP EVPN, los routers aprenden automáticamente qué VTEP tiene qué host (MAC address) detrás, permitiendo la comunicación L2 entre hosts a través de la red L3 enrutada.
