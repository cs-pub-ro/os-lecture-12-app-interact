# Single-Container WordPress Deployment

This project demonstrates a **monolithic container architecture** for running WordPress.
Instead of the standard multi-container approach (separate containers for the web server and database), this setup runs **Nginx**, **MariaDB**, and **PHP-FPM** all within a single Docker container.

This approach is useful for:

- **Development environments:** Easy to spin up/down as a single unit.
- **Education:** Understanding how the components (Web Server, Database, App Processor) interact on a file-system level.
- **Resource constrained environments:** Reducing Docker networking overhead.

> [!NOTE]
> In a production high-traffic environment, separating services is generally recommended for scalability and isolation.

## Contents

| File/Directory | Purpose |
| :--- | :--- |
| **`Dockerfile`** | Defines the custom Debian-based image. It installs Nginx, MariaDB, PHP extensions, and Supervisor, and downloads the WordPress source code. |
| **`docker-compose.yml`** | orchestrates the deployment. It builds the image, maps port `8080` (host) to `80` (container), and defines persistent volumes for database and web files. |
| **`config/nginx.conf`** | The Nginx server block configuration, tuned to serve PHP files and secure the WordPress installation. |
| **`config/supervisord.conf`** | Configuration for **Supervisor**, the process manager that keeps Nginx, PHP-FPM, and MariaDB running simultaneously in the foreground. |
| **`scripts/entrypoint.sh`** | The startup script. It handles initialization logic: initializing the MariaDB data directory, creating the database/user, configuring `wp-config.php`, and finally handing control over to Supervisor. |

## Prerequisites

Install [Docker](https://docs.docker.com/engine/install/) and [Docker Compose](https://docs.docker.com/compose/install/) on your system.

## Setup

Run the following command to build the image and start the container in detached mode (background):

```console
docker compose up -d --build
```

These actions happen during the build:

1. **Build:** Docker builds the image based on `Dockerfile`, installing all necessary packages.
1. **Volume Check:** The `entrypoint.sh` script checks if the persistent volume `/var/www/html` is empty.
   If so, it copies the WordPress source files there.
1. **Database Init:** The script checks if MariaDB is initialized.
   If not, it creates the system tables.
1. **Auto-Configuration:** It temporarily starts the database server to create the `wordpress` database and user (defined in `docker-compose.yml`) and automatically writes the `wp-config.php` file with these credentials.
1. **Process Management:** Finally, it starts `supervisord`, which launches and monitors Nginx, PHP-FPM, and MariaDB.

## How to Test / Use

1. **Access the Website:**
   Open your web browser and navigate to:
   [http://localhost:8080](http://localhost:8080)

   You should see the WordPress installation language selection screen.

1. **Verify Components:**
   You can check the running processes inside the container to verify everything is active:

   ```console
   docker exec -it wp-single-container ps aux
   ```

   You should see processes for `nginx`, `php-fpm`, `mariadbd`, and `supervisord`.

1. **Check Logs:**

   If you encounter issues, view the container logs:

   ```console
   docker compose logs -f
   ```

1. **Stop the Deployment:**
   To stop and remove the container (data will persist in Docker volumes):

   ```console
   docker compose down
   ```

   To stop and **delete all data**:

   ```console
   docker compose down -v
   ```
