#ifndef CSOCKPP_LINUX_FLAG_HH__
#define CSOCKPP_LINUX_FLAG_HH__

#include <sys/socket.h>


namespace csockpp {
namespace linux_ {

class Flag {
public:
  enum class Sock {
#ifdef SOCK_NONBLOCK
    kNonblock = SOCK_NONBLOCK,
#endif
#ifdef SOCK_CLOEXEC
    kCloseOnExecute = SOCK_CLOEXEC,
#endif
  };

  enum class Msg {
#ifdef MSG_CONFIRM
    kConfirm = MSG_CONFIRM,
#endif
#ifdef MSG_DONTROUTE
    kDontRoute = MSG_DONTROUTE,
#endif
#ifdef MSG_DONTWAIT
    kDontWait = MSG_DONTWAIT,
#endif
#ifdef MSG_EOR
    kEor = MSG_EOR,
#endif
#ifdef MSG_MORE
    kMore = MSG_MORE,
#endif
#ifdef MSG_NOSIGNAL
    kNoSignal = MSG_NOSIGNAL,
#endif
#ifdef MSG_OOB
    kOob = MSG_OOB,
#endif
    
  };

};

}
}


#endif
