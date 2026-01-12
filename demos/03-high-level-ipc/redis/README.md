# Redis Reader/Writer Demo

This project demonstrates a simple communication pattern using Redis as a shared key-value store.

It uses two independent Python scripts can share data using Redis:

- **`writer.py`**: Connects to the Redis server and sets a key named `my_message` with a specific string value.
- **`reader.py`**: Connects to the Redis server, looks up the key `my_message`, and prints its value.

## Contents

- **`writer.py`**: Script to write data to Redis.
- **`reader.py`**: Script to read data from Redis.
- **`requirements.txt`**: List of Python dependencies (the `redis` client library).
- **`README.md`**: This documentation file.

## Prerequisites

You must have [Python](https://www.python.org/) 3.x installed on your system.

Install [Docker](https://docs.docker.com/engine/install/) to run the Redis server.

## Setup

### 1. Start Redis

Start a Redis instance using Docker:

```console
docker run -d --name redis_demo -p 6379:6379 redis:alpine
```

### 2. Install Dependencies

Create a virtual environment and install the required library:

```console
python3 -m venv .venv
source .venv/bin/activate  # On Windows: .venv\Scripts\activate
pip install -r requirements.txt
```

## Running the Demo

### 1. Run the Writer

Execute the writer script to store data in Redis:

```console
python writer.py
```

Output:

```text
 [x] Set key 'my_message' to 'Hello from Redis Writer!'
```

### 2. Run the Reader

Execute the reader script to retrieve the data:

```console
python reader.py
```

Output:

```text
 [x] Retrieved key 'my_message': Hello from Redis Writer!
```
