FROM ubuntu:latest

ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=Europe/Rome

RUN apt-get update && apt-get install -y \
php apache2 python3 python3-pip

RUN mkdir /var/www/api/

RUN a2enmod rewrite

COPY ./apache-conf/000-default.conf /etc/apache2/sites-available/000-default.conf
COPY ./apache-conf/ports.conf /etc/apache2/ports.conf

EXPOSE 80
EXPOSE 8080

CMD ["apache2ctl", "-D", "FOREGROUND"]