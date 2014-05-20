Simple-Message-Store-And-Forward
================================

Simple 'message store and forward system' in a connection-oriented, iterative client/server configuration. The server should store a message of up to 120 characters for a client. The server should be a simple iterative one able to handle several clients but only one client at a time, passing a message from one client to the next. The message need only be stored while the server is running and need not be preserved between successive executions.  On startup, the client should connect to the server, read the message and write it to the screen. It should then prompt the user to enter a new message. It should read the message, send it to the server and exit. If the user does not wish to change the message he/she should be able to enter a C/R.  The server should read a new message from the client and store it for forwarding later to a new client when it connects. On the first execution, the server should send the message, 'no message stored' to the client.
