#ifndef HTTPS_SOCKET_H
#define HTTPS_SOCKET_H

#include <iostream>
#include <string>
#include "openssl/ssl.h"

std::string https_socket(std::string request_str,std::string host);
std::string https_body(std::string request_str,std::string host);

#endif
