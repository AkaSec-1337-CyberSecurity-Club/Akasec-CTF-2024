FROM node:21-alpine

WORKDIR /app

COPY package*.json ./

RUN apk update
RUN apk add --no-cache zlib-dev udev nss ca-certificates
RUN apk add --no-cache chromium

RUN npm install
RUN npm i randomstring
RUN mkdir uploads

EXPOSE 5000

COPY . .

CMD [ "node", "app.js" ]
