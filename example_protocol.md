# Example: Yet Another “Message of the Day” (YAMOTD) Protocol

## 1. Overview

The YAMOTD protocol is a line-oriented client-server protocol. All commands and responses are transmitted as ASCII text and terminated by a newline character (`\n`).

When the server starts, it opens a file containing five initial messages of the day. A message of the day is a short, single-line phrase, such as:

- `One can never be too rich, too thin, or have too much bandwidth.`
- `Anyone who has never made a mistake has never tried anything new.`

The server must:

1. Read the messages into an internal data structure.
2. Track the number of stored messages.
3. Listen for client connections.
4. maintain login information separately for each connected client.
5. Support multiple clients simultaneously.
6. Preserve newly stored messages by appending them to the message file.

The client must allow the user to issue any of the following commands:

- `MSGGET`
- `MSGSTORE`
- `LOGIN`
- `LOGOUT`
- `WHO`
- `SEND`
- `QUIT`
- `SHUTDOWN`

After executing a command, the client should return to its command prompt unless the command causes the client or server to terminate.

---

## 2. Response Codes

The protocol uses the following response codes:

| Code | Meaning |
|---|---|
| `200 OK` | The command was accepted or completed successfully. |
| `210 the server is about to shutdown` | The server is shutting down. |
| `300 message format error` | The command or message was incorrectly formatted. |
| `401 You are not currently logged in, login first.` | The command requires an authenticated user. |
| `402 User not allowed to execute this command.` | The authenticated user does not have permission to execute the command. |
| `410 Wrong UserID or Password.` | The supplied credentials are invalid. |
| `420 either the user does not exist or is not logged in` | The intended message recipient is invalid or inactive. |

---

## 3. Commands

### 3.1 `MSGGET`

The `MSGGET` command requests one message of the day.

#### Client request

```text
MSGGET\n
```

After sending the command, the client waits for the server’s response and displays both the status line and the returned message.

#### Server behavior

When the server receives `MSGGET`, it returns:

1. `200 OK`, terminated by a newline.
2. One message of the day, terminated by a newline.

Messages must be selected sequentially. After the final message is returned, the server cycles back to the first message.

The client does not need to be logged in to use `MSGGET`.

#### Example

```text
c: MSGGET
s: 200 OK
s: Anyone who has never made a mistake has never tried anything new.
```

---

### 3.2 `MSGSTORE`

The `MSGSTORE` command allows an authenticated user to add one message to the server’s message store.

Messages must be single-line ASCII strings terminated by a newline.

#### Client request

The client first sends:

```text
MSGSTORE\n
```

The client must then wait for the server’s authorization response.

If the server responds with:

```text
200 OK
```

the client sends one message, terminated by a newline. It then waits for and displays the server’s final response.

If the server responds with:

```text
401 You are not currently logged in, login first.
```

the client must not send a message.

#### Server behavior

When the server receives `MSGSTORE`, it checks the login status associated with that client connection.

- If the client is not logged in, the server returns:

```text
401 You are not currently logged in, login first.
```

- If the client is logged in, the server returns:

```text
200 OK
```

The server then reads one message from the client, adds it to its internal data structure, and appends it to the message file.

If the message is received and stored successfully, the server returns:

```text
200 OK
```

If the message is incorrectly formatted, the server returns:

```text
300 message format error
```

#### Example

```text
c: MSGSTORE
s: 200 OK
c: Imagination is more important than knowledge.
s: 200 OK
```

---

### 3.3 `LOGIN`

The `LOGIN` command authenticates a user.

#### Client request

```text
LOGIN <UserID> <Password>\n
```

The command name, user ID, and password must be separated by single spaces.

#### Server behavior

The server verifies that:

1. The user ID exists.
2. The password is correct for that user ID.

If the credentials are valid, the server records the user as logged in on that client connection and returns:

```text
200 OK
```

If the credentials are invalid, the server returns:

```text
410 Wrong UserID or Password.
```

Login status is associated with the individual client connection. One client’s login must not authenticate another client.

#### Example

```text
c: LOGIN john john2025
s: 200 OK
```

---

### 3.4 `LOGOUT`

The `LOGOUT` command logs the current user out of the server without terminating the client connection.

#### Client request

```text
LOGOUT\n
```

#### Server behavior

The server clears the login information associated with the client connection and returns:

```text
200 OK
```

After logging out, the client may continue to use commands that do not require authentication, such as `MSGGET`. The client may not use `MSGSTORE` or `SHUTDOWN` unless it logs in again with the required credentials.

#### Example

```text
c: LOGOUT
s: 200 OK
```

---

### 3.5 `WHO`

The `WHO` command lists all currently active, logged-in users.

#### Client request

```text
WHO\n
```

#### Server behavior

The server returns:

1. `200 OK`
2. A heading
3. The user ID and IP address of each active, logged-in user

Each user must appear on a separate line.

The response should end with a blank line so the client can determine where the list ends.

#### Example

```text
c: WHO
s: 200 OK
s: The list of active users:
s: john    141.215.10.30
s: root    127.0.0.1
s:
```

Only logged-in users should appear in the list. If the same user is logged in through multiple connections, each active connection may be listed separately.

---

### 3.6 `SEND`

The `SEND` command allows a logged-in user to send a private, single-line message to another active user.

#### Client request

The client first sends:

```text
SEND <UserID>\n
```

The client then waits for the server’s response.

If the intended recipient exists and is logged in, the server returns:

```text
200 OK
```

The sending client then transmits one single-line message terminated by a newline. After the server receives and forwards the message, it returns a final:

```text
200 OK
```

#### Server behavior

Before accepting the message, the server should verify that:

1. The sender is logged in.
2. The recipient’s user ID exists.
3. The recipient is currently logged in.

If the sender is not logged in, the server returns:

```text
401 You are not currently logged in, login first.
```

If the recipient does not exist or is not currently logged in, the server returns:

```text
420 either the user does not exist or is not logged in
```

Otherwise, the server accepts the next line as the message and immediately forwards it to the recipient’s client.

Because incoming private messages may arrive while the recipient is entering another command, the client must be able to receive and display asynchronous server messages.

#### Example at David’s client

```text
c: SEND john
s: 200 OK
c: Hello John
s: 200 OK
```

#### Example at John’s client

```text
s: 200 OK you have a new message from david
s: david: Hello John
```

---

### 3.7 `QUIT`

The `QUIT` command terminates the current client connection without shutting down the server.

#### Client request

```text
QUIT\n
```

#### Server behavior

The server returns:

```text
200 OK
```

The server then closes only that client’s socket and removes the client from the active-user list. The client should exit after receiving the confirmation.

The server must remain active and continue serving other clients.

#### Example

```text
c: QUIT
s: 200 OK
```

---

### 3.8 `SHUTDOWN`

The `SHUTDOWN` command terminates the server. Only a client logged in as `root` may execute this command.

#### Client request

```text
SHUTDOWN\n
```

#### Server behavior

When the server receives `SHUTDOWN`, it checks the identity associated with the requesting connection.

- If the client is not logged in, the server returns:

```text
401 You are not currently logged in, login first.
```

- If the client is logged in but is not `root`, the server returns:

```text
402 User not allowed to execute this command.
```

- If the client is logged in as `root`, the server returns:

```text
200 OK
```

The server must then notify all other connected clients by sending:

```text
210 the server is about to shutdown
```

Finally, the server must:

1. Close all client sockets.
2. Close its listening socket.
3. Flush and close all open files.
4. Release other allocated resources.
5. Terminate normally.

If the command is incorrectly formatted, the server returns:

```text
300 message format error
```

#### Example at the root client

```text
c: SHUTDOWN
s: 200 OK
```

#### Example at every other connected client

```text
s: 210 the server is about to shutdown
```

---

## 4. Required User Accounts

The server must contain the following user accounts. User IDs are lowercase and should be treated as case-sensitive.

| User ID | Password |
|---|---|
| `root` | `root2025` |
| `john` | `john2025` |
| `david` | `david2025` |
| `mary` | `mary2025` |

All authenticated users may execute `MSGSTORE` and `SEND`. Only `root` may execute `SHUTDOWN`.

---

## 5. General Protocol Requirements

1. Every command and response must end with `\n`.
2. Commands and user IDs are case-sensitive.
3. Messages of the day and private messages must each occupy exactly one line.
4. Login status must be maintained separately for each client connection.
5. A disconnected or quitting client must be removed from the active-user list.
6. The server must continue running after a client sends `QUIT`.
7. The server must support asynchronous private-message delivery.
8. Newly stored messages must be retained both in memory and in the server’s message file.
9. Malformed commands should receive:

```text
300 message format error
```

10. Passwords must never be included in `WHO` output or private-message notifications.