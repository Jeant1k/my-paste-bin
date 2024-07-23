.PHONY: build-hash-service
build-hash-service:
	docker-compose build -d hs-postgres
	docker-compose build hs-redis
	docker-compose build hs-flyway
	docker-compose build hash-service

.PHONY: run-hash-service
run-hash-service:
	docker-compose up -d hs-postgres
	docker-compose up -d hs-redis
	sleep 3
	docker-compose run hs-flyway
	docker-compose up hash-service

.PHONY: build-and-run-hash-service
build-and-run-hash-service: build-hash-service run-hash-service

.PHONY: stop-hash-service
stop-hash-service:
	docker-compose stop hs-postgres
	docker-compose stop hs-redis
	docker-compose stop hash-service


.PHONY: build-new-note-service
build-new-note-service:
	docker-compose build -d nns-postgres
	docker-compose build nns-flyway
	docker-compose build new-note-service

.PHONY: run-new-note-service
run-new-note-service:
	docker-compose up -d nns-postgres
	sleep 3
	docker-compose run nns-flyway
	docker-compose up new-note-service

.PHONY: build-and-run-new-note-service
build-and-run-new-note-service: build-new-note-service run-new-note-service

.PHONY: stop-new-note-service
stop-new-note-service:
	docker-compose stop nns-postgres
	docker-compose stop new-note-service

.PHONY: down
down:
	docker-compose down

.PHONY: stop
stop:
	docker compose stop

.PHONY: new-note-test
new-note-test:
	curl -X POST http://localhost:8081/new -d 'text=Hello world!'
