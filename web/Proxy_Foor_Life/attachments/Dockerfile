FROM golang:latest

WORKDIR /app

COPY go.mod go.sum ./

RUN go mod download

COPY . .

RUN go build -o main .

EXPOSE 1337

USER nobody

CMD ["./main", "--FLAG=AKASEC{REDACTED}"]
