# DC = COMPOSE_BAKE=true $(DC_CMD) -f ./docker-compose.yml
DC = docker compose -f ./docker-compose.yml

# ============================== CONTAINER RULES ==============================

all: up

# Create containers
up:
	@$(DC) up -d || exit 1
	@printf "\n"

# Removes containers
down:
	@$(DC) down || exit 1
	@printf "\n"

# Restarts containers
restart:
	@$(DC) down || exit 1
	@$(DC) up -d || exit 1
	@printf "\n"

clean:
	@$(DC) down || exit 1
	@printf "\nplease wait...\n"
	@$(MAKE) -s _remove_images
	@$(MAKE) -s _remove_volumes
	@$(MAKE) -s _remove_networks
	@printf "$(CU)$(CL) ✔ Images\t\t$(GR)Removed$(NC)\n"
	@printf " ✔ Volumes\t\t$(GR)Removed$(NC)\n"
	@printf " ✔ Network\t\t$(GR)Removed$(NC)\n\n"

# Removes images, volumes, network and cache
fclean:
	@$(DC) down || exit 1
	@printf "\nplease wait...\n"
	@$(MAKE) -s _remove_images
	@$(MAKE) -s _remove_volumes
	@$(MAKE) -s _remove_networks

	@docker volume rm auth_data > /dev/null 2>&1 || true
	@docker image prune -a -f > /dev/null 2>&1 || true
	@docker volume prune -f > /dev/null 2>&1 || true
	@docker network prune -f > /dev/null 2>&1 || true
	@docker builder prune -f > /dev/null 2>&1 || true

	@printf "$(CU)$(CL) ✔ Images\t\t$(GR)Removed$(NC)\n"
	@printf " ✔ Volumes\t\t$(GR)Removed$(NC)\n"
	@printf " ✔ Network\t\t$(GR)Removed$(NC)\n"
	@printf " ✔ Cache\t\t$(GR)Removed$(NC)\n\n"

re:
	@$(MAKE) fclean
	@$(MAKE) up