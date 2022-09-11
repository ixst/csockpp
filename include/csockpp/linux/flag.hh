#ifndef CSOCKPP_LINUX_FLAG_HH__
#define CSOCKPP_LINUX_FLAG_HH__

#include <sys/socket.h>


namespace csockpp {
namespace linux_ {

enum class Flag {
#ifdef SOCK_NONBLOCK
  kNonblock = SOCK_NONBLOCK,
#endif
#ifdef SOCK_CLOEXEC
  kCloseOnExecute = SOCK_CLOEXEC,
#endif

};

}
}


#endif
