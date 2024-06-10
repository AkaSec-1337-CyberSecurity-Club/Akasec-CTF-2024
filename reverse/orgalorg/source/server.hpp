#ifndef SERVER_HPP
# define SERVER_HPP

# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/poll.h>
# include <sys/socket.h>
# include <sys/time.h>
# include <netinet/in.h>
# include <errno.h>
# include <iostream>
# include <unistd.h>
# include <cstring>
# include <iterator>
# include <map>
# include <fcntl.h>
# include <arpa/inet.h>
# include <fstream>
# include <sstream>
# include <ctime>
# include <sys/types.h>
# include <sys/stat.h>
# include <netdb.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <vector>
# include <cstdarg>
# include <csignal>
# include <sys/prctl.h>
# include "md5.hpp"


# define BUFF_SIZE		512
# define MAX_CONN		65535

// server time out after two days
# define TIMEOUT		2880* 60 * 1000

extern std::string g_name;
extern std::string g_port_env;
extern int g_port;
bool	isNumeric(std::string const &str);
std::string decrypt(const std::vector<uint32_t>& input);
bool    isBeingDebugged();

int main_server();

class Server
{
	private:
		int				socket_fd;
		struct pollfd	fds[MAX_CONN + 1];
		int				nfds;
		int				on;
		int				port;
		std::string		password;
		std::string		name;
		std::string		version;
		char 			*creationTime;
		std::string		pass;

		Server(void) {}

	public:

		Server(int port);
		~Server(void);

		std::string			getPass(void);
		void				setPass(std::string pass);
		int					getSocketFd(void) const;
		struct pollfd *		getFds(void);
		int					getNfds(void) const;
		void				setNfds(int nfds);
		int					getPort(void) const;

		void	clientDisconnect(int fd);
		std::string readAsciiArtFromFile(void);
		int checkCode(int fd,std::string  &msg);

		int		Create_socket(void);
		int		reusable_socket(void);
		int		nonblocking_socket(void);
		int		bind_socket(void);
		int		listen_from_socket(void);
		void	poll_trait(void);
		bool	accept_connections(void);
		bool	recv_send_msg(int fd);

		bool 	checkPassword(std::string &msg);

		bool 	checkSecretPass(std::string &pass);

		bool 	firstCheck(std::string &msg);
		bool 	secondCheck(std::string &msg);
		bool 	thirdCheck(std::string &msg);
		bool 	fouthCheck(std::string &msg);
		bool 	isPrime(int a);


		std::string sendAsciiArt();

		void	split(std::string const &s1,char delim,
		std::vector<std::string> &out);
		
};

#endif
