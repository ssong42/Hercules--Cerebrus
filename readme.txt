#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h> /* struct hostent, gethostbyname */

** A web proxy is a program that reads a request 
** from a browser, forwards that request to a web
** server, reads the reply from the web server, and
** forwards the reply back to the browser. People
** typically use web proxies to cache pages for better
** performance, to modify web pages in transit
** (e.g. to remove annoying advertisements), or for weak anonymity.
*/

/* Usually HTTP a client communicated directly with a server
** but with a proxy. The Proxy opens a connection to the server
** , and passes on the client's requests. The proxy recieves the 
** reply from the server, and then sends that reply back to the
** client. 
** Notice that the proxy acts as a server to the client
** 	and as a client to the server.
*/

/*
** Why use a proxy? There are a few possible reasons:
**
** Performance: By saving a copy of the pages that it fetches, 
**	a proxy can reduce the need to create connections to remote 
**	servers. This can reduce the overall delay involved in 
**	retrieving a page, particularly if a server is remote or 
**	under heavy load.
** 
** Content Filtering and Transformation: While in the simplest 
**	case the proxy merely fetches a resource without inspecting it
**	, there is nothing that says that a proxy is limited to blindly
** 	fetching and serving files. The proxy can inspect the requested
**	URL and selectively block access to certain domains, reformat web
**	pages (for instances, by stripping out images to make a page 
**	easier to display on a handheld or other limited-resource client)
**	, or perform other transformations and filtering.
**
** Privacy: Normally, web servers log all incoming requests for resources.
**	This information typically includes at least the IP address of the client,
**	the browser or other client program that they are using 
**	(called the User-Agent), the date and time, and the requested file.
**	If a client does not wish to have this personally identifiable
**	information recorded, routing HTTP requests through a proxy is one
**	solution. All requests coming from clients using the same proxy
**	appear to come from the IP address and User-Agent of the proxy itself,
**	rather than the individual clients. If a number of clients use the
**	same proxy (say, an entire business or university), it becomes much
**	harder to link a particular HTTP transaction to a single computer or
**	individual.
*/
