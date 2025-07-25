# Use sudo if docker is not in rootless mode
SUDO			= $(shell docker info > /dev/null 2> /dev/null || echo sudo)
DOCKER_COMPOSE_FILE	= docker/docker-compose.yml

all: up
.PHONY: all

clean: down
.PHONY: clean

up:
	$(SUDO) docker compose -f ${DOCKER_COMPOSE_FILE} up -d
.PHONY: up

down:
	$(SUDO) docker compose -f ${DOCKER_COMPOSE_FILE} down
.PHONY: down

build:
	$(SUDO) docker compose -f ${DOCKER_COMPOSE_FILE} up --build -d
.PHONY: build

connect:
	ssh -p 2222 aria@127.0.0.1
.PHONY: connect
