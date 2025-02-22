FROM alpine:latest AS builder

RUN apk add --no-cache build-base

WORKDIR /app
COPY ../Makefile .
COPY ../viewer/ ./viewer

RUN make -C viewer

FROM alpine:latest

WORKDIR /app
COPY --from=builder /app/viewer/aart_viewer /usr/local/bin/aart_viewer

ENTRYPOINT ["aart_viewer"]
