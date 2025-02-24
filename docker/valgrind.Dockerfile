FROM alpine:latest
RUN apk add --no-cache build-base bash valgrind

WORKDIR /tmp
#COPY ./docker/logo.png logo.png # -> Just use a mounted volume later in the Makefile target

ENTRYPOINT [ "/usr/bin/env", "bash"]
