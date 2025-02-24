.PHONY: all clean help check-for-docker docker-build-generator docker-build-viewer

all: 
	@$(MAKE) -C generator
	@$(MAKE) -C viewer

clean:
	@$(MAKE) -C generator clean
	@$(MAKE) -C viewer clean

check-for-docker:
	@if (! docker stats --no-stream > /dev/null 2>&1 ); then	\
		printf "\e[31;1m%s\n"  "❌ ERROR: Start the docker daemon before running Makefile";	\
		exit 1;	\
	fi

docker-build-generator: check-for-docker
	@docker build -t ascii-art-generator -f docker/generator.Dockerfile .

docker-build-viewer: check-for-docker
	@docker build -t ascii-art-viewer -f docker/viewer.Dockerfile .

#valgrind: check-for-docker
#	@docker run -it --rm -v $(PWD):/app -w /app ascii-art-generator valgrind --leak-check=full ./generator/ascii-art-generator

help:
	@echo "Usage:"
	@echo ""
	@echo "  make        			- Builds both ASCII art generator and viewer"
	@echo "  make clean  			- Removes compiled files"
	@echo "  make -C generator		- Builds only the generator"
	@echo "  make -C viewer		- Builds only the viewer"
	@echo "  make docker-build-generator	- Builds the docker image for the ASCII art generator"
	@echo "  make docker-build-viewer	- Builds the docker image for the ASCII art viewer"
	@echo "  make valgrind			- Runs valgrind on the generator and viewer applications"
	@echo "  make help   			- Shows this message"
