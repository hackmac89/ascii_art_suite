FROM alpine:latest AS builder
RUN apk add --no-cache build-base

WORKDIR /tmp
# -> Or should I just use a mounted volume later in the Makefile target?
COPY . .

RUN make

FROM alpine:latest AS runner

RUN apk add --no-cache valgrind

COPY --from=builder /tmp/generator/aart_generator /usr/bin/aart_generator
COPY --from=builder /tmp/viewer/aart_viewer /usr/bin/aart_viewer
COPY ./docker/valgrind_check.sh /usr/bin/valgrind_check.sh
COPY ./docker/logo.png /logo.png

ENTRYPOINT [ "/usr/bin/valgrind_check.sh"]
