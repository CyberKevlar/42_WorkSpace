# DC = COMPOSE_BAKE=true $(DC_CMD) -f ./docker-compose.yml
DC = docker-compose -f ./docker-compose.yml

# ============================== CONTAINER RULES ==============================

all: up

# Run GNS3 with graphical interface (alias for up)
gns3: up

# Create containers and run GNS3 with graphical interface
up:
	@echo "Otorgando permisos de X11 para aplicaciones gráficas en local a los usuarios/grupos..."
	@xhost +local:docker
	@$(DC) run --rm gns3
	@echo "Revirtiendo permisos de X11..."
	@xhost -local:docker

# Removes containers
down:
	@$(DC) down || exit 1
	@echo "Contenedores detenidos"
	@printf "\n"

# Restarts containers
restart:
	@$(DC) down || exit 1
	@$(DC) up -d || exit 1
	@printf "\n"

clean:
	@$(DC) down || exit 1
	@printf "\nplease wait...\n"
	@docker image ls -q | xargs -r docker image rm -f > /dev/null 2>&1 || true
	@docker volume ls -q | xargs -r docker volume rm -f > /dev/null 2>&1 || true
	@docker network ls -q | xargs -r docker network rm > /dev/null 2>&1 || true
	@printf " ✔ Images\t\tRemoved\n"
	@printf " ✔ Volumes\t\tRemoved\n"
	@printf " ✔ Network\t\tRemoved\n\n"

# Removes images, volumes, network and cache
fclean:
	@$(DC) down || exit 1
	@printf "\nplease wait...\n"
	@docker image ls -q | xargs -r docker image rm -f > /dev/null 2>&1 || true
	@docker volume ls -q | xargs -r docker volume rm -f > /dev/null 2>&1 || true
	@docker network ls -q --filter type=custom | xargs -r docker network rm > /dev/null 2>&1 || true
	@docker image prune -a -f > /dev/null 2>&1 || true
	@docker volume prune -f > /dev/null 2>&1 || true
	@docker network prune -f > /dev/null 2>&1 || true
	@docker builder prune -f > /dev/null 2>&1 || true
	@printf " ✔ Images\t\tRemoved\n"
	@printf " ✔ Volumes\t\tRemoved\n"
	@printf " ✔ Network\t\tRemoved\n"
	@printf " ✔ Cache\t\tRemoved\n\n"

re:
	@$(MAKE) fclean
	@$(MAKE) up