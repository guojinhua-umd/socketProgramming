# Socket Programming Project  
## Designing a Networked Service That Creates Value

### Entrepreneurial Mindset Focus: Creating Value  
**Supporting habits:** Customer-Centric Thinking and Scale

---

## Project Overview

When software engineers build networked applications, success is rarely measured by whether the sockets merely compile or transmit bytes. Success is measured by whether users can reliably accomplish something meaningful.

Messaging platforms, multiplayer games, banking systems, reservation services, and cloud applications all create value by solving problems for users. The engineers behind these systems must continually ask:

- Who benefits from this application?
- What problem does it solve?
- Which features matter most to users?
- How will the system respond when communication fails?
- What must change as the number of users grows?

In this project, your team will design and implement a useful client-server application using TCP sockets. You will begin by investigating a user need, develop and document a protocol, build a working application for one client, and then scale the system to support multiple simultaneous clients.

The project has three phases:

1. **Proposal: Curiosity Report and Detailed Design**
2. **Working Application: One Client and One Server**
3. **Working Application: Multiple Clients and One Server**

The goal is not simply to demonstrate socket programming. Your goal is to create a reliable networked service that delivers value to users.

---

# 1. Learning Objectives

By completing this project, students will be able to:

1. Explain the roles of clients, servers, sockets, ports, and protocols.
2. Design and implement a TCP client-server application.
3. Create an application-layer protocol with clearly structured messages.
4. Account for the stream-oriented nature of TCP through appropriate message framing.
5. Maintain application state on a server.
6. Detect and respond to malformed messages and communication failures.
7. Support multiple simultaneous clients using threads, asynchronous I/O, or another approved concurrency model.
8. Protect shared data from race conditions and inconsistent updates.
9. Gather evidence about user needs and translate those needs into technical requirements.
10. Evaluate how technical decisions affect usability, reliability, and scalability.
11. Communicate a software design through diagrams, protocol documentation, testing evidence, and demonstrations.
12. Reflect on how an engineering solution creates value for users and other stakeholders.

---

# 2. Project Scenario

Your team has been asked to identify a problem that could be addressed through a networked application. You are responsible for discovering the user need, proposing a solution, designing the client-server architecture, and implementing a functional prototype.

Possible projects include:

- Collaborative to-do list
- Multiplayer quiz game
- Chat room
- File-sharing service
- Remote note-sharing application
- Classroom polling system
- Appointment scheduler
- Library book reservation system
- Distributed calculator
- Networked tic-tac-toe
- Inventory tracker
- Study-group coordination service
- Help-request queue
- Shared brainstorming board
- Campus event coordination service
- Equipment checkout system

These examples are starting points, not limitations. Teams are free to propose another idea.

Projects will be evaluated according to the quality of the problem-solution fit, protocol design, implementation, reliability, testing, and scalability—not according to flashy graphics or excessive feature count.

---

# 3. Team and Scope Expectations

Unless otherwise specified by the instructor:

- Teams should contain **2–4 students**.
- All team members must make substantial technical contributions.
- The system must contain:
  - One server application
  - At least one client application
  - A documented application-layer protocol
  - Shared or server-managed application data
- The client interface must be plain text, command-line or menu-driven.
- Networking must be implemented using **TCP sockets**.
- External networking frameworks may be used only with instructor approval.
- The core socket communication, protocol handling, and concurrency behavior must be clearly identifiable in the submitted code.

Each team should assign and rotate responsibilities when practical. Possible responsibilities include:

- Customer or user research
- Protocol design
- Client implementation
- Server implementation
- Data model design
- Concurrency and synchronization (Optional)
- Testing and quality assurance
- Documentation and demonstration planning

---

# 4. Baseline System Requirements

The project will be completed incrementally, but the final application must satisfy all requirements below.

## 4.1 Server Requirements

The final server must:

- Create and bind a TCP socket.
- Listen on a configurable port.
- Accept connections from multiple clients.
- Process requests according to the documented protocol.
- Maintain shared or server-managed application data.
- Validate incoming messages before processing them.
- Return clear success and error responses.
- Continue operating after a client sends an invalid request.
- Handle unexpected client disconnections without crashing.
- terminate client sessions gracefully when requested.
- Record important client and server activities in a log.
- Synchronize access to shared mutable data when necessary. (optional)
- Shut down cleanly and release networking resources.

## 4.2 Client Requirements

The final client must:

- Connect to a server using a configurable hostname or IP address and port.
- Provide a clear menu-driven or command-driven interface.
- Send properly formatted requests.
- Display server responses in a readable form.
- Validate user input where appropriate.
- Detect and report connection errors.
- Handle a server disconnect without crashing.
- Support graceful session termination.

## 4.3 Protocol Requirements

The application-layer protocol must:

- Define how messages are separated or framed.
- Use a consistent structured message format.
- Identify the purpose or type of each message.
- Define the fields required for each request and response.
- Distinguish successful responses from errors.
- Describe how invalid or unsupported messages are handled.
- Define the connection and disconnection sequence.
- Work correctly even when one logical message is split across multiple socket reads.
- Work correctly if multiple logical messages arrive in one socket read.

Teams may use:

- Delimited text
- Key-value pairs
- JSON
- Another instructor-approved structure

Because TCP is a byte stream, teams may **not** assume that one `send` operation corresponds to exactly one `receive` operation. The protocol must use an explicit framing strategy, such as:

- Newline-delimited messages
- A length-prefixed message
- A fixed-length header containing payload size
- Another documented and reliable framing method

## 4.4 Reliability and Error-Handling Requirements

The application must account for conditions such as:

- Invalid hostname or IP address
- Invalid port
- Server unavailable
- Unexpected server shutdown
- Unexpected client disconnection
- Empty messages
- Malformed requests
- Missing required fields
- Unknown commands
- Invalid application data
- Duplicate requests where relevant
- Timeout conditions where appropriate
- Attempts to perform operations that violate application rules

Error messages should be useful to the user without revealing sensitive implementation details.

---

# 5. Phase 1: Proposal: Curiosity Report and Detailed Design Documents

## Purpose

Before writing the full application, your team will investigate the problem, identify the intended users, define the value your application provides, and create a design that can scale from one client to multiple clients.

This phase emphasizes **curiosity before implementation**. Do not begin by asking, “What can we make sockets do?” Begin by asking, “What do users need, and how can a networked system help?”

---

## 5.1 Curiosity Report

Submit a report that addresses the following areas.

### A. Problem Exploration

Describe:

- The problem or opportunity your team identified
- Who experiences the problem
- When and where the problem occurs
- How people currently address the problem
- Limitations of existing approaches
- Why a networked application is appropriate

### B. Curiosity Questions

Develop at least **eight meaningful questions** your team explored. Questions should go beyond implementation details.

Examples:

- Who would use this application most often?
- What outcome is the user trying to achieve?
- What information must be shared between users?
- Which tasks must happen in real time?
- What happens when two users update the same data?
- What would cause a user to stop trusting the application?
- What is the minimum feature set that would still be valuable?
- What changes when the system grows from one user to 100 users?
- Which data must persist after users disconnect?
- What accessibility or usability barriers could affect users?

For each question, briefly summarize what your team learned or what assumption still needs to be tested.

### C. User and Stakeholder Evidence

Gather evidence from at least one appropriate source, such as:

- A short interview
- A brief survey
- Observation of an existing process
- Review of an existing product
- A scenario analysis
- Published documentation or research

Summarize the evidence and explain how it influenced the project proposal.

Do not collect sensitive personal information. Any user research should be voluntary and appropriate for a classroom project.

### D. Target Users

Identify:

- Primary users
- Secondary users or stakeholders
- User goals
- Likely user frustrations
- Technical experience assumptions
- Accessibility considerations

Include at least **two user stories** in the following form:

> As a **[type of user]**, I want to **[perform an action]** so that **[valuable outcome]**.

Example:

> As a student working on a group project, I want to update a shared task list so that every team member can see the current responsibilities.

### E. Value Proposition

Write a concise value proposition:

> For **[target users]** who need **[need or opportunity]**, our application provides **[service or benefit]**. Unlike **[current approach or alternative]**, it **[meaningful difference]**.

Explain how the application creates value in at least three dimensions:

- **Functional value:** What useful task does it enable?
- **Experiential value:** How does it improve the user’s experience?
- **Reliability value:** Why can users trust the system?
- **Scalability value:** How does supporting additional users increase or affect its value?

### F. Assumptions, Risks, and Open Questions

List at least:

- Three assumptions
- Three technical or user-facing risks
- Two unanswered questions

For each risk, include a possible mitigation.

---

## 5.2 Project Proposal

The proposal must include:

1. Application name
2. Problem statement
3. Target users
4. Value proposition
5. Project scope
6. Minimum viable product, or MVP
7. Proposed unique feature
8. Features intentionally excluded from the initial version
9. Expected client-server interactions
10. Team member responsibilities

The MVP should include enough functionality to create value while remaining achievable within the available time.

---

## 5.3 Functional Requirements Document

Create a numbered list of functional requirements.

Example:

- **FR-01:** The client shall allow a user to create an account name for the session.
- **FR-02:** The server shall reject duplicate active account names.
- **FR-03:** The client shall allow a user to submit a new task.
- **FR-04:** The server shall distribute the updated task list to connected clients.

Each requirement should be:

- Specific
- Testable
- Relevant to user value
- Assigned a priority

Use one of the following priority labels:

- **Must Have**
- **Should Have**
- **Could Have**
- **Future Work**

Include at least:

- Six “Must Have” requirements
- Two error-handling requirements
- One graceful-disconnection requirement
- One requirement involving shared server data
- One requirement involving multiple clients

---

## 5.4 Nonfunctional Requirements

Define measurable expectations for:

- Reliability
- Usability
- Performance
- Scalability
- Maintainability
- Security
- Accessibility

Example:

> **NFR-01:** The server shall continue running after receiving an unsupported command from a client.

> **NFR-02:** A new user shall be able to identify the main client commands without reading the source code.

Avoid vague requirements such as “The application will be fast” or “The interface will be user-friendly.”

---

## 5.5 Client-Server Architecture Diagram

Provide a labeled diagram showing:

- Client application components
- Server application components
- TCP connections
- Request and response directions
- Shared data
- Logging component
- Thread, task, or event-loop structure planned for Phase 3
- Any persistent storage, if used

A second sequence diagram should illustrate at least one important user interaction from connection through response.

---

## 5.6 Application-Layer Protocol Specification

Document the complete protocol before implementation.

For every message type, specify:

- Message name or command
- Sender
- Receiver
- Required fields
- Optional fields
- Field data types
- Valid values
- Example request
- Example success response
- Example error response

The protocol specification must also explain:

- Message-framing strategy
- Character encoding
- Maximum message size, if applicable
- Connection initialization
- Session state
- Normal disconnection
- Invalid-message handling
- Versioning strategy
- Whether server notifications can occur without a client request

Here is a detailed example on [Yet Another “Message of the Day” (YAMOTD) Protocol](example_protocol.md).
---

## 5.7 Data Design

Document the major data structures used by the client and server.

Include:

- Structure or class name
- Purpose
- Fields and data types
- Ownership: client, server, or shared
- Validation rules
- Whether it is mutable
- How concurrent access will be controlled in Phase 3 (optional)

If persistence is used, include a file or database schema.

---

## 5.8 Testing Plan

Create a test plan containing at least:

- Three normal-operation tests
- Three invalid-input tests
- Two networking failure tests
- Two protocol-framing tests
- Two concurrency tests planned for Phase 3

Each test should identify:

1. Test ID
2. Requirement tested
3. Initial conditions
4. Input or action
5. Expected result
6. Actual result, when available
7. Pass/fail status

---

## Phase 1 Deliverables

Submit:

- Curiosity Report
- Project proposal
- Functional and nonfunctional requirements
- Architecture diagram
- Sequence diagram
- Protocol specification
- Data design
- Initial test plan
- Team contribution plan

---

# 6. Phase 2: Working Application—One Client and One Server

## Purpose

In Phase 2, your team will implement the first complete vertical slice of the system. One client must connect to one server, exchange properly framed messages, perform useful application operations, and disconnect gracefully.

This phase should validate the architecture and protocol before concurrency is introduced.

---

## 6.1 Required Functionality

### Server

The Phase 2 server must:

- Start on a configurable port.
- Accept one active client connection.
- Receive and reconstruct complete protocol messages.
- Validate each request.
- Perform at least three meaningful application operations.
- Maintain server-side state during the session.
- Send structured responses.
- Record client activity in a log.
- Handle malformed or unsupported requests.
- Detect client disconnection.
- Shut down or return to a listening state as specified in the design.

### Client

The Phase 2 client must:

- Accept a hostname or IP address and port.
- Connect to the server.
- Present a menu or command interface.
- Support at least three meaningful operations.
- Validate user input.
- Send requests using the documented protocol.
- Display successful and unsuccessful responses clearly.
- Recover from invalid user input.
- Exit gracefully through a documented command.
- Report connection failures without crashing.

### Meaningful Operations

A meaningful operation changes or retrieves application state in a way that contributes to user value.

For example, a collaborative task application might support:

1. Add a task
2. List tasks
3. Mark a task complete
4. Remove a task

A simple “send text and echo it back” application is not sufficient unless the echo behavior is one component of a more substantial service.

---

## 6.2 Protocol Implementation Requirements

The Phase 2 implementation must:

- Match the approved protocol specification.
- Correctly frame messages.
- Correctly process partial reads.
- Correctly process multiple messages received together.
- Include structured success and error responses.
- Avoid relying on arbitrary delays to separate messages.
- Avoid assuming that one `send` equals one `receive`.

If the implementation differs from the Phase 1 design, update the protocol document and explain why the design changed.

---

## 6.3 Logging Requirements

At minimum, the server log must record:

- Server startup
- Listening address and port
- Client connection
- Client address or generated client identifier
- Request type
- Request outcome
- Validation or protocol errors
- Client disconnection
- Server shutdown

Logs should include timestamps. Sensitive information, such as passwords or private message content, should not be logged unnecessarily.

Example:

```text
2026-03-14T14:22:07 INFO  Server listening on 0.0.0.0:5050
2026-03-14T14:22:13 INFO  Client client-001 connected from 127.0.0.1
2026-03-14T14:22:20 INFO  client-001 CREATE_TASK success task_id=17
2026-03-14T14:22:41 WARN  client-001 invalid request: missing title
2026-03-14T14:23:05 INFO  client-001 disconnected gracefully
```

---

## 6.4 Error Scenarios to Demonstrate

Your Phase 2 application must demonstrate recovery from at least four of the following:

- Client attempts to connect when the server is not running.
- Client enters an invalid port.
- Client submits an empty command.
- Client sends an unknown command.
- A request contains a missing field.
- A field contains an invalid value.
- A message is split across multiple socket reads.
- Two messages arrive in a single socket read.
- Client exits unexpectedly.
- Server disconnects while the client is active.
- Client requests a nonexistent record or resource.

The application should not display an unhandled exception or terminate abruptly during the required scenarios.

---

## 6.5 Phase 2 Code Quality Expectations

The implementation should separate major responsibilities. For example:

- Network connection management
- Message framing and serialization
- Protocol validation
- Application logic
- Data management
- User interface
- Logging

Avoid placing all client or server behavior in one large function.

Code must include:

- Meaningful names
- Appropriate comments
- Functions or classes with focused responsibilities
- Consistent formatting
- Instructions for compilation and execution
- No hard-coded machine-specific paths or addresses

---

## 6.6 Phase 2 Demonstration

The demonstration must show:

1. Server startup
2. Client connection
3. At least three useful operations
4. A server-side data update
5. A valid protocol exchange
6. At least two invalid requests
7. Recovery after an error
8. Graceful client termination
9. Relevant server log entries

Each team member should explain at least one technical component.

---

## Phase 2 Deliverables

Submit:

- Client source code
- Server source code
- Build or dependency files
- README with execution instructions
- Updated protocol specification
- Updated architecture diagram, if needed
- Server log sample
- Completed Phase 2 test report
- Brief design-change summary
- Demonstration or instructor checkoff

---

# 7. Phase 3: Working Application—Multiple Clients and One Server

## Purpose

In Phase 3, your team will scale the application from a single-client prototype to a service that supports multiple simultaneous users.

Adding concurrency is not simply a matter of accepting more connections. The server must protect shared data, isolate failures, preserve protocol correctness, and provide predictable behavior when users perform overlapping operations.

---

## 7.1 Multi-Client Requirements

The final server must:

- Accept simultaneous clients.
- Process requests from multiple clients without one client unnecessarily blocking all others.
- Maintain shared application state.
- Prevent race conditions and corrupted data. (optional)
- Isolate most client-specific errors to the affected client session.
- Continue serving other clients after one client disconnects.
- assign each connection a unique identifier or session representation.
- Clean up resources when a client leaves.
- Log concurrent client activities.
- Shut down gracefully.

Unless the instructor specifies otherwise, the application should support a minimum of **three simultaneously connected clients**.

---

## 7.2 Approved Concurrency Approaches

Teams may use one of the following:

- One thread per client
- A thread pool
- Asynchronous I/O
- An event loop
- Nonblocking sockets with a selector
- Another instructor-approved approach

The design document must explain:

- Why the approach was selected
- How client sessions are represented
- Which data is shared
- Which operations require synchronization
- How synchronization is implemented
- How deadlocks or excessive lock contention are avoided
- How client resources are cleaned up

---

## 7.3 Shared-State Requirements

The final application must include at least one resource shared across clients.

Examples include:

- Shared task list
- Chat-room membership and message history
- Quiz scores
- Game state
- Reservation schedule
- Inventory records
- Poll results
- Shared notes
- Connected-user list

The system must define what happens when clients perform conflicting or overlapping actions.

Examples:

- Two users attempt to reserve the same time slot.
- Two users update the same record.
- One user deletes an item another user is viewing.
- Two players make a move at nearly the same time.
- A user disconnects during a transaction.

Conflict behavior must be documented and tested.

---

## 7.4 Client Update Strategy

Your application must use at least one of these approaches:

### Request-Response

Clients request the current state when needed.

### Server Push

The server sends notifications or updated state to clients when changes occur.

### Hybrid

The system uses request-response for operations and server push for selected notifications.

If server push is used, the client must be able to receive unsolicited server messages without corrupting user input or other responses. The protocol should distinguish notifications from responses.

---

## 7.5 Scalability Analysis

Your team must evaluate how the system would behave at larger scale.

Discuss:

- Expected behavior with 10 clients
- Expected behavior with 100 clients
- Likely bottlenecks
- Memory usage per client
- Thread or task growth
- Logging overhead
- Shared-data contention
- Network bandwidth
- Persistent-storage limitations
- Single-server failure risk
- Changes needed to support hundreds or thousands of users

You are not required to implement a distributed system. You are required to recognize the limits of the current design and propose realistic improvements.

Possible future improvements include:

- Thread pooling
- Asynchronous processing
- Database-backed persistence
- Caching
- Rate limiting
- Authentication
- Load balancing
- Replication
- Partitioning
- Message queues
- Horizontal scaling
- Monitoring and health checks

---

## 7.6 Final Testing Requirements

The final test report must include the Phase 1 and Phase 2 tests plus the following.

### Concurrent Operation Tests

Test at least:

1. Three clients connecting simultaneously
2. Three clients performing different operations
3. Two clients modifying shared data
4. Two clients attempting a conflicting operation
5. One client disconnecting while others remain active
6. One client sending an invalid request while others continue normally
7. Repeated connections and disconnections
8. Rapid submission of multiple valid messages
9. Partial-message delivery
10. Multiple messages arriving together

### Reliability Tests

Test at least:

- Unexpected client termination
- Server handling of malformed data
- Request for missing or nonexistent data
- Invalid state transition
- Graceful shutdown
- Restart behavior

### Load or Stress Test

Perform a modest automated or scripted test appropriate to the course level. Record:

- Number of simulated or actual clients
- Number of requests
- Test duration
- Successful requests
- Failed requests
- Average or approximate response time
- Observed limitations

Do not conduct stress tests against systems or networks without authorization.

---

## 7.7 Final Demonstration

The final demonstration must show:

1. Server startup
2. At least three simultaneous client connections
3. Client identities or session information
4. Shared application state
5. Concurrent user operations
6. A conflicting or overlapping operation
7. Correct synchronization or conflict resolution
8. One unexpected client disconnect
9. Continued operation for remaining clients
10. A malformed or invalid request
11. Graceful connection termination
12. Server logs
13. The project’s distinctive value-creating feature
14. A brief scalability discussion

All team members must participate.

---

## 7.8 Final Documentation

Submit a final technical report containing:

- Revised Curiosity Report
- Final problem statement and value proposition
- Final requirements
- Architecture diagram
- Sequence diagram
- Concurrency design
- Protocol specification
- Data structures
- Error-handling strategy
- Test results
- Known limitations
- Scalability analysis
- Team contribution summary
- Ripple Report reflection

The documentation must match the submitted implementation.

---

# 8. Reflection Activity: Ripple Report

Engineering decisions create ripples. A protocol decision may simplify the client but complicate the server. A locking strategy may prevent data corruption but reduce performance. An unclear error message may save development time while frustrating users.

Each team will submit a **Ripple Report** addressing the effects of its decisions.

## Part A: Effects on Users

Discuss:

- Which feature created the greatest value for users?
- Which design decision most improved reliability?
- Which part of the interface was most difficult for users to understand?
- How did error handling influence user trust?
- What user assumption turned out to be inaccurate?
- What evidence suggests the application solves the intended problem?

## Part B: Effects on Teammates

Discuss:

- How did the protocol design affect parallel development?
- Which documentation helped teammates work independently?
- Where did unclear responsibilities or assumptions create rework?
- How did the team resolve conflicting technical ideas?
- What would the team change about its development process?

## Part C: Effects of Networking Decisions

Discuss the ripple effects of at least three of the following:

- Message framing
- Protocol structure
- Client-session management
- Shared-state design
- Concurrency model
- Synchronization
- Error handling
- Logging
- Connection termination
- Data persistence

For each decision, explain:

1. The decision made
2. Why it was made
3. The benefit
4. The tradeoff or unintended consequence
5. What the team would change in a future version

## Part D: Scale Reflection

Respond to the following:

> If this application were deployed to hundreds or thousands of users, what would you improve first, and why?

Consider:

- Performance
- Reliability
- Security
- Accessibility
- Monitoring
- Persistence
- Deployment
- Redundancy
- User support

## Individual Reflection

Each student should include a short individual section explaining:

- Their contributions
- The most important networking concept they learned
- A technical challenge they overcame
- A skill they want to improve
- How their work contributed to user value

---

# 9. Submission Structure

A suggested repository structure is:

```text
project-name/
├── README.md
├── client/
│   └── source-files
├── server/
│   └── source-files
├── shared/
│   └── protocol-or-common-files
├── tests/
│   └── test-files
├── docs/
│   ├── curiosity-report.pdf
│   ├── requirements.pdf
│   ├── architecture-diagram.pdf
│   ├── protocol-specification.pdf
│   ├── test-report.pdf
│   └── ripple-report.pdf
├── logs/
│   └── sample-server.log
└── build-or-dependency-files
```

The README must include:

- Project name and purpose
- Team members
- Required software
- Build instructions
- Server startup instructions
- Client startup instructions
- Command-line arguments
- Example interaction
- Test instructions
- Known limitations
- Attribution for external libraries or resources

---

# 10. Grading Rubric

## Phase 1: Curiosity Report and Detailed Design — 30%

Excellent work demonstrates:

- A clearly supported user need
- Strong connection between features and user value
- Specific, testable requirements
- A protocol detailed enough for another team to implement
- Explicit consideration of TCP message framing
- A realistic plan for concurrency and shared state
- Thoughtful risks, assumptions, and scalability questions

---

## Phase 2: One Client and One Server — 30%

Excellent work:

- Operates reliably without arbitrary timing assumptions
- Correctly reconstructs protocol messages
- Provides useful functionality
- Handles invalid requests without crashing
- Separates networking, protocol, and application logic
- Includes clear setup instructions and repeatable tests

---

## Phase 3: Multiple Clients and One Server — 40%

Excellent work:

- Supports simultaneous clients predictably
- Protects shared data from races and corruption (Optional)
- Keeps serving active clients when another fails
- Demonstrates deliberate conflict-resolution behavior
- Provides evidence from concurrency and stress tests
- Clearly identifies scalability limits
- Connects technical decisions to user and stakeholder value

---

# 11. Entrepreneurial Mindset Closer

Networking software is not valuable simply because it transmits data correctly. Valuable systems anticipate user needs, remain reliable when conditions change, and evolve as demand grows.

As you complete this project, consider how every technical choice affects someone else. Protocol design affects future developers. Error handling affects user trust. Concurrency affects responsiveness. Synchronization affects correctness. Scalability decisions affect whether a useful prototype can grow into a sustainable service.

The final question is therefore not only:

> “Does the network application work?”

It is also:

> “For whom does it work, what value does it create, and what happens when more people depend on it?”