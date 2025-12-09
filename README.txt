<< DOCUMENTACION RESUMIDA DEL PROYECTO 42_BADASS >>

***************************************
*** P1: creacion de imagenes Docker ***
***************************************

El objetivo es crear las imagenes base que se utilizaran en el programa GNS3 para simular los distintos dispositivos de red.

+ Imagen host (Dockerfile_host):

    - Usamos 'Alpine' como base por ser un sistema ligero y estable, perfecto para emular el equipo de un usuario final.
    - Instalamos los paquetes que creemos convenientes para usarlos durante las pruebas:
    
        * bash (shell).
        * iputils (ping).
        * vim (editor de texto basico en consola para editar archivos de configuracion si fuera necesario).
        * iproute2 (para gestión de IP's).
        * tcpdump (analisis de tráfico).

+ Imagen router (Dockerfile_router):
    
    - Usamos una imagen oficial de 'FRRouting', o FRR. Se trata de un sistema operativo que emula sobre una base de linux un router con todas sus caracterirsticas.
    - Instalamos los paquetes necesarios para el correcto funcionamiento de FRR:
    
        * iputils.
        * vim.
        * bash.
        * bridge (para crear 'bridges').

    - Instalamos y habilitamos los demons de enrutamiento necesarios en la ruta '/etc/frr/daemons':
    
        * `zebra` (gestiona las tablas de enrutamiento).
        * `bgpd` (BGP o Border Gateway Protocol: protocolo para intercambiar rutas entre equipos).
        * `ospfd` (OSPF: protocolo de enrutamiento Underlay, el cual 'calcula' la ruta mas corta).
        * `isisd` (ISIS: protocolo de enrutamiento Overlay, que usaremos para implementar spine-leaf y BGP EVPN).
    
    - Se ha configurado un script de entrada como entripoint (`start.sh`) que inicia los servicios de FRR y mantiene el contenedor en ejecución y que no secuestre la terminal.

*****************
*** P2: VXLAN ***
*****************

Aqui implementaremos una red utilizando una VXLAN para conectar los hosts de distintas redes a traves de un túnel.

La idea es implementar dos routers conectados mediante un switch, y cada router conectado a un host diferente.

Se han configurado dos modos de funcionamiento:

- Modo Multicast/Dinamico/Automatico (_g):

    Se configuran las interfaces VXLAN asociandolas a un "grupo" multicast.
    Asi los VTEP's (Virtual Tunnel End Points) descubriran automáticamente a otros miembros del grupo sin configurar manualmente las IP's.

- Modo Estatico/Manual/Fijo (_s):

    Se configuran manualmente las interfaces VXLAN en cada host, definiendo explícitamente la IP remota del otro router.

Para ambas configuraciones se crea un Bridge en cada router, al cual se asocian las interfaces físicas (conectadas al switch) y las interfaces VXLAN (conectadas a los hosts).

**************************************************
*** P3: BGP y EVPN con arquitectura Spine-Leaf ***
**************************************************

Como desarollo final utilizaremos BGP y EVPN para gestionar el plano de control de la red VXLAN, eliminando la necesidad de multicast o configuración estática manual punto a punto.
Es decir, con BGP y EVPN podremos "descubrir o exponer" automaticamente los VTEP y las direcciones de los hosts detras de cada router y asi agilizar la comunicacion entre ellos 

Como funciona Spine-Leaf en el proyecto:

    - 1 Spine (de ahora en adelante 'router principal'): será el router maestro/padre/principal, que actuara como nucleo de la red.
    - 3 Leaves (de ahora en adelante 'routers secundarios'): los otros routers, que se conectan al router Spine y estos a su vez a los host.

Configuracion:

    1. Configuracion del Underlay (OSPF):

        - Configuramos direcciones IP para interfaces de red que conectan el router principal con los routers secundarios.
        - Configuramos interfaces loopback (lo) en cada router para tener una IP a modo de ID (Router-ID), que usaremos para identificar cada router en los protocolos de enrutamiento.
        - Utilizamos OSPF para anunciar las rutas loopbacks de los routers y asegurar que todos tengan conectividad IP entre si.

    2. Configuracion del Overlay (BGP y EVPN)**:

        - Todos los routers forman parte del mismo "sistema"(as 1) utilizando iBGP, que permite intercambiar rutas dentro de un mismo sistema.
        - Router principal: lo configuramos como "router reflector", que es para que los routers secundarios no tengan que conectarse entre si directamente, sino que todo el trafico pasa por el router principal.
        - Routers secundarios: se configuran como "clientes" del router reflector.
        - Se activa la familia de direcciones 'l2vpn evpn' para intercambiar información sobre las direcciones y los VNI (VXLAN Network Identifiers).

    3. Configuracion de VXLAN:

        - En los routers secundarios se crean interfaces VXLAN utilizando la IP de loopback como origen del tunel y la IP de loopback del router principal como destino.
        - Se crea un bridge en cada router secundario, al cual se asocian las interfaces de red y las interfaces VXLAN (conectadas a los hosts).
        - Haciendo uso de BGP y EVPN los routers "aprenden" automaticamente qué VTEP (Virtual Tunnel End Point) tiene cada host por detras de su red,permitiendo la comunicación entre ellos (simulando una red local).

<< FIN >>
