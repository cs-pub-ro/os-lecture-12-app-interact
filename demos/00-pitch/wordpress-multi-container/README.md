# Multi-Container WordPress Deployment

This project demonstrates a **microservices-style container architecture** for running WordPress.
Unlike the single-container approach, this setup separates concerns by running each major component in its own container:

1.  **Nginx:** Acts as the web server and reverse proxy.
2.  **WordPress (PHP-FPM):** Handles the PHP application logic.
3.  **MariaDB:** Stores the database content.

This is the standard, production-ready way to deploy applications with Docker, allowing for independent scaling, maintenance, and upgrades of each component.

## Contents

| File/Directory | Purpose |
| :--- | :--- |
| **`docker-compose.yml`** | Defines the 3 services (`db`, `wordpress`, `nginx`), their networks, and shared volumes. |
| **`nginx/conf.d/default.conf`** | The Nginx configuration file. It tells Nginx to serve static files from the shared volume and pass `.php` requests to the `wordpress` container on port 9000. |

## Prerequisites

Install [Docker](https://docs.docker.com/engine/install/) and [Docker Compose](https://docs.docker.com/compose/install/) on your system.

## Steps

Run the following command to download the images and start the cluster:

```console
docker compose up -d
```

All containers share a custom bridge network (`wp-network`), allowing them to communicate by container name (e.g., Nginx talks to `wordpress:9000`).

Two volumes are involved:

1. `wp_data`: Shared between the `wordpress` container (to write code/uploads) and `nginx` container (to serve static files like CSS/JS).
1. `db_data`: Persists the database storage.

## How to Test / Use

1. **Access the Website:**
   Open your web browser and navigate to:
   [http://localhost:8081](http://localhost:8081)

   **Note**: This setup uses port **8081** to avoid conflict with the single-container demo on 8080.

   **Troubleshooting**: If you see a **500 Internal Server Error** immediately after starting, wait a few seconds and refresh.
   This can happen if the MariaDB container is still initializing the database when WordPress first tries to connect.

2. **Verify Separation:**

   List the running containers to see the three distinct instances:

   ```console
   docker ps | grep wp-multi
   ```

   You will see `wp-multi-web`, `wp-multi-app`, and `wp-multi-db`.

3. **Stop the Deployment:**

   To stop the cluster:

   ```console
   docker compose down
   ```
