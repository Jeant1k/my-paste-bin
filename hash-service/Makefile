# Сборка hash-service
.PHONY: build
build:
	docker-compose build

# Произвести миграции БД
.PHONY: migrate
migrate:
	docker-compose run flyway

# Запуск hash-service
.PHONY: run
run:
	docker-compose up hash-service

# Сборка, миграция и запуск
.PHONY: build-and-run
build-and-run: build migrate up

# Остановка hash-service
.PHONY: down
down:
	docker-compose down

# Удаление служебных файлов
.PHONY: clean
clean:
	sudo rm -r postgres-data/