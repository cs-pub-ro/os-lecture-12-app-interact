# Application Interaction

# 0. Pitch

- **discussion**: How do search engines work? https://substackcdn.com/image/fetch/f_auto,q_auto:good,fl_progressive:steep/https%3A%2F%2Fsubstack-post-media.s3.amazonaws.com%2Fpublic%2Fimages%2F8d428e8b-48d0-4268-8a50-9781b20375f3_2000x2600.gif
- **demo**: Wordpress deployment: a) all in one container; b) separate containers for each component (web server, PHP engine, database) (as Docker Compose specification)

# 1. Applications as Processes

- **diagram**: compute (CPU + memory) + IO (interaction with the outside world)
- generally: do one thing
- isolated from the others to prevent abuse and exploitation
- in certain situations, a use case requires a single process: edit a file, watch a movie, play a game
  - **diagram**: typically user-centered scenarios: something that a user actually interacts with
- in other situation, a use case requires multiple processes: deploy a search engine, have an LLM-based recommendations engine, deploy a web application
  - **diagram**: typically service-centered scenarios: something exposed to other applications
- so processes interact with each other to provide an actual use case, to provide a service
- even in single process use cases, process will interact with the others
  - an editor will interact with the desktop manager
  - a web browser will interact with a web server
  - a game will connect to a remote server for login and scoring

# 2. Why Applications as Multi-processes

- a process does one thing
- modularity and reusability
- isolation among components, reduce the potential damage
- flexibility in connecting processes
- distribution among different systems: redundancy (fail over) and scalability (load balancing)
- **diagram** + **discussion**: GitLab: https://docs.gitlab.com/administration/dedicated/architecture/
- **diagram** + **discussion**: How does Discord work? https://discord.com/blog/how-discord-stores-trillions-of-messages, https://discord.com/blog/how-discord-handles-two-and-half-million-concurrent-voice-users-using-webrtc, https://www.linkedin.com/posts/alexandre-zajac_softwareengineering-systemdesign-coding-activity-7317796588049866753-1CuY/, https://www.almabetter.com/bytes/articles/build-a-distributed-messaging-system-like-discord
- **diagram** + **discussion**: How does Netflix work? https://rockybhatia.substack.com/p/inside-netflixs-architecture-how, https://substackcdn.com/image/fetch/$s_!PGgA!,f_auto,q_auto:good,fl_progressive:steep/https%3A%2F%2Fsubstack-post-media.s3.amazonaws.com%2Fpublic%2Fimages%2F3b516bb3-bd9e-4d21-ab68-a294f70a8154_800x1074.gif, https://blog.bytebytego.com/p/how-netflix-manages-238-million-memberships, https://newsletter.techworld-with-milan.com/p/how-does-netflix-manage-to-show-you, https://www.geeksforgeeks.org/system-design/system-design-netflix-a-complete-architecture/

# 3. Application Interaction Primitives

- send_message(), receive_message(), broadcast_message()
- store_data(), read_data()
- notify(), wait_for_notification()
- **demo**: RabbitMQ
- **demo**: Redis

# 4. Application Interaction Low-level Primitives

- IPC: Inter-process communication
- messages: sockets, pipes, FIFOs, message queues
- store: files (databases) - persistent, shared memory (non-persistent)
  - synchronization required
- **demo**: shared memory
- notifications: signals, timers, eventfd, synchronization primitives (mutexes, semaphores, file locking)
- **demo**: signals
- **demo**: eventfd

# 5. Taxonomy of Applications

- local (all IPCs all except network sockets) vs distributed (remote IPCs, network sockets)
- homogeneous (multi-process app: web servers) vs heterogeneous (multiple processes app: GitLab, Wordpress)
- for homogeneous: multi-process vs multi-thread app: isolation / security vs speed / efficiency

# 6. Table of Low-Level IPC Primitives

| Primitive                  | Primitive Type          | Speed     | Persistence | One-to-one or One-to-many | Local or Remote Use |
|----------------------------|-------------------------|-----------|-------------|---------------------------|---------------------|
| Files                      | Store                   | Medium    | Yes         | One-to-many               | Local               |
| Pipes                      | Messaging               | Fast      | No          | One-to-one                | Local               |
| FIFOs (Named Pipes)        | Messaging               | Fast      | Yes         | One-to-one                | Local               |
| Shared Memory              | Store                   | Very Fast | Yes         | One-to-many               | Local               |
| Message Queues             | Messaging               | Moderate  | Yes         | One-to-many               | Local               |
| Signals (UNIX)             | Notification            | Very Fast | No          | One-to-one                | Local               |
| Synchronization Primitives | Notification/Control    | Very Fast | No          | One-to-many               | Local               |
| eventfd (Linux)            | Notification            | Very Fast | No          | One-to-one                | Local               |
| Local-Domain Sockets       | Messaging               | Fast      | Yes         | One-to-one/One-to-many    | Local               |
| Network Sockets            | Messaging               | Fast      | Yes         | One-to-one/One-to-many    | Remote              |
| Memory Mapped Files        | Store                   | Very Fast | Yes         | One-to-many               | Local               |
| Binder (Android/Linux)     | Messaging/RPC           | Fast      | No          | One-to-one/One-to-many    | Local               |
| Mach Ports (macOS)         | Messaging               | Fast      | No          | One-to-one                | Local               |
| ALPC (Windows)             | Messaging               | Very Fast | No          | One-to-one                | Local               |

# Conclusion and Takeaways

- Applications are running as single-processes or multi-processes.
- Service-type application generally run as multiple processes (e.g. Discord, Netflix, GitHub): diverse processes doing different things.
- Having multiple processes and a decentralized architecture benefits modularity, scaling, redundancy, security.
- Processes interact via message passing, storing and reading data, and notifying and waiting for notifications.
- The low-level primitives used for process interaction are called IPC (_Inter-process communication_) mechanisms.
- Processes in a multi-process application may run local or distributed, may be homogeneous or heterogeneous.
