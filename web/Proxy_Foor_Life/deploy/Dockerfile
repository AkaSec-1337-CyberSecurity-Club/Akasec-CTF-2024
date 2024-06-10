FROM golang:latest

WORKDIR /app

COPY go.mod go.sum ./

RUN go mod download

COPY . .

RUN go build -o main .

EXPOSE 1337

USER nobody

CMD ["./main", "--FLAG=AKASEC{p20x1n9_f002_11f3_15n7_92347_4f732_411}"]
