#ifndef _PPNET_H
#define _PPNET_H

#define MSGPACK_DEBUGLOG_ENABLE
#include <MsgPack.h>

namespace pplus
{
  namespace ppnet
  {
    struct CustomClassBase
    {
      int i;
      float f;
      MsgPack::str_t s;

      bool operator!=(const CustomClassBase &x) const
      {
        return (x.i != i) || (x.f != f) || (x.s != s);
      }

      MSGPACK_DEFINE(i, f, s);
    };
  }
}

#endif /* _PPNET_H */
