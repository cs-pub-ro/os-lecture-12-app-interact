#!/bin/bash
set -e

# Copy WordPress if volume is empty
if [ ! -f /var/www/html/wp-settings.php ]; then
    echo "WordPress not found in /var/www/html, copying from source..."
    cp -a /usr/src/wordpress/. /var/www/html/
    chown -R www-data:www-data /var/www/html
fi

# Fix MariaDB permissions
chown -R mysql:mysql /var/lib/mysql
mkdir -p /run/mysqld
chown -R mysql:mysql /run/mysqld

# Initialize MariaDB if needed
if [ ! -d "/var/lib/mysql/mysql" ]; then
    echo "Initializing MariaDB..."
    mariadb-install-db --user=mysql --datadir=/var/lib/mysql > /dev/null
fi

# Start MariaDB in background
echo "Starting MariaDB for setup..."
/usr/bin/mysqld_safe --datadir='/var/lib/mysql' --nowatch &
# Wait for MariaDB
echo "Waiting for MariaDB..."
for i in {30..0}; do
    if mysqladmin ping --silent; then
        break
    fi
    sleep 1
done

if [ "$i" -eq 0 ]; then
    echo "MariaDB failed to start"
    exit 1
fi

# Setup DB
DB_NAME=${DB_NAME:-wordpress}
DB_USER=${DB_USER:-wordpress}
DB_PASS=${DB_PASS:-wordpress}

echo "Setting up Database..."
mysql -u root <<EOF
CREATE DATABASE IF NOT EXISTS \`${DB_NAME}\`;
CREATE USER IF NOT EXISTS '${DB_USER}'@'localhost' IDENTIFIED BY '${DB_PASS}';
GRANT ALL PRIVILEGES ON \`${DB_NAME}\`.* TO '${DB_USER}'@'localhost';
FLUSH PRIVILEGES;
EOF

# Setup WP Config
if [ ! -f /var/www/html/wp-config.php ]; then
    echo "Configuring wp-config.php..."
    cp /var/www/html/wp-config-sample.php /var/www/html/wp-config.php
    sed -i "s/database_name_here/$DB_NAME/" /var/www/html/wp-config.php
    sed -i "s/username_here/$DB_USER/" /var/www/html/wp-config.php
    sed -i "s/password_here/$DB_PASS/" /var/www/html/wp-config.php

    # Fix permissions
    chown www-data:www-data /var/www/html/wp-config.php
fi

# Shutdown MariaDB nicely so Supervisor can take over
echo "Shutting down setup MariaDB..."
mysqladmin -u root shutdown
sleep 2

# Ensure PHP version is correct in supervisord and nginx
PHP_VERSION=$(php -r 'echo PHP_MAJOR_VERSION.".".PHP_MINOR_VERSION;')
sed -i "s/php-fpm7.4/php-fpm$PHP_VERSION/g" /etc/supervisor/conf.d/supervisord.conf
sed -i "s/php7.4-fpm/php$PHP_VERSION-fpm/g" /etc/nginx/sites-available/default

echo "Starting Supervisor..."
exec /usr/bin/supervisord -c /etc/supervisor/conf.d/supervisord.conf
