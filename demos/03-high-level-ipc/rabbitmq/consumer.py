import pika
import sys
import os

def main():
    # Establish a connection with RabbitMQ server
    connection = pika.BlockingConnection(pika.ConnectionParameters('localhost'))
    channel = connection.channel()

    # Ensure the queue exists
    channel.queue_declare(queue='hello')

    # Define a callback function to handle incoming messages
    def callback(ch, method, properties, body):
        print(f" [x] Received {body.decode()}")

    # Tell RabbitMQ that this particular function should receive messages from our 'hello' queue
    channel.basic_consume(queue='hello',
                          on_message_callback=callback,
                          auto_ack=True)

    print(' [*] Waiting for messages. To exit press CTRL+C')
    channel.start_consuming()

if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print('Interrupted')
        try:
            sys.exit(0)
        except SystemExit:
            os._exit(0)
