# RabbitMQ Producer-Consumer Demo

This is a simple Python demonstration of the Producer-Consumer pattern using RabbitMQ as the message broker.

It has two main components:

- **`producer.py`**: Connects to RabbitMQ, declares a queue named `hello`, and sends a single "Hello World!" message.
- **`consumer.py`**: Connects to RabbitMQ, ensures the `hello` queue exists, and waits for messages. When it receives a message, it prints the content to the console.

## Prerequisites

You must have [Python](https://www.python.org/) 3.x installed on your system.

Install [Docker](https://docs.docker.com/engine/install/) to run the RabbitMQ broker.

## Setup

### 1. Start RabbitMQ

Run the following command to start a RabbitMQ container:

```console
docker run -d --name rabbitmq -p 5672:5672 -p 15672:15672 rabbitmq:3-management
```

### 3. Install Dependencies

It is recommended to use a virtual environment:

```console
python3 -m venv .venv
source .venv/bin/activate  # On Windows use: .venv\Scripts\activate
pip install -r requirements.txt
```

## Running the Demo

### 1. Start the Consumer

Open a terminal and run the consumer.
It will stay active, waiting for messages:

```console
python consumer.py
```

### 2. Run the Producer

Open a second terminal and run the producer to send a message:

```console
python producer.py
```

### 3. Observe Results

In the consumer's terminal, you should see:

```text
 [*] Waiting for messages. To exit press CTRL+C
 [x] Received Hello World!
```
