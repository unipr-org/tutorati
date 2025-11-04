# Base image
FROM ubuntu:22.04

# Setup ambiente non interattivo per evitare prompt durante le installazioni
ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=Europe/Rome

# Aggiornamento di sistema
RUN apt-get update -y && apt-get upgrade -y

# Installazione Apache e PHP
RUN apt-get install -y php-common libapache2-mod-php php-cli python3-pip

EXPOSE 80

# Esecuzione di Apache in foreground
CMD ["apachectl", "-D", "FOREGROUND"]