FROM alpine:latest

RUN sed -i 's/dl-cdn.alpinelinux.org/mirrors.aliyun.com/g' /etc/apk/repositories

RUN apk add --no-cache \
    build-base \
    socat \
    iputils

RUN chmod 4755 $(which ping)

RUN adduser -D -h /home/kagureion kagureion

WORKDIR /home/kagureion/challenge

COPY inc/ ./inc/
COPY src/ ./src/
COPY data/ ./data/

RUN gcc src/main.c src/protocol.c src/utils.c src/crypto.c -o data/vocaend -I ./inc -fstack-protector-all -no-pie -lm -Wall -z lazy -s -O2

RUN chown -R kagureion:kagureion /home/kagureion/challenge && \
    chmod 700 /home/kagureion/challenge/data && \
    chmod 700 /home/kagureion/challenge/data/vocaend

USER kagureion

WORKDIR /home/kagureion/challenge/data

EXPOSE 9999

CMD sh -c 'echo "$GZCTF_FLAG" > flag && exec socat TCP-LISTEN:9999,reuseaddr,fork EXEC:./vocaend,stderr'