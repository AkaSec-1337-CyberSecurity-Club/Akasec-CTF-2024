# Dockerfile

FROM python:latest

RUN apt-get update \
    && apt-get install --no-install-recommends -y socat \
    && groupadd ctf \
    && useradd -r -g ctf ctf

WORKDIR /usr/src/app

COPY generator.py chall.py ./

RUN python generator.py \
    && chmod 500 chall.py \
    && chown ctf:root chall.py 

USER ctf

EXPOSE 4213

CMD socat TCP-L:4213,fork,reuseaddr EXEC:"python3 chall.py",pty,stderr,setsid,sane,raw,echo=0
