import redis

def main():
    # Connect to local Redis instance
    r = redis.Redis(host='localhost', port=6379, decode_responses=True)

    key = 'my_message'
    
    # Get the value
    value = r.get(key)
    
    if value:
        print(f" [x] Retrieved key '{key}': {value}")
    else:
        print(f" [!] Key '{key}' not found.")

if __name__ == "__main__":
    main()
