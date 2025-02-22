.PHONY: all clean help

all: 
	@$(MAKE) -C generator
	@$(MAKE) -C viewer

clean:
	@$(MAKE) -C generator clean
	@$(MAKE) -C viewer clean

docker-build-generator:
	@docker build -t ascii-art-generator -f docker/generator.Dockerfile .

docker-build-viewer:
	@docker build -t ascii-art-viewer -f docker/viewer.Dockerfile .

help:
	@echo "Usage:"
	@echo ""
	@echo "  make        			- Builds both ASCII art generator and viewer"
	@echo "  make clean  			- Removes compiled files"
	@echo "  make -C generator		- Builds only the generator"
	@echo "  make -C viewer		- Builds only the viewer"
	@echo "  make docker-build-generator	- Builds the docker image for the ASCII art generator"
	@echo "  make docker-build-viewer	- Builds the docker image for the ASCII art viewer"
	@echo "  make help   			- Shows this message"
