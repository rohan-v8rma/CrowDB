FROM ubuntu:18.04

# updating and installing required applications

RUN apt-get update -y && apt-get upgrade -y && apt-get install -y build-essential\
    cmake \
    libboost-all-dev --no-install-recommends

# now setting up the project
COPY . usr/project/Mr-Database/
WORKDIR /usr/project/Mr-Database/build
RUN cmake .. && make


EXPOSE 3000
CMD [ "./bin/Mr-Database" ]
