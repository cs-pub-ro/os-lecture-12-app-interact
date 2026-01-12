import redis

def main():
    # Connect to local Redis instance
    r = redis.Redis(host='localhost', port=6379, decode_responses=True)

    key = 'my_message'
    value = 'Hello from Redis Writer!'

    # Set the key-value pair
    r.set(key, value)
    
    print(f" [x] Set key '{key}' to '{value}'")

if __name__ == "__main__":
    main()
