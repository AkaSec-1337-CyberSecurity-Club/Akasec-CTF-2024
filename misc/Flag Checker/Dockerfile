FROM gcc:13.3.0

RUN apt-get update \
    && apt-get install --no-install-recommends -y socat

COPY . /usr/src/myapp

WORKDIR /usr/src/myapp

RUN gcc -o chall chall.c

EXPOSE 4443

CMD socat -T60 TCP-L:4443,fork,reuseaddr EXEC:"./chall",pty,stderr,setsid,sane,raw,echo=0
