FROM ubuntu:latest

RUN apt-get update
RUN apt-get install socat make gcc curl -y

EXPOSE 1338

RUN useradd ctf

WORKDIR /chal
COPY main.c /chal
COPY makefile /chal
COPY flag.txt /chal

RUN make
RUN rm -rf makefile
USER ctf

CMD ["socat", "tcp-l:1338,reuseaddr,fork", "EXEC:./warmup"]
