FROM python:3.11-slim

RUN apt-get update \
    && apt-get install --no-install-recommends -y socat

WORKDIR /usr/src/app

COPY . .

RUN pip install --no-cache-dir -r requirements.txt

ENV FLAG AKASEC{1nd33d_1t_1s_s0_l0ng!!}

EXPOSE 4441

CMD socat -T1200 TCP-L:4441,fork,reuseaddr EXEC:"python3 chall.py",pty,stderr,setsid,sane,raw,echo=0
