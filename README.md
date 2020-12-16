<h1>Throttling Server</h1>

<p>It will throttle the client requests based on the configuration specified in the conf file.
Basically, throttling will happen for each user for number of requests sent per sec. The throttling configuration is specified in the conf file which is loaded at the time of starting the server.
Server will keep listening for client requests and respond with allow/deny requests.
Client will keep sending requests to server at equal intervals.
</p>

<p>The conf file specifies that User1 can at most do 5 requests/sec to the server, User2 can do 10 requests/sec ...</p>
<h3>Contents of conf file:</h3>
<pre>
User1:5
User2:10
</pre>

<h3>Build server and client:</h3>
<pre>
$make
</pre>

<h3>Usage:</h3>
<pre>
./server port conf_file
./client serverName port userName
</pre>

<h3>Sample Output:</h3>
<pre>
#./client punnbuucsm5b04-vm4 5001 User1
Allow User1
Allow User1
Allow User1
Allow User1
Allow User1
Deny User1
Deny User1
Deny User1
Deny User1

</br>

#./client punnbuucsm5b04-vm4 5001 User2
Allow User2
Allow User2
Allow User2
Allow User2
Allow User2
Allow User2
Allow User2
Allow User2
Allow User2
Allow User2
Deny User2
Deny User2
Deny User2
Deny User2
Deny User2
</pre>
