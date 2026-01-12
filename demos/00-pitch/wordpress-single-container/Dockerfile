FROM debian:bullseye-slim AS base

ENV DEBIAN_FRONTEND=noninteractive

# Install dependencies
RUN apt-get update && apt-get install -y \
    nginx \
    mariadb-server \
    php-fpm \
    php-mysql \
    php-curl \
    php-gd \
    php-mbstring \
    php-xml \
    php-xmlrpc \
    supervisor \
    curl \
    ca-certificates \
    unzip \
    less \
    && rm -rf /var/lib/apt/lists/*

# Download WordPress to a source directory
RUN mkdir -p /usr/src/wordpress && \
    curl -o /tmp/latest.zip https://wordpress.org/latest.zip && \
    unzip /tmp/latest.zip -d /usr/src/ && \
    rm /tmp/latest.zip && \
    chown -R www-data:www-data /usr/src/wordpress

# Create required directories
RUN mkdir -p /run/php /var/run/mysqld /var/www/html && \
    chown -R mysql:mysql /var/run/mysqld && \
    chown -R www-data:www-data /var/www/html

# Copy configuration and scripts
COPY config/nginx.conf /etc/nginx/sites-available/default
COPY config/supervisord.conf /etc/supervisor/conf.d/supervisord.conf
COPY scripts/entrypoint.sh /usr/local/bin/entrypoint.sh

RUN chmod +x /usr/local/bin/entrypoint.sh

EXPOSE 80

ENTRYPOINT ["/usr/local/bin/entrypoint.sh"]
