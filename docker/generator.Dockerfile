FROM alpine:latest AS builder

RUN apk add --no-cache build-base

WORKDIR /app
COPY ../Makefile .
COPY ../generator/ ./generator

RUN make -C generator

FROM alpine:latest

WORKDIR /app
COPY --from=builder /app/generator/aart_generator /usr/local/bin/aart_generator

ENTRYPOINT ["aart_generator"]
