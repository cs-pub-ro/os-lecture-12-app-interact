import pika

def main():
    # Establish a connection with RabbitMQ server
    connection = pika.BlockingConnection(pika.ConnectionParameters('localhost'))
    channel = connection.channel()

    # Create a queue named 'hello'
    channel.queue_declare(queue='hello')

    message = "Hello World!"

    # Send a message to the 'hello' queue
    channel.basic_publish(exchange='',
                          routing_key='hello',
                          body=message)

    print(f" [x] Sent '{message}'")

    # Close the connection
    connection.close()

if __name__ == "__main__":
    main()
