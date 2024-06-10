#include "server.hpp"


void sigchld_handler(int signum) {
	(void) signum;
    while (waitpid(-1, NULL, WNOHANG) > 0);
}

bool	isNumeric(std::string const &str)
{
	std::string::const_iterator it = str.begin();
	while (it != str.end() && std::isdigit(*it))
		++it;
	return (!str.empty() && it == str.end());
}

void	close_server(Server & serv, int exit_status)
{
	close(serv.getSocketFd());
	serv.~Server();
	exit(exit_status);
}
  
int main_server()
{

	Server serv = Server(g_port);
    if (isBeingDebugged()) {
        exit(1);
    } 
	if (!serv.Create_socket())
		return (EXIT_FAILURE);
	
	if(!serv.reusable_socket()
		|| !serv.nonblocking_socket()
		|| !serv.bind_socket()
		|| !serv.listen_from_socket())
		close_server(serv, EXIT_FAILURE);

	serv.poll_trait();
	//p455
	serv.setPass(decrypt({0x600000c6, 0xe00000ce, 0xc00000ce, 0xc00000ce, }).c_str());

	signal(SIGCHLD, sigchld_handler);
	do
	{
		
		int	rc = poll(serv.getFds(), serv.getNfds(), TIMEOUT);
		if (rc < 0)
		{
			// close_server(serv, EXIT_FAILURE);
		}
		if (rc == 0)
		{
			close_server(serv, EXIT_FAILURE);
		}
		for (int i = 0; i < serv.getNfds(); i++)
		{
			if (serv.getFds()[i].revents == 0)
				continue;
			if (serv.getFds()[i].fd == serv.getSocketFd())
			{
				if (!serv.accept_connections())
					close_server(serv, EXIT_FAILURE);
			}
			else
			{
				if (!serv.recv_send_msg(serv.getFds()[i].fd))
				{
					serv.clientDisconnect(serv.getFds()[i].fd);
					for (int j = i; j < serv.getNfds(); j++)
					{
						memcpy(&serv.getFds()[j], &serv.getFds()[j + 1], sizeof(struct pollfd));
					}
					serv.setNfds(serv.getNfds() - 1);
					i --;
				}
			}
		}
	} while (true);
	
	return (EXIT_SUCCESS);
}
