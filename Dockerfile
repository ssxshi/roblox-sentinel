FROM gcc:latest

WORKDIR /app

COPY . .

RUN g++ -o sentinel main.cpp -lpthread

EXPOSE 8080

CMD ["./sentinel"]